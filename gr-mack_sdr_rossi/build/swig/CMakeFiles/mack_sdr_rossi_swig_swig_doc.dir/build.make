# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build

# Utility rule file for mack_sdr_rossi_swig_swig_doc.

# Include the progress variables for this target.
include swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/progress.make

swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc: swig/mack_sdr_rossi_swig_doc.i

swig/mack_sdr_rossi_swig_doc.i: swig/mack_sdr_rossi_swig_doc_swig_docs/xml/index.xml
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating python docstrings for mack_sdr_rossi_swig_doc"
	cd /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/docs/doxygen && /usr/bin/python2 -B /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/docs/doxygen/swig_doc.py /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig/mack_sdr_rossi_swig_doc_swig_docs/xml /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig/mack_sdr_rossi_swig_doc.i

swig/mack_sdr_rossi_swig_doc_swig_docs/xml/index.xml: swig/_mack_sdr_rossi_swig_doc_tag
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating doxygen xml for mack_sdr_rossi_swig_doc docs"
	cd /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig && ./_mack_sdr_rossi_swig_doc_tag
	cd /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig && /usr/bin/doxygen /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig/mack_sdr_rossi_swig_doc_swig_docs/Doxyfile

mack_sdr_rossi_swig_swig_doc: swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc
mack_sdr_rossi_swig_swig_doc: swig/mack_sdr_rossi_swig_doc.i
mack_sdr_rossi_swig_swig_doc: swig/mack_sdr_rossi_swig_doc_swig_docs/xml/index.xml
mack_sdr_rossi_swig_swig_doc: swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/build.make
.PHONY : mack_sdr_rossi_swig_swig_doc

# Rule to build all files generated by this target.
swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/build: mack_sdr_rossi_swig_swig_doc
.PHONY : swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/build

swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/clean:
	cd /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig && $(CMAKE_COMMAND) -P CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/cmake_clean.cmake
.PHONY : swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/clean

swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/depend:
	cd /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/swig /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig /home/rossi/Desktop/GitHub/projeto_grc/gr-mack_sdr_rossi/build/swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : swig/CMakeFiles/mack_sdr_rossi_swig_swig_doc.dir/depend

