#pragma once

#include <glm\gtc\matrix_transform.hpp>

class Camera final {
public:
    static const void           Target      (const glm::vec3&);
    static const void           Translate   (const glm::vec3&);

    static const glm::vec3&     Position    ();
    static const glm::vec3      Direction   ();
    static const glm::mat4      ViewMatrix  ();
private:
                                Camera      () = delete;
                                ~Camera     () = delete;

    static glm::vec3            m_position;
    static glm::vec3            m_target;
};