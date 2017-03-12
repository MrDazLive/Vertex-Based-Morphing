#pragma once

#include <Engine\Scene\Scene.h>

class UniformMorphScene final : public Scene {
public:
            UniformMorphScene   (const std::string&);
            ~UniformMorphScene  () = default;

    void    OnOpen              () final override;
    void    OnFocusEnter        () final override;
    void    OnUpdate            () final override;
    void    OnFocusLeave        () final override;
    void    OnClose             () final override;
private:
};