#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T> class concurrent_queue {
private:
    mutable std::mutex mx;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:
    concurrent_queue(){
    }

    concurrent_queue(concurrent_queue const& other_queue){
        std::lock_guard<std::mutex> lk(other_queue.mx);
        data_queue = other_queue.data_queue;
    }

    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mx);
        data_queue.push(new_value);
        data_cond.notify_one();
    }

    std::shared_ptr<T> wait_and_pop(){
        std::unique_lock<std::mutex> lk(mx);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    std::shared_ptr<T> try_pop(){
        std::lock_guard<std::mutex> lk(mx);
        if(data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mx);
        return data_queue.empty();
    }
};

