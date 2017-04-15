#pragma once

#include <glm\vec3.hpp>

#include <Engine\Scene\GameObject\Component.h>

class MorphSet;

class PointMorph final : public BaseComponent<PointMorph> {
public:
                            PointMorph      (GameObject* const);
                            ~PointMorph     () = default;

    float const             getRange        () const;
    float const             getWeight       () const;

    void                    setRange        (const float);
    void                    setWeight       (const float);

    void                    OnStart         () override final;
    void                    OnUpdate        () override final;
private:
    using Neighbour = std::vector<unsigned int>;

    void Distribute(const unsigned int, const float, std::vector<float>&, const glm::vec3&);

    std::vector<Neighbour>  m_neighbours;
    const glm::vec3*        m_positions     { nullptr };
    const unsigned int*     m_elements      { nullptr };
    MorphSet*               m_morphSet      { nullptr };
    float                   m_morphWeight   { 1.0f };
    float                   m_morphRange    { 1.0f };
};