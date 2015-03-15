#include<iostream>
#include<thread>
#include<sstream>
#include"concurrent_queue.h"

const int NUMBER_COUNT = 100;

void producer(concurrent_queue<int>& cq){
    for (int i = 0; i < NUMBER_COUNT; i++){
        std::stringstream ss;
        ss << "[" << std::this_thread::get_id() << "] Putting value " 
            << i << std::endl;
        std::cout << ss.str();
        cq.push(i);
    }
} 

void consumer(concurrent_queue<int>& cq, int n){
    for (int i = 0; i < n; i++){
        auto number = cq.wait_and_pop();
        std::stringstream ss;
        ss << "[" << std::this_thread::get_id() << "] Extracting  value "
           <<  *number << std::endl;
        std::cout << ss.str();
    }
}

int main(){
    concurrent_queue<int> cq;
    std::thread p(producer, std::ref(cq));
    std::thread c1(consumer, std::ref(cq), NUMBER_COUNT / 2);
    std::thread c2(consumer, std::ref(cq), NUMBER_COUNT / 2);
    p.join();
    c1.join();
    c2.join();
}
