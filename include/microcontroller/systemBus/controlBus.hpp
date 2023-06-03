#pragma once

#include <stdint.h>
#include "rom.hpp"
//buses are by their nature, shared 
//so making their methods and data members 
//inline static is the way to go
//inline makes it such that initialization
//is not required outside the struct and 
//the use of static should be obvious


//the control bus is under direct control
//of the control unit/timingAndControl
namespace systemBus 
{
	struct controlBus
	{
		//the clock out from the muP
		inline static unsigned clockCycleCounter = 0;

		//reset signals
		inline static signal resetIN_0 = HIGH, resetOUT = LOW;
		//ready signal; idk what to do with this
		inline static signal READY = HIGH;

		//Initially undefined so can't be used to
		//do something until initialized which makes
		//sense
		//io/memory operation 
		inline static signal IO_M = STABLE;
		//_0 = complement i.e. active low
		inline static signal READ_0 = STABLE;
		inline static signal WRITE_0 = STABLE;
		//input/output operation
		inline static signal S1 = STABLE, S0 = STABLE;
		//address latch enable
		inline static signal ALE = LOW;

		//interrupt signals
		inline static signal INTR = LOW, INTA_0 = LOW;
		inline static signal TRAP = LOW;
		inline static signal RST7_5 = LOW, RST6_5 = LOW, RST5_5 = LOW;

		//dma
		inline static signal HOLD = LOW, HLDA = LOW;
	};		

}
