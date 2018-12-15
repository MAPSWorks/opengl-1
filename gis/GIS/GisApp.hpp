#pragma once
#include "GisPlatform.hpp"

namespace GIS
{
	class GisApp
	{
	public:

		//创建窗口函数
		virtual bool createWindow(int width, int height, INSTANCE hInst) = 0;


		virtual void main(int argc, char** argv) = 0;
	};
}