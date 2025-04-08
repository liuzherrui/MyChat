set(SERVERKERNEL_HEADER_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add ServerKernel
file(GLOB SERVELKERNEL_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB SERVERKERNEL_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(ServerKernel
${SERVELKERNEL_HEADER_FILES} ${SERVERKERNEL_SOURCE_FILES}
)

# add source_group for each file folder
source_group(include FILES ${SERVELKERNEL_HEADER_FILES})
source_group(src FILES ${SERVERKERNEL_SOURCE_FILES})

set_target_properties(ServerKernel PROPERTIES FOLDER "modules")

