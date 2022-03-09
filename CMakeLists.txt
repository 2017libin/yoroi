# 1. Set cmake version
cmake_minimum_required(VERSION 3.2)

# 2. Set project name
PROJECT(yoroi)

SET(BUILD_NAME main)

# ------------------
# Compiler Environment Configure
#
message(STATUS "CMAKE_BUILD_TYPE:\t" ${CMAKE_BUILD_TYPE})

set(CMAKE_C_FLAGS_RELEASE     "-O2 -g")

########################## source file  ##########################
AUX_SOURCE_DIRECTORY(sample SRCS)
AUX_SOURCE_DIRECTORY(src SRCS)

add_executable(${BUILD_NAME} ${SRCS})

########################## headers  ##########################
INCLUDE_DIRECTORIES(include)

########################## link lib  ##########################
if(KEYSTORE_LINKS)
    message(STATUS KEYSTORE_LINKS: ${KEYSTORE_LINKS})
    TARGET_LINK_LIBRARIES(${BUILD_NAME} ${KEYSTORE_LINKS} )
ENDIF(KEYSTORE_LINKS)

add_subdirectory(lib/mbedtls EXCLUDE_FROM_ALL)
# link to mbedtls
target_link_libraries(${BUILD_NAME} PUBLIC mbedtls)
