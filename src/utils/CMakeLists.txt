set (UTILS_LIB_SUFFIX "utils")
set (UTILS_LIB_NAME  "cru_${UTILS_LIB_SUFFIX}")

set (UTILS_INCLUDE_DIR "${CRU_INCLUDE_DIR}/cru/utils")

add_library(${UTILS_LIB_NAME})

target_sources(${UTILS_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/log/logger.cc
)

target_sources(${UTILS_LIB_NAME}
    PRIVATE
    ${UTILS_INCLUDE_DIR}/log/logger.hpp
)

add_library(${PROJECT_SHORTNAME}::${UTILS_LIB_SUFFIX} ALIAS ${UTILS_LIB_NAME})
target_link_libraries(${UTILS_LIB_NAME} fmt::fmt)