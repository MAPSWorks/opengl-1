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

	public:
		virtual bool initialize(GisOpenGL* device);

		virtual void destroy();

		//使用shader
		virtual void begin();
		virtual void end();

		//创建shader

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

		void initialize();

		bool createProgram(GisProgram& shaderPrg, const char* vs, const char* ps);
		void destroyProgram(GisProgram& shaderPrg);
		GLint getAttributeLocation(GLint program, const char* name);
		GLint getUniformLocation(GLint program, const char* name);

		void enableVertexAttribArray(GLint vertexAttribue);
		void disableVertexAttribArray(GLint vertexAttribue);
		void useProgram(GLint program);

		void setUniformMatrix4fv(int index, int count, bool transpose, const float* value);
		void setUniform4f(int index, float v0, float v1, float v2, float v3);

		void attributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
		void drawArrays(GLenum mode, GLint first, GLsizei count);
	};

}