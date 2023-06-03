#pragma once
#include "microprocessor.hpp"

#include "ram.hpp"
#include "rom.hpp"

#include "controlBus.hpp"
#include "dataAddressBus.hpp"

#include "input.hpp"
#include "output.hpp"

#include <memory>
#include <iostream>

//8085 connected to sfml
//this should be the first time this has happened
namespace microcontroller
{
	//I'm calling it a system, one could call it a computer 
	struct system
	{
		//cpu, memory, io, bus
		std::unique_ptr<microprocessor::atat5> m_atat5; 
		std::unique_ptr<microcontroller::memory> m_ram; 
		std::unique_ptr<io::input> m_input; 
		std::unique_ptr<io::output> m_output; 
		std::unique_ptr<systemBus::controlBus> m_controlSignals; 
		std::unique_ptr<systemBus::dataAddressBus> m_dataAddress;

		system() 
		:
			m_atat5(std::make_unique<microprocessor::atat5>()),
			m_ram(std::make_unique<microcontroller::memory>()),
			m_input(std::make_unique<io::input>()),
			m_output(std::make_unique<io::output>()),
			m_controlSignals(std::make_unique<systemBus::controlBus>()),
			m_dataAddress(std::make_unique<systemBus::dataAddressBus>())
		{
		}

		void execute(twoBytes startingAddress = 0)
		{
			//initialize stuff for execution;
			m_atat5->m_registers->m_programCounter = startingAddress;
			this->m_atat5->m_HLT = false;
/*
			//INPUT PROGRAM; 
			m_ram->dmaInput(startingAddress, 0x3c); //INR A
			m_ram->dmaInput(startingAddress, 0x3c); //INR A
			m_ram->dmaInput(startingAddress, 0x3c); //INR A
			m_ram->dmaInput(startingAddress, 0x3c); //INR A
			m_ram->dmaInput(startingAddress, 0x3c); //INR A
			m_ram->dmaInput(startingAddress + 4, 0x76); //HLT
*/

			std::cout<<"Value of Accumulator before execution: "<<(unsigned)m_atat5->m_accumulator->value<<"\n";	

			//oscillation crystal
			//1 iteration = 1 instruction cycle
			//an instruction cycle always starts with 
			//opcode fetch i.e. tstates()
			while(true) //if it encounters HLT, it breaks
			{
				//intializate the clock counter for the instruction cycle
				systemBus::controlBus::clockCycleCounter = 0;  
				machineCycle tem = opcodeFetch;
				//opcode fetch
				for(unsigned i = 0; i<3; i++)
				{
					m_atat5->m_timingAndControl->clockFallingEdge(tem);
		
					//extra stuff because I'm not working with wires here
					//commands equivalent to transmission of signal using wires
					m_atat5->m_registers->asyncUpdate();
					systemBus::dataAddressBus::asyncUpdate();
					
					m_ram->clockFallingEdge();

					systemBus::dataAddressBus::asyncUpdate();
					
				}
				//std::cout<<"Program Counter: "<<this->m_atat5->m_registers->m_programCounter<<"\n";
				this->m_atat5->m_registers->instructionRegister = microprocessor::internalBus::dataBus;
				if(this->m_atat5->m_registers->instructionRegister == 0x76) break; 

				this->m_atat5->m_registers->m_programCounter++;
				//std::cout<<"Opcode in instruction register is: "<<(unsigned)this->m_atat5->m_registers->instructionRegister<<"\n";
				

				//decoding
				try
				{
					auto decodedInstruction = this->m_atat5->instructionDecoder[this->m_atat5->m_registers->instructionRegister];					
					//this is where memRead, memWrite, etc stuff happen
					for(auto &cycle: decodedInstruction)
					{
						m_atat5->m_timingAndControl->clockFallingEdge(cycle);

						//send the cycle, get the control signals on the bus,
						//then can asyncUpdate on everything
						//Normally this would be automatically implemented in 
						//physical systems
						this->m_atat5->m_alu->asyncUpdate();
					}
				}
				catch(...)
				{
					this->m_output->consoleWrite("Opcode not implemented in decoder");
				}
				
			}
			std::cout<<"Value of Accumulator after execution: "<<(unsigned)m_atat5->m_accumulator->value<<"\n";	
		}
	};
}
