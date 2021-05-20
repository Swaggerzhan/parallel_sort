//
// Created by swagger on 2021/5/20.
//

#ifndef THREAD_PARALLELSORT_H
#define THREAD_PARALLELSORT_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <memory>
#include "ThreadPool.h"


using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::string;


class ParallelSort{
public:

    typedef vector<int>::iterator It;


    struct Pack{
        It begin_;
        It end_;
        bool isSort_;
        Pack(It begin, It end)
        :   begin_(begin),
            end_(end),
            isSort_(false)
        {}
    };

    ParallelSort(int size, int thread);

    ~ParallelSort();
    /* 获取输入 */
    void getInput();
    /* 子线程任务 */
    void sectionSort(Pack *pack);
    /* 分配任务 */
    void signJob();

    void merge();


private:

    void cal_time(const string& name, timeval left, timeval right);



private:

    int threadNum_;

    int kMicroPerSecond;
    std::unique_ptr<ThreadPool> pool_; // 线程池指针

    int size_; // 预判大小
    vector<int> data_;

    vector<Pack*> secData_; // 区分完后的包

};


#endif //THREAD_PARALLELSORT_H
