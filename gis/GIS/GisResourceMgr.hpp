#pragma once

#include "GisProgramLibrary.hpp"
namespace GIS
{
	class GisResourceMgr
	{
	public:
		//针对绘制屏幕2维数据
		PROGRAM_P2_UC _PROGRAM_P2UC;

	public:
		GisResourceMgr()
		{

		}

		~GisResourceMgr()
		{

		}

	public:
		void initialize(GisOpenGL* device)
		{
			_PROGRAM_P2UC.initialize(device);
		}

		void destroy()
		{
			_PROGRAM_P2UC.destroy();
		}
	};
}