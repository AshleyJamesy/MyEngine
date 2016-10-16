#pragma once
#include "source\memath\Vector2.h"
#include "source\memath\Vector3.h"
#include "source\memath\Vector4.h"
#include "source\memath\Matrix2.h"
#include "source\memath\Matrix3.h"
#include "source\memath\Matrix4.h"

#include "GameObject.h"

class GameObject;

class Component
{
	friend class GameObject;

public:
	bool m_Enabled;

	GameObject& SetGameObject(GameObject* _gameObject);
	GameObject& GetGameObject();

protected:
	virtual void Start()	{};
	virtual void Update()	{};
	virtual void Render()	{};

private:
	GameObject* m_Parent;

};