# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alien/q

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alien/q

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/alien/q/CMakeFiles /home/alien/q/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/alien/q/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named q

# Build rule for target.
q : cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 q
.PHONY : q

# fast build rule for target.
q/fast:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/build
.PHONY : q/fast

src/exe.o: src/exe.c.o

.PHONY : src/exe.o

# target to build an object file
src/exe.c.o:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/exe.c.o
.PHONY : src/exe.c.o

src/exe.i: src/exe.c.i

.PHONY : src/exe.i

# target to preprocess a source file
src/exe.c.i:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/exe.c.i
.PHONY : src/exe.c.i

src/exe.s: src/exe.c.s

.PHONY : src/exe.s

# target to generate assembly for a file
src/exe.c.s:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/exe.c.s
.PHONY : src/exe.c.s

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/main.c.s
.PHONY : src/main.c.s

src/parser.o: src/parser.c.o

.PHONY : src/parser.o

# target to build an object file
src/parser.c.o:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/parser.c.o
.PHONY : src/parser.c.o

src/parser.i: src/parser.c.i

.PHONY : src/parser.i

# target to preprocess a source file
src/parser.c.i:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/parser.c.i
.PHONY : src/parser.c.i

src/parser.s: src/parser.c.s

.PHONY : src/parser.s

# target to generate assembly for a file
src/parser.c.s:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/parser.c.s
.PHONY : src/parser.c.s

src/token.o: src/token.c.o

.PHONY : src/token.o

# target to build an object file
src/token.c.o:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/token.c.o
.PHONY : src/token.c.o

src/token.i: src/token.c.i

.PHONY : src/token.i

# target to preprocess a source file
src/token.c.i:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/token.c.i
.PHONY : src/token.c.i

src/token.s: src/token.c.s

.PHONY : src/token.s

# target to generate assembly for a file
src/token.c.s:
	$(MAKE) -f CMakeFiles/q.dir/build.make CMakeFiles/q.dir/src/token.c.s
.PHONY : src/token.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... q"
	@echo "... src/exe.o"
	@echo "... src/exe.i"
	@echo "... src/exe.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/parser.o"
	@echo "... src/parser.i"
	@echo "... src/parser.s"
	@echo "... src/token.o"
	@echo "... src/token.i"
	@echo "... src/token.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

