#include "timingAndControl.hpp"
#include <iostream>

namespace microprocessor
{
	timingAndControl::timingAndControl()
	{
	}
	
	timingAndControl::~timingAndControl()
	{
	}
	
	//Like I said machine cycles are basically hardcoded
	//in the microprocessor so to be true to it,
	void timingAndControl::memoryReadSignals()
	{
		//t states
		switch(systemBus::controlBus::clockCycleCounter)
		{
			//t1
			case 1:
				internalBus::pcToBuffers = HIGH;

				systemBus::controlBus::ALE = HIGH;
				systemBus::controlBus::IO_M = LOW;
				systemBus::controlBus::READ_0 = HIGH;
				systemBus::controlBus::WRITE_0 = HIGH;
				systemBus::controlBus::S1 = HIGH;
				systemBus::controlBus::S0 = HIGH;
				break;
			//t2
			case 2:
			//everthing else remains same except for
				internalBus::pcToBuffers = LOW;
				
				systemBus::controlBus::ALE = LOW;
				systemBus::controlBus::READ_0 = LOW;
				break;
			//t3
			case 3:
				systemBus::controlBus::READ_0 = HIGH;
				internalBus::mbrWrite = HIGH;
				break;
			default:
				break;
		}
	}

	void timingAndControl::memoryWriteSignals()
	{
		//t states
		switch(systemBus::controlBus::clockCycleCounter)
		{
			//t1
			case 1:
				internalBus::pcToBuffers = HIGH;

				systemBus::controlBus::ALE = HIGH;
				systemBus::controlBus::IO_M = LOW;
				systemBus::controlBus::READ_0 = HIGH;
				systemBus::controlBus::WRITE_0 = HIGH;
				systemBus::controlBus::S1 = HIGH;
				systemBus::controlBus::S0 = HIGH;
				break;
			//t2
			case 2:
			//everthing else remains same except for
				internalBus::pcToBuffers = LOW;
				
				systemBus::controlBus::ALE = LOW;
				systemBus::controlBus::READ_0 = LOW;
				break;
			//t3
			case 3:
				systemBus::controlBus::READ_0 = HIGH;
				internalBus::mbrWrite = HIGH;
				break;
			default:
				break;
		}
	}
	void timingAndControl::aluINRSignals()
	{
		internalBus::aluINR = HIGH;
	}

	void timingAndControl::aluDCRSignals()
	{
		internalBus::aluDCR = HIGH;
	}

	void timingAndControl::clockFallingEdge(machineCycle &activeCycle)
	{
		systemBus::controlBus::clockCycleCounter++;  
		if(activeCycle == opcodeFetch || activeCycle == memoryRead) memoryReadSignals();
		else if(activeCycle == aluINR) aluINRSignals();
		else if(activeCycle == aluDCR) aluDCRSignals();
	}
}
