#pragma once

#include "../Utilities/Handler.h"

class GameObject;

class Scene : public Handler<Scene> {
public:
					Scene			(const std::string&);
					~Scene			() = default;

			void	OnUpdate		();

	virtual void	OnOpen			() {}
	virtual void	OnFocusEnter	() {}
	virtual void	OnFocusLeave	() {}
	virtual void	OnClose			() {}
protected:
	void			AddGameObject	(GameObject* const);
private:
	std::vector<GameObject*> m_gameObject;
};