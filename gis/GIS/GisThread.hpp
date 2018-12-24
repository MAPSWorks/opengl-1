#pragma once

#include "GisPlatform.hpp"
#include "GisObject.hpp"
#include <process.h>

namespace GIS
{
	class GisThread : public GisObject
	{
	public:
		DWORD	_threadId;
		HANDLE	_thread;

	protected:

		/// <summary>
		/// 线程入口函数
		/// </summary>
		static unsigned long __stdcall threadEnter(void* pVoid)
		{
			GisThread* pThis = (GisThread*)pVoid;
			if (NULL != pThis)
			{
				pThis->onCreate();
				pThis->onRun();
				pThis->onDestroy();
			}
			return 0;
		}

	public:
		GisThread()
		{
			_thread = 0;
		}

		virtual ~GisThread()
		{
			join();
		}

		DWORD threadId() const
		{
			return _threadId;
		}

		bool isRun() const
		{
			return _threadId != 0;
		}
		/// <summary>
		/// 创建完成通知函数
		/// </summary>
		virtual bool onCreate()
		{
			return false;
		}

		/// <summary>
		/// 线程执行函数
		/// </summary>
		virtual bool onRun()
		{
			return false;
		}

		/// <summary>
		/// 结束函数
		/// </summary>
		virtual bool onDestroy()
		{
			return false;
		}

		/// <summary>
		/// 启动线程函数
		/// </summary>
		virtual bool start()
		{
			if (0 != _thread)
			{
				return false;
			}
			//_thread = (HANDLE)_beginthreadex(NULL, NULL, threadEnter, NULL, 0, &_threadId);
			_thread = CreateThread(NULL	// 默认安全属性
				, NULL		// 默认堆栈大小
				, threadEnter // 线程入口地址
				, this	//传递给线程函数的参数
				, 0		// 指定线程立即运行
				, &_threadId	//线程ID号
			);
			
			return true;
		}

		/// <summary>
		/// 启动线程函数
		/// </summary>
		virtual void join()
		{
			if (0 != _thread)
			{
				WaitForSingleObject(_thread, INFINITE);
				CloseHandle(_thread);
				_thread = 0;
			}
		}

		/// <summary>
		/// 启动线程函数
		/// </summary>
		virtual void close()
		{
			CloseHandle(_thread);
			_thread = 0;
		}
	};
}
