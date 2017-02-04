#pragma once

#include "../Utilities/Handler.h"

class Scene : public Handler<Scene> {
public:
	Scene(const std::string& name) : Handler<Scene>(this, name) {}
	~Scene() = default;

	void OnOpen() {}
	void OnFocusEnter() {}
	void OnFocusLeave() {}
	void OnClose() {}
protected:
};