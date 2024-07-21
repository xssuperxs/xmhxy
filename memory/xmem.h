//
// Created by Administrator on 2024/7/12.
//

#ifndef XMHXY_XMEM_H
#define XMHXY_XMEM_H

#include <vector>
#include <cstdint>
#include <string>
#include <thread>
#include <future>


// ==================================================  android =====================================================
#ifdef __ANDROID_API__


#include <unistd.h>
#include <sys/uio.h>
#include <sys/syscall.h>


#define PAGE_NOACCESS 0x01
#define PAGE_READONLY 0x02
#define PAGE_READWRITE 0x04
#define PAGE_WRITECOPY 0x08
#define PAGE_EXECUTE 0x10
#define PAGE_EXECUTE_READ 0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80

typedef int HANDLE;

bool parseMemInfo(std::string &line, uintptr_t &startAddress, uintptr_t &stopAddress, std::string &protectionString);

uint32_t ProtectionStringToProtection(const std::string &protectionString);

bool ReadProcessMemory(HANDLE hProcess, const void *lpBaseAddress, void *lpBuffer, size_t nSize, size_t *lpNumberOfBytesRead);

bool WriteProcessMemory(HANDLE hProcess, void *lpBaseAddress, const void *lpBuffer, size_t nSize, size_t *lpNumberOfBytesWritten);

// ==================================================  windows =====================================================
#else

#include <windows.h>

#endif


// ==================================================  struct =====================================================
typedef struct {
    uintptr_t BaseAddress;
    uint64_t MemorySize;
    bool IsChild;       // Indicates if there is a region before it
    uintptr_t startAddress; // Pointer to the start of this region in the whole memory copy
    uintptr_t stopAddress;
} MEMORY_REGION;




//  ================================================   const  ====================================================
#define BEGIN_ADDRESS 0
#define END_ADDRESS 0x00007fffffffffff
#define PAGE_PROTECTION PAGE_READWRITE

//  ================================================   public  ====================================================

std::vector<uintptr_t> searchMemory(int pid, const char *pattern, int inc = 0, int protection = PAGE_PROTECTION, uint64_t start = BEGIN_ADDRESS, uint64_t end = END_ADDRESS);

std::vector<MEMORY_REGION> collectMemInfo(int pid, int protection = PAGE_PROTECTION, uint64_t start = BEGIN_ADDRESS, uint64_t end = END_ADDRESS);

// 转换文本到 byte数组  "0A 00 00 00 0A 00 00 00" 转换成数组
std::vector<int> convertStringToBytes(const std::string &scanValue, char delimiter = ' ', bool hex = true);

std::vector<uintptr_t> thread_ScanMem(HANDLE hProcess, const std::vector<MEMORY_REGION> &memRegions, size_t maxMemRegionSize, int startRegion, int stopRegion, const int *pArrayToFind, int nArrayToFindLength);

unsigned long getCPUCount();

bool arrayOfByteExact(const char * buffer, const int * pArrayToFind,size_t nArrayLength);



//DWORD AOBScan(HANDLE hProcess, const char *pattern, const char *mask, uint64_t start, uint64_t end, int inc, int protection, uint64_t *match_addr)


#endif //XMHXY_XMEM_H
