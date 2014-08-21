#pragma once

#include "sys/RenderWindow.hpp"
#include "sys/System.hpp"
#include "level/Level.hpp"
#include "sys/TCPSocket.hpp"
#include "entity/Player.hpp"
#include "Config.hpp"

class Game {
public:
    /// @brief Initialize the resources, player and level
    Game(Config const &cfg);
    /// @brief Free resources to avoid memory leaks n shit
    ~Game();
    /// @brief Game loop.
    void exec();
    /// @brief Get the active game instance
    static Game &get();
    /// @brief Get the window on which things are rendered.
    sys::RenderWindow &getWindow();
    /// @brief Join a game server.
    void joinServer(std::string host);

private:
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    sys::System m_system;
    sys::RenderWindow m_window;
    net::TCPSocket m_socket;
    Level m_level;
    Player *m_player;
    Config const &m_cfg;
};
