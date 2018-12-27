#pragma once

namespace GIS
{
	class GisResourceMgr;
	class GisOpenGL;
	class GisContext
	{
	public:
		GisOpenGL* _device;
		GisResourceMgr* _resMgr;

		/// ��굱ǰλ��x
		int _mouseX;
		/// ��굱ǰλ��y
		int _mouseY;

		//���ڿ��
		int _width;
		int _height;

		//2d��ĻͶӰ����
		//matrix4r _screenPrj;
	};
}