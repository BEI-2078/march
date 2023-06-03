#pragma once
#include <memory>

#include "timingAndControl.hpp"
#include "alu.hpp"
#include "instruction.hpp"
#include "registerManager.hpp"
#include "interruptControl.hpp"
#include "dataAddressBus.hpp"
#include "controlBus.hpp"

#include <iostream>
#include <string>

namespace microprocessor
{
	struct atat5 
	{
		std::unique_ptr<microprocessor::timingAndControl> m_timingAndControl;
		std::unique_ptr<microprocessor::alu> m_alu;
		std::unique_ptr<microprocessor::accumulator> m_accumulator;
		std::unique_ptr<microprocessor::temRegister> m_temRegister;
		std::unique_ptr<microprocessor::flipFlops> m_flipFlops;

		std::unique_ptr<microprocessor::registerManager> m_registers;

		atat5()
		:
			m_timingAndControl(std::make_unique<microprocessor::timingAndControl>()),
			m_alu(std::make_unique<microprocessor::alu>()),
			m_accumulator(std::make_unique<microprocessor::accumulator>()),
			m_temRegister(std::make_unique<microprocessor::temRegister>()),
			m_flipFlops(std::make_unique<microprocessor::flipFlops>()),
			m_registers(std::make_unique<microprocessor::registerManager>())
		{
			//populate opcodes here for now
			instructionDecoder[0x3c] = {aluINR}; //INR A
			instructionDecoder[0x3d] = {aluDCR}; //DCR A
								     
			std::cout<<"Creation of instruction table completed\n";
		}

		//ok so supppose its LDA,
		//it is decoded to 
		//memoryRead() 
		//MBR->internal Bus->W register
		//memoryRead() 
		//MBR->internal Bus->Z register
		//WZ register pair->...
		std::unordered_map<oneByte, std::vector<machineCycle>> instructionDecoder;
		//this might be replaced with a function reduced neural network later
		
		bool m_HLT;
	};



}
