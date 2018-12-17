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

	GIS::GisWinApp* app = new GIS::GisWinApp();
	if (NULL == app)
	{
		return 1;
	}
	if (false == app->createWindow(800, 600, hInstance))
	{
		delete app;
		return 2;
	}
	app->main(0, 0);
	delete app;

	return 0;
}
