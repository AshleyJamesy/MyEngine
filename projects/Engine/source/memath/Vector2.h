#pragma once
#include "Vector.h"

template<typename T>
class Vector2 : public Vector<T, 2>
{
public:
	T& x = m_Values[0];
	T& y = m_Values[1];

	const Vector2 operator + (const Vector2& _vector)
	{
		Vector2 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] + _vector.m_Values[i];

		return _new;
	}

	const Vector2 operator - (const Vector2& _vector)
	{
		Vector2 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] - _vector.m_Values[i];

		return _new;
	}

	const Vector2 operator * (const Vector2& _vector)
	{
		Vector2 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] * _vector.m_Values[i];

		return _new;
	}

	const Vector2 operator / (const Vector2& _vector)
	{
		Vector2 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] / _vector.m_Values[i];

		return _new;
	}

	Vector2 Normalised()
	{
		Vector2 _vector;

		T _magnitude = Magnitude();

		for (size_t i = 0; i < Size(); ++i)
			_vector.m_Values[i] = m_Values[i] / _magnitude;

		return _vector;
	}

private:

};

typedef Vector2<float> Vector2f;