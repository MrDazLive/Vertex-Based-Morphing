#pragma once

#include <vector>

class Scene;

class Engine final {
public:
    static void     Initialise      (int*, char*[]);
    static void     Loop            ();
    static void     Quit            ();

    static void     OpenScene       (const std::string&);
    static void     SwapScene       (const std::string&, const unsigned int = 0);
    static void     ReloadScene     ();
    static void     CloseScene      ();
private:
                    Engine          () = delete;

    static void     IdleUpdate      ();
    static void     DisplayUpdate   ();

    static void     ResumeScene     ();
    static void     SuspendScene    ();

    static Scene*   getCurrentScene ();

    static std::vector<Scene*>  m_activeScene;
};