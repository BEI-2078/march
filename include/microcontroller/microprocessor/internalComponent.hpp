#pragma once

namespace microprocessor
{
	class internalComponent
	{
	public:
		internalComponent(){};
		virtual ~internalComponent(){};

		//some internal components just read the bus 
		//while some do both
		virtual void readBus() {};
		virtual void writeBus() {};

		//non-negotiable
		virtual void asyncUpdate() = 0;
	};
}
