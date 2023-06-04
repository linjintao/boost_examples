cmake_minimum_required(VERSION 2.8)

project(boost_demo CXX)

# we will use static libs
#set(Boost_USE_STATIC_LIBS ON)

# Boost::log required Boost version >= 1.54.0 
find_package(Boost 1.54.0 REQUIRED COMPONENTS ALL)
#find_package(ZSTD REQUIRED)
# Interpreter is used to set Python3_EXECUTABLE
find_package(Python3 COMPONENTS  Development Interpreter)

find_package(Threads)

include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})
link_directories(${Python3_RUNTIME_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
link_directories("/usr/local/lib")



set(SRC_FILES
  src/greet.cpp)
if(FALSE)

add_library(hello SHARED ${SRC_FILES})
set_target_properties(hello PROPERTIES OUTPUT_NAME "hello")
set_target_properties(hello PROPERTIES SUFFIX ".so")

set(name hello)
# customize library name to follow module name rules
set_property (TARGET ${name} PROPERTY PREFIX "")
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set_property (TARGET ${name} PROPERTY SUFFIX ".pyd")
endif()

endif()

Python3_add_library(hello MODULE ${SRC_FILES})
target_link_libraries(hello ${Boost_LIBRARIES} Threads::Threads boost_python311 ${Python3_LIBRARIES}  )

ENABLE_TESTING()
message(STATUS "${Python3_EXECUTABLE}")
ADD_TEST(NAME 01-HelloWorld COMMAND ${Python3_EXECUTABLE} hello.py)
