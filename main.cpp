#include <iostream>
#include "memory/xmem.h"
#include <vector>

using namespace std ;

#define WORD unsigned short


using namespace std;
//

//
///*
//* P 为模式串，下标从 0 开始。
//* nextval 数组是模式串 SubString 中每个字符失配时应该回溯的位置。
//*/
//void GetNextval(string SubString, int nextval[])
//{
//    int SubStringLen = SubString.size(); // 计算模式串的长度
//    int i = 0;                           // 子串的指针
//    int j = -1;                          // 前缀的指针
//    nextval[0] = -1;                     // 初始化 nextval 数组，将第一个值设为 -1
//
//    while (i < SubStringLen - 1)
//    {
//        if (j == -1 || SubString[i] == SubString[j]) // 如果子串和前缀相等，或 j==-1
//        {
//            i++; j++;                                // 子串指针和前缀指针分别加一
//            if (SubString[i] != SubString[j])        // 如果下一个字符不相等
//            {
//                nextval[i] = j;                      // 将前缀指针 j 的值赋给 nextval 数组中的当前位置 i
//            }
//            else                                     // 如果下一个字符相等
//            {
//                nextval[i] = nextval[j];             // 已经有 nextval[j]，所以将它赋给 nextval[i]
//            }
//        }
//        else                                        // 如果子串和前缀不相等
//        {
//            j = nextval[j];                        // 更新前缀指针 j 的值，指向 nextval[j]
//        }
//    }
//}
//
///* 在 MainString 中找到 SubString 第一次出现的位置 下标从0开始*/
//int KMPSearchString(string MainString, string SubString, int next[])
//{
//    GetNextval(SubString, next);
//
//    int MainStringIndex = 0;                 // 存储主字符串下标
//    int SubStringIndex = 0;                  // 存储子字符串下标
//    int MainStringLen = MainString.size();   // 主字符串大小
//    int SubStringLen = SubString.size();     // 子字符串大小
//
//    // 循环遍历字符串,因为末尾 '\0' 的存在，所以不会越界
//    while (MainStringIndex < MainStringLen && SubStringIndex < SubStringLen)
//    {
//        // MainString 的第一个字符不匹配或 MainString[] == SubString[]
//        if (SubStringIndex == -1 || MainString[MainStringIndex] == SubString[SubStringIndex])
//        {
//            MainStringIndex++; SubStringIndex++;
//        }
//        else   // 当字符串匹配失败则跳转
//        {
//            SubStringIndex = next[SubStringIndex];
//        }
//    }
//    // 最后匹配成功直接返回位置
//    if (SubStringIndex == SubStringLen)
//    {
//        return MainStringIndex - SubStringIndex;
//    }
//    return -1;
//}
//
//// 内存特征码搜索
//ULONG ScanMemorySignatureCode(DWORD Pid, DWORD beginAddr, DWORD endAddr, char *ShellCode, DWORD ShellCodeLen)
//{
//    char *read = new char[ShellCodeLen];
//
//    // 打开进程
//    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, Pid);
//    int next[100] = { 0 };
//
//    // 开始搜索内存特征
//    for (int x = 0; x < endAddr; x++)
//    {
//        DWORD addr = beginAddr + x;
//
//        // 每次读入ShellCodeLen字节特征
//        ReadProcessMemory(process, (LPVOID)addr, read, ShellCodeLen, 0);
//
//        // 在Str字符串中找Search子串,找到后返回位置
//        int ret = KMPSearchString(read, ShellCode, next);
//
//        if (ret != -1)
//        {
//            return addr;
//        }
//    }
//    return 0;
//}
//
//int main(int argc, char *argv[])
//{
//    // 通过进程名获取进程PID号
//    DWORD Pid = GetPidByName("PlantsVsZombies.exe");
//    printf("[*] 获取进程PID = %d \n", Pid);
//
//    // 开始搜索特征码
//    char ScanOpCode[3] = { 0x56, 0x57, 0x33 };
//
//    // 依次传入开始地址，结束地址，特征码，以及特征码长度
//    ULONG Address = ScanMemorySignatureCode(Pid, 0x401000, 0x7FFFFFFF, ScanOpCode, 3);
//
//    printf("[*] 找到内存地址 = 0x%x \n", Address);
//
//    system("pause");
//    return 0;
//}


int main() {

    int id = 3038;

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

    searchMemory(id, "0A 00 00 00 0A 00 00 00 0A 00 00 00 0A 00 00 00 0A 00 00 00 0A 00 00 00");

    std::cout << "end " << std::endl;

    // 获取函数运行后的时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算运行时间（以微秒为单位）
    std::chrono::duration<double,std::milli> duration = end - start;

    std::cout << "Function execution time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
