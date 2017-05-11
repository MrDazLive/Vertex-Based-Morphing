#pragma once

#include <Engine\Scene\Scene.h>

class LocalMorphScene2 final : public Scene {
public:
    LocalMorphScene2(const std::string&);
    ~LocalMorphScene2() = default;

    void    OnOpen() final override;
    void    OnFocusEnter() final override;
    void    OnUpdate() final override;
    void    OnFocusLeave() final override;
    void    OnClose() final override;
private:
};