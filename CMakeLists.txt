cmake_minimum_required(VERSION 3.0...3.12)

project(CRU)
set (PROJECT_NAME "CPP reusable utilities")
set (PROJECT_SHORTNAME "cru")

set(CMAKE_CXX_STANDARD 14)

# To get rid of undefined reference to `cru::utils::logger::timestamp[abi:cxx11]()
# Stack overflow : https://stackoverflow.com/questions/55406770/gcc-undefined-references-with-abicxx11
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

set(CRU_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

if(MSVC)
    add_compile_options(/W3 /WX /std:c++14)
else()
    add_compile_options(-W -Wall )#-Werror)
endif()

include_directories("${CRU_INCLUDE_DIR}")

#libs
add_subdirectory(libs/boost)
add_subdirectory(libs/fmt)
add_subdirectory(libs/googletest)
#sources
add_subdirectory(src/net)
add_subdirectory(src/utils)
#tests
add_subdirectory(test)