
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

}
