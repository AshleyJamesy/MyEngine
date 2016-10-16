#pragma once
#include "Component.h"

class Camera : public Component
{
public:
	float m_FieldOfView = 60.0f;
	float m_Distance	= 1000.0f;
	
	Matrix4<float> GetView()
	{
		return GetGameObject().GetTransform().GetGlobal();
	}

	void Render();

private:
	Matrix4<float> m_Perspective = 
		Matrix4<float>::CreatePerspective(m_FieldOfView, 1.0f, 0.1f, m_Distance);

};