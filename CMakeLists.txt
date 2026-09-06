cmake_minimum_required(VERSION 3.18)

if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
endif()

project(NFD)

add_subdirectory(src)
