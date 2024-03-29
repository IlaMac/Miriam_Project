cmake_minimum_required(VERSION 3.15)

# Set default install directory for dependencies
# Append directory <libname> to CMAKE_INSTALL_PREFIX
# Useful if you want to have separate directories for each libs
# and to easily delete them individually
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "Setting default install prefix -- CMAKE_INSTALL_PREFIX --> ${CMAKE_BINARY_DIR}/pkg-install")
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/pkg-install" CACHE PATH "..." FORCE)
endif ()


# Transform CMAKE_INSTALL_PREFIX to full path
if(DEFINED CMAKE_INSTALL_PREFIX
        AND NOT IS_ABSOLUTE CMAKE_INSTALL_PREFIX
        AND NOT CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    get_filename_component(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
            ABSOLUTE BASE_DIR ${CMAKE_BINARY_DIR} CACHE FORCE)
    message(STATUS "Setting absolute path CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")
endif()

# Setup build and install directories for dependencies
if(NOT GL_DEPS_BUILD_DIR)
    set(GL_DEPS_BUILD_DIR ${CMAKE_BINARY_DIR}/pkg-build)
endif()

# Install dependencies to the same location as the main project by default
if(NOT GL_DEPS_INSTALL_DIR)
    set(GL_DEPS_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
endif()

set(PKG_INSTALL_DIR_DEFAULT ${GL_DEPS_INSTALL_DIR} CACHE STRING "" FORCE )
set(PKG_BUILD_DIR_DEFAULT   ${GL_DEPS_BUILD_DIR}   CACHE STRING "" FORCE )

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PKG_INSTALL_DIR_DEFAULT} ${CMAKE_INSTALL_PREFIX})
list(REMOVE_DUPLICATES CMAKE_PREFIX_PATH)
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" CACHE INTERNAL "Paths for find_package lookup" FORCE)


if (CMAKE_SIZEOF_VOID_P EQUAL 8 OR CMAKE_GENERATOR MATCHES "64")
    set(FIND_LIBRARY_USE_LIB64_PATHS ON)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(FIND_LIBRARY_USE_LIB32_PATHS ON)
endif ()


if(WIN32)
    # On Windows it is standard practice to collect binaries into one directory.
    # This way we avoid errors from .dll's not being found at runtime.
    # These directories will contain h5pp tests, examples and possibly dependencies
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Collect .exe and .dll")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Collect .lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Collect .lib")
endif()

if (GL_PACKAGE_MANAGER MATCHES "conan")
    # Paths to search for conan installation.
    list(APPEND GL_CONAN_HINTS
            ${CONAN_PREFIX}
            $ENV{CONAN_PREFIX}
            ${CONDA_PREFIX}
            $ENV{CONDA_PREFIX}
            $ENV{HOME}/anaconda3
            $ENV{HOME}/anaconda
            $ENV{HOME}/miniconda3
            $ENV{HOME}/miniconda
            )
    list(APPEND GL_CONAN_PATH_SUFFIXES
            bin envs/dmrg/bin
            )
endif ()


mark_as_advanced(GL_CONAN_CANDIDATE_PATHS)