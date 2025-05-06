cmake_minimum_required(VERSION 3.18)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

project(MyChatServer VERSION 1.0)

set(DEBUG_FLAG 1) 

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  # Debug 配置
  #添加可编辑并继续的程序数据库用于调试
  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "-Od ${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "/ZI")
    set(CMAKE_SHARED_LINKER_FLAGS "/SAFESEH:NO")
    set(CMAKE_EXE_LINKER_FLAGS "/SAFESEH:NO")
  endif()
  set(DEBUG_FLAG 1)
  MESSAGE("DEBUG_FLAG value change to 1")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  # Release 配置
  set(DEBUG_FLAG 0)
  MESSAGE("DEBUG_FLAG value change to 0")
endif ()

# 添加预处理器定义屏蔽vs的全局max和min宏
add_compile_definitions(NOMINMAX)

# 添加工作目录
set(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
MESSAGE("working directory: " ${PROJECT_SOURCE_DIR})
#ADD_DEFINITIONS(-D _WORKING_DIRECTORY=\"${WORKING_DIRECTORY}\")

MESSAGE(STATUS "(1 for debug and 0 for release) DEBUG_FLAG Value : " ${DEBUG_FLAG})

# include Modules directory
#include_directories("${PROJECT_SOURCE_DIR}/Modules")


# Save libs and executables in the same place
if(DEBUG_FLAG EQUAL 1)
  set(EXECUTABLE_OUTPUT_PATH      "${CMAKE_BINARY_DIR}/bin")
  set(LIBRARY_OUTPUT_PATH         "${CMAKE_BINARY_DIR}/lib")
elseif(DEBUG_FLAG EQUAL 0)
  set(EXECUTABLE_OUTPUT_PATH      "${CMAKE_BINARY_DIR}/bin")
  set(LIBRARY_OUTPUT_PATH         "${CMAKE_BINARY_DIR}/lib")
endif()

# use virtual folders to manage projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# find libraries
find_library(WS2_32_LIB ws2_32)
MESSAGE(STATUS "--------------- Path: " ${WS2_32_LIB} " ---------------")

# add sub directory
MESSAGE("---------------Starting Modules Make---------------")
add_subdirectory(Modules)
MESSAGE("---------------Modules Make Finish---------------")
