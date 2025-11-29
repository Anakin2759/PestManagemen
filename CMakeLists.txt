cmake_minimum_required(VERSION 4.0)
project(PestMan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #生成compile_commands.json文件
set(CMAKE_CXX_EXTENSIONS OFF)


# Optionally enable clang-tidy static analysis. Can be overridden by passing
# -DENABLE_CLANG_TIDY=OFF to CMake command line.
option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis" ON)

# Try to locate clang-tidy (check several common names)
find_program(CLANG_TIDY_EXE
    NAMES clang-tidy
)


if (ENABLE_CLANG_TIDY)
    if (CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        # Default checks can be customized by setting CLANG_TIDY_OPTIONS
        set(CLANG_TIDY_OPTIONS "--checks=*,-clang-analyzer-alpha*")
        # Apply globally so all targets are analyzed; users can override with
        # -DCMAKE_CXX_CLANG_TIDY="<path>;[options]"
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};${CLANG_TIDY_OPTIONS}")
    else()
        message(STATUS "ENABLE_CLANG_TIDY is ON but clang-tidy executable not found.")
        message(STATUS "Install clang-tidy or set CLANG_TIDY_EXE to its path to enable.")
    endif()
else()
    message(STATUS "clang-tidy integration disabled (ENABLE_CLANG_TIDY=OFF)")
endif()

set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

add_subdirectory(third_party/mimalloc)
add_subdirectory(third_party/entt)
add_subdirectory(third_party/json)
add_subdirectory(third_party/spdlog)
add_subdirectory(third_party/asio)
add_subdirectory(third_party/SDL)
add_subdirectory(third_party/imgui)
add_subdirectory(third_party/abseil-cpp)



set(EXET_NAME PestManKill)
add_executable(${EXET_NAME} ${SOURCES})

target_compile_options(${EXET_NAME} PRIVATE
    # GCC
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Debug>>:-Wall -Wextra -Wpedantic -O0 -g>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-Wall -O3 -DNDEBUG>

    # Clang
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-Wall -Wextra -Wpedantic -O0 -g>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:-Wall -O3 -DNDEBUG>

    # MSVC
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/W4 /Od /Zi>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2 /DNDEBUG>
)
target_include_directories(${EXET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



target_link_libraries(${EXET_NAME} PRIVATE mimalloc-static asio::asio spdlog::spdlog_header_only  SDL3::SDL3 imgui::imgui  EnTT::EnTT nlohmann_json::nlohmann_json absl::base absl::memory absl::strings)

# Optional: install rule
install(TARGETS ${EXET_NAME} 
    RUNTIME DESTINATION bin
)

