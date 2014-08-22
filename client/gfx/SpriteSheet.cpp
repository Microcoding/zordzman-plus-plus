#include "SpriteSheet.hpp"

unsigned int SpriteSheet::getSpriteSize() const { return m_spriteSize; }

SpriteSheet::SpriteSheet(std::string const &filename, unsigned int spriteSize)
    : Texture(filename), m_spriteSize(spriteSize) {}

void SpriteSheet::setSpriteSize(unsigned int size) { m_spriteSize = size; }