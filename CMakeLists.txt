cmake_minimum_required(VERSION 3.5)
project(CPP_Joules VERSION 0.0.1 DESCRIPTION "Energy Measurement toolkit for cpp/cuda" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(CPP_Joules SHARED)

target_sources(CPP_Joules
    PRIVATE  
    ${PROJECT_SOURCE_DIR}/src/cppJoules.cpp 
    ${PROJECT_SOURCE_DIR}/src/energy_state.cpp 
    ${PROJECT_SOURCE_DIR}/src/nvidia_devices.cpp 
    ${PROJECT_SOURCE_DIR}/src/rapl_devices.cpp
)

target_include_directories(CPP_Joules
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(CPP_Joules PRIVATE "-fexceptions")
endif()

if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is not set\n"
        "Default value: ${CMAKE_INSTALL_PREFIX}\n"
        "Will set it to /usr"
    )
    set(CMAKE_INSTALL_PREFIX
        "/usr"
        CACHE PATH "Where the library will be installed to" FORCE
    )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX was already set\n"
        "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

set(public_headers
  include/cppJoules.h
)
#for debug postfix
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

# find_library(NVML_LIBRARY nvidia-ml PATHS /usr/local/cuda/lib64 /usr/local/cuda/lib /usr/lib /usr/lib64)
# target_link_libraries(CPP_Joules PUBLIC ${NVML_LIBRARY})
# if(NOT NVML_LIBRARY)
#     message(FATAL_ERROR "Could not find the NVML library.")
# endif()

include(GNUInstallDirs)

install(TARGETS CPP_Joules 
        EXPORT CPP_Joules_Targets
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CPP_Joules
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT CPP_Joules_Targets
        FILE CPP_Joules_Targest.cmake
        NAMESPACE CPP_Joules::
        DESTINATION cmake
)

# Package configuration
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/CPP_Joules_ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPP_Joules_Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/CPP_Joules_Config.cmake"
  INSTALL_DESTINATION cmake
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/CPP_Joules_Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/CPP_Joules_ConfigVersion.cmake"
  DESTINATION cmake
)

