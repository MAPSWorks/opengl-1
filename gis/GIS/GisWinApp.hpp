#pragma once
#include "GisApp.hpp"
#include <windows.h>
#include <tchar.h>
#include "GisGLContext.hpp"
#include "GisOpenGL.h"
#include "GisFrameMap.h"
#include "GisContext.hpp"
#include "GisThread.hpp"
#include "GisEvent.hpp"
#include "GisProgramLibrary.hpp"
#include "GisResourceMgr.hpp"
#include <assert.h>

namespace GIS
{
	class GisWinApp : public GisApp, public GisThread
	{
	public:

		HWND			_hWnd;	//���ھ��
		GisGLContext	_contextGL;
		GisContext		_context;
		GisResourceMgr	_resMgr;
		GisOpenGL		_device;
		GisFrame*		_frame;
		bool			_threaRun;
		bool			_makeResult;
		GisEvent		_event;

		GisWinApp()
		{
			_hWnd				= NULL;
			_frame				= NULL;
			_threaRun			= true;
			_makeResult			= false;
			_context._device	= &_device;
			_context._resMgr	= &_resMgr;
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
			_device.initialize();
			_context._resMgr->initialize(_context._device);
			///��������̰߳�
			_contextGL.makeCurrentNone();
			return true;
		}

		/// <summary>
		/// �������
		/// </summary>
		virtual GisFrame* createFrame()
		{
			if (TRUE == IsWindow(_hWnd))
			{
				RECT rect;
				GetClientRect(_hWnd, &rect);
				_context._width = rect.right - rect.left;
				_context._height = rect.bottom - rect.top;
			}
			else
			{
				_context._width = 64;
				_context._height = 64;
			}
			return new GisFrameMap(_context);
		}

		//��ں���
		virtual void main(int argc, char** argv)
		{
			_frame = createFrame();
			if (nullptr != _frame)
			{
				GisThread::start();
				_event.wait();

				if (false == _makeResult)
				{
					_threaRun = false;
					GisThread::join();
					delete _frame;
					_contextGL.shutdown();
					return;
				}
				MSG msg = { 0 };
#if 1
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
				_contextGL.shutdown();
#endif
			}
			
			
			
		}

		//���ƺ���
		virtual void render()
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

		protected:
			/// <summary>
			/// �������֪ͨ����
			/// </summary>
			virtual bool onCreate()
			{
				_makeResult = _contextGL.makeCurrent();
				assert(_makeResult);
				_event.set();
				return _makeResult;
			}

			/// <summary>
			/// �߳�ִ�к���
			/// </summary>
			virtual bool onRun()
			{
				while (_threaRun)
				{
					render();
				}
				return false;
			}

			/// <summary>
			/// ��������
			/// </summary>
			virtual bool onDestroy()
			{
				_contextGL.shutdown();
				return false;
			}

		LRESULT eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_LBUTTONDOWN:
				_frame->onLButtonDown(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_LBUTTONUP:
				_frame->onLButtonUp(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MOUSEMOVE:
				_context._mouseX = LOWORD(lParam);
				_context._mouseY = HIWORD(lParam);
				_frame->onMouseMove(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
			}
				break;
			case WM_SIZE:
			{
				if (TRUE == IsWindow(_hWnd))
				{
					RECT rect;
					GetClientRect(_hWnd, &rect);
					_context._width = rect.right - rect.left;
					_context._height = rect.bottom - rect.top;
				}				
			}
				break;
			case WM_DESTROY:
				_threaRun = false;
				GisThread::join();
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
