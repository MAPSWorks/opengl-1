#pragma once


namespace GIS
{
	class GisApp
	{
	public:

		//创建窗口函数
		virtual bool createWindow(int width, int height, HINSTANCE hInst) = 0;


		virtual void main(int argc, char** argv) = 0;
	};
}