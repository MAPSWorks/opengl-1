#pragma once
#include "GisPlatform.hpp"

#if GIS_PLATFORM == GIS_PLATFORM_WIN32

namespace GIS
{
	class GisGLContext
	{
	protected:
		int			_format;
		HWINDOW		_hWnd;
		HDISPLAY	_hDC;
		HGLRC		_hRC;
	public:
		int			_winWidth;
		int			_winHeight;

	public:
		GisGLContext()
		{
			_format		= 0;
			_hWnd		= NULL;
			_hDC		= NULL;
			_hRC		= NULL;
			_winWidth	= 64;
			_winHeight	= 64;
		}

		~GisGLContext()
		{
			shutdown();
		}

		bool init(HWINDOW hWnd, HDISPLAY hDC)
		{
			_hWnd = hWnd;
			_hDC = hDC;
			unsigned PixelFormat;

			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 32;
			pfd.iLayerType = PFD_MAIN_PLANE;

			RECT rt = { 0, 0, 0, 0 };
			GetClientRect(hWnd, &rt);
			_winWidth = rt.right - rt.left;
			_winHeight = rt.bottom - rt.top;
			_hDC = GetDC(_hWnd);
			if (0 == _format)
			{
				PixelFormat = ChoosePixelFormat(hDC, &pfd);
			}
			else
			{
				PixelFormat = _format;
			}
			

			if (FALSE == SetPixelFormat(_hDC, PixelFormat, &pfd))
			{
				return false;
			}

			_hRC = wglCreateContext(hDC);
			if (FALSE == wglMakeCurrent(hDC, _hRC))
			{
				return false;
			}
			glewInit();
			return true;
		}

		bool makeCurrent()
		{
			return wglMakeCurrent(_hDC, _hRC);
		}

		bool makeCurrentNone()
		{
			return wglMakeCurrent(0, 0);
		}

		void shutdown()
		{
			if (NULL != _hRC)
			{
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(_hRC);
				_hRC = NULL;
			}

			if (NULL != _hDC)
			{
				ReleaseDC(_hWnd, _hDC);
				_hDC = NULL;
			}
		}

		void swapBuffer()
		{
			SwapBuffers(_hDC);
		}

	


	private:

	};
}


#endif
