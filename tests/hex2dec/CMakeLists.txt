add_executable(T_Hex2Dec main.cpp)

target_link_libraries(T_Hex2Dec Voxelite_Utils)

add_test(NAME Hex2Dec COMMAND T_Hex2Dec)
