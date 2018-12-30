#include "stdafx.h"
#include "GisPlatform.hpp"
#include "GisFrameMap.h"
#include "GisOpenGL.h"
#include "GisResourceMgr.hpp"
#include "GisProgramLibrary.hpp"
#include "GisMath.hpp"

namespace GIS
{
	GisFrameMap::GisFrameMap(GisContext& context)
		:GisFrame(context)
	{
	}


	GisFrameMap::~GisFrameMap()
	{
	}

	
	void GisFrameMap::onFrameStart(GisContext& context)
	{
		context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		context._device->clearColor(0, 0, 0, 1);
		PROGRAM_P2_UC& prg = context._resMgr->_PROGRAM_P2UC;

		float2 vLines[2] = {
			float2(0, 0),
			float2(100, 100)
		};
		Rgba color(255, 0, 0, 255);
		prg.begin();
		{
			context._device->setUniformMatrix4fv(prg._mvp, 1, GL_FALSE, &context._screenPrj[0][0]);
			context._device->setUniform4f(prg._color, color._r / 255.0f, 
				color._g / 255.0f, 
				color._b / 255.0f, 
				color._a / 255.0f);
			context._device->attributePointer(prg._position, 2, GL_FLOAT, GL_FALSE, sizeof(float2), vLines);
			context._device->drawArrays(GL_LINES, 0, 2);
		}
		prg.end();
	}

	void GisFrameMap::update(GisContext& context)
	{
		_context._screenPrj = glm::ortho(0.0f, (float)_context._width, (float)context._height, 0.0f, -1000.0f, 1000.0f);
	}

	void GisFrameMap::onFrameEnd(GisContext& context)
	{

	}

	void GisFrameMap::onLButtonDown(int x, int y)
	{

	}

	void GisFrameMap::onLButtonUp(int x, int y)
	{

	}

	void GisFrameMap::onMouseMove(int x, int y)
	{

	}

}

