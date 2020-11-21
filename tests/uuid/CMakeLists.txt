add_executable(T_UUID main.cpp)

target_link_libraries(T_UUID Voxelite_Utils)

add_test(NAME UUID COMMAND T_UUID)
