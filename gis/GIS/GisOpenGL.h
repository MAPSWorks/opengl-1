#pragma once

#include "GisPlatform.hpp"

namespace GIS
{
	class GisOpenGL;


	class GisProgram
	{
	public :
		typedef GLint attribute;
		typedef GLint uniform;
	public:
		enum ShaderType
		{
			SHADER_NONE		= 0,
			SHADER_VERTEX	= 1,
			SHADER_FRAGMENT	=2,
			SHADER_TES		= 3,
			SHADER_TCS		= 4,
			SHADER_GEM		= 5,
			SHADER_COMPUTE	= 6,
		};
	public:
		friend GisOpenGL;
	public:
		GLint		_vHandle;
		GLint		_pHandle;
		GLint		_program;
		GisOpenGL*	_device;
	public:
		GisProgram();
		virtual ~GisProgram();
	};


	class GisOpenGL
	{
	public:
		char _vertexBuffer[1024 * 1024 * 8];	//顶点缓冲区

		char _indexBuffer[1024 * 1024];			//索引缓冲区

	public:
		GisOpenGL();
		virtual ~GisOpenGL();

		void clear(unsigned int mask);
		void clearColor(float red, float green, float blue, float alpha);
		
	};

}