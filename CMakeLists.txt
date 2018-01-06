cmake_minimum_required(VERSION 3.7)
project(DS_Wet_4)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp
        linkedList.h
        Coliseum.h
        Coliseum.cpp
        DSFunctions.cpp
        Exceptions.h
        Gladiator.h
        Gladiator.cpp
        CompGlads.h
        splayTree.h
        genericFunction.h
        TreeNode.h
        binTree.h
        minHeap.h
        minHeap.cpp
        TrainingGroup.h
        TrainingGroup.cpp
        library2.h
        HashTable.h
        )
add_executable(DS_Wet_4 ${SOURCE_FILES})