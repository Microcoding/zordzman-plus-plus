#pragma once

#include <string>

namespace client {

/// The configuration structure that holds
///  different config variables.
struct Config {
    std::string host = "127.0.0.1"; // localhost doesn't work
    int port = 4544;

    std::string name = "SneakySnake";
};
} // namespace client
