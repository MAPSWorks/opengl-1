#pragma once

#include "GisPlatform.hpp"

namespace GIS
{
	class GisOpenGL
	{
	public:
		char _vertexBuffer[1024 * 1024 * 8];	//顶点缓冲区

		char _indexBuffer[1024 * 1024];			//索引缓冲区

	public:
		GisOpenGL();
		virtual ~GisOpenGL();

	};

}