#pragma once


namespace GIS
{
	class GisApp
	{
	public:

		//�������ں���
		virtual bool createWindow(int width, int height, HINSTANCE hInst) = 0;


		virtual void main(int argc, char** argv) = 0;
	};
}