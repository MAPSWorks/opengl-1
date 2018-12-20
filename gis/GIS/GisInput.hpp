#pragma once

namespace GIS
{
	class GisInput
	{
	public:
		/// <summary>
		/// 鼠标左键按下
		/// </summary>
		virtual void onLButtonDown(int x, int y) = 0;

		/// <summary>
		/// 鼠标左键弹起
		/// </summary>
		virtual void onLButtonUp(int x, int y) = 0;

		/// <summary>
		/// 鼠标移动
		/// </summary>
		virtual void onMouseMove(int x, int y) = 0;
	};
}