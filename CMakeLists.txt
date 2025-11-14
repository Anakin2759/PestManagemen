cmake_minimum_required(VERSION 3.15)
project(PestManagement LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure MSVC treats source files as UTF-8 so non-ASCII filenames work correctly.
if (MSVC)
	add_compile_options(/utf-8)
endif()

# Source files (explicitly list files with non-ASCII names)
set(SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/º¦³æ.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/createº¦³æ.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Optional: install rule
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

