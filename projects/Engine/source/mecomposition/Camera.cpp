#include "Camera.h"
#include <GLEW\glew.h>

void Camera::Render()
{
	GLint _program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &_program);

	if (_program > 0)
	{
		unsigned int _projection	= glGetUniformLocation(_program, "u_projection");
		unsigned int _view			= glGetUniformLocation(_program, "u_view");

		if(_projection)
			glUniformMatrix4fv(_projection, 1, GL_FALSE, m_Perspective.GetPtr());

		if(_view)
			glUniformMatrix4fv(_view, 1, GL_FALSE, GetView().GetPtr());
	}
}
