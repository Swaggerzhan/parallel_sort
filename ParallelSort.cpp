//
// Created by swagger on 2021/5/20.
//

#include "ParallelSort.h"


ParallelSort::ParallelSort(int size, int thread)
        :   size_(size),
            threadNum_(thread),
            kMicroPerSecond(1000*1000),
            pool_(new ThreadPool) // 初始化线程池
{
    data_.reserve(size_); // 提前开辟空间
    pool_->start(threadNum_); // 启动线程池
}

ParallelSort::~ParallelSort(){}

void ParallelSort::getInput(){
    timeval start{};
    gettimeofday(&start, nullptr);
    int tmp;
    for (int i=0; i<size_; i++){
        cin >> tmp;
        data_.push_back(tmp);
    }
    timeval end{};
    gettimeofday(&end, nullptr);
    cal_time("init vector", start, end);
}


void ParallelSort::sectionSort(Pack *pack){
    if (pack->isSort_)
        return;
    std::sort(pack->begin_, pack->end_);
    pack->isSort_ = true;
}


void ParallelSort::cal_time(const string& name, timeval left, timeval right){
    int64_t leftMicro = left.tv_sec * kMicroPerSecond
                        + left.tv_usec;
    int64_t rightMicro = right.tv_sec * kMicroPerSecond
                         + right.tv_usec;
    int64_t diffMicro;
    if (rightMicro > leftMicro){
        diffMicro = rightMicro - leftMicro;
    }else{
        diffMicro = leftMicro - rightMicro;
    }
    cout << name << " used: " << diffMicro / kMicroPerSecond;
    cout << " s and " << diffMicro % kMicroPerSecond << " us" << endl;

}


void ParallelSort::signJob(){
    int section = size_ / 10; // 先写死
    It begin = data_.begin();
    for (int idx=0; idx<threadNum_; ++idx){
        It end = begin + section;
        end ++; // 指向下一个迭代器
        Pack* pack = new Pack(begin, end);
        secData_.push_back(pack);
        pool_->put(
                std::bind(&ParallelSort::sectionSort, this, pack)
                );
        begin = end; // 下一组任务
    }
}
