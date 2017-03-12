#pragma once

#include "Geometry.h"

class MorphGeometry final : public Geometry{
public:
            MorphGeometry   () = default;
            ~MorphGeometry  () = default;

    void    FillBuffers     () final override;
    void    BuildArray      () final override;

    void    Draw            () final override;
    void    DrawRequest     (const unsigned int, const unsigned int, const glm::mat4&) final override;
private:
    std::unordered_map<unsigned int, std::map<unsigned int, std::map<unsigned int, std::vector<Instance>>>> m_commandList;
};