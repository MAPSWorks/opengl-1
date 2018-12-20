#pragma once

namespace GIS
{
	class GisOpenGL;
	class GisContext
	{
	public:
		GisOpenGL* _device;
		/// 鼠标当前位置x
		int _mouseX;
		/// 鼠标当前位置y
		int _mouseY;
	};
}