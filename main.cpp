#include <iostream>
#include "memory/xmem.h"
#include <vector>

using namespace std ;


//// Sunday算法查找函数，支持通配符'?'的匹配
//vector<int> sundaySearch(const unsigned char* text, int text_len,
//                         const unsigned char* pattern, int pattern_len) {
//    vector<int> matches;
//    int shift[256]; // 记录字符右移位数，默认为模式长度+1
//
//    // 初始化shift表
//    for (int i = 0; i < 256; ++i) {
//        shift[i] = pattern_len + 1;
//    }
//
//    // 设置pattern中每个字符的右移位数
//    for (int i = 0; i < pattern_len; ++i) {
//        shift[pattern[i]] = pattern_len - i;
//    }
//
//    int i = 0;
//    while (i <= text_len - pattern_len) {
//        int j = 0;
//        while (j < pattern_len && (pattern[j] == '?' || pattern[j] == text[i + j])) {
//            ++j;
//        }
//
//        if (j == pattern_len) {
//            matches.push_back(i);
//        }
//
//        if (i + pattern_len >= text_len) {
//            break;
//        }
//
//        i += shift[text[i + pattern_len]];
//    }
//    return matches;
//}


int main() {

    int id = 2835;

//
//    const unsigned char memory[] = { 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,0xAA, 0xBB, 0xCC};
//    const unsigned char pattern[] = { 0xAA, 0xBB, '?', 0xDD };
//
//    int memory_len = sizeof(memory) / sizeof(memory[0]);
//    int pattern_len = sizeof(pattern) / sizeof(pattern[0]);
//
//    vector<int> matches = sundaySearch(memory, memory_len, pattern, pattern_len);
//
//    if (!matches.empty()) {
//        cout << "Pattern found at positions:";
//        for (int matche : matches) {
//            cout << " " << matche;
//        }
//        cout << endl;
//    } else {
//        cout << "Pattern not found." << endl;
//    }
//
//    return 0;


    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "begin " << std::endl;

    searchMemory(id, "0A 00 00 00 0A 00 00 00");

    std::cout << "end " << std::endl;

    // 获取函数运行后的时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算运行时间（以微秒为单位）
    std::chrono::duration<double,std::milli> duration = end - start;

    std::cout << "Function execution time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
