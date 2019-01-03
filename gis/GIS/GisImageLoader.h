#pragma once

#include "GisImage.hpp"

namespace GIS
{
	class GisImageLoader
	{
	public:
		static GisImage* load(const char* fileName);
		static bool loadImage(const char* fileName, GIS::GisImage& image);
		
		//加载png/jpg格式数据并转化成rgb
		static RgbBuffer* loadRgb_256X256(const char* fileName);

		//加载png/jpg格式数据并转化成rgba
		static RgbaBuffer* loadRgba_256X256(const char* fileName);

		static bool loadImageToRgb(const char* fileName, GisImage& image);
	};
}