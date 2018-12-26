#pragma once

namespace GIS
{
	class GisEvent
	{
	protected:
		HANDLE _handle;

	public:
		GisEvent()
		{
			_handle = CreateEvent(0, 0, 0, 0);
		}

		virtual ~GisEvent()
		{
			CloseHandle(_handle);
			_handle = 0;
		}

		bool set()
		{
			BOOL res = SetEvent(_handle);
			return TRUE == res;
		}

		bool wait(DWORD ms = INFINITE)
		{
			bool ret = false;
			DWORD res = WaitForSingleObject(_handle, ms);
			switch (res)
			{
			case WAIT_OBJECT_0:
				ret = true;
			case WAIT_TIMEOUT:
				ret = false;
				break;
			default:
				ret = false;
				break;
			}
			return ret;
		}

		void reset()
		{
			return;
		}
	};
}