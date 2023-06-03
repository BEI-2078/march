#pragma once
#include "rom.hpp"
#include "internalComponent.hpp"
#include "internalBus.hpp"
#include "dataAddressBus.hpp"

//full disclaimer, even though we generally work 
//with hex in these muPs, I'm purposely gonna
//work with decimals because I don't know of a 
//system to change the base-system of in-built
//data bytes


namespace microprocessor
{
	struct registerManager : public microprocessor::internalComponent
	{
	public:
		registerManager();
		~registerManager();
		
		void asyncUpdate() override
		{
			if(internalBus::pcToBuffers == HIGH)
			{
				systemBus::dataAddressBus::MBR = static_cast<uint8_t>(m_programCounter & 255);
				systemBus::dataAddressBus::MAR = static_cast<uint8_t>(m_programCounter>>8);			
				
				//std::cout<<(unsigned)systemBus::dataAddressBus::MAR<<(unsigned)systemBus::dataAddressBus::MBR<<"\n";
				internalBus::pcToBuffers = LOW;
			}
			if(internalBus::irRead == HIGH)
			{
				instructionRegister = internalBus::dataBus;
				internalBus::irRead = LOW;
			}

		}

		oneByte B, C, D, E, H, L;
		oneByte instructionRegister;
		twoBytes m_stackPointer, m_programCounter;

	private:
		oneByte W, Z;
	};

}

//as it stands, homa and loma are completely useless 
//in this emulation as the program counter does 
//everything but i'm gonna include them for 
//completeness' sake as you look into this 
//emulator more, you're gonna realise this 
//theme is more prevelant than not
