#include "log.h"
#include <iostream>
#include <string>
#include <mutex>
#include <ctime>
#include <string_view>

namespace {
    [[nodiscard]] constexpr std::string_view severity_label(log_type type) noexcept {
        using enum log_type;

        switch (type) {
            case info:
                return "INFO";
            case error:
                return "ERRO";
            case warning:
                return "WARN";
            case debug:
                return "DEBG";
        }

        return "UNKO"; //Short for "unknown"
    }

    [[nodiscard]] constexpr std::string_view end_color() noexcept {
        return "\033[0m";
    }

    [[nodiscard]] constexpr std::string_view color(log_type type) noexcept {
        using enum log_type;

        switch (type) {
            case info:
                return "\033[34m";
            case error:
                return "\033[31m";
            case warning:
                return "\033[33m";
            case debug:
                return "\033[90m";
        }

        return "";
    }

    [[nodiscard]] std::tm get_local_time(std::time_t timestamp)
    {
        std::tm result{};
        localtime_r(&timestamp, &result);

        return result;
    }
}

void log(std::string_view message, log_type type) {
    static std::mutex mtx;

    std::time_t now = std::time(nullptr); //Gets the current time. Pointer is "null" so it stores the result to the object: https://cplusplus.com/reference/ctime/time/
    std::tm local_time = get_local_time(now);

    char time_buffer[16];
    std::size_t written = std::strftime(
        time_buffer,
        sizeof(time_buffer),
        "%I:%M:%S %p",
        &local_time
    );

    std::string_view time_text = (written > 0) ? std::string_view(time_buffer, written) : "??:??:?? ??";

    std::scoped_lock lock(mtx);

    std::ostream* out = &std::cout;
    *out << time_text;
    *out << ' ';
    *out << color(type);
    *out << severity_label(type);
    *out << end_color();
    *out << ' ';
    *out << message;
    *out << "\n";

    if (type == log_type::error) {
        *out << std::flush;
    }
}