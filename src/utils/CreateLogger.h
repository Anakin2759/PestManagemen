#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>
#include <spdlog/sinks/rotating_file_sink.h>
#include <filesystem>

inline std::shared_ptr<spdlog::logger> CreateRollingLogger()
{
    std::filesystem::create_directories("logs");


    auto logger = spdlog::rotating_logger_mt("game_logger",
                                             "logs/debug.log",
                                             static_cast<size_t>(1024 * 1024 * 5), // 5MB
                                             1                                     // 保留3个文件
    );

    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::info);

    spdlog::info("Rolling logger initialized (5MB per file, keep 3 files)");

    return logger;
}