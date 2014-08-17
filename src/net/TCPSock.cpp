#include "net/Net.hpp"

using namespace net;

namespace net {
bool TCPSock::connectToHost(std::string host, int portnum) {
    if (SDLNet_ResolveHost(&m_server, host.c_str(), portnum) < 0) {
        fprintf(stderr, "[ERROR] SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        fprintf(stderr, "[ERROR] Could not resolve host %s\n", host.c_str());
        return false;
    }

    if (!(m_socket = SDLNet_TCP_Open(&m_server))) {
        fprintf(stderr, "[ERROR] SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        fprintf(stderr, "[ERROR] Could not open socket\n");
        return false;
    }
    m_open = true;
    return true;
}

void TCPSock::startReading() {
}

bool TCPSock::send(std::string buf) {
    buf += "\r\n";
    int len = strlen(buf.c_str()) + 1;
    if (SDLNet_TCP_Send(m_socket, (void*) buf.c_str(), len) < len) {
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        return false;
    }

    printf("Message: %s", buf.c_str());
    return true;
}

void TCPSock::close() {
    if (m_open) {
        SDLNet_TCP_Close(m_socket);
        m_open = false;
    }
}

TCPSock::~TCPSock() {
    close();
}
} // namespace net