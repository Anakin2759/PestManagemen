cmake_minimum_required(VERSION 3.15)
project(asio VERSION 1.36.0 LANGUAGES CXX)

# ASIO is a header-only library
add_library(asio INTERFACE)
add_library(asio::asio ALIAS asio)

# Set include directory
target_include_directories(asio INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ASIO requires C++11 or higher
target_compile_features(asio INTERFACE cxx_std_11)

# Define ASIO_STANDALONE to use ASIO without Boost
target_compile_definitions(asio INTERFACE
    ASIO_STANDALONE
    ASIO_HAS_STD_ADDRESSOF
    ASIO_HAS_STD_ARRAY
    ASIO_HAS_CSTDINT
    ASIO_HAS_STD_SHARED_PTR
    ASIO_HAS_STD_TYPE_TRAITS
)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(asio INTERFACE
        _WIN32_WINNT=0x0601  # Windows 7 or later
    )
    # Link with Windows socket library
    target_link_libraries(asio INTERFACE ws2_32 wsock32)
elseif(UNIX)
    # Link with pthread on Unix-like systems
    find_package(Threads REQUIRED)
    target_link_libraries(asio INTERFACE Threads::Threads)
endif()

# Optional: Installation rules
install(TARGETS asio
    EXPORT asioTargets
    INCLUDES DESTINATION include
)

install(DIRECTORY include/asio
    DESTINATION include
)

install(FILES include/asio.hpp
    DESTINATION include
)

install(EXPORT asioTargets
    FILE asioTargets.cmake
    NAMESPACE asio::
    DESTINATION lib/cmake/asio
)
