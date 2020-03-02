//
// Created by zxjcarrot on 2019-12-28.
//

#ifndef MULTI_TIER_BUF_MGR_SYNC_H
#define MULTI_TIER_BUF_MGR_SYNC_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <cassert>
#include <cstring>

namespace silkstore {
#define COMPILER_MEMORY_FENCE asm volatile("" ::: "memory")

class ThreadEpoch;

class EpochManager {
public:
    void AddEpoch(ThreadEpoch *te) {
        int i = idx.fetch_add(1);
        assert(i < max_num_threads);
        thread_epoches[i] = te;
    }

    void DeleteEpoch(ThreadEpoch *te) {
        assert(idx <= max_num_threads);
        restart:
        for (int i = 0; i < thread_epoches.size(); ++i) {
            if (thread_epoches[i] == te) {
                thread_epoches[i] = nullptr;
                break;
            }
        }
    }

    void IterateThreadEpoches(std::function<void(ThreadEpoch *)> processor) {
        assert(idx <= max_num_threads);
        size_t count = idx.load();
        for (int i = 0; i < count; ++i) {
            ThreadEpoch *te = thread_epoches[i];
            if (thread_epoches[i] != nullptr)
                processor(thread_epoches[i]);
        }
    }

    EpochManager(size_t max_num_threads) : thread_epoches(max_num_threads, nullptr), max_num_threads(max_num_threads),
                                           idx(0) {}

private:
    std::vector<ThreadEpoch *> thread_epoches;
    const size_t max_num_threads;
    std::atomic<int> idx;
};

class ThreadEpoch {
public:
    ThreadEpoch() : v(0), registered(false), manager(nullptr) {}

    uintptr_t SetValue(uintptr_t new_v) {
        v = new_v | Active();
        return new_v;
    }

    uintptr_t GetValue() { return v & (~1); }

    inline void Register(EpochManager *manager) {
        if (registered)
            return;
        this->manager = manager;
        manager->AddEpoch(this);
        registered = true;
    }

    ~ThreadEpoch() {
        if (manager) {
            manager->DeleteEpoch(this);
            manager = nullptr;
        }
    }

    void Enter() {
        v = v | 1;
    }

    void Leave() { v = 0; }

    bool Active() { return v & 1; }

private:
    uintptr_t v;
    bool registered;
    EpochManager *manager;
};

// RAII-style Enter and Leave
class EpochGuard {
public:
    EpochGuard(ThreadEpoch &epoch) : epoch(epoch) {
        epoch.Enter();
        asm volatile("mfence"::
        : "memory");
    }

    ~EpochGuard() { epoch.Leave(); }

private:
    ThreadEpoch &epoch;
};

static void WaitUntilNoRefs(EpochManager &manager, uintptr_t V) {
    while (true) {
        bool might_have_refs = false;
        manager.IterateThreadEpoches(
                [&might_have_refs,
                        V](ThreadEpoch *te) {
                    auto tev = te->GetValue();
                    if (te->Active() && (tev == 0 || te->GetValue() == V)) {
                        might_have_refs = true;
                    }
                });
        if (might_have_refs == false)
            break;
        std::this_thread::yield();
    }
}

static bool WaitUntilNoRefsNonBlocking(EpochManager &manager, uintptr_t V, int wait_times) {
    while (wait_times--) {
        bool might_have_refs = false;
        manager.IterateThreadEpoches(
                [&might_have_refs,
                        V](ThreadEpoch *te) {
                    auto tev = te->GetValue();
                    if (te->Active() && (tev == 0 || te->GetValue() == V)) {
                        might_have_refs = true;
                    }
                });
        if (might_have_refs == false) {
            return true;
        }

        std::this_thread::yield();
    }
    return false;
}

class ThreadPool {
public:
    ThreadPool(size_t);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
        :   stop(false)
{
    for(size_t i = 0;i<threads;++i)
        workers.emplace_back(
                [this]
                {
                    for(;;)
                    {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock,
                                                 [this]{ return this->stop || !this->tasks.empty(); });
                            if(this->stop && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }

                        task();
                    }
                }
        );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
-> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}

class CountDownLatch {
public:
    explicit CountDownLatch(const unsigned int count): count(count) { }
    virtual ~CountDownLatch() = default;

    void Await(void) {
        std::unique_lock<std::mutex> lock(mtx);
        if (count > 0) {
            cv.wait(lock, [this](){ return count == 0; });
        }
    }

    void CountDown(void) {
        std::unique_lock<std::mutex> lock(mtx);
        if (count > 0) {
            count--;
            cv.notify_all();
        }
    }

    unsigned int GetCount(void) {
        std::unique_lock<std::mutex> lock(mtx);
        return count;
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    unsigned int count = 0;
};

class DeferCode {
public:
    DeferCode(std::function<void()> code): code(code) {}
    ~DeferCode() { code(); }
private:
    std::function<void()> code;
};

#ifndef CACHE_LINE_SIZE
#define CACHE_LINE_SIZE  64 // 64 byte cache line on x86 and x86-64
#endif

#define INT64S_PER_CACHELINE (CACHE_LINE_SIZE / sizeof(int64_t))
#define INT64S_PER_CACHELINE_SCALE 4

template<int buckets>
class DistributedCounter {
public:
    static_assert(buckets == 0 || (buckets & (buckets - 1)) == 0, "buckets must be a multiple of 2");

    DistributedCounter(int initVal = 0) {
        countArrayPtr = malloc(buckets * INT64S_PER_CACHELINE * sizeof(int64_t) + CACHE_LINE_SIZE - 1);
        memset(countArrayPtr, 0, buckets * INT64S_PER_CACHELINE * sizeof(int64_t) + CACHE_LINE_SIZE - 1);
        countArray = (int64_t *)(((size_t)countArrayPtr + CACHE_LINE_SIZE - 1) & ~(CACHE_LINE_SIZE - 1));
        increment(initVal);
    }

    ~DistributedCounter() {
        free(countArrayPtr);
    }

    void operator +=( int by ) { increment(by); }
    void operator -=( int by ) { decrement(by); }
    void operator ++() { *this += 1; }
    void operator ++(int) { *this += 1; }
    void operator --() { *this -= 1; }
    void operator --(int) { *this -= 1; }

    int64_t load() const { return get(); }

    inline void increment(int v = 1) {
        __atomic_add_fetch(&countArray[arrayIndex() * INT64S_PER_CACHELINE], v, __ATOMIC_RELAXED);
        //countArray[arrayIndex() * INT64S_PER_CACHELINE] += v;
    }

    inline void decrement(int v = 1) {
        __atomic_sub_fetch(&countArray[arrayIndex() * INT64S_PER_CACHELINE], v, __ATOMIC_RELAXED);
        //countArray[arrayIndex() * INT64S_PER_CACHELINE] -= v;
    }

    int64_t get() const {
        int64_t val = 0;
        for (int i = 0; i < totalINT64S; i += INT64S_PER_CACHELINE) {
            val += __atomic_load_n(&countArray[i], __ATOMIC_RELAXED);
        }
        return val;
    }

private:
    static constexpr int totalINT64S = buckets * INT64S_PER_CACHELINE;
    inline uint64_t getCPUId() {
        if (cpuIdInitialized == false) {
            //cpuId = (uint64_t)std::hash<int>{}(Thread::getID());
            cpuId = (uint64_t)std::hash<std::thread::id>{}(std::this_thread::get_id());
            cpuIdInitialized = true;
            //printf("cpuid %lu, arrayIndex %d, pointer %p\n", cpuId, arrayIndex(), &countArray[arrayIndex() * INT64S_PER_CACHELINE]);
        }
        return cpuId;
    }

    inline int arrayIndex() {
        return getCPUId() & (buckets  - 1);
    }

    int64_t * countArray;
    void * countArrayPtr;

    static thread_local bool cpuIdInitialized;
    static thread_local uint64_t cpuId;
};

template<int buckets>
thread_local bool DistributedCounter<buckets>::cpuIdInitialized;

template<int buckets>
thread_local uint64_t DistributedCounter<buckets>::cpuId;

}
#endif //MULTI_TIER_BUF_MGR_SYNC_H
