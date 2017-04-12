#pragma once

#include <vector>
#include <glm\glm.hpp>

#include "Enumerators\RenderMode.h"

class Image;
class Program;
class Texture;
class Material;
class Geometry;
class Perspective;
class MorphGeometry;

class Renderer final {
public:
    static void             Initialise          (int*, char*[]);
    static void             Loop                ();
    static void             Quit                ();

    static const RenderMode getRenderMode       ();

    static void             setRenderMode       (const RenderMode&);

    static void             DrawRequest         (const unsigned int, const unsigned int, const glm::mat4&);
    static void             MorphDrawRequest    (const unsigned int, const unsigned int, const glm::mat4&);
    static Material* const  CreateMaterial      (const std::string&);
    static Texture* const   CreateTexture       (const std::string&, Image* const);

    static void             ConfirmMorphSets    ();
private:
                            Renderer            () = delete;
                            ~Renderer           ();

    static int              m_window;

    static RenderMode       m_renderMode;

    static Geometry*                m_geometry;
    static MorphGeometry*           m_morphGeometry;
    static Perspective*             m_perspective;
    static std::vector<Program*>    m_program;
    static std::vector<Material*>   m_material;
    static std::vector<Texture*>    m_texture;
};