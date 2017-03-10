#include "Renderer.h"

#include "ShaderProgram\Shader.h"
#include "ShaderProgram\Program.h"
#include "Geometry\Geometry.h"
#include "Geometry\MorphGeometry.h"
#include "Camera\Camera.h"

#include "UniformBlocks\Material.h"
#include "UniformBlocks\Perspective.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GL\glut.h>

int Renderer::m_window = 0;

RenderMode Renderer::m_renderMode = RenderMode::SHADED;

Geometry* Renderer::m_geometry = nullptr;
MorphGeometry* Renderer::m_morphGeometry = nullptr;
Perspective* Renderer::m_perspective = nullptr;
std::vector<Program*> Renderer::m_program;
std::vector<Material*> Renderer::m_material;

Renderer::~Renderer() {
    Renderer::Quit();
}

void Renderer::Initialise(int* argc, char* argv[]) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1080, 720);
    m_window = glutCreateWindow("Vertex-Based Rendering");

    glewInit();
    glClearColor(0.0f, 0.0f, 0.25f, 0.0f);

    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    m_geometry = new Geometry();
    m_geometry->FillBuffers();
    m_geometry->BuildArray();

    Program* def = new Program("Default");
    m_program.push_back(def);

    Shader r_vs(GL_VERTEX_SHADER);
    Shader r_fs(GL_FRAGMENT_SHADER);

    r_vs.LoadFromFile("Resource/Shader/default.vs");
    r_fs.LoadFromFile("Resource/Shader/default.fs");

    def->AddShader(&r_vs, &r_fs);
    def->Link();

    Program* blue = new Program("Default_Morph");
    m_program.push_back(blue);

    Shader b_vs(GL_VERTEX_SHADER);
    Shader b_fs(GL_FRAGMENT_SHADER);

    b_vs.LoadFromFile("Resource/Shader/default_morph.vs");
    b_fs.LoadFromFile("Resource/Shader/default_morph.fs");

    blue->AddShader(&b_vs, &b_fs);
    blue->Link();

    m_perspective = new Perspective("Main");

    Perspective::BindBlock("Block_Perspective", def, blue);

    CreateMaterial("Default")->setShader("Default");
    CreateMaterial("Default_Morph")->setShader("Default_Morph");
    Material::BindBlock("Block_Material", def, blue);

    const float aspectRatio = 1080.0f / 720.0f;
    glm::mat4 projection = glm::perspective(1.31f, aspectRatio, 1.0f, 1000.0f);
    m_perspective->setProjection(projection);

    Program::Reset();
}

void Renderer::Loop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_perspective->setView(Camera::ViewMatrix());
    Perspective::BufferBlock();
    Material::BufferBlock();

    m_geometry->Draw();
    m_morphGeometry->Draw();
    
    VertexArray::Reset();
    Program::Reset();

    glutSwapBuffers();
}

void Renderer::Quit() {
    glutDestroyWindow(m_window);

    delete m_geometry;
    m_geometry = nullptr;
    delete m_morphGeometry;
    m_morphGeometry = nullptr;
    delete m_perspective;
    m_perspective = nullptr;
    delete[] m_program.data();
    m_program.clear();
    delete[] m_material.data();
    m_material.clear();
}

const RenderMode Renderer::getRenderMode() {
    return m_renderMode;
}

void Renderer::setRenderMode(const RenderMode& mode) {
    m_renderMode = mode;
	glPolygonMode(GL_FRONT_AND_BACK, m_renderMode == RenderMode::SHADED ? GL_FILL : GL_LINE);
}

void Renderer::DrawRequest(const unsigned int mesh, const unsigned int material, const glm::mat4& transform) {
    m_geometry->DrawRequest(mesh, material, transform);
}

void Renderer::MorphDrawRequest(const unsigned int morphSet, const unsigned int material, const glm::mat4& transform) {
    m_morphGeometry->DrawRequest(morphSet, material, transform);
}

Material* const Renderer::CreateMaterial(const std::string& name) {
    Material* material = new Material(name);
    m_material.push_back(material);
    return material;
}

void Renderer::ConfirmMorphSets() {
    m_morphGeometry = new MorphGeometry();
    m_morphGeometry->FillBuffers();
    m_morphGeometry->BuildArray();
}