#pragma once
#include "internalComponent.hpp"
#include "rom.hpp"
#include "internalBus.hpp"

namespace microprocessor
{
	//the alu is defined here as the combination of the
	//accumulator, temRegister and flipFlops; kind of like
	//a mini blob unit like microprocessor

	struct accumulator : public microprocessor::internalComponent
	{
		void readBus() override { value = internalBus::dataBus; }
		void writeBus() override { internalBus::dataBus = value; }

		void asyncUpdate() override
		{
			if(internalBus::accumulatorRead_Write == STABLE){return;}
			else if(internalBus::accumulatorRead_Write == HIGH)
			{
				readBus();
			}
			else if(internalBus::accumulatorRead_Write == LOW)
			{
				writeBus();
			}
			internalBus::accumulatorRead_Write = STABLE;

		}

		inline static oneByte value = 0;
	};

	struct temRegister : public microprocessor::internalComponent
	{
		void readBus() override { value = internalBus::dataBus; }

		void asyncUpdate() override
		{
			if(internalBus::temRegisterRead == HIGH)
			{
				readBus();
			}
			internalBus::temRegisterRead = LOW;
		}

		inline static oneByte value = 0;
	};

	struct flipFlops : public microprocessor::internalComponent
	{
		void writeBus() override { internalBus::dataBus = value; }

		void asyncUpdate() override
		{
			if(internalBus::flagWrite == HIGH)
			{
				writeBus();
			}
			internalBus::flagWrite = LOW;
		}

		inline static oneByte value = 0;
	};


	struct alu : public microprocessor::internalComponent
	{
		//the timing and control will iterate through the machine
		//cycles of the opcode and update the internal control bus
		//and call the asyncUpdate() function
		void asyncUpdate()
		{
			if(internalBus::aluAdd == HIGH)
			{
				result = accumulator::value + temRegister::value;
				internalBus::dataBus = result;
				internalBus::aluAdd = LOW;
			}

			if(internalBus::aluDCR == HIGH)
			{
				accumulator::value--;
				internalBus::aluDCR = LOW;
			}

			if(internalBus::aluINR == HIGH)
			{
				accumulator::value++;
				internalBus::aluINR = LOW;
			}
			//other comparison stuff
		}
	private:
		oneByte result;
	};
}


