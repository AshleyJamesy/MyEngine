#pragma once
#include "Vector.h"

template<typename T>
class Vector4 : public Vector<T, 4>
{
public:
	T& x = m_Values[0];
	T& y = m_Values[1];
	T& z = m_Values[2];
	T& w = m_Values[3];

	Vector4 Normalised()
	{
		Vector4 _vector;

		T _magnitude = Magnitude();

		for (size_t i = 0; i < Size(); ++i)
			_vector.m_Values[i] = m_Values[i] / _magnitude;

		return _vector;
	}

	const Vector4 operator + (const Vector4& _vector)
	{
		Vector4 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] + _vector.m_Values[i];

		return _new;
	}

	const Vector4 operator - (const Vector4& _vector)
	{
		Vector4 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] - _vector.m_Values[i];

		return _new;
	}

	const Vector4 operator * (const Vector4& _vector)
	{
		Vector4 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] * _vector.m_Values[i];

		return _new;
	}

	const Vector4 operator / (const Vector4& _vector)
	{
		Vector4 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] / _vector.m_Values[i];

		return _new;
	}

private:

};

typedef Vector4<float> Vector4f;