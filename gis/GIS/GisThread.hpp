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
		/// �߳���ں���
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
		/// �������֪ͨ����
		/// </summary>
		virtual bool onCreate()
		{
			return false;
		}

		/// <summary>
		/// �߳�ִ�к���
		/// </summary>
		virtual bool onRun()
		{
			return false;
		}

		/// <summary>
		/// ��������
		/// </summary>
		virtual bool onDestroy()
		{
			return false;
		}

		/// <summary>
		/// �����̺߳���
		/// </summary>
		virtual bool start()
		{
			if (0 != _thread)
			{
				return false;
			}
			//_thread = (HANDLE)_beginthreadex(NULL, NULL, threadEnter, NULL, 0, &_threadId);
			_thread = CreateThread(NULL	// Ĭ�ϰ�ȫ����
				, NULL		// Ĭ�϶�ջ��С
				, threadEnter // �߳���ڵ�ַ
				, this	//���ݸ��̺߳����Ĳ���
				, 0		// ָ���߳���������
				, &_threadId	//�߳�ID��
			);
			
			return true;
		}

		/// <summary>
		/// �����̺߳���
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
		/// �����̺߳���
		/// </summary>
		virtual void close()
		{
			CloseHandle(_thread);
			_thread = 0;
		}
	};
}
