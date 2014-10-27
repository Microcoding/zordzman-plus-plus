#include "System.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <stdexcept>

#include "format.h"

namespace client {
namespace sys {

System::System() {
#define INIT_OR_THROW(cond, ...)                                               \
    if (!(cond)) {                                                             \
        throw std::runtime_error(fmt::format(__VA_ARGS__));                    \
    }

#define AUDIO_RATE 44100
#define AUDIO_FORMAT AUDIO_S16SYS
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFERS 4096

    INIT_OR_THROW(SDL_Init(SDL_INIT_EVERYTHING) == 0,
                  "Failed to initialize SDL: {}", SDL_GetError());
    INIT_OR_THROW(IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG,
                  "Failed to initialize SDL_image: {}", IMG_GetError());
    INIT_OR_THROW(SDLNet_Init() != -1, "Failed to initialize SDL_net: {}",
                  SDLNet_GetError());
    INIT_OR_THROW(Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS,
                  AUDIO_BUFFERS) > -1, "Failed to initialize SDL_mixer: {}",
                  Mix_GetError());

#undef INIT_OR_THROW
}

System::~System() {
    SDLNet_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
}
}
