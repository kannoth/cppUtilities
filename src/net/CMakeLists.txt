set (NET_LIB_SUFFIX "net")
set (NET_LIB_NAME  "cru_${NET_LIB_SUFFIX}")

set (NET_INCLUDE_DIR "${CRU_INCLUDE_DIR}/cru/net/comm/tcp")

add_library(${NET_LIB_NAME})

target_sources(${NET_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/comm/tcp/client/client.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/comm/tcp/server/server.cc
)

target_sources(${NET_LIB_NAME}
    PRIVATE
    ${NET_INCLUDE_DIR}/client/api/i_client.hpp
    ${NET_INCLUDE_DIR}/client/client.hpp
    ${NET_INCLUDE_DIR}/server/api/i_server.hpp
    ${NET_INCLUDE_DIR}/server/server.hpp
    ${NET_INCLUDE_DIR}/server/session.hpp
)

add_library(${PROJECT_SHORTNAME}::${NET_LIB_SUFFIX} ALIAS ${NET_LIB_NAME})
target_link_libraries(${NET_LIB_NAME} Boost::asio Boost::align)