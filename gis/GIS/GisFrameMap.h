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
		/// 开始绘制
		/// </summary>
		virtual void onFrameStart(GisContext& context);

		/// <summary>
		/// 更新数据
		/// </summary>
		virtual void update(GisContext& context);

		/// <summary>
		/// 结束绘制
		/// </summary>
		virtual void onFrameEnd(GisContext& context);
	};
}



