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

		//��Դ������ָ��
		GisResourceMgr* _resMgr;

		/// ��굱ǰλ��x
		int _mouseX;
		/// ��굱ǰλ��y
		int _mouseY;

		//���ڿ��
		int _width;
		int _height;

		//2d��ĻͶӰ����
		glm::mat4 _screenPrj;
	};
}