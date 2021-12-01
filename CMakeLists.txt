cmake_minimum_required(VERSION 3.1)

# project's name
project(Yoroi)

# add all sources in current directory to DIR_SRCS
aux_source_directory(. DIR_SRCS)

# 
add_subdirectory(Hash_DRBG/src)

# add header directory
INCLUDE_DIRECTORIES(./Hash_DRBG/header)

# 
add_executable(main1 ${DIR_SRCS})

target_link_libraries(main1 hash_drbg)
