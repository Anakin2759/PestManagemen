cmake_minimum_required(VERSION 3.15)
project(PestMan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)
add_subdirectory(third_party/entt)
add_subdirectory(third_party/json)

set(EXET_NAME PestManKill)
add_executable(${EXET_NAME} ${SOURCES})
target_include_directories(${EXET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)


target_link_libraries(${EXET_NAME} PRIVATE entt Qt6::Core Qt6::Widgets)

# Optional: install rule
install(TARGETS ${EXET_NAME} RUNTIME DESTINATION bin)

