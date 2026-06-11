cmake_minimum_required ( VERSION 3.10)
project (sfml)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS "-g")

FILE(GLOB MyCSources ./src/*.cpp ./src/*.cc)
set(SOURCE_FILES ${MyCSources})


if (DEFINED ENV{LOADEDMODULES} AND (" $ENV{LOADEDMODULES}" MATCHES ".* prog/gcc /6.1.0.*"))
set(CMAKE_CXX_COMPILER /sw/gcc -6.1.0/ bin/g++)
if (DEFINED ENV{SFML_ROOT})
list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/ share/SFML/cmake/ Modules ")
endif()
endif()

set(SFML_MODULES network graphics window system )

find_package (SFML 2 COMPONENTS ${SFML_MODULES})
include_directories (${SFML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
if (NOT (${SFML_FOUND} STREQUAL "TRUE "))
set(SFML_LIBRARIES "")
foreach (i ${SFML_MODULES})
list(APPEND SFML_LIBRARIES "sfml-${i}")
endforeach(i)
endif()

add_executable(sfml ${SOURCE_FILES})

target_link_libraries(sfml ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
