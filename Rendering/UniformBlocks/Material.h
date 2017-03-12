#pragma once

#include "UniformBlock.h"

#include <algorithm>
#include <glm\glm.hpp>

class Material final : public UniformBlock<Material> {
    friend class UniformBlock<Material>;
public:
                            Material        (const std::string&);
                            ~Material       () = default;

    const unsigned int      getShader       () const;
    const glm::vec3         getColour       () const;
    const float             getMorph        () const;

    void                    setShader       (const std::string&);
    void                    setColour       (const glm::vec3&);
    void                    setMorph        (const float&);

    void                    slideMorph      (const float&);
protected:
    void                    BuildBlock      (float* const) final override;

    unsigned int            m_shader        { 0 };
    glm::vec3               m_colour        { 1.0f, 1.0f, 1.0f };
    float                   m_morph         { 0.0f };
};