#pragma once

namespace Sexy
{
	class RtClass;

	class RtObject
	{
	public:
		virtual RtClass* GetType() {};
		virtual bool Function1() {};
		virtual void Destruct1() {};
		virtual void Destruct2() {};
		virtual bool IsType(RtClass* type) {};
		virtual bool Function5() {};
		virtual bool Serialize(RtClass* type) {};
	};
}