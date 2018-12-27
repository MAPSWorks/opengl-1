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

		/// 鼠标当前位置x
		int _mouseX;
		/// 鼠标当前位置y
		int _mouseY;

		//窗口宽高
		int _width;
		int _height;

		//2d屏幕投影矩阵
		//matrix4r _screenPrj;
	};
}