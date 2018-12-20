#pragma once
#include "GisPlatform.hpp"
#include "GisFrame.hpp"

namespace GIS
{
	class GisApp
	{
	public:

		//�������ں���
		virtual bool createWindow(int width, int height, INSTANCE hInst) = 0;
		/// <summary>
		/// �������
		/// </summary>
		virtual GisFrame* createFrame() = 0;

		virtual void main(int argc, char** argv) = 0;
	};
}