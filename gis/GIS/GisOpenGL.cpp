
#include "GisOpenGL.h"

namespace GIS
{

	GisProgram::GisProgram()
	{

	}

	GisProgram::~GisProgram()
	{

	}


	bool GisProgram::initialize(GisOpenGL* device)
	{
		return true;
	}

	void GisProgram::destroy()
	{
		_device->destroyProgram(*this);
		return;
	}

	void GisProgram::begin()
	{

	}


	void GisProgram::end()
	{

	}

	/////////////////////////////////////////////
	GisOpenGL::GisOpenGL()
	{

	}

	GisOpenGL::~GisOpenGL()
	{

	}

	void GisOpenGL::clear(unsigned int mask)
	{
		glClear(mask);
	}

	void GisOpenGL::clearColor(float red, float green, float blue, float alpha)
	{
		glClearColor(red, green, blue, alpha);
	}

	void GisOpenGL::setViewPort(int x, int y, int width, int height)
	{
		glViewport(0, 0, width, height);
		return;
	}

	void GisOpenGL::initialize()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_PROGRAM_POINT_SIZE);
	}

	bool GisOpenGL::createProgram(GisProgram& shaderPrg, const char* vs, const char* ps)
	{
		bool result = false;
		do 
		{
			shaderPrg._vHandle = glCreateShader(GL_VERTEX_SHADER);
			shaderPrg._pHandle = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(shaderPrg._vHandle, 1, (const GLchar**)&vs, 0);
			glShaderSource(shaderPrg._pHandle, 1, (const GLchar**)&ps, 0);

			glCompileShader(shaderPrg._vHandle);
			GLint status = 0;
			char compileLog[1024] = { 0 };
			GLsizei logLen = 0;
			glGetShaderiv(shaderPrg._vHandle, GL_COMPILE_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetShaderInfoLog(shaderPrg._vHandle, sizeof(compileLog), &logLen, compileLog);
				break;
			}

			glCompileShader(shaderPrg._pHandle);

			glGetShaderiv(shaderPrg._pHandle, GL_COMPILE_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetShaderInfoLog(shaderPrg._pHandle, sizeof(compileLog), &logLen, compileLog);
				break;
			}

			shaderPrg._program = glCreateProgram();
			glAttachShader(shaderPrg._program, shaderPrg._vHandle);
			glAttachShader(shaderPrg._program, shaderPrg._pHandle);

			glLinkProgram(shaderPrg._program);

			glGetProgramiv(shaderPrg._program, GL_LINK_STATUS, &status);
			if (GL_FALSE == status)
			{
				glGetProgramInfoLog(shaderPrg._program, sizeof(compileLog), &logLen, compileLog);
				break;
			}
			result = true;
		} while (false);
		
		if (false == result)
		{
			shaderPrg._vHandle = -1;
			shaderPrg._pHandle = -1;
			shaderPrg._program = -1;
		}

		return result;
	}

	void GisOpenGL::destroyProgram(GisProgram& shaderPrg)
	{
		glDeleteProgram(shaderPrg._program);
		return;
	}

	GLint GisOpenGL::getAttributeLocation(GLint program, const char* name)
	{
		GLint attributeValue = 0;
		attributeValue = glGetAttribLocation(program, name);
		return attributeValue;
		return 0;
	}

	GLint GisOpenGL::getUniformLocation(GLint program, const char* name)
	{
		GLint uniformValue = 0;
		uniformValue = glGetUniformLocation(program, name);
		return uniformValue;
	}

	void GisOpenGL::enableVertexAttribArray(GLint vertexAttribue)
	{
		glEnableVertexAttribArray(vertexAttribue);
		return;
	}

	void GisOpenGL::disableVertexAttribArray(GLint vertexAttribue)
	{
		glDisableVertexAttribArray(vertexAttribue);
		return;
	}

	void GisOpenGL::useProgram(GLint program)
	{
		glUseProgram(program);
		return;
	}

	void GisOpenGL::setUniformMatrix4fv(int index, int count, bool transpose, const float* value)
	{
		glUniformMatrix4fv(index, count, transpose, value);
		return;
	}

	void GisOpenGL::setUniform4f(int index, float v0, float v1, float v2, float v3)
	{
		glUniform4f(index, v0, v1, v2, v3);
	}

	void GisOpenGL::attributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, ptr);
	}

	void GisOpenGL::drawArrays(GLenum mode, GLint first, GLsizei count)
	{
		glDrawArrays(mode, first, count);
	}

	Texture1d GisOpenGL::createTexture1D(int level, int internalfmt, 
		int width, int border, int format, int type, const void* data)
	{
		Texture1d tex;
		tex._width = width;

		glGenTextures(1, &tex._texture);
		glBindTexture(GL_TEXTURE_1D, tex._texture);

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		if (GL_COMPRESSED_RGBA_S3TC_DXT1_EXT == format)
		{
			glCompressedTexImage1D(GL_TEXTURE_1D, level, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, width, 0, width / 4, data);
		}
		else if (GL_COMPRESSED_RGBA_S3TC_DXT3_EXT == format)
		{
			glCompressedTexImage1D(GL_TEXTURE_1D, level, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, width, 0, width, data);
		}
		else if (GL_COMPRESSED_RGBA_S3TC_DXT5_EXT == format)
		{
			glCompressedTexImage1D(GL_TEXTURE_1D, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width, 0, width, data);
		}
		else
		{
			glTexImage1D(GL_TEXTURE_1D, level, internalfmt, width, border, format, type, data);
		}
		return tex;
	}

	Texture2d GisOpenGL::createTexture2D(int level, int internalfmt,
		int width, int height, int border, int format, int type, const void* data)
	{
		Texture2d tex;
		tex._width	= width;
		tex._height = height;

		glGenTextures(1, &tex._texture);
		glBindTexture(GL_TEXTURE_2D, tex._texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		if (GL_COMPRESSED_RGBA_S3TC_DXT1_EXT == format)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, width, height, 0, width / 4, data);
		}
		else if (GL_COMPRESSED_RGBA_S3TC_DXT3_EXT == format)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, width, height, 0, width, data);
		}
		else if (GL_COMPRESSED_RGBA_S3TC_DXT5_EXT == format)
		{
			glCompressedTexImage2D(GL_TEXTURE_2D, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width, height, 0, width, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, level, internalfmt, width, height, border, format, type, data);
		}
		return tex;
	}

	Texture3d GisOpenGL::createTexture3D(int level, int internalfmt,
		int width, int height, int depth, int border, int format, int type, const void* data)
	{
		Texture3d tex;
		tex._width	= width;
		tex._height = height;
		tex._depth	= depth;

		glGenTextures(1, &tex._texture);
		glBindTexture(GL_TEXTURE_3D, tex._texture);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		if (GL_COMPRESSED_RGBA_S3TC_DXT1_EXT == format)
		{
			glCompressedTexImage3D(GL_TEXTURE_3D, level, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, width, height, depth, 0, width / 4, data);
		}
		else if (GL_COMPRESSED_RGBA_S3TC_DXT3_EXT == format)
		{
			glCompressedTexImage3D(GL_TEXTURE_3D, level, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, width, height, depth, 0, width, data);
		}
		else if (GL_COMPRESSED_RGBA_S3TC_DXT5_EXT == format)
		{
			glCompressedTexImage3D(GL_TEXTURE_3D, level, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, width, height, depth, 0, width, data);
		}
		else
		{
			glTexImage3D(GL_TEXTURE_3D, level, internalfmt, width, height, depth, border, format, type, data);
		}

		return tex;
	}

	Texture3d GisOpenGL::createTexture2dArray(int width, int height, int layers, unsigned int fmt)
	{
		Texture3d tex;
		return tex;
	}

}
