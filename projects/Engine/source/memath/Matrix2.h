#pragma once
#include "Vector2.h"

template<typename T>
class Matrix2
{
public:
	Vector2<T>& x = m_Components[0];
	Vector2<T>& y = m_Components[1];

	T& m00 = m_Components[0][0];
	T& m01 = m_Components[0][1];

	T& m10 = m_Components[1][0];
	T& m11 = m_Components[1][1];

protected:
	Vector2<T> m_Components[2];

};