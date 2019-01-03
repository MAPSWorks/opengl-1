#pragma once

#include "GisPlatform.hpp"

namespace GIS
{
	class GisOpenGL;

	class Texture
	{
	public:
		enum 
		{
			TEXTURE_NONE,
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D,
		};
	public:
		unsigned _texture;
		unsigned _texType;
	public:
		Texture(unsigned type = TEXTURE_NONE):
			_texture(0xFFFFFFFF), _texType(type)
		{}
		virtual ~Texture()
		{}
	};

	class Texture1d :public Texture
	{
	public:
		unsigned _width;
	public:
		Texture1d() :Texture(TEXTURE_1D)
		{
			_width = 0;
		}
		virtual ~Texture1d()
		{}

	};

	class Texture2d :public Texture
	{
	public:
		unsigned _width;
		unsigned _height;
	public:
		Texture2d() :Texture(TEXTURE_2D)
		{
			_width = 0;
			_height = 0;
		}
		virtual ~Texture2d()
		{}

	};

	class Texture3d :public Texture
	{
	public:
		unsigned _width;
		unsigned _height;
		unsigned _depth;
	public:
		Texture3d() :Texture(TEXTURE_3D)
		{
			_width = 0;
			_height = 0;
			_depth = 1;
		}
		virtual ~Texture3d()
		{}

	};


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

		void setViewPort(int x, int y, int width, int height);
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

		//创建1维纹理
		static Texture1d createTexture1D(int level, int internalfmt,
			int width, int border, int format, int type, const void* data);

		//创建2维纹理
		static Texture2d createTexture2D(int level, int internalfmt,
			int width, int height, int border, int format, int type, const void* data);

		//创建3维纹理
		static Texture3d createTexture3D(int level, int internalfmt,
			int width, int height, int depth, int border, int format, int type, const void* data);

		static Texture3d createTexture2dArray(int width, int height, int layers, unsigned int fmt);
	};

}