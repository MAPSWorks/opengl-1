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
	};
}



