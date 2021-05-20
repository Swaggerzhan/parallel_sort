#include <iostream>
#include "ThreadPool.h"
#include <algorithm>
#include <vector>
#include <ctime>
#include <unistd.h>



void MySort(std::vector<int> target){
    std::cout << "start sort..." << std::endl;
    std::sort(target.begin(), target.end());
    std::cout << "end..." << std::endl;


}



int main(){

    srand(time(nullptr));
    ThreadPool pool;
    pool.start(2);
    std::vector<int> target;
    int n = 10000;
    target.reserve(n);
    std::cout << "put task" << std::endl;
    for (int loop=0; loop<10; loop++){
        for (int i=0; i<n; i++)
            target.push_back(rand());
        pool.put(std::move(std::bind(MySort, target)));

    }
    std::cout << "task finish" << std::endl;
    sleep(10);
    pool.stop();
    sleep(2);
    std::cout << "main exit..." << std::endl;


}