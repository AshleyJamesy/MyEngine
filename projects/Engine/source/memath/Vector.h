#pragma once
#include <math.h>

template<typename T, size_t N>
class Vector
{
public:
	Vector()
	{
		for (size_t i = 0; i < N; ++i)
			m_Values[i] = 0;

		m_Size = N;
	}

	T Sum()
	{
		T _value = 0;

		for (size_t i = 0; i < N; i++)
			_value += m_Values[i];

		return _value;
	}

	T Magnitude()
	{
		T _value = 0;

		for (size_t i = 0; i < N; i++)
			_value += m_Values[i] * m_Values[i];

		return sqrtf(_value);
	}
	
	unsigned int Size()
	{
		return m_Size;
	}
	
	Vector<T, N> Normalised()
	{
		Vector<T, N> _vector;

		T _magnitude = Magnitude();

		for (size_t i = 0; i < Size(); ++i)
			_vector.m_Values[i] = m_Values[i] / _magnitude;

		return _vector;
	}

	T& operator [] (unsigned int _index)
	{
		return m_Values[_index];
	}

protected:
	unsigned int m_Size = 0;

	T m_Values[N];

};


