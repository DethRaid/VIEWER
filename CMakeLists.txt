cmake_minimum_required(VERSION 3.9)
project(viewer)

# Functions
function(viewer_set_all_target_outputs target output_dir)
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${output_dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${output_dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${output_dir})
    set_target_properties(${target} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${output_dir})
    set_target_properties(${target} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${output_dir})
    set_target_properties(${target} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${output_dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${output_dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${output_dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${output_dir})
endfunction()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR})

set(BUILD_SHARED_LIBS ON)

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

set(3RD_PARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdparty)

find_package(PythonLibs)

set(GLM_DYNAMIC_LIBRARY_ENABLE ON)

add_subdirectory(${3RD_PARTY_DIR}/glfw)
add_subdirectory(${3RD_PARTY_DIR}/glm)
add_subdirectory(${3RD_PARTY_DIR}/easyloggingpp)
add_subdirectory(${3RD_PARTY_DIR}/json)

find_package(glm)

set(COMMON_LINK_LIBS ${CMAKE_DL_LIBS} glfw ${GLFW_LIBRARIES} ${PYTHON_LIBRARIES})

set(VIEWER_SOURCE
        3rdparty/easyloggingpp/src/easylogging++.cc

        src/main/cpp/objects/material_store.cpp
        src/main/cpp/objects/material_store.h
        src/main/cpp/core/data_transfer_point.h
        src/main/cpp/python_interface/python_interface.cpp src/main/cpp/python_interface/python_interface.h src/main/cpp/utils/export.h)

add_library(viewer SHARED ${VIEWER_SOURCE})
target_include_directories(viewer SYSTEM PUBLIC ${PYTHON_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${3RD_PARTY_DIR}/easyloggingpp/src ${3RD_PARTY_DIR}/glad/include ${3RD_PARTY_DIR}/json/src)
target_link_libraries(viewer ${COMMON_LINK_LIBS})
target_compile_definitions(viewer PRIVATE DLL_IMPORT)

get_target_property(OUTPUT_DIR viewer LIBRARY_OUTPUT_DIRECTORY)
viewer_set_all_target_outputs(viewer ${OUTPUT_DIR})
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set_target_properties(viewer PROPERTIES CXX_VISIBILITY_PRESET hidden)
elseif(WIN32)
    set_target_properties(viewer PROPERTIES PREFIX "")
endif()

set(VIEWER_TEST_SORUCE
        src/test/cpp/main.cpp)

add_executable(viewer_test ${VIEWER_TEST_SORUCE})
target_link_libraries(viewer_test viewer)
target_compile_definitions(viewer_test PRIVATE DLL_EXPORT)
set_target_properties(viewer_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
