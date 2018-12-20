#pragma once
#include "GisContext.hpp"
#include "GisInput.hpp"

namespace GIS
{
	class GisFrame : public GisInput
	{
	public:
		GisContext & _context;
	public:
		GisFrame(GisContext& context):_context(context)
		{}
		virtual ~GisFrame()
		{}

		/// <summary>
		/// ��ʼ����
		/// </summary>
		virtual void onFrameStart(GisContext& context) = 0;

		/// <summary>
		/// ��������
		/// </summary>
		virtual void update(GisContext& context) = 0;

		/// <summary>
		/// ��������
		/// </summary>
		virtual void onFrameEnd(GisContext& context) = 0;
	};
}