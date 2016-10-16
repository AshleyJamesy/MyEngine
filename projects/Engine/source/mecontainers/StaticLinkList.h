#pragma once

template<typename T, size_t size>
class StaticLinkList
{
	struct Node
	{
		T m_Object;

		Node* m_Next = nullptr;
		Node* m_Prev = nullptr;
	};

public:
	void Push(const T& _object)
	{
		if (m_Count < size)
			for (size_t i = 0; i < size; i++)
				if (&m_Array[i] != m_Head)
					if (m_Array[i].m_Next == nullptr && m_Array[i].m_Prev == nullptr)
					{
						m_Array[i].m_Object = _object;

						m_Array[i].m_Prev = m_Head;

						if (m_Head)
							m_Head->m_Next = &m_Array[i];

						m_Head = &m_Array[i];

						m_Count++;

						return;
					}
	}

	T Pop()
	{
		if (m_Count > 0)
		{
			Node* _node = m_Head;

			m_Head = _node->m_Prev;
			m_Head->m_Next = nullptr;

			_node->m_Next = nullptr;
			_node->m_Prev = nullptr;

			--m_Count;

			return _node->m_Object;
		}

		return T();
	}

	T& operator[] (unsigned int _index)
	{
		return m_Array[_index].m_Object;
	}

	unsigned int Count()
	{
		return m_Count;
	}

protected:
	Node*			m_Head = nullptr;
	unsigned int	m_Count = 0;

	Node	m_Array[size];

};
