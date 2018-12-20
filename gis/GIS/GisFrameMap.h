#pragma once
#include "GisFrame.hpp"

namespace GIS
{
	class GisFrameMap : public GisFrame
	{
	public:
		GisFrameMap(GisContext& context);
		virtual ~GisFrameMap();

		/// <summary>
		/// ��ʼ����
		/// </summary>
		virtual void onFrameStart(GisContext& context);

		/// <summary>
		/// ��������
		/// </summary>
		virtual void update(GisContext& context);

		/// <summary>
		/// ��������
		/// </summary>
		virtual void onFrameEnd(GisContext& context);

		/// <summary>
		/// ����������
		/// </summary>
		virtual void onLButtonDown(int x, int y);

		/// <summary>
		/// ����������
		/// </summary>
		virtual void onLButtonUp(int x, int y);

		/// <summary>
		/// ����ƶ�
		/// </summary>
		virtual void onMouseMove(int x, int y);
	};
}



