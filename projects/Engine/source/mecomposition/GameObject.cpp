#include "GameObject.h"
#include "Component.h"

void GameObject::Start()
{
	for (auto _component : m_Components)
		if (_component)
			if (_component->m_Enabled)
				_component->Start();
}

void GameObject::Update()
{
	for (auto _component : m_Components)
		if (_component)
			if(_component->m_Enabled)
				_component->Update();
}

void GameObject::Render()
{
	for (auto _component : m_Components)
		if (_component)
			if (_component->m_Enabled)
				_component->Render();
}
