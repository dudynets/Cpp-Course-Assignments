cmake_minimum_required(VERSION 3.24)
project(programming_2022)

set(CMAKE_CXX_STANDARD 17)

# Homeworks
file(GLOB_RECURSE homeworks "src/homeworks/*")
foreach (homework ${homeworks})
    get_filename_component(homework_ext ${homework} EXT)
    if (NOT ${homework_ext} STREQUAL ".cpp")
        continue()
    endif ()
    get_filename_component(homework_name ${homework} NAME)
    string(REPLACE ".cpp" "" homework_name ${homework_name})
    add_executable(${homework_name} ${homework})
endforeach ()

# Classworks
file(GLOB_RECURSE classworks "src/classworks/*")
foreach (classwork ${classworks})
    get_filename_component(classwork_ext ${classwork} EXT)
    if (NOT ${classwork_ext} STREQUAL ".cpp")
        continue()
    endif ()
    get_filename_component(classwork_name ${classwork} NAME)
    string(REPLACE ".cpp" "" classwork_name ${classwork_name})
    set(executable_name "classwork_${classwork_name}")
    add_executable(${executable_name} ${classwork})
endforeach ()

# Projects
file(GLOB_RECURSE projects "src/projects/*")
foreach (project ${projects})
    get_filename_component(project_ext ${project} EXT)
    if (NOT ${project_ext} STREQUAL ".cpp")
        continue()
    endif ()
    get_filename_component(project_name ${project} NAME)
    string(REPLACE ".cpp" "" project_name ${project_name})
    set(executable_name "project_${project_name}")
    add_executable(${executable_name} ${project})
endforeach ()

# Tests
file(GLOB_RECURSE tests "src/tests/*")
foreach (test ${tests})
    get_filename_component(test_ext ${test} EXT)
    if (NOT ${test_ext} STREQUAL ".cpp")
        continue()
    endif ()
    get_filename_component(test_name ${test} NAME)
    string(REPLACE ".cpp" "" test_name ${test_name})
    set(executable_name "test_${test_name}")
    add_executable(${executable_name} ${test})
endforeach ()

# Shared libraries
include_directories(shared)
