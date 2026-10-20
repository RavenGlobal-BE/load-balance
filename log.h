#ifndef RAVENBALANCER_LOG_H
#define RAVENBALANCER_LOG_H
#include <string_view>

enum class log_type {info, debug, warning, error};

// Prints a message to the with it's appropriate warning tags in the terminal.
void log(std::string_view message, log_type type);

#endif //RAVENBALANCER_LOG_H
