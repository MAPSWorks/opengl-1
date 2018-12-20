#pragma once
#include "GisApp.hpp"
#include <windows.h>
#include <tchar.h>
#include "GisGLContext.hpp"
#include "GisOpenGL.h"
#include "GisFrameMap.h"
#include "GisContext.hpp"

namespace GIS
{
	class GisWinApp : public GisApp
	{
	public:

		HWND			_hWnd;	//窗口句柄
		GisGLContext	_contextGL;
		GisContext		_context;
		GisOpenGL		_device;
		GisFrame*		_frame;

		GisWinApp()
		{
			_hWnd	= NULL;
			_frame	= NULL;
		}

		//创建窗口函数
		virtual bool createWindow(int width, int height, HINSTANCE hInst)
		{
			//注册窗口类
			WNDCLASSEXW wcex;

			wcex.cbSize = sizeof(WNDCLASSEX);

			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= wndProc;
			wcex.cbClsExtra		= 0;
			wcex.cbWndExtra		= 0;
			wcex.hInstance		= hInst;
			wcex.hIcon			= 0;
			wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
			wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
			wcex.lpszMenuName	= 0;
			wcex.lpszClassName	= _T("GIS.Map");
			wcex.hIconSm		= 0;

			if (0 == RegisterClassExW(&wcex))
			{
				return false;
			}

			_hWnd = CreateWindow(_T("GIS.Map"), _T("GISMap"), WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, this);
			if (NULL == _hWnd)
			{
				return false;
			}
			ShowWindow(_hWnd, SW_SHOW);
			UpdateWindow(_hWnd);

			HDISPLAY hDC = GetDC(_hWnd);
			if (false == _contextGL.init(_hWnd, hDC))
			{
				DestroyWindow(_hWnd);
				return false;
			}
			return true;
		}

		/// <summary>
		/// 创建框架
		/// </summary>
		virtual GisFrame* createFrame()
		{
			return new GisFrameMap(_context);
		}

		//入口函数
		virtual void main(int argc, char** argv)
		{
			_frame = createFrame();
			if (nullptr != _frame)
			{
				MSG msg = { 0 };
#if 0
				// 主消息循环: 
				while (GetMessage(&msg, nullptr, 0, 0))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
#else
				while (WM_QUIT != msg.message)
				{
					if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					render();
				}
#endif
			}
			
			
			_contextGL.shutdown();
		}

		//绘制函数
		void render()
		{
			if (nullptr == _frame)
			{
				return;
			}

			_frame->update(_context);
			_frame->onFrameStart(_context);
			_frame->onFrameEnd(_context);

			
			_contextGL.swapBuffer();
		}

		LRESULT eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
			}
			break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			return S_OK;
		}
		
	protected:
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (WM_CREATE == message)
			{
				LPCREATESTRUCT pCreateStruct = (LPCREATESTRUCT)lParam;
				if (NULL != pCreateStruct)
				{
					GisWinApp* pApp = (GisWinApp*)pCreateStruct->lpCreateParams;
					if (NULL != pApp)
					{
						SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pApp);
						pApp->eventProc(hWnd, message, wParam, lParam);
					}
				}
			}
			else
			{
				GisWinApp* pApp = (GisWinApp*)GetWindowLongPtr(hWnd, GWL_USERDATA);
				if (NULL != pApp)
				{
					return pApp->eventProc(hWnd, message, wParam, lParam);
				}
				else
				{
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
			
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	};
}
