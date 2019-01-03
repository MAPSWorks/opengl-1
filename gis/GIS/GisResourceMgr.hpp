#pragma once

#include "GisProgramLibrary.hpp"
#include "GisImageLoader.h"
#include <map>

namespace GIS
{
	class GisResourceMgr
	{
	public:
		typedef std::map<std::string, Texture*> MapTexture;
	public:
		GisOpenGL*		_device;
		//针对绘制屏幕2维数据
		PROGRAM_P2_UC _PROGRAM_P2UC;
		///
		MapTexture _mapTexture;
	public:
		GisResourceMgr() : _device(0)
		{

		}

		~GisResourceMgr()
		{

		}

	public:
		void initialize(GisOpenGL* device)
		{
			_device = device;
			_PROGRAM_P2UC.initialize(device);
		}

		void destroy()
		{
			_PROGRAM_P2UC.destroy();
		}

		///获取纹理资源
		Texture* getTexture(const char* filePathname)
		{
			MapTexture::iterator itr = _mapTexture.find(filePathname);
			if (itr != _mapTexture.end())
			{
				///加载数据，并创建纹理
				///加入系统中
				return 0;
			}
			else
			{
				return itr->second;
			}
		}

		//创建1D纹理方法
		Texture1d* createTexture1d(const char* pName)
		{
			Texture* pTex = getTexture(pName);
			if (NULL != pTex)
			{
				return dynamic_cast<Texture1d*>(pTex);
			}
			else
			{
				Texture1d* pTex1d = new Texture1d;
				*pTex1d = createTexture1DFromImage(pName);
				_mapTexture[pName] = pTex1d;
				return pTex1d;
			}
		}

		//创建2D纹理方法
		Texture2d* createTexture2d(const char* pName)
		{
			Texture* pTex = getTexture(pName);
			if (NULL != pTex)
			{
				return dynamic_cast<Texture2d*>(pTex);
			}
			else
			{
				Texture2d* pTex2d = new Texture2d;
				*pTex2d = createTexture2DFromImage(pName);
				_mapTexture[pName] = pTex2d;
				return pTex2d;
			}
		}

		//创建3D纹理方法
		Texture3d* createTexture3d(const char* pId, int w, int h, int d, int fmt)
		{
			Texture* pTex = getTexture(pId);
			if (NULL != pTex)
			{
				return dynamic_cast<Texture3d*>(pTex);
			}
			else
			{
				Texture3d* pTex3d = new Texture3d;
				*pTex3d = _device->createTexture2dArray(w, h, d, fmt);
				_mapTexture[pId] = pTex3d;
				return pTex3d;
			}
		}

	protected:
		Texture1d createTexture1DFromImage(const char* pathName)
		{
			Texture1d	tex;
			GisImage	image;
			bool res = GisImageLoader::loadImage(pathName, image);
			if (true == res)
			{
				switch (image._format)
				{
				case GisImage::FORMAT_RGB8:
					_device->createTexture1D(0, GL_RGB, image._width, 0, GL_RGB, GL_UNSIGNED_BYTE, image._buffer);
					break;
				case GisImage::FORMAT_RGBA8:
					_device->createTexture1D(0, GL_RGB, image._width, 0, GL_RGBA, GL_UNSIGNED_BYTE, image._buffer);
					break;
				default:
					break;
				}				
			}
			return tex;
		}

		Texture2d createTexture2DFromImage(const char* pathName)
		{
			Texture2d tex;
			GisImage	image;
			bool res = GisImageLoader::loadImage(pathName, image);
			if (true == res)
			{
				switch (image._format)
				{
				case GisImage::FORMAT_RGB8:
					_device->createTexture2D(0, GL_RGB, image._width, image._height, 0, GL_RGB, GL_UNSIGNED_BYTE, image._buffer);
					break;
				case GisImage::FORMAT_RGBA8:
					_device->createTexture2D(0, GL_RGB, image._width, image._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image._buffer);
					break;
				default:
					break;
				}
			}
			return tex;
		}

		Texture3d createTexture3DFromImage(const char* pathName)
		{
			/*Texture3d tex;
			GisImage	image;
			bool res = GisImageLoader::loadImage(pathName, image);
			if (true == res)
			{
				switch (image._format)
				{
				case GisImage::FORMAT_RGB8:
					_device->createTexture3D(0, GL_RGB, image._width, image._height, image._depth, 0, GL_RGB, GL_UNSIGNED_BYTE, image._buffer);
					break;
				case GisImage::FORMAT_RGBA8:
					_device->createTexture3D(0, GL_RGB, image._width, image._height, image._depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image._buffer);
					break;
				default:
					break;
				}
			}
			return tex;*/
		}

	};
}