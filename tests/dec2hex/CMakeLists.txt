add_executable(T_Dec2Hex main.cpp)

target_link_libraries(T_Dec2Hex Voxelite_Utils)

add_test(NAME Dec2Hex COMMAND T_Dec2Hex)
