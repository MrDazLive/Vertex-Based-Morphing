#pragma once

#include <vector>
#include <glm\glm.hpp>

class Program;
class Material;
class Geometry;
class Perspective;
class MorphGeometry;

class Renderer final {
public:
    static void             Initialise          (int*, char*[]);
    static void             Loop                ();
    static void             Quit                ();

    static void             DrawRequest         (const unsigned int, const unsigned int, const glm::mat4&);
    static void             MorphDrawRequest    (const unsigned int, const unsigned int, const glm::mat4&);
    static Material* const  CreateMaterial      (const std::string&);

    static void             ConfirmMorphSets    ();
private:

                            Renderer            () = delete;
                            ~Renderer           ();

    int static              m_window;

    static Geometry*                m_geometry;
    static MorphGeometry*           m_morphGeometry;
    static Perspective*             m_perspective;
    static std::vector<Program*>    m_program;
    static std::vector<Material*>   m_material;
};