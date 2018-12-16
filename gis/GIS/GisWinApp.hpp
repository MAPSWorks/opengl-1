#pragma once
#include "GisApp.hpp"
#include <windows.h>
#include <tchar.h>
#include "GisGLContext.hpp"

namespace GIS
{
	class GisWinApp : public GisApp
	{
	public:
		GisWinApp()
		{
			_hWnd = NULL;
		}

		//�������ں���
		virtual bool createWindow(int width, int height, HINSTANCE hInst)
		{
			//ע�ᴰ����
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
				CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
			if (NULL == _hWnd)
			{
				return false;
			}
			ShowWindow(_hWnd, SW_SHOW);
			UpdateWindow(_hWnd);

			HDISPLAY hDC = GetDC(_hWnd);
			if (false == _context.init(_hWnd, hDC))
			{
				DestroyWindow(_hWnd);
				return false;
			}
			return true;
		}

		//��ں���
		virtual void main(int argc, char** argv)
		{
			MSG msg = { 0 };
#if 0
			// ����Ϣѭ��: 
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
			
			_context.shutdown();
		}

		//���ƺ���
		void render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(1, 0, 0, 1);
			_context.swapBuffer();
		}


		HWND			_hWnd;	//���ھ��
		GisGLContext	_context;
	protected:
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_COMMAND:
			break;
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
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

	};
}
