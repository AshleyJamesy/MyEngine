#pragma once
#include <vector>
#include "source\memath\Vector2.h"
#include "source\memath\Vector3.h"
#include "source\memath\Vector4.h"
#include "source\memath\Matrix2.h"
#include "source\memath\Matrix3.h"
#include "source\memath\Matrix4.h"
#include "source\metypes\Transform.h"

class Component;

class GameObject
{
public:
	template<typename T>
	T& AddComponent();

	template<typename T>
	T* GetComponent();

	template<typename T>
	void RemoveComponent();

	void Start();

	void Update();

	void Render();

	Transform& GetTransform()
	{
		return m_Transform;
	}

private:
	Transform m_Transform;

	std::vector<Component*> m_Components;

};

template<typename T>
inline T& GameObject::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit type 'Component'");

	for (auto _component : m_Components)
		if (T* _type = dynamic_cast<T*>(_component))
			return *_type;

	T* _component = new T();

	((Component*) _component)->SetGameObject(this);

	m_Components.push_back(_component);

	return *_component;
}

template<typename T>
inline T* GameObject::GetComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit type 'Component'");

	for (auto _component : m_Components)
		if (T* _type = dynamic_cast<T*>(_component))
			return _type;

	return nullptr;
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit type 'Component'");

	T* _item = nullptr;
	for (auto _component : m_Components)
		if (T* _type = dynamic_cast<T*>(_component))
		{
			_item = _type;
			break;
		}

	if (_item)
	{
		auto _find =
			std::find(m_Components.begin(), m_Components.end(), _item);

		m_Components.erase(_find);

		delete _item;
	}
}