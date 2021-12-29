cmake_minimum_required(VERSION 3.0...3.12)

project(CRU)
set (PROJECT_NAME "CPP reusable utilities")
set (PROJECT_SHORTNAME "cru")

set(CMAKE_CXX_STANDARD 11)

set(CRU_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

if(MSVC)
    add_compile_options(/W3 /WX /std:c++11)
else()
    add_compile_options(-W -Wall )#-Werror)
endif()

#libs
add_subdirectory(libs/boost)
#sources
add_subdirectory(src)
#tests
#add_subdirectory(test)