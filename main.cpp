#include <iostream>
#include "memory/xmem.h"
#include <vector>




int main() {

   // int id = 0x1840;
    int id = 2843;

    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "begin " << std::endl;

    searchMemory(id, "0A 00 00 00 0A 00 00 00 0A 00 00 00");

    std::cout << "end " << std::endl;

    // 获取函数运行后的时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算运行时间（以微秒为单位）
    std::chrono::duration<double,std::milli> duration = end - start;

    std::cout << "Function execution time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
