#pragma once
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "GisMath.hpp"
#include "GisObject.hpp"

namespace GIS
{
	class GisImage : public GisObject
	{
	public:
		enum Format
		{
			FORMAT_NONE		= 0,
			FORMAT_RGB8		= 1,
			FORMAT_RGBA8	= 2,
			FORMAT_DXT1		= 3,
			FORMAT_DXT5		= 4,
		};

	public:
		unsigned int	_width;
		unsigned int	_height;
		Format			_format;
		unsigned char*	_buffer;
	public:
		GisImage()
		{
			_width	= 0;
			_height	= 0;
			_format = FORMAT_NONE;
			_buffer = 0;
		}
		virtual ~GisImage()
		{
			destroy();
		}

		virtual bool isEmpty()
		{
			return 0 == _buffer;
		}

		virtual int size()
		{
			return calcSize(_width, _height, _format);
		}

		virtual void destroy()
		{
			if (_buffer)
			{
				delete [] _buffer;
				_buffer = 0;
				_width	= 0;
				_height = 0;
				_format = FORMAT_NONE;
			}
		}

		virtual void create(unsigned int w, unsigned int h, Format fmt)
		{
			if (_width != w || _height != h || _format != fmt)
			{
				destroy();
				_width = w;
				_height = h;
				_format = fmt;
				_buffer = new unsigned char[calcSize(w, h, fmt)];
			}
		}

		virtual void create(unsigned int w, unsigned int h, Format fmt, const void* data)
		{
			size_t length = calcSize(w, h, fmt);
			if (_width != w || _height != h || _format != fmt)
			{
				destroy();
				_width = w;
				_height = h;
				_format = fmt;
				
			}
			if (0 == _buffer)
			{
				_buffer = new unsigned char[length];
			}

			if (0 != data)
			{
				memcpy(_buffer, data, length);
			}
		}

		virtual void* data()
		{
			return _buffer;
		}

		virtual void detach()
		{
			_buffer	= 0;
			_width	= 0;
			_height = 0;
		}

	protected:
		static int calcSize(int w, int h, Format fmt)
		{
			int imageSize = 0;
			switch (fmt)
			{
			case FORMAT_NONE:
				imageSize = 0;
				break;
			case FORMAT_RGB8:
				imageSize = w * h * 3;
				break;
			case FORMAT_RGBA8:
				imageSize = w * h * 4;
				break;
			case FORMAT_DXT1:
				imageSize = w * h * 4 / 8;
				break;
			case FORMAT_DXT5:
				imageSize = w * h * 4 / 4;
				break;
			default:
				imageSize = 0;
				break;
			}

			return imageSize;
		}
	};

	template<int w = 256, int h = 256>
	class GisImageRgb : public GisImage
	{
	public:
		unsigned char _data[w * h * 3];
	public:
		GisImageRgb()
		{
			_width = 0;
			_height = 0;
			_format = FORMAT_RGB8;
			_buffer = 0;
		}

		virtual ~GisImageRgb()
		{
			_buffer = 0;
		}
	};

	template<int w = 256, int h = 256>
	class GisImageRgba : public GisImage
	{
	public:
		unsigned char _data[w * h * 4];
	public:
		GisImageRgba()
		{
			_width = 0;
			_height = 0;
			_format = FORMAT_RGBA8;
			_buffer = 0;
		}

		virtual ~GisImageRgba()
		{
			_buffer = 0;
		}
	};

	template<int w = 256, int h = 256>
	class GisImageDXT1 : public GisImage
	{
	public:
		unsigned char _data[w * h * 4 / 8];
	public:
		GisImageDXT1()
		{
			_width = 0;
			_height = 0;
			_format = FORMAT_DXT1;
			_buffer = 0;
		}

		virtual ~GisImageDXT1()
		{
			_buffer = 0;
		}
	};

	template<int w = 256, int h = 256>
	class GisImageDXT5 : public GisImage
	{
	public:
		unsigned char _data[w * h * 4 / 4];
	public:
		GisImageDXT5()
		{
			_width = 0;
			_height = 0;
			_format = FORMAT_DXT5;
			_buffer = 0;
		}

		virtual ~GisImageDXT5()
		{
			_buffer = 0;
		}
	};

	typedef GisImageRgba<256, 256>	RgbaBuffer;
	typedef GisImageRgb<256, 256>	RgbBuffer;
	typedef GisImageDXT1<256, 256>	DXT1Buffer;
	typedef GisImageDXT5<256, 256>	DXT5Buffer;
}