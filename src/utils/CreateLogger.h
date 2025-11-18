#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <filesystem>

std::shared_ptr<spdlog::logger> createRollingLogger()
{
    std::filesystem::create_directories("logs");

    // 创建循环日志：每个文件最大5MB，保留3个文件（总共约15MB）
    auto logger = spdlog::rotating_logger_mt("game_logger",
                                             "logs/debug.log",
                                             1024 * 1024 * 5, // 5MB
                                             3                // 保留3个文件
    );

    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
    logger->set_level(spdlog::level::debug);
    logger->flush_on(spdlog::level::info);

    spdlog::info("Rolling logger initialized (5MB per file, keep 3 files)");

    return logger;
}