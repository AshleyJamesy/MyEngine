#pragma once
#include "Vector4.h"

template<typename T>
class Matrix4
{
public:
	Matrix4()
	{
		SetValues();
	}

	Matrix4(const T& _scale)
	{
		SetValues();

		for (size_t i = 0; i < 4; ++i)
			m_Components[i][i] = _scale;
	}

	Vector4<T>& x = m_Components[0];
	Vector4<T>& y = m_Components[1];
	Vector4<T>& z = m_Components[2];
	Vector4<T>& w = m_Components[3];

	T& m00 = m_Components[0][0];
	T& m01 = m_Components[0][1];
	T& m02 = m_Components[0][2];
	T& m03 = m_Components[0][3];

	T& m10 = m_Components[1][0];
	T& m11 = m_Components[1][1];
	T& m12 = m_Components[1][2];
	T& m13 = m_Components[1][3];

	T& m20 = m_Components[2][0];
	T& m21 = m_Components[2][1];
	T& m22 = m_Components[2][2];
	T& m23 = m_Components[2][3];

	T& m30 = m_Components[3][0];
	T& m31 = m_Components[3][1];
	T& m32 = m_Components[3][2];
	T& m33 = m_Components[3][3];

	void operator = (const Matrix4<T>& _matrix)
	{
		m00 = _matrix.m00;
		m01 = _matrix.m01;
		m02 = _matrix.m02;
		m03 = _matrix.m03;
		m10 = _matrix.m10;
		m11 = _matrix.m11;
		m12 = _matrix.m12;
		m13 = _matrix.m13;
		m20 = _matrix.m20;
		m21 = _matrix.m21;
		m22 = _matrix.m22;
		m23 = _matrix.m23;
		m30 = _matrix.m30;
		m31 = _matrix.m31;
		m32 = _matrix.m32;
		m33 = _matrix.m33;		
	}

	Matrix4<T> operator + (const Matrix4<T>& _matrix)
	{
		Matrix4<T> _result;

		_result.m00 = _result.m00 + _matrix.m00;
		_result.m01 = _result.m01 + _matrix.m01;
		_result.m02 = _result.m02 + _matrix.m02;
		_result.m03 = _result.m03 + _matrix.m03;
		_result.m10 = _result.m10 + _matrix.m10;
		_result.m11 = _result.m11 + _matrix.m11;
		_result.m12 = _result.m12 + _matrix.m12;
		_result.m13 = _result.m13 + _matrix.m13;
		_result.m20 = _result.m20 + _matrix.m20;
		_result.m21 = _result.m21 + _matrix.m21;
		_result.m22 = _result.m22 + _matrix.m22;
		_result.m23 = _result.m23 + _matrix.m23;
		_result.m30 = _result.m30 + _matrix.m30;
		_result.m31 = _result.m31 + _matrix.m31;
		_result.m32 = _result.m32 + _matrix.m32;
		_result.m33 = _result.m33 + _matrix.m33;

		return _result;
	}

	Matrix4<T> operator * (const Matrix4<T>& _matrix)
	{
		Matrix4<T> _result;

		_result.m00 = (m00 * _matrix.m00) + (m01 * _matrix.m10) + (m02 * _matrix.m20) + (m03 * _matrix.m30);
		_result.m01 = (m00 * _matrix.m01) + (m01 * _matrix.m11) + (m02 * _matrix.m21) + (m03 * _matrix.m31);
		_result.m02 = (m00 * _matrix.m02) + (m01 * _matrix.m12) + (m02 * _matrix.m22) + (m03 * _matrix.m32);
		_result.m03 = (m00 * _matrix.m03) + (m01 * _matrix.m13) + (m02 * _matrix.m23) + (m03 * _matrix.m33);
		_result.m10 = (m10 * _matrix.m00) + (m11 * _matrix.m10) + (m12 * _matrix.m20) + (m13 * _matrix.m30);
		_result.m11 = (m10 * _matrix.m01) + (m11 * _matrix.m11) + (m12 * _matrix.m21) + (m13 * _matrix.m31);
		_result.m12 = (m10 * _matrix.m02) + (m11 * _matrix.m12) + (m12 * _matrix.m22) + (m13 * _matrix.m32);
		_result.m13 = (m10 * _matrix.m03) + (m11 * _matrix.m13) + (m12 * _matrix.m23) + (m13 * _matrix.m33);
		_result.m20 = (m20 * _matrix.m00) + (m21 * _matrix.m10) + (m22 * _matrix.m20) + (m23 * _matrix.m30);
		_result.m21 = (m20 * _matrix.m01) + (m21 * _matrix.m11) + (m22 * _matrix.m21) + (m23 * _matrix.m31);
		_result.m22 = (m20 * _matrix.m02) + (m21 * _matrix.m12) + (m22 * _matrix.m22) + (m23 * _matrix.m32);
		_result.m23 = (m20 * _matrix.m03) + (m21 * _matrix.m13) + (m22 * _matrix.m23) + (m23 * _matrix.m33);
		_result.m30 = (m30 * _matrix.m00) + (m31 * _matrix.m10) + (m32 * _matrix.m20) + (m33 * _matrix.m30);
		_result.m31 = (m30 * _matrix.m01) + (m31 * _matrix.m11) + (m32 * _matrix.m21) + (m33 * _matrix.m31);
		_result.m32 = (m30 * _matrix.m02) + (m31 * _matrix.m12) + (m32 * _matrix.m22) + (m33 * _matrix.m32);
		_result.m33 = (m30 * _matrix.m03) + (m31 * _matrix.m13) + (m32 * _matrix.m23) + (m33 * _matrix.m33);

		return _result;
	}

	void operator *= (const Matrix4<T>& _matrix)
	{
		m00 = (m00 * _matrix.m00) + (m01 * _matrix.m10) + (m02 * _matrix.m20) + (m03 * _matrix.m30);
		m01 = (m00 * _matrix.m01) + (m01 * _matrix.m11) + (m02 * _matrix.m21) + (m03 * _matrix.m31);
		m02 = (m00 * _matrix.m02) + (m01 * _matrix.m12) + (m02 * _matrix.m22) + (m03 * _matrix.m32);
		m03 = (m00 * _matrix.m03) + (m01 * _matrix.m13) + (m02 * _matrix.m23) + (m03 * _matrix.m33);
		m10 = (m10 * _matrix.m00) + (m11 * _matrix.m10) + (m12 * _matrix.m20) + (m13 * _matrix.m30);
		m11 = (m10 * _matrix.m01) + (m11 * _matrix.m11) + (m12 * _matrix.m21) + (m13 * _matrix.m31);
		m12 = (m10 * _matrix.m02) + (m11 * _matrix.m12) + (m12 * _matrix.m22) + (m13 * _matrix.m32);
		m13 = (m10 * _matrix.m03) + (m11 * _matrix.m13) + (m12 * _matrix.m23) + (m13 * _matrix.m33);
		m20 = (m20 * _matrix.m00) + (m21 * _matrix.m10) + (m22 * _matrix.m20) + (m23 * _matrix.m30);
		m21 = (m20 * _matrix.m01) + (m21 * _matrix.m11) + (m22 * _matrix.m21) + (m23 * _matrix.m31);
		m22 = (m20 * _matrix.m02) + (m21 * _matrix.m12) + (m22 * _matrix.m22) + (m23 * _matrix.m32);
		m23 = (m20 * _matrix.m03) + (m21 * _matrix.m13) + (m22 * _matrix.m23) + (m23 * _matrix.m33);
		m30 = (m30 * _matrix.m00) + (m31 * _matrix.m10) + (m32 * _matrix.m20) + (m33 * _matrix.m30);
		m31 = (m30 * _matrix.m01) + (m31 * _matrix.m11) + (m32 * _matrix.m21) + (m33 * _matrix.m31);
		m32 = (m30 * _matrix.m02) + (m31 * _matrix.m12) + (m32 * _matrix.m22) + (m33 * _matrix.m32);
		m33 = (m30 * _matrix.m03) + (m31 * _matrix.m13) + (m32 * _matrix.m23) + (m33 * _matrix.m33);
	}

	void operator += (const Matrix4<T>& _matrix)
	{
		m00 = m00 + _matrix.m00;
		m01 = m01 + _matrix.m01;
		m02 = m02 + _matrix.m02;
		m03 = m03 + _matrix.m03;
		m10 = m10 + _matrix.m10;
		m11 = m11 + _matrix.m11;
		m12 = m12 + _matrix.m12;
		m13 = m13 + _matrix.m13;
		m20 = m20 + _matrix.m20;
		m21 = m21 + _matrix.m21;
		m22 = m22 + _matrix.m22;
		m23 = m23 + _matrix.m23;
		m30 = m30 + _matrix.m30;
		m31 = m31 + _matrix.m31;
		m32 = m32 + _matrix.m32;
		m33 = m33 + _matrix.m33;
	}
	
	static Matrix4<T> CreateIdentity()
	{
		Matrix3<T> _matrix;

		for (size_t i = 0; i < 4; ++i)
			_matrix.m_Components[i][i] = 1;

		return _matrix;
	}

	static Matrix4<T> CreateScale(const T& _scale)
	{
		Matrix3<T> _matrix;

		for (size_t i = 0; i < 4; ++i)
			_matrix.m_Components[i][i] = _scale;

		return _matrix;
	}

	static Matrix4<T> CreateRotation(const T& _x, const T& _y, const T& _z)
	{
		Matrix4<T> _matrix;

		_matrix.m00 = +cosf(_y) * +cosf(_z);
		_matrix.m01 = -sinf(_z);
		_matrix.m02 = +sinf(_y);
		_matrix.m10 = +sinf(_z);
		_matrix.m11 = +cosf(_x) * +cosf(_z);
		_matrix.m12 = -sinf(_x);
		_matrix.m20 = -sinf(_y);
		_matrix.m21 = +sinf(_x);
		_matrix.m22 = +cosf(_x) * +cosf(_y);

		return _matrix;
	}

	static Matrix4<T> CreateTranslation(const T& _x, const T& _y, const T& _z)
	{
		Matrix4<T> _matrix;

		_matrix.m30 = _x;
		_matrix.m31 = _y;
		_matrix.m32 = _z;

		return _matrix;
	}
	
	static Matrix4<T> CreatePerspective(const T& _fov, const T& _aspect, const T& _near, const T& _far)
	{
		float _depth		= _far - _near;
		float _overdepth	= 1.0f / _depth;

		m11 = 1 / tan(0.5f * _fov);
		m00 = m11 / _aspect;
		m22 = _far * _overdepth;
		m32 = (-_far * _near) * _overdepth;
		m23 = 1.0f;
		m33 = 0;
	}

	const T* GetPtr()
	{
		return m_Values[0];
	}

protected:
	Vector4<T> m_Components[4];

	T* m_Values[16];

private:
	void SetValues()
	{
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				m_Values[i * 3 + j] = &m_Components[i][j];
	}


};
