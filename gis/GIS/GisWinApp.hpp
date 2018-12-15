#pragma once
#include "GisApp.hpp"
#include <windows.h>
#include <tchar.h>

namespace GIS
{
	class GisWinApp : public GisApp
	{
	public:
		GisWinApp()
		{
			_hwnd = NULL;
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

			_hwnd = CreateWindow(_T("GIS.Map"), _T("GISMap"), WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
			if (NULL == _hwnd)
			{
				return false;
			}
			ShowWindow(_hwnd, SW_SHOW);
			UpdateWindow(_hwnd);
			return true;
		}

		//��ں���
		virtual void main(int argc, char** argv)
		{
			MSG msg;

			// ����Ϣѭ��: 
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}


		HWND _hwnd;	//���ھ��
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
