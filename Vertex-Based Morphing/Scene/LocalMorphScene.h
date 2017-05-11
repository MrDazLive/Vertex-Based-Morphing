#pragma once

#include <Engine\Scene\Scene.h>

class LocalMorphScene final : public Scene {
public:
    LocalMorphScene(const std::string&);
    ~LocalMorphScene() = default;

    void    OnOpen() final override;
    void    OnFocusEnter() final override;
    void    OnUpdate() final override;
    void    OnFocusLeave() final override;
    void    OnClose() final override;
private:
};