# add main file
file(GLOB RUN_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)



add_executable(MyChatServer 
${RUN_SOURCE_FILE}
)

#target_include_directories(MyChatServer PRIVATE
#${SERVERKERNEL_HEADER_DIRECTORY}
#)

target_link_libraries(MyChatServer
ServerKernel
)

source_group(src FILES ${RUN_SOURCE_FILE})

set_target_properties(MyChatServer PROPERTIES FOLDER "modules")
