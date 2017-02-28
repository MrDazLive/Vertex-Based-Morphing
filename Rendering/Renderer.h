#pragma once

#include <vector>
#include <glm\glm.hpp>

class Program;
class Geometry;
class Perspective;

class Renderer final {
public:
    static void     Initialise      (int*, char*[]);
    static void     Loop            ();
    static void     Quit            ();

    static void     DrawRequest     (const unsigned int, const unsigned int, const glm::mat4&);
private:

                    Renderer        () = delete;
                    ~Renderer       ();

    int static      m_window;

    static Geometry*                m_geometry;
    static Perspective*             m_perspective;
    static std::vector<Program*>    m_program;
};
