add_executable(T_Version main.cpp)

target_link_libraries(T_Version Voxelite_Utils)

add_test(NAME Version COMMAND T_Version)
