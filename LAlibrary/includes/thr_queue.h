//
// Created by ivddorrka on 4/11/22.
//

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <deque>
#include <ostream>
#include <map>
#include <thread>


template<typename T>
class mt_que{
public:
    mt_que() = default;
    ~mt_que() = default;
    mt_que(const mt_que&) = delete;
    mt_que& operator=(const mt_que&) = delete;

    void enque(const T& a){

        {
            std::unique_lock<std::mutex> lock(m_m);

            while (que_m.size() > maxsize ) {

                cv_m1.wait(lock);

            }

            que_m.push_back(a);
        }
        cv_m.notify_one();
    }

    T deque(){
        T a;
        {
            std::unique_lock<std::mutex> lock(m_m);
            while (que_m.empty() ) {
                cv_m.wait(lock);
            }
            a = que_m.front();
            que_m.pop_front();
        }
        cv_m1.notify_one();

        return a;
    }

    void set_maxsize(int mxsize) {
        std::unique_lock<std::mutex> lock(m_m);
        maxsize = mxsize;
    }

    size_t get_size() const {
        std::lock_guard<std::mutex> lock(m_m);
        return que_m.size();
    }

private:
    std::deque<T> que_m;
    mutable std::mutex m_m;
    std::condition_variable cv_m;
    std::condition_variable cv_m1;
    int maxsize{};
};






#endif //QUEUE_H
