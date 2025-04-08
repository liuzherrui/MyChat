# add sub directory

MESSAGE("---------------Starting ServerKernel Make---------------")
add_subdirectory(ServerKernel)
MESSAGE("---------------ServerKernel Make Finish---------------")

MESSAGE("---------------Starting Run Make---------------")
add_subdirectory(Run)
MESSAGE("---------------Run Make Finish---------------")
