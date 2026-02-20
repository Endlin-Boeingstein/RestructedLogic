#pragma once
#include <cstdint>
#include <string>

namespace Sexy
{
	typedef std::string SexyString;

	typedef uint8_t byte;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned long ulong;

	// idfk i found this in Board's buildSymbols
	// its probably just a float
	typedef float pvztime_t;

	struct SexyVector2
	{
		float mX, mY;

		SexyVector2() : mX(0), mY(0) {}

		SexyVector2(float x, float y)
		{
			this->mX = x;
			this->mY = y;
		}
	};

	struct SexyVector3
	{
		float mX, mY, mZ;

		SexyVector3() : mX(0), mY(0), mZ(0) {};

		SexyVector3(float x, float y, float z)
		{
			mX = x;
			mY = y;
			mZ = z;
		}
	};
	struct Point
	{
		int mX;
		int mY;

		Point() {};

		Point(int x, int y) : mX(x), mY(y) {};
	};

	struct FPoint
	{
		float mX;
		float mY;

		FPoint() {};

		FPoint(float x, float y) : mX(x), mY(y) {};
	};
};

struct Rect
{
	int mX, mY, mWidth, mHeight;

	Rect() : mX(0), mY(0), mWidth(0), mHeight(0) {}

	Rect(int x, int y, int width, int height)
	{
		mX = x;
		mY = y;
		mWidth = width;
		mHeight = height;
	}
};

struct FRect
{
	float mX, mY, mWidth, mHeight;

	FRect() : mX(0), mY(0), mWidth(0), mHeight(0) {}

	FRect(float x, float y, float width, float height)
	{
		mX = x;
		mY = y;
		mWidth = width;
		mHeight = height;
	}
};



struct ValueRange
{
	float Min;
	float Max;

	ValueRange() : Min(0), Max(0) {};

	ValueRange(float Min, float Max) : Min(Min), Max(Max) {};
};