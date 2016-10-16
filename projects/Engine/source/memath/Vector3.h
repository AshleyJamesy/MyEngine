#pragma once
#include "Vector.h"

template<typename T>
class Vector3 : public Vector<T, 3>
{
public:
	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	T& x = m_Values[0];
	T& y = m_Values[1];
	T& z = m_Values[2];

	Vector3 Normalised()
	{
		Vector3 _vector;

		T _magnitude = Magnitude();

		for (size_t i = 0; i < Size(); ++i)
			_vector.m_Values[i] = m_Values[i] / _magnitude;

		return _vector;
	}

	const Vector3 operator + (const Vector3& _vector)
	{
		Vector3 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] + _vector.m_Values[i];

		return _new;
	}

	const Vector3 operator - (const Vector3& _vector)
	{
		Vector3 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] - _vector.m_Values[i];

		return _new;
	}

	const Vector3 operator * (const Vector3& _vector)
	{
		Vector3 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] * _vector.m_Values[i];

		return _new;
	}

	const Vector3 operator / (const Vector3& _vector)
	{
		Vector3 _new;

		for (size_t i = 0; i < Size(); i++)
			_new.m_Values[i] = m_Values[i] / _vector.m_Values[i];

		return _new;
	}

private:

};

typedef Vector3<float> Vector3f;