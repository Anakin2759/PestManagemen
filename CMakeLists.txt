cmake_minimum_required(VERSION 3.15)
project(PestMan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Source files (explicitly list files with non-ASCII names)
set(SOURCES

)
add_subdirectory(third_party/entt)

set(EXET_NAME PestManKill)
add_executable(${EXET_NAME} ${SOURCES})
target_include_directories(${EXET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(${EXET_NAME} PRIVATE entt)

# Optional: install rule
install(TARGETS ${EXET_NAME} RUNTIME DESTINATION bin)

