#pragma once

#define GIS_PLATFORM_WIN32	 1
#define GIS_PLATFORM_LINUX	 2
#define GIS_PLATFORM_APPLE	 3
#define GIS_PLATFORM_ANDROID 4

#define GIS_PATH_LENGTH		1024
#define GIS_CALL			__stdcall

#define GIS_PLATFORM	GIS_PLATFORM_WIN32

#if GIS_PLATFORM == GIS_PLATFORM_WIN32

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <tchar.h>
#include <windows.h>

#include <GL\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#ifdef GISMAP3D_EXPORTS
#define GISMAP3D_API __declspec(dllexport)
#else
#define GISMAP3D_API __declspec(dllimport)
#endif

typedef HDC			HDISPLAY;
typedef HWND		HWINDOW;
typedef HMODULE		HLIBRARY;
typedef HINSTANCE	INSTANCE;

typedef const char* STRING;




#endif