#pragma once

namespace GIS
{
	class GisOpenGL;
	class GisContext
	{
	public:
		GisOpenGL* _device;
		/// ��굱ǰλ��x
		int _mouseX;
		/// ��굱ǰλ��y
		int _mouseY;
	};
}