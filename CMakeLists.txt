cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME TddCpp)
set(EXECUTABLE_NAME out)
set(TEST_EXECUTABLE_NAME ut)

set(FILES main.cpp
	  FileParser.cpp)
set(TEST_FILES TestFileParser.cpp)

set(CXX_FLAGS "
  -Wall
  -Werror
  -std=c++14")

add_definitions(${CXX_FLAGS})
add_library(FileParser FileParser.cpp)

if(test)
  add_subdirectory(ext/googletest)
  enable_testing()
  include_directories(${gtest_SOURCE_DIR}/googletest/include 
		      ${gtest_SOURCE_DIR})
  add_executable(${TEST_EXECUTABLE_NAME} 
		 ${TEST_FILES})
  target_link_libraries(${TEST_EXECUTABLE_NAME} 
			gtest 
			gtest_main 
			FileParser)
else()
  add_executable(${EXECUTABLE_NAME} 
		 ${FILES})
endif()

