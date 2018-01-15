cmake_minimum_required (VERSION 2.6)
project (fastint C)
set(CMAKE_CXX_STANDARD 14)

# Locate python package - note that you need have a matching bitness of python
find_package(PythonLibs 2.7 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

add_library(FASTINT_DLL SHARED main.c)
set_target_properties(FASTINT_DLL PROPERTIES OUTPUT_NAME "fastint")

# Python/C extension need to have .pyd extension
set_target_properties(FASTINT_DLL PROPERTIES SUFFIX ".pyd")

target_link_libraries(FASTINT_DLL ${PYTHON_LIBRARIES})
