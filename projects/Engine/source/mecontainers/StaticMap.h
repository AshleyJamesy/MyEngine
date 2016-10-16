#pragma once
#include "StaticLinkList.h"

template<typename Key, typename Value>
struct Pair
{
	Key		m_Key;
	Value	m_Value;

	Pair()
	{

	}

	Pair(const Key& _key, const Value& _value)
	{
		m_Key = _key;
		m_Value = _value;
	}

};

template<typename Key, typename Value, size_t size>
class StaticMap : public StaticLinkList<Pair<Key, Value>, size>
{
public:
	struct Iterator
	{
		int m_Index = -1;

		Iterator()
		{

		}

		Iterator(int _index)
		{
			m_Index = _index;
		}
	};

	void Set(const Key& _key, const Value& _value)
	{
		Pair<Key, Value> _pair(_key, _value);

		for (size_t i = 0; i < m_Count; i++)
			if (m_Array[i].m_Object.m_Key == _key)
			{
				m_Array[i].m_Object.m_Value = _value;

				return;
			}

		Push(_pair);
	}

	Iterator Find(const Key& _key)
	{
		for (size_t i = 0; i < m_Count; i++)
			if (m_Array[i].m_Object.m_Key == _key)
				return Iterator(i);

		return Iterator();
	}

	Value& Get(Iterator& _iterator)
	{
		return m_Array[_iterator.m_Index].m_Object.m_Value;
	}

};