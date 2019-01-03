#pragma once

#include "GisImage.hpp"

namespace GIS
{
	class GisImageLoader
	{
	public:
		static GisImage* load(const char* fileName);
		static bool loadImage(const char* fileName, GIS::GisImage& image);
		
		//����png/jpg��ʽ���ݲ�ת����rgb
		static RgbBuffer* loadRgb_256X256(const char* fileName);

		//����png/jpg��ʽ���ݲ�ת����rgba
		static RgbaBuffer* loadRgba_256X256(const char* fileName);

		static bool loadImageToRgb(const char* fileName, GisImage& image);
	};
}