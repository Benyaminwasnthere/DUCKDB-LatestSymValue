cmake_minimum_required(VERSION 3.5)

set(TARGET_NAME scrooge)

# DuckDB's extension distribution supports vcpkg. As such, dependencies can be
# added in ./vcpkg.json and then used in cmake with find_package. Feel free to
# remove or replace with other dependencies. Note that it should also be removed
# from vcpkg.json to prevent needlessly installing it..
find_package(OpenSSL REQUIRED)

set(EXTENSION_NAME ${TARGET_NAME}_extension)
set(LOADABLE_EXTENSION_NAME ${TARGET_NAME}_loadable_extension)

project(${TARGET_NAME})
include_directories(src/include)
include_directories(third_party)
include_directories(duckdb/third_party/httplib)
include_directories(${OPENSSL_INCLUDE_DIR})

set(EXTENSION_SOURCES
    src/scrooge_extension.cpp
    src/functions/first.cpp
    src/functions/last.cpp
    src/functions/latest.cpp
    src/functions/timebucket.cpp
    src/scanner/yahoo_finance.cpp
    src/scanner/ethereum_blockchain.cpp
    src/functions/aliases.cpp
    src/functions/portfolio_frontier.cpp)

build_static_extension(${TARGET_NAME} ${EXTENSION_SOURCES})
build_loadable_extension(${TARGET_NAME} " " ${EXTENSION_SOURCES})

# Link OpenSSL in both the static library as the loadable extension
target_link_libraries(${EXTENSION_NAME} OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${LOADABLE_EXTENSION_NAME} OpenSSL::SSL OpenSSL::Crypto)

install(
  TARGETS ${EXTENSION_NAME}
  EXPORT "${DUCKDB_EXPORT_SET}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}")
