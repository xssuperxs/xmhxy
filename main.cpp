#include <iostream>
#include "memory/xmem.h"



#include <sys/mman.h>

int main() {


    int id = 2826;
////
//    std::vector<uintptr_t> vec_uintptr;
//
//    char * buffer = nullptr;
//
//    int result = posix_memalign(reinterpret_cast<void **>(&buffer), 4096, 4096 + 4096);
////    char *buff = static_cast<char *>(malloc(4096+16));
////    char *buff = static_cast<char *>(malloc(4096+16));
//
//    bool isSuccess = ReadProcessMemory(id, reinterpret_cast<const void *>(0x12c00000), buffer, 4096, nullptr);
//
////    free(buff);
////    buff = static_cast<char *>(malloc(4096+16));
////    char *buff1  = static_cast<char *>(malloc(4096+16));
//
//
////    vec_uintptr.size();
//    vec_uintptr.push_back(666);
//    vec_uintptr.clear();
//
//
//    // 重要！！！！！！重新分配 内存
//    buffer = static_cast<char *>(realloc(buffer, 4096 + 16));
//
////    char *buff1 = static_cast<char *>(malloc(4096+16));
////    char *buff1  = static_cast<char *>(malloc(4096+16));
//    isSuccess = ReadProcessMemory(id, reinterpret_cast<const void *>(0x40000000), buffer, 4096, nullptr);
////    free(buff1);
//
//    std::cout << "end" << std::endl;


    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "begin " << std::endl;

    searchMemory(id, "0A 00 00 00 0A 00 00 00");

    std::cout << "end " << std::endl;

    // 获取函数运行后的时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算运行时间（以微秒为单位）
    std::chrono::duration<double, std::micro> duration = end - start;

    std::cout << "Function execution time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
