#pragma once
#include "rom.hpp"
#include <vector>
#include <string>

namespace microprocessor
{
	//an instruction is defined here 
	//as an array of control signals
	//that come one after another
	
	//this isn't working properly, i'm using the vector of machineCycles directly now
	//but it'd be nice to store the name with the machineCycles
	struct instruction
	{
		instruction(std::string mnemonic, const std::vector<machineCycle> &cycles)
		:
			m_mnemonic(std::move(mnemonic)),
			m_cycles(cycles)
		{
		}
		std::string m_mnemonic;
		std::vector<machineCycle> m_cycles;
	};
}


