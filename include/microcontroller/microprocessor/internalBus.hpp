#pragma once
#include "rom.hpp"

namespace microprocessor
{
	//the keyboard for the opcodes
	struct internalBus
	{
		//internal dataAddress bus
		inline static oneByte dataBus = 0;

		//internal control signals bus
		inline static signal accumulatorRead_Write = STABLE;
		inline static signal temRegisterRead = LOW;
		inline static signal flagWrite = LOW;
		inline static signal aluAdd = LOW;
		inline static signal aluDCR = LOW;
		inline static signal aluINR = LOW;
		inline static signal pcToBuffers = LOW;
		inline static signal irRead = LOW;
		inline static signal mbrWrite = LOW;
	};
}
