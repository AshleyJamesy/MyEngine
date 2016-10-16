#pragma once
#include <list>
#include "source\memath\Matrix4.h"

class Transform
{
	const unsigned int _MaxChildren = 50;

public:
	static Transform& Root()
	{
		return m_Root;
	}

	void Scale(float _scale)
	{
		m_Scale.m00 = m_Scale.m00 + _scale;
		m_Scale.m11 = m_Scale.m11 + _scale;
		m_Scale.m22 = m_Scale.m22 + _scale;
		m_Scale.m33 = m_Scale.m33 + _scale;
	}

	void SetScale(float _scale)
	{
		m_Scale.m00 = _scale;
		m_Scale.m11 = _scale;
		m_Scale.m22 = _scale;
		m_Scale.m33 = _scale;
	}

	void Translate(float _x, float _y, float _z)
	{
		m_Translation.m30 = m_Translation.m30 + _x;
		m_Translation.m31 = m_Translation.m31 + _y;
		m_Translation.m32 = m_Translation.m32 + _z;
	}

	void SetPosition(float _x, float _y, float _z)
	{
		m_Translation.m30 = _x;
		m_Translation.m31 = _y;
		m_Translation.m32 = _z;
	}

	void AddChild(Transform& _transform)
	{
		for each(Transform* child in m_Children)
			if (&_transform == child)
				return;

		(&_transform)->m_Parent = this;

		m_Children.push_back(&_transform);
	}

	void RemoveChild(Transform& _transform)
	{
		bool exists = false;

		for each(Transform* child in m_Children)
			if (&_transform == child)
			{
				exists = true;
				break;
			}

		(&_transform)->m_Parent = &m_Root;

		m_Children.remove(&_transform);
	}

	inline Matrix4<float>& GetLocal() { return m_Local; }
	inline Matrix4<float>& GetGlobal() { return m_Global; }

	inline const float* GetLocalPtr() { return m_Local.GetPtr(); }
	inline const float* GetGlobalPtr() { return m_Global.GetPtr(); }

	void Update()
	{
		m_Local =
			m_Scale *
			m_Rotation *
			m_Translation;

		if (m_Parent)
			m_Global = m_Parent->m_Global * m_Local;
		else
			m_Global = m_Local;

		for each (Transform* _child in m_Children)
			_child->Update();
	}
	
private:
	static Transform m_Root;

	Transform* m_Parent;
	std::list<Transform*> m_Children;

	Matrix4<float> m_Global;
	Matrix4<float> m_Local;

	Matrix4<float> m_Scale;
	Matrix4<float> m_Rotation;
	Matrix4<float> m_Translation;

};