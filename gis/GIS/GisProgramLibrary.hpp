#pragma once

#include "GisOpenGL.h"

namespace GIS
{
	class PROGRAM_P2_UC : public GisProgram
	{
	public:
		attribute	_position;
		uniform		_color;
		uniform		_mvp;
	public:
		virtual bool initialize(GisOpenGL* device)
		{
			const char* vs = {
				"#version 330 \n"
				"precision highp float \n;"
				"uniform mat4 _MVP; \n"
				"attribute vec4 _position; \n"
				"void main() \n"
				"{\n"
				"	vec4 pos = vec4(_position.x, _position.y, 0, 1); \n"
				"	gl_position = _MVP * pos; \n"
				"}"
			};

			const char* ps = {
				"#version 330 \n"
				"precision highp float; \n"
				"uniform vec4 _color; \n"
				"void main() \n"
				"{\n"
				"	gl_FragColor = _color; \n"
				"}\n"
			};

			
		}

		// π”√shader
		virtual void begin()
		{

		}

		virtual void end()
		{

		}
	};
}