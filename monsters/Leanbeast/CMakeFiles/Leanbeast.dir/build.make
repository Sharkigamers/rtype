# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast

# Include any dependencies generated for this target.
include CMakeFiles/Leanbeast.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Leanbeast.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Leanbeast.dir/flags.make

CMakeFiles/Leanbeast.dir/Leanbeast.cpp.o: CMakeFiles/Leanbeast.dir/flags.make
CMakeFiles/Leanbeast.dir/Leanbeast.cpp.o: Leanbeast.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Leanbeast.dir/Leanbeast.cpp.o"
	/usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Leanbeast.dir/Leanbeast.cpp.o -c /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/Leanbeast.cpp

CMakeFiles/Leanbeast.dir/Leanbeast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Leanbeast.dir/Leanbeast.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/Leanbeast.cpp > CMakeFiles/Leanbeast.dir/Leanbeast.cpp.i

CMakeFiles/Leanbeast.dir/Leanbeast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Leanbeast.dir/Leanbeast.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/Leanbeast.cpp -o CMakeFiles/Leanbeast.dir/Leanbeast.cpp.s

CMakeFiles/Leanbeast.dir/entryPoint.cpp.o: CMakeFiles/Leanbeast.dir/flags.make
CMakeFiles/Leanbeast.dir/entryPoint.cpp.o: entryPoint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Leanbeast.dir/entryPoint.cpp.o"
	/usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Leanbeast.dir/entryPoint.cpp.o -c /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/entryPoint.cpp

CMakeFiles/Leanbeast.dir/entryPoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Leanbeast.dir/entryPoint.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/entryPoint.cpp > CMakeFiles/Leanbeast.dir/entryPoint.cpp.i

CMakeFiles/Leanbeast.dir/entryPoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Leanbeast.dir/entryPoint.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/entryPoint.cpp -o CMakeFiles/Leanbeast.dir/entryPoint.cpp.s

# Object files for target Leanbeast
Leanbeast_OBJECTS = \
"CMakeFiles/Leanbeast.dir/Leanbeast.cpp.o" \
"CMakeFiles/Leanbeast.dir/entryPoint.cpp.o"

# External object files for target Leanbeast
Leanbeast_EXTERNAL_OBJECTS =

libLeanbeast.so: CMakeFiles/Leanbeast.dir/Leanbeast.cpp.o
libLeanbeast.so: CMakeFiles/Leanbeast.dir/entryPoint.cpp.o
libLeanbeast.so: CMakeFiles/Leanbeast.dir/build.make
libLeanbeast.so: CMakeFiles/Leanbeast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libLeanbeast.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Leanbeast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Leanbeast.dir/build: libLeanbeast.so

.PHONY : CMakeFiles/Leanbeast.dir/build

CMakeFiles/Leanbeast.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Leanbeast.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Leanbeast.dir/clean

CMakeFiles/Leanbeast.dir/depend:
	cd /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast /home/niels/Cpool/OOP/B-CPP-501-PAR-5-1-rtype-emmanuel.blineau/monsters/Leanbeast/CMakeFiles/Leanbeast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Leanbeast.dir/depend

