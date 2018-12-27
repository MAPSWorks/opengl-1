#pragma once

#include "GisProgramLibrary.hpp"
namespace GIS
{
	class GisResourceMgr
	{
	public:
		//��Ի�����Ļ2ά����
		PROGRAM_P2_UC _PROGRAM_P2UC;

	public:
		GisResourceMgr()
		{

		}

		~GisResourceMgr()
		{

		}

	public:
		void initialize(GisOpenGL* device)
		{
			_PROGRAM_P2UC.initialize(device);
		}

		void destroy()
		{
			_PROGRAM_P2UC.destroy();
		}
	};
}