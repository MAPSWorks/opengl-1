#pragma once

#include "GisPlatform.hpp"

namespace GIS
{
	class GisOpenGL
	{
	public:
		char _vertexBuffer[1024 * 1024 * 8];	//���㻺����

		char _indexBuffer[1024 * 1024];			//����������

	public:
		GisOpenGL();
		virtual ~GisOpenGL();

	};

}