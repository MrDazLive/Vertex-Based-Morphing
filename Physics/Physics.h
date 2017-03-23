#pragma once

#include <vector>
#include <glm\glm.hpp>
#include <unordered_map>

struct RayHit;

class Physics final {
public:
    static void         Initialise  (int*, char*[]);
    static void         Loop        ();
    static void         Quit        ();

    static void         AddCollider(const unsigned int, const glm::mat4&);
    static bool         Raycast(const glm::vec3&, const glm::vec3&);
    static bool         Raycast(const glm::vec3&, const glm::vec3&, RayHit* const);
private:
                        Physics     () = delete;

    static std::unordered_map<unsigned int, std::vector<glm::mat4>>     m_colliders;
};