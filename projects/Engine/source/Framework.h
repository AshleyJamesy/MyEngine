#pragma once
#include "Message.h"
#include "MessageBus.h"

#include <random>

namespace MyEngine
{
	Message* m_Message = Message::CreateMessage();

	struct Render
	{
		static void DoRender()
		{
			for (size_t i = 0; i < 2500; i++)
			{
				m_Message = Message::CreateMessage();

				m_Message->m_Size	= 0;
				m_Message->m_Index	= 0;
				m_Message->m_Free	= true;

				m_Message->Write<unsigned int>(rand() % 10 + 0);

				MessageBus::_MessageBus().PostMessage(m_Message);
			}
		}
	};

	struct Input
	{
		static void DoInput()
		{
			
		}
	};

	struct Sound
	{
		static void DoSound()
		{

		}
	};

	struct Utilities
	{
		static void DoUtilities()
		{

		}
	};

	void Update()
	{
		Input::DoInput();
		Sound::DoSound();
		Render::DoRender();
		Utilities::DoUtilities();
	}
}

