cmake_minimum_required(VERSION 3.26)
project(SIAOD_5)

set(CMAKE_CXX_STANDARD 17)

add_executable(SIAOD_5 main.cpp
        BST.cpp
        BST.h
        BinaryFile.cpp
        BinaryFile.h
        HashTable.cpp
        HashTable.h
        SplayTree.cpp
        SplayTree.h
)
