cmake_minimum_required(VERSION 3.28)
project(Projekt2_PIAA)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt2_PIAA main.cpp
        Dikstrja.cpp
        Graf.cpp
        Dikstrja.h
        Graf.h
        Bellman-Ford.cpp
        BellmanFord.h
        DFS.cpp
        DFS.h
        Lista.cpp
        Lista.h
)
