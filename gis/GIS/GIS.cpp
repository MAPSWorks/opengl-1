// GIS.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GIS.h"
#include "GisWinApp.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	GIS::GisWinApp app;
	if (false == app.createWindow(800, 600, hInstance))
	{
		return 0;
	}
	app.main(0, 0);

	return 0;
}
