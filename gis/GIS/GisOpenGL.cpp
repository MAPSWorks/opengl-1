
#include "GisOpenGL.h"

namespace GIS
{

	GisProgram::GisProgram()
	{

	}

	GisProgram::~GisProgram()
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
