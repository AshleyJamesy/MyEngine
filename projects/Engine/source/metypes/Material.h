#pragma once
#include "GLEW\glew.h"

struct Material
{
	struct MaterialType
	{
		enum Type
		{
			MATERIAL_DIFFUSE,
			MATERIAL_SPECULAR,
			MATERIAL_NORMAL,
			MATERIAL_GLOW,
			MATERIAL_GLOSS,
			MATERIAL_NULL,
			MATERIAL_COUNT
		};
	};

	GLint	m_Textures[MaterialType::MATERIAL_COUNT];
	GLint	m_Samplers[MaterialType::MATERIAL_COUNT];

	void BindMaterial()
	{
		GLint _program;
		glGetIntegerv(GL_CURRENT_PROGRAM, &_program);

		if (_program)
		{
			unsigned int _samplers = 0;
			_samplers = glGetUniformLocation(_program, "u_samplers");

			if (_samplers)
			{
				for (size_t i = 0; i < MaterialType::MATERIAL_COUNT; i++)
					if (m_Textures[i] > 0)
					{
						m_Samplers[i] = i;

						glActiveTexture(GL_TEXTURE0 + i);

						glBindTexture(GL_TEXTURE_2D, m_Textures[i]);
					}

				glUniform1iv(_samplers, MaterialType::MATERIAL_COUNT, m_Samplers);
			}
		}
	}

};