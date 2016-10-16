#pragma once
#include "Vector3.h"

template<typename T>
class Matrix3
{
public:
	Matrix3()
	{
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++)
				m_Values[i * 3 + j] = &m_Components[i][j];
	}

	Vector3<T>& x = m_Components[0];
	Vector3<T>& y = m_Components[1];
	Vector3<T>& z = m_Components[2];

	T& m00 = m_Components[0][0];
	T& m01 = m_Components[0][1];
	T& m02 = m_Components[0][2];

	T& m10 = m_Components[1][0];
	T& m11 = m_Components[1][1];
	T& m12 = m_Components[1][2];

	T& m20 = m_Components[2][0];
	T& m21 = m_Components[2][1];
	T& m22 = m_Components[2][2];

	static Matrix3<T> CreateIdentity()
	{
		Matrix3<T> _matrix;

		for (size_t i = 0; i < 3; ++i)
			_matrix.m_Components[i][i] = 1;

		return _matrix;
	}

	static Matrix3<T> CreateScale(const T& _scale)
	{
		Matrix3<T> _matrix;

		for (size_t i = 0; i < 3; ++i)
			_matrix.m_Components[i][i] = _scale;

		return _matrix;
	}

	static Matrix3<T> CreateRotation(const T& _radians)
	{
		Matrix3<T> _matrix;

		_matrix.m00 = +cosf(_radians);
		_matrix.m01 = -sinf(_radians);
		_matrix.m11 = +sinf(_radians);
		_matrix.m12 = +cosf(_radians);

		return _matrix;
	}

	static Matrix3<T> CreateTranslation(const T& _x, const T& _y)
	{
		Matrix3 _matrix;

		_matrix.m20 = x;
		_matrix.m21 = y;

		return _matrix;
	}

	const T* GetPtr()
	{
		return m_Values;
	}

protected:
	Vector3<T> m_Components[3];

	T* m_Values[9];

};