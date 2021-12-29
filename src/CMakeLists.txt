set (TCP_LIB_SUFFIX "tcp")
set (TCP_LIB_NAME  "tcp_${TCP_LIB_SUFFIX}")

set (TCP_INCLUDE_DIR "${CRU_INCLUDE_DIR}/net/comm/tcp")

add_library(${TCP_LIB_NAME})

target_sources(${TCP_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/net/comm/tcp/client/client.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/net/comm/tcp/server/server.cc
)

target_sources(${TCP_LIB_NAME}
    PRIVATE
    ${TCP_INCLUDE_DIR}/client/api/i_client.hpp
    ${TCP_INCLUDE_DIR}/client/client.hpp
    ${TCP_INCLUDE_DIR}/server/api/i_server.hpp
    ${TCP_INCLUDE_DIR}/server/server.hpp
)

add_library(${PROJECT_SHORTNAME}::${TCP_LIB_SUFFIX} ALIAS ${TCP_LIB_NAME})
target_link_libraries(${TCP_LIB_NAME} Boost::asio Boost::align)