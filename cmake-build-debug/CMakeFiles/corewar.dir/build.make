# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /nfs/2016/y/ysavenko/CLionProjects/cor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/corewar.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/corewar.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/corewar.dir/flags.make

CMakeFiles/corewar.dir/main.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/corewar.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/main.c.o   -c /nfs/2016/y/ysavenko/CLionProjects/cor/main.c

CMakeFiles/corewar.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/2016/y/ysavenko/CLionProjects/cor/main.c > CMakeFiles/corewar.dir/main.c.i

CMakeFiles/corewar.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/2016/y/ysavenko/CLionProjects/cor/main.c -o CMakeFiles/corewar.dir/main.c.s

CMakeFiles/corewar.dir/main.c.o.requires:

.PHONY : CMakeFiles/corewar.dir/main.c.o.requires

CMakeFiles/corewar.dir/main.c.o.provides: CMakeFiles/corewar.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/corewar.dir/build.make CMakeFiles/corewar.dir/main.c.o.provides.build
.PHONY : CMakeFiles/corewar.dir/main.c.o.provides

CMakeFiles/corewar.dir/main.c.o.provides.build: CMakeFiles/corewar.dir/main.c.o


CMakeFiles/corewar.dir/fill_bot.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/fill_bot.c.o: ../fill_bot.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/corewar.dir/fill_bot.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/fill_bot.c.o   -c /nfs/2016/y/ysavenko/CLionProjects/cor/fill_bot.c

CMakeFiles/corewar.dir/fill_bot.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/fill_bot.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/2016/y/ysavenko/CLionProjects/cor/fill_bot.c > CMakeFiles/corewar.dir/fill_bot.c.i

CMakeFiles/corewar.dir/fill_bot.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/fill_bot.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/2016/y/ysavenko/CLionProjects/cor/fill_bot.c -o CMakeFiles/corewar.dir/fill_bot.c.s

CMakeFiles/corewar.dir/fill_bot.c.o.requires:

.PHONY : CMakeFiles/corewar.dir/fill_bot.c.o.requires

CMakeFiles/corewar.dir/fill_bot.c.o.provides: CMakeFiles/corewar.dir/fill_bot.c.o.requires
	$(MAKE) -f CMakeFiles/corewar.dir/build.make CMakeFiles/corewar.dir/fill_bot.c.o.provides.build
.PHONY : CMakeFiles/corewar.dir/fill_bot.c.o.provides

CMakeFiles/corewar.dir/fill_bot.c.o.provides.build: CMakeFiles/corewar.dir/fill_bot.c.o


CMakeFiles/corewar.dir/map.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/map.c.o: ../map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/corewar.dir/map.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/map.c.o   -c /nfs/2016/y/ysavenko/CLionProjects/cor/map.c

CMakeFiles/corewar.dir/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/map.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/2016/y/ysavenko/CLionProjects/cor/map.c > CMakeFiles/corewar.dir/map.c.i

CMakeFiles/corewar.dir/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/map.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/2016/y/ysavenko/CLionProjects/cor/map.c -o CMakeFiles/corewar.dir/map.c.s

CMakeFiles/corewar.dir/map.c.o.requires:

.PHONY : CMakeFiles/corewar.dir/map.c.o.requires

CMakeFiles/corewar.dir/map.c.o.provides: CMakeFiles/corewar.dir/map.c.o.requires
	$(MAKE) -f CMakeFiles/corewar.dir/build.make CMakeFiles/corewar.dir/map.c.o.provides.build
.PHONY : CMakeFiles/corewar.dir/map.c.o.provides

CMakeFiles/corewar.dir/map.c.o.provides.build: CMakeFiles/corewar.dir/map.c.o


CMakeFiles/corewar.dir/champion.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/champion.c.o: ../champion.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/corewar.dir/champion.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/champion.c.o   -c /nfs/2016/y/ysavenko/CLionProjects/cor/champion.c

CMakeFiles/corewar.dir/champion.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/champion.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/2016/y/ysavenko/CLionProjects/cor/champion.c > CMakeFiles/corewar.dir/champion.c.i

CMakeFiles/corewar.dir/champion.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/champion.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/2016/y/ysavenko/CLionProjects/cor/champion.c -o CMakeFiles/corewar.dir/champion.c.s

CMakeFiles/corewar.dir/champion.c.o.requires:

.PHONY : CMakeFiles/corewar.dir/champion.c.o.requires

CMakeFiles/corewar.dir/champion.c.o.provides: CMakeFiles/corewar.dir/champion.c.o.requires
	$(MAKE) -f CMakeFiles/corewar.dir/build.make CMakeFiles/corewar.dir/champion.c.o.provides.build
.PHONY : CMakeFiles/corewar.dir/champion.c.o.provides

CMakeFiles/corewar.dir/champion.c.o.provides.build: CMakeFiles/corewar.dir/champion.c.o


CMakeFiles/corewar.dir/instruct.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/instruct.c.o: ../instruct.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/corewar.dir/instruct.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/instruct.c.o   -c /nfs/2016/y/ysavenko/CLionProjects/cor/instruct.c

CMakeFiles/corewar.dir/instruct.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/instruct.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/2016/y/ysavenko/CLionProjects/cor/instruct.c > CMakeFiles/corewar.dir/instruct.c.i

CMakeFiles/corewar.dir/instruct.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/instruct.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/2016/y/ysavenko/CLionProjects/cor/instruct.c -o CMakeFiles/corewar.dir/instruct.c.s

CMakeFiles/corewar.dir/instruct.c.o.requires:

.PHONY : CMakeFiles/corewar.dir/instruct.c.o.requires

CMakeFiles/corewar.dir/instruct.c.o.provides: CMakeFiles/corewar.dir/instruct.c.o.requires
	$(MAKE) -f CMakeFiles/corewar.dir/build.make CMakeFiles/corewar.dir/instruct.c.o.provides.build
.PHONY : CMakeFiles/corewar.dir/instruct.c.o.provides

CMakeFiles/corewar.dir/instruct.c.o.provides.build: CMakeFiles/corewar.dir/instruct.c.o


CMakeFiles/corewar.dir/sti_ldi.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/sti_ldi.c.o: ../sti_ldi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/corewar.dir/sti_ldi.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/sti_ldi.c.o   -c /nfs/2016/y/ysavenko/CLionProjects/cor/sti_ldi.c

CMakeFiles/corewar.dir/sti_ldi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/sti_ldi.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/2016/y/ysavenko/CLionProjects/cor/sti_ldi.c > CMakeFiles/corewar.dir/sti_ldi.c.i

CMakeFiles/corewar.dir/sti_ldi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/sti_ldi.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/2016/y/ysavenko/CLionProjects/cor/sti_ldi.c -o CMakeFiles/corewar.dir/sti_ldi.c.s

CMakeFiles/corewar.dir/sti_ldi.c.o.requires:

.PHONY : CMakeFiles/corewar.dir/sti_ldi.c.o.requires

CMakeFiles/corewar.dir/sti_ldi.c.o.provides: CMakeFiles/corewar.dir/sti_ldi.c.o.requires
	$(MAKE) -f CMakeFiles/corewar.dir/build.make CMakeFiles/corewar.dir/sti_ldi.c.o.provides.build
.PHONY : CMakeFiles/corewar.dir/sti_ldi.c.o.provides

CMakeFiles/corewar.dir/sti_ldi.c.o.provides.build: CMakeFiles/corewar.dir/sti_ldi.c.o


CMakeFiles/corewar.dir/op.c.o: CMakeFiles/corewar.dir/flags.make
CMakeFiles/corewar.dir/op.c.o: ../op.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/corewar.dir/op.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/corewar.dir/op.c.o   -c /nfs/2016/y/ysavenko/CLionProjects/cor/op.c

CMakeFiles/corewar.dir/op.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/corewar.dir/op.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /nfs/2016/y/ysavenko/CLionProjects/cor/op.c > CMakeFiles/corewar.dir/op.c.i

CMakeFiles/corewar.dir/op.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/corewar.dir/op.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /nfs/2016/y/ysavenko/CLionProjects/cor/op.c -o CMakeFiles/corewar.dir/op.c.s

CMakeFiles/corewar.dir/op.c.o.requires:

.PHONY : CMakeFiles/corewar.dir/op.c.o.requires

CMakeFiles/corewar.dir/op.c.o.provides: CMakeFiles/corewar.dir/op.c.o.requires
	$(MAKE) -f CMakeFiles/corewar.dir/build.make CMakeFiles/corewar.dir/op.c.o.provides.build
.PHONY : CMakeFiles/corewar.dir/op.c.o.provides

CMakeFiles/corewar.dir/op.c.o.provides.build: CMakeFiles/corewar.dir/op.c.o


# Object files for target corewar
corewar_OBJECTS = \
"CMakeFiles/corewar.dir/main.c.o" \
"CMakeFiles/corewar.dir/fill_bot.c.o" \
"CMakeFiles/corewar.dir/map.c.o" \
"CMakeFiles/corewar.dir/champion.c.o" \
"CMakeFiles/corewar.dir/instruct.c.o" \
"CMakeFiles/corewar.dir/sti_ldi.c.o" \
"CMakeFiles/corewar.dir/op.c.o"

# External object files for target corewar
corewar_EXTERNAL_OBJECTS =

corewar: CMakeFiles/corewar.dir/main.c.o
corewar: CMakeFiles/corewar.dir/fill_bot.c.o
corewar: CMakeFiles/corewar.dir/map.c.o
corewar: CMakeFiles/corewar.dir/champion.c.o
corewar: CMakeFiles/corewar.dir/instruct.c.o
corewar: CMakeFiles/corewar.dir/sti_ldi.c.o
corewar: CMakeFiles/corewar.dir/op.c.o
corewar: CMakeFiles/corewar.dir/build.make
corewar: ../libft/libft.a
corewar: CMakeFiles/corewar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable corewar"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/corewar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/corewar.dir/build: corewar

.PHONY : CMakeFiles/corewar.dir/build

CMakeFiles/corewar.dir/requires: CMakeFiles/corewar.dir/main.c.o.requires
CMakeFiles/corewar.dir/requires: CMakeFiles/corewar.dir/fill_bot.c.o.requires
CMakeFiles/corewar.dir/requires: CMakeFiles/corewar.dir/map.c.o.requires
CMakeFiles/corewar.dir/requires: CMakeFiles/corewar.dir/champion.c.o.requires
CMakeFiles/corewar.dir/requires: CMakeFiles/corewar.dir/instruct.c.o.requires
CMakeFiles/corewar.dir/requires: CMakeFiles/corewar.dir/sti_ldi.c.o.requires
CMakeFiles/corewar.dir/requires: CMakeFiles/corewar.dir/op.c.o.requires

.PHONY : CMakeFiles/corewar.dir/requires

CMakeFiles/corewar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/corewar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/corewar.dir/clean

CMakeFiles/corewar.dir/depend:
	cd /nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /nfs/2016/y/ysavenko/CLionProjects/cor /nfs/2016/y/ysavenko/CLionProjects/cor /nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug /nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug /nfs/2016/y/ysavenko/CLionProjects/cor/cmake-build-debug/CMakeFiles/corewar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/corewar.dir/depend

