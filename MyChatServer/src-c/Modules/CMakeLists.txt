

# add sub directory
MESSAGE("---------------Starting Common Make---------------")
add_subdirectory(Common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common/include)
MESSAGE("---------------Common Make Finish---------------")

MESSAGE("---------------Starting ServerKernel Make---------------")
add_subdirectory(ServerKernel)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ServerKernel/include)
MESSAGE("---------------ServerKernel Make Finish---------------")

MESSAGE("---------------Starting Run Make---------------")
add_subdirectory(Run)
MESSAGE("---------------Run Make Finish---------------")
