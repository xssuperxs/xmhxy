# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = D:/CLion/bin/cmake/win/x64/bin/cmake.exe

# The command to remove a file.
RM = D:/CLion/bin/cmake/win/x64/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/code/Clion/xmhxy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/code/Clion/xmhxy/cmake-build-debug_android

# Include any dependencies generated for this target.
include CMakeFiles/xmhxy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/xmhxy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/xmhxy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/xmhxy.dir/flags.make

CMakeFiles/xmhxy.dir/main.cpp.o: CMakeFiles/xmhxy.dir/flags.make
CMakeFiles/xmhxy.dir/main.cpp.o: D:/code/Clion/xmhxy/main.cpp
CMakeFiles/xmhxy.dir/main.cpp.o: CMakeFiles/xmhxy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/code/Clion/xmhxy/cmake-build-debug_android/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/xmhxy.dir/main.cpp.o"
	D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe --target=x86_64-none-linux-android21 --sysroot=D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/xmhxy.dir/main.cpp.o -MF CMakeFiles/xmhxy.dir/main.cpp.o.d -o CMakeFiles/xmhxy.dir/main.cpp.o -c D:/code/Clion/xmhxy/main.cpp

CMakeFiles/xmhxy.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/xmhxy.dir/main.cpp.i"
	D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe --target=x86_64-none-linux-android21 --sysroot=D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/code/Clion/xmhxy/main.cpp > CMakeFiles/xmhxy.dir/main.cpp.i

CMakeFiles/xmhxy.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/xmhxy.dir/main.cpp.s"
	D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe --target=x86_64-none-linux-android21 --sysroot=D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/code/Clion/xmhxy/main.cpp -o CMakeFiles/xmhxy.dir/main.cpp.s

CMakeFiles/xmhxy.dir/memory/xmem.cpp.o: CMakeFiles/xmhxy.dir/flags.make
CMakeFiles/xmhxy.dir/memory/xmem.cpp.o: D:/code/Clion/xmhxy/memory/xmem.cpp
CMakeFiles/xmhxy.dir/memory/xmem.cpp.o: CMakeFiles/xmhxy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:/code/Clion/xmhxy/cmake-build-debug_android/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/xmhxy.dir/memory/xmem.cpp.o"
	D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe --target=x86_64-none-linux-android21 --sysroot=D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/xmhxy.dir/memory/xmem.cpp.o -MF CMakeFiles/xmhxy.dir/memory/xmem.cpp.o.d -o CMakeFiles/xmhxy.dir/memory/xmem.cpp.o -c D:/code/Clion/xmhxy/memory/xmem.cpp

CMakeFiles/xmhxy.dir/memory/xmem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/xmhxy.dir/memory/xmem.cpp.i"
	D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe --target=x86_64-none-linux-android21 --sysroot=D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/code/Clion/xmhxy/memory/xmem.cpp > CMakeFiles/xmhxy.dir/memory/xmem.cpp.i

CMakeFiles/xmhxy.dir/memory/xmem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/xmhxy.dir/memory/xmem.cpp.s"
	D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe --target=x86_64-none-linux-android21 --sysroot=D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/sysroot $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/code/Clion/xmhxy/memory/xmem.cpp -o CMakeFiles/xmhxy.dir/memory/xmem.cpp.s

# Object files for target xmhxy
xmhxy_OBJECTS = \
"CMakeFiles/xmhxy.dir/main.cpp.o" \
"CMakeFiles/xmhxy.dir/memory/xmem.cpp.o"

# External object files for target xmhxy
xmhxy_EXTERNAL_OBJECTS =

xmhxy: CMakeFiles/xmhxy.dir/main.cpp.o
xmhxy: CMakeFiles/xmhxy.dir/memory/xmem.cpp.o
xmhxy: CMakeFiles/xmhxy.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:/code/Clion/xmhxy/cmake-build-debug_android/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable xmhxy"
	D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/bin/clang++.exe --target=x86_64-none-linux-android21 --sysroot=D:/androidSDK/ndk/android-ndk-r27/toolchains/llvm/prebuilt/windows-x86_64/sysroot -g -DANDROID -fdata-sections -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security   -fno-limit-debug-info  -static-libstdc++ -Wl,--build-id=sha1 -Wl,--no-rosegment -Wl,--no-undefined-version -Wl,--fatal-warnings -Wl,--no-undefined -Qunused-arguments   $(xmhxy_OBJECTS) $(xmhxy_EXTERNAL_OBJECTS) -o xmhxy  -latomic -lm 

# Rule to build all files generated by this target.
CMakeFiles/xmhxy.dir/build: xmhxy
.PHONY : CMakeFiles/xmhxy.dir/build

CMakeFiles/xmhxy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xmhxy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xmhxy.dir/clean

CMakeFiles/xmhxy.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/code/Clion/xmhxy D:/code/Clion/xmhxy D:/code/Clion/xmhxy/cmake-build-debug_android D:/code/Clion/xmhxy/cmake-build-debug_android D:/code/Clion/xmhxy/cmake-build-debug_android/CMakeFiles/xmhxy.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/xmhxy.dir/depend

