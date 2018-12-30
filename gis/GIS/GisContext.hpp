#pragma once
#include "glm\gtc\matrix_transform.hpp"

namespace GIS
{
	class GisResourceMgr;
	class GisOpenGL;
	class GisContext
	{
	public:
		GisOpenGL* _device;

		//资源管理者指针
		GisResourceMgr* _resMgr;

		/// 鼠标当前位置x
		int _mouseX;
		/// 鼠标当前位置y
		int _mouseY;

		//窗口宽高
		int _width;
		int _height;

		//2d屏幕投影矩阵
		glm::mat4 _screenPrj;
	};
}