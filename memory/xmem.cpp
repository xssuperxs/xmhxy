
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "xmem.h"


// ================================================================ 公用函数 ============================================================================
// 内存搜索
std::vector<uintptr_t> searchMemory(int pid, const char *pattern, int offset, const char *szProtection, uint64_t start, uint64_t end) {

    std::vector<std::thread> scanThreads;
    std::vector<uintptr_t> foundAddress;
    size_t _startAddress;
    size_t _stopAddress = 0;
//    size_t pageSize = 0;
    std::vector<MEMORY_REGION> thread_memRegions;
    size_t DEFAULT_BLOCK_SIZE = 128 * 1024 * 1024; // 默认块在大小
    size_t currentBlockSize = 0;
    size_t currentMemRegionSize;
    size_t previousLeftMemSize = 0;
//    unsigned long threadCount = getCPUCount();      // 获取可用的CPU线程
    unsigned long memRegionsCount;
    MEMORY_REGION tmpMemoryRegion;
    MEMORY_REGION leftMemoryRegion = {0};

    size_t subBlockCount;

#ifdef __ANDROID_API__
    HANDLE hProcess = pid;
//    pageSize = PAGE_SIZE;
#else
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    SYSTEM_INFO si;
    GetSystemInfo(&si);
//    pageSize = si.dwPageSize;
#endif

    // 获取要找的字节数组 长度 和指针
    std::vector<int> abs_arrayToFind = convertStringToBytes(pattern);
    const int *pArrayToFind = abs_arrayToFind.data();
    unsigned long arrayToFindLength = abs_arrayToFind.size();
    if (arrayToFindLength < 1)
        return {};

    // 收集内存
    std::vector<MEMORY_REGION> memRegions = collectMemInfo(pid, szProtection, start, end);
    if (memRegions.empty())
        return {};

    memRegionsCount = memRegions.size();

    // 所有的线程
    std::vector<std::future<std::vector<uintptr_t>>> futures;

    // 从这里开始分配多个块  起动线程
    for (int i = 0; i < memRegionsCount; i++) {

        currentMemRegionSize = memRegions[i].MemorySize;
        currentBlockSize += currentMemRegionSize;
        _startAddress = memRegions[i].BaseAddress;

        // 如果有多余的一块
        if (leftMemoryRegion.MemorySize > 0) {
            currentBlockSize += leftMemoryRegion.MemorySize;
            previousLeftMemSize = leftMemoryRegion.MemorySize;
            thread_memRegions.push_back(leftMemoryRegion);
            leftMemoryRegion.MemorySize = 0;
        }

        // 小于默认块
        if (currentBlockSize < DEFAULT_BLOCK_SIZE) {
            tmpMemoryRegion.MemorySize = memRegions[i].MemorySize;
            tmpMemoryRegion.startAddress = memRegions[i].BaseAddress;
            tmpMemoryRegion.stopAddress = memRegions[i].stopAddress;
            thread_memRegions.push_back(tmpMemoryRegion);

            if (i == memRegionsCount - 1) {
                // 这里起动最后一个线程
                futures.push_back(std::async(std::launch::async, thread_ScanMem, hProcess, thread_memRegions, DEFAULT_BLOCK_SIZE, pArrayToFind, arrayToFindLength,offset));
                thread_memRegions.clear();
            }

        } else {     // 大于默认块

            // 大于默认块大小
            leftMemoryRegion.MemorySize = currentBlockSize % DEFAULT_BLOCK_SIZE;
            if (leftMemoryRegion.MemorySize > 0) {
                leftMemoryRegion.stopAddress = memRegions[i].stopAddress;
                leftMemoryRegion.startAddress = memRegions[i].stopAddress - leftMemoryRegion.MemorySize;
            }
            subBlockCount = currentBlockSize / DEFAULT_BLOCK_SIZE;

            for (int j = 0; j < subBlockCount; ++j) {
                if (previousLeftMemSize > 0) {
                    _stopAddress = _startAddress + (DEFAULT_BLOCK_SIZE - previousLeftMemSize);
                    tmpMemoryRegion.MemorySize = _stopAddress - _startAddress;
                    previousLeftMemSize = 0;
                } else {
                    if (currentMemRegionSize - leftMemoryRegion.MemorySize >= 0) {
                        _stopAddress = _startAddress + DEFAULT_BLOCK_SIZE;
                        tmpMemoryRegion.MemorySize = DEFAULT_BLOCK_SIZE;
                    } else {
                        _stopAddress = _startAddress + (_stopAddress - leftMemoryRegion.MemorySize);
                        tmpMemoryRegion.MemorySize = _stopAddress - leftMemoryRegion.MemorySize - _startAddress;
                    }
                }
                tmpMemoryRegion.startAddress = _startAddress;
                tmpMemoryRegion.stopAddress = _stopAddress;
                thread_memRegions.push_back(tmpMemoryRegion);

                // 在这里起动线程
                futures.push_back(std::async(std::launch::async, thread_ScanMem, hProcess, thread_memRegions, DEFAULT_BLOCK_SIZE, pArrayToFind, arrayToFindLength,offset));
                thread_memRegions.clear();
                _startAddress = _stopAddress;
            }
            previousLeftMemSize = leftMemoryRegion.MemorySize;
            currentBlockSize = 0;
        }
    }
    // 等待所有的异步任务完成
    for (auto &fut: futures) {
        fut.wait();
    }
    for (auto &fut: futures) {
        auto result = fut.get();
        foundAddress.insert(foundAddress.end(), result.begin(), result.end());
    }

    for (auto addr: foundAddress) {
        std::cout << std::hex << addr << std::endl;
    }
    std::cout << foundAddress.size() << std::endl;
    return foundAddress;
}


std::vector<uintptr_t> thread_ScanMem(HANDLE hProcess, const std::vector<MEMORY_REGION> &memRegions, size_t maxMemRegionSize, const int *pArrayToFind, int nArrayToFindLength, int offset) {

    // 实际读取的长度
    size_t actualRead = 0;
    size_t bufferSize = maxMemRegionSize + 16 + nArrayToFindLength;
    bool isReadSuccess;
    std::vector<uintptr_t> foundAddresses;

    char* pOriginalBuf;

    // 要分配最大的一个内存
    char *buffer = static_cast<char *>(malloc(bufferSize));
    const char *p;
    if (!buffer)
        return foundAddresses;

    pOriginalBuf = buffer;
    for (auto memRegion: memRegions) {

        buffer = static_cast<char *>(realloc(buffer, bufferSize));
        if(buffer == nullptr) {
            free(pOriginalBuf);
            break;
        }
        // 读入内存到BUFF中
        isReadSuccess = ReadProcessMemory(hProcess, (void *) memRegion.startAddress, buffer, memRegion.MemorySize, &actualRead);

        if (!isReadSuccess)
            continue;

        p = buffer;
        // 从第一个字节 开始搜索
        for (int j = 0; j < actualRead; ++j) {
            if (arrayOfByteExact(p, pArrayToFind, nArrayToFindLength)) {
                foundAddresses.push_back(memRegion.startAddress + j + offset);
            }
            p++;
        }
    }

    if(buffer)
        free(buffer);
    return foundAddresses;

}

std::vector<MEMORY_REGION> collectMemInfo(int pid, const char *szProtect, uint64_t start, uint64_t end) {

    std::vector<MEMORY_REGION> memRegions;
    MEMORY_REGION region;

    std::string protect = szProtect;
    uint32_t nProtect = 0;

    if (protect.find('x') != -1) {
        nProtect |= PAGE_EXECUTE;
        nProtect |= PAGE_EXECUTE_READ;
        nProtect |= PAGE_EXECUTE_READWRITE;
        nProtect |= PAGE_EXECUTE_WRITECOPY;
    }
    if (protect.find('w') != -1)
        nProtect |= PAGE_READWRITE;

    if (protect.find('c') != -1) {
        nProtect |= PAGE_WRITECOPY;
        nProtect |= PAGE_EXECUTE_WRITECOPY;
    }

#ifdef __WIN32
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    uintptr_t currentBaseAddress;
    MEMORY_BASIC_INFORMATION mbi;
    bool validRegion;

    if (start % 8 > 0)
        start -= start % 8;
    currentBaseAddress = start;

    // mem_information
    memset(&mbi, 0, sizeof(mbi));

    if (!hProcess)
        return {};

    // 查询内存区域
    while (VirtualQueryEx(hProcess, reinterpret_cast<void *>(currentBaseAddress), &mbi, sizeof(mbi)) != 0
           && currentBaseAddress < end
           && (currentBaseAddress + mbi.RegionSize) > currentBaseAddress) {

        if ((uintptr_t) mbi.BaseAddress < start) {
            mbi.RegionSize -= start - reinterpret_cast<uintptr_t>(mbi.BaseAddress);
            mbi.BaseAddress = reinterpret_cast<void *>(start);
        }

        if (reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize >= end) {
            mbi.RegionSize = end - reinterpret_cast<uintptr_t>(mbi.BaseAddress);
        }


        // 判断是不是有效内存
        validRegion = (mbi.State == MEM_COMMIT);
        validRegion = validRegion && (reinterpret_cast<uintptr_t>(mbi.BaseAddress) < reinterpret_cast<uintptr_t>(end));
        validRegion = validRegion && ((mbi.Protect & PAGE_GUARD) == 0);
        validRegion = validRegion && ((mbi.Protect & PAGE_NOACCESS) == 0);

        validRegion = validRegion && mbi.Type != MEM_MAPPED;
        validRegion = validRegion && (mbi.Protect & PAGE_WRITECOMBINE) <= 0;


        validRegion = validRegion && ((nProtect & mbi.Protect) > 0);



//        if (protection == PAGE_READWRITE) {
//            isWrite_execute_copy = ((mbi.Protect & PAGE_READWRITE) > 0) ||
//                                   ((mbi.Protect & PAGE_WRITECOPY) > 0) ||
//                                   ((mbi.Protect & PAGE_EXECUTE_READWRITE) > 0) ||
//                                   ((mbi.Protect & PAGE_EXECUTE_WRITECOPY) > 0);
//
//
//        } else if (protection == PAGE_EXECUTE) {
//
//            isWrite_execute_copy = ((mbi.Protect & PAGE_EXECUTE) > 0) ||
//                                   ((mbi.Protect & PAGE_EXECUTE_READ) > 0) ||
//                                   ((mbi.Protect & PAGE_EXECUTE_READWRITE) > 0) ||
//                                   ((mbi.Protect & PAGE_EXECUTE_WRITECOPY) > 0);
//
//        } else {
//            isWrite_execute_copy = ((mbi.Protect & PAGE_WRITECOPY) > 0) ||
//                                   ((mbi.Protect & PAGE_EXECUTE_WRITECOPY) > 0);
//
//        }
//       validRegion = validRegion && isWrite_execute_copy;

        // 不是需要的内存 接着循环
        if (!validRegion) {
            currentBaseAddress += mbi.RegionSize;
            continue;
        }

        // 如果仍然有效，则将该区域添加到内存区域列表中
        region.BaseAddress = reinterpret_cast<uintptr_t>(mbi.BaseAddress);
        region.MemorySize = mbi.RegionSize;
        region.stopAddress = region.BaseAddress + mbi.RegionSize;
        memRegions.push_back(region);
        currentBaseAddress += mbi.RegionSize;
    }


#else    // ============== androoid ==================
    HANDLE hProcess = pid;
    std::string mapsPath = "/proc/";
    mapsPath += std::to_string(hProcess);
    mapsPath += "/maps";

    uintptr_t _startAddress = 0;
    uintptr_t _stopAddress = 0;
    std::string protectionString;
    std::string line;

    std::ifstream maps(mapsPath); // 打开文件

    uint32_t memProtection;


    if (!maps)
        return {};

    while (std::getline(maps, line)) { // 逐行读取文件内容

        // 分割文本 得到自己需要的数据
        parseMemInfo(line, _startAddress, _stopAddress, protectionString);

        memProtection = ProtectionStringToProtection(protectionString);

        if (protectionString.find('s') != -1)
            continue;

        if ((nProtect & memProtection) != 0) {
            region.BaseAddress = _startAddress;
            region.MemorySize = _stopAddress - _startAddress;
            region.stopAddress = _stopAddress;
            memRegions.push_back(region);
        }
    }
    maps.close();
#endif
    return memRegions;
}

std::vector<int> convertStringToBytes(const std::string &scanValue, char delimiter, bool hex) {

    // Lambda函数用于修剪字符串两端的空白字符
    auto trim = [](std::string &s) {
        // 从字符串开始处找到第一个非空白字符的位置
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));

        // 从字符串末尾找到第一个非空白字符的位置，并从此处截断字符串
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    };

    // 定义 Lambda 函数
    auto split = [](const std::string &text, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream tokenStream(text);
        std::string token;

        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    };

    std::vector<int> bytes;
    if (scanValue.empty())
        return bytes;

    std::string scanStr = scanValue;
    trim(scanStr);

    // split
    std::vector<std::string> words = split(scanStr, delimiter);

    for (const auto &helpStr: words) {
        if (helpStr.empty())
            continue;
        try {
            if (hex) {
                bytes.push_back(std::stoi(helpStr, nullptr, 16));
            } else {
                bytes.push_back(std::stoi(helpStr));
            }
        } catch (...) {
            bytes.push_back(-1); // wildcard
        }
    }
    return bytes;
}

//unsigned long getCPUCount() {
//    unsigned long cpuCount = 0; // 静态变量，用于存储 CPU 核心数量
//#ifdef _WIN32
//
//    // Lambda函数，计算一个无符号整数中置位为1的位的个数
//    auto getBitCount = [](uintptr_t value) {
//        int result = 0;
//        while (value > 0) {
//            if (value % 2 == 1) { // 判断当前位是否为1
//                result++; // 如果是1，则增加置位的个数
//            }
//            value >>= 1; // 右移一位，相当于除以2
//        }
//        return static_cast<unsigned long>(result); // 返回置位为1的个数，转换为unsigned long类型
//    };
//
//    DWORD_PTR PA, SA;
//    // 获取当前进程的 CPU 亲和性掩码，只使用进程掩码
//    GetProcessAffinityMask(GetCurrentProcess(), &PA, &SA);
//    cpuCount = getBitCount(PA); // 计算 PA 中置位的位数，即 CPU 核心数量
//    if (cpuCount == 0) cpuCount = 1; // 如果获取失败，默认设置为 1
//#else
//    cpuCount = std::thread::hardware_concurrency(); // 获取系统中可用的 CPU 核心数量
//#endif
//    return cpuCount;
//}

bool arrayOfByteExact(const char *buffer, const int *pArrayToFind, size_t nArrayLength) {
    for (int i = 0; i < nArrayLength; ++i) {
        if ((pArrayToFind[i]) != -1 && (int) (buffer[i]) != pArrayToFind[i]) {
            return false; // no match
        }
    }
    return true; // still here, so a match
}

// =================================================================  android 用的函数
#ifdef __ANDROID_API__

bool parseMemInfo(std::string &line, uintptr_t &startAddress, uintptr_t &stopAddress, std::string &protectionString) {

    auto split = [](const std::string &str, char delimiter) -> std::vector<std::string> {
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(str);

        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    };

    try {
        // get result
        std::vector<std::string> result = split(line, ' ');
        // split  address
        std::vector<std::string> memAddr = split(result[0], '-');
        // translator result
        startAddress = std::stoull(memAddr[0], nullptr, 16);
        stopAddress = std::stoull(memAddr[1], nullptr, 16);
        protectionString = result[1];
    }
    catch (...) {
        return false;
    }
    return true;
}

bool ReadProcessMemory(HANDLE hProcess, const void *lpBaseAddress, void *lpBuffer, size_t nSize, size_t *lpNumberOfBytesRead) {

    struct iovec local{nullptr, 0};
    struct iovec remote{nullptr, 0};

    // 初始化Buffer
    local.iov_base = lpBuffer;
    local.iov_len = nSize;

    remote.iov_base = (void *) lpBaseAddress;
    remote.iov_len = nSize;

    //
    long ret = syscall(__NR_process_vm_readv, hProcess, &local, 1, &remote, 1, 0);

    if (ret == -1) {
        std::cout << "SYS_process_vm_read error! = " << strerror(errno) << std::hex << lpBaseAddress << std::endl;
        return false;
    }
    if (lpNumberOfBytesRead)
        *lpNumberOfBytesRead = ret;
    return true;
}

bool WriteProcessMemory(HANDLE hProcess, void *lpBaseAddress, const void *lpBuffer, size_t nSize, size_t *lpNumberOfBytesWritten) {
    struct iovec local{nullptr, 0};
    struct iovec remote{nullptr, 0};


    local.iov_base = (void *) lpBuffer;
    local.iov_len = nSize;

    remote.iov_base = lpBaseAddress;
    remote.iov_len = nSize;

    long ret = syscall(SYS_process_vm_writev, hProcess, &local, 1, &remote, 1, 0);
    if (ret == -1) {
        std::cout << "SYS_process_vm_write error! = " << strerror(errno) << std::endl;
        return false;
    }
    if (lpNumberOfBytesWritten)
        *lpNumberOfBytesWritten = ret;
    return true;
}

uint32_t ProtectionStringToProtection(const std::string &protectionString) {

    int w, x, ret;
    x = protectionString.find('x') != -1 ? 1 : 0;
    w = protectionString.find('w') != -1 ? 1 : 0;

    if (x)
        ret = w ? PAGE_EXECUTE_READWRITE : PAGE_EXECUTE_READ;
    else
        ret = w ? PAGE_READWRITE : PAGE_READONLY;
    return ret;
}


#endif