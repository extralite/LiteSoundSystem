set(OGG_DIR ${OGG_SOURCE_DIR})
set(OGG_INCLUDE_DIR ${OGG_DIR}/include ${CMAKE_BINARY_DIR}/ogg/include)

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
add_subdirectory(${OGG_DIR} ${CMAKE_BINARY_DIR}/ogg)
