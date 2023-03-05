cmake_minimum_required(VERSION 3.23)
project(Project_C_C__)

set(CMAKE_CXX_STANDARD 17)


add_executable(BiTreeArray Data_Structure/Tree/BiTree/BiTreeArray.cpp)
add_executable(BiTreeLink Data_Structure/Tree/BiTree/BiTreeLink.cpp)
add_executable(ThreadBinaryTree Data_Structure/Tree/BiTree/ThreadBinaryTree.cpp)
add_executable(CreateMGraph Data_Structure/Graph/CreateMGraph.cpp)
add_executable(CreateALGraph Data_Structure/Graph/CreateALGraph.cpp)
add_executable(BinarySortTree Data_Structure/Search/BinarySortTree.cpp)
add_executable(AVLTree Data_Structure/Search/AVLTree.cpp)