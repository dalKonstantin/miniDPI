cmake_minimum_required(VERSION 3.20)
# ============
# DEFAULT BUILD TYPE
# ============
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# ============
# PROJECT SETUP
# ============
project(miniDPI VERSION 0.1.0 LANGUAGES CXX)

# ============
# EXPORT COMPILE COMMANDS
# ============
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============
# SET STANDARDS
# ============
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ============
# PCAP
# ============
find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)


# ============
# PRINT SOME INFO
# ============
message("===== miniDPI =====")
message("Build type: ${CMAKE_BUILD_TYPE}")
message("Version: ${PROJECT_VERSION}")


# ============
# FIND PACKAGES
# ============

add_subdirectory(src)
