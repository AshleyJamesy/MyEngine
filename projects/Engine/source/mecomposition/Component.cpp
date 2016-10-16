#include "Component.h"

GameObject& Component::SetGameObject(GameObject* _gameObject)
{
	m_Parent = _gameObject;

	return *_gameObject;
}

GameObject& Component::GetGameObject()
{
	return *m_Parent;
}