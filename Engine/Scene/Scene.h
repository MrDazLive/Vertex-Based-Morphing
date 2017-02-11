#pragma once

#include <Utilities\BaseClass\Handler.h>

class GameObject;

class Scene : public Handler<Scene> {
public:
					Scene			(const std::string&);
					~Scene			() = default;

	virtual void	OnOpen			();
	virtual void	OnFocusEnter	();
	virtual void	OnUpdate		();
	virtual void	OnFocusLeave	();
	virtual void	OnClose			();
protected:
	void			AddGameObject	(GameObject* const);
private:
	std::vector<GameObject*> m_gameObject;
};