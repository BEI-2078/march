#pragma once
#include "component.hpp"
#include "controlBus.hpp"
#include "dataAddressBus.hpp"
#include "internalBus.hpp"
#include "rom.hpp"	

namespace microprocessor
{
	//From a higher view, all this does is 
	//change the signal values in the buses
	class timingAndControl
	{
	public:
		timingAndControl();
		~timingAndControl();
		
		void memoryReadSignals();
		void memoryWriteSignals();
		void aluINRSignals();
		void aluDCRSignals();
		void clockFallingEdge(machineCycle& activeCycle);
	};
}
