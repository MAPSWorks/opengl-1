#pragma once

#include "GisOpenGL.h"
#include <assert.h>

namespace GIS
{
	class PROGRAM_P2_UC : public GisProgram
	{
	public:
		attribute	_position;
		uniform		_color;
		uniform		_mvp;
	public:
		PROGRAM_P2_UC()
		{}

		virtual ~PROGRAM_P2_UC()
		{}

		virtual bool initialize(GisOpenGL* device)
		{
			_device = device;
			const char* vs = {
				"#version 330 \n"
				"precision highp float; \n"
				"uniform mat4 _mvp; \n"
				"attribute vec2 _position; \n"
				"void main() \n"
				"{\n"
				"	vec4 pos = vec4(_position.x, _position.y, 0, 1); \n"
				"	gl_Position = _mvp * pos; \n"
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

			bool result = device->createProgram(*this, vs, ps);
			if (true == result)
			{
				_position = device->getAttributeLocation(_program, "_position");
				_color = device->getUniformLocation(_program, "_color");
				_mvp = device->getUniformLocation(_program, "_mvp");
			}
			else
			{
				assert(true == result);
			}
			return result;
		}

		//Ê¹ÓÃshader
		virtual void begin()
		{
			_device->useProgram(_program);
			_device->enableVertexAttribArray(_position);
		}

		virtual void end()
		{
			_device->disableVertexAttribArray(_position);
			_device->useProgram(0);
			
		}
	};
}