#pragma once
#include <vector>

class System;
class Message;

class MessageBus
{
public:
	static MessageBus& _MessageBus()
	{
		return m_MessageBus;
	}

	void AttachSystem(System& _system);

	/*
	Description:	adds message to write queue to be read next update
	Parameters:		Message* _message
	Return:			void
	Notes:			if recipient is nullptr, message will be broadcasted
	*/
	void PostMessage(Message* _message);
	
	/*
	Description:	reads the queue
	Parameters:		void
	Return:			void
	*/
	void ReadQueue();

	/*
	Description:	returns the read queue
	Parameters:		void
	Return:			std::vector<Message*>*
	*/
	std::vector<Message*>* Queue();

	/*
	Description:	returns the write queue to be read next update
	Parameters:		void
	Return:			std::vector<Message*>*
	*/
	std::vector<Message*>* WriteQueue();

	/*
		Description:	clears the read queue and swaps queues for next update
		Parameters:		void
		Return:			void
	*/
	void SwapQueue();

	std::vector<System*>	m_Systems;

private:
	static MessageBus m_MessageBus;

	
	std::vector<Message*>	m_MessageQueue_01;
	std::vector<Message*>	m_MessageQueue_02;

	std::vector<Message*>*	m_ReadQueue		= &m_MessageQueue_01;
	std::vector<Message*>*	m_WriteQueue	= &m_MessageQueue_02;
};