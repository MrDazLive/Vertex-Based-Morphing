#pragma once

#include <vector>

class Image {
public:
                                Image           () = default;
                                ~Image          () = default;

    const unsigned int          getWidth        () const;
    const unsigned int          getHeight       () const;
    unsigned char* const        getData         ();

    bool                        LoadFromFile    (const std::string&);
private:
    std::vector<unsigned char>  m_data;
    unsigned int                m_width         { 0 };
    unsigned int                m_height        { 0 };
};