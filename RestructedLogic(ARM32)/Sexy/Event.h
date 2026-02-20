#pragma once
#include "DelegateBase.h"
#include "RtObject.h"

namespace Sexy
{
	class Event : public RtObject
	{
	private:
		std::vector<DelegateBase> delegates;

	public:
		void AddDelegate(DelegateBase& delegate);
	};
};