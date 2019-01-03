#include "GisImageLoader.h"

namespace GIS
{
	GisImage* GisImageLoader::load(const char* fileName)
	{
		GisImage* pImage = 0;
		return pImage;
	}

	bool GisImageLoader::loadImage(const char* fileName, GIS::GisImage& image)
	{
		return true;
	}

	RgbBuffer* GisImageLoader::loadRgb_256X256(const char* fileName)
	{
		RgbBuffer* pBufer = 0;
		return pBufer;
	}

	RgbaBuffer* GisImageLoader::loadRgba_256X256(const char* fileName)
	{
		RgbaBuffer* pBufer = 0;
		return pBufer;
	}

	bool GisImageLoader::loadImageToRgb(const char* fileName, GisImage& image)
	{
		int width = 0;
		int height = 0;
		int channel = 0;

		return true;
	}

	

}

