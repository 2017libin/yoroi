# Install script for directory: /home/chase511/code/yoroi/lib/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/certs.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/check_config.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/compat-1.3.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/config.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/debug.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/error.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/net.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/net_sockets.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/pkcs11.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/ssl.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/ssl_cache.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/ssl_cookie.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/ssl_internal.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/ssl_ticket.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/version.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/x509.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/x509_crl.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/x509_crt.h"
    "/home/chase511/code/yoroi/lib/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

