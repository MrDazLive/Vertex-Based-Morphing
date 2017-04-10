#include "Image.h"

#include <Utilities\Helper\lodepng.h>

const unsigned int Image::getWidth() const {
    return m_width;
}

const unsigned int Image::getHeight() const {
    return m_height;
}

unsigned char* const Image::getData() {
    return m_data.data();
}

bool Image::LoadFromFile(const std::string& file) {
    return lodepng::decode(m_data, m_width, m_height, file) == 0;
}