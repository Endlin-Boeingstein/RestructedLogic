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

	struct SexyVector2 {
		float mX, mY;
		SexyVector2() : mX(0), mY(0) {};
		SexyVector2(float x, float y) : mX(x), mY(y) {};
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

	struct Point {
		int x;
		int y;

		Point() {};

		Point(int x, int y) : x(x), y(y) {};
	};

	struct FPoint {
		float x;
		float y;

		FPoint() {};

		FPoint(float x, float y) : x(x), y(y) {};
	};
}

struct Rect
{
	int mX, mY, mWidth, mHeight;

	Rect() {
		this->mX = 0;
		this->mY = 0;
		this->mWidth = 0;
		this->mHeight = 0;
	}

	Rect(int mX, int mY, int mWidth, int mHeight) {
		this->mX = mX;
		this->mY = mY;
		this->mWidth = mWidth;
		this->mHeight = mHeight;
	}
};

struct FRect {
	float mX, mY, mWidth, mHeight;

	FRect() {
		this->mX = 0;
		this->mY = 0;
		this->mWidth = 0;
		this->mHeight = 0;
	}

	FRect(float mX, float mY, float mWidth, float mHeight) {
		this->mX = mX;
		this->mY = mY;
		this->mWidth = mWidth;
		this->mHeight = mHeight;
	}
};

struct CornerRect {
	Sexy::FPoint topLeft;
	Sexy::FPoint topRight;
	Sexy::FPoint bottomLeft;
	Sexy::FPoint bottomRight;

	CornerRect() {}

	CornerRect(Sexy::FPoint&& topLeft, Sexy::FPoint&& topRight, Sexy::FPoint&& bottomLeft, Sexy::FPoint&& bottomRight) :
		topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight) {
	};
};

struct ValueRange
{
	float Min;
	float Max;

	ValueRange() : Min(0), Max(0) {};

	ValueRange(float Min, float Max) : Min(Min), Max(Max) {};
};