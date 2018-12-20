#include "stdafx.h"
#include "GisPlatform.hpp"
#include "GisFrameMap.h"
#include "GisOpenGL.h"

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
		context._device->clearColor(1, 0, 0, 1);
	}

	void GisFrameMap::update(GisContext& context)
	{

	}

	void GisFrameMap::onFrameEnd(GisContext& context)
	{

	}

}

