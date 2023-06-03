#pragma once

#include "controlBus.hpp"
#include "internalBus.hpp"
#include "component.hpp"
#include "rom.hpp"

#include <iostream>
namespace systemBus 
{

	//using only one bus to transmit data and address
	struct dataAddressBus : public microcontroller::component
	{
	public:
		
		inline static oneByte addressLatch;
		inline static oneByte MAR;
		inline static oneByte MBR;

		static void asyncUpdate()
		{
			if(systemBus::controlBus::ALE == HIGH)
			{
				addressLatch = MBR;
				systemBus::controlBus::ALE = LOW;
			}

			if(microprocessor::internalBus::mbrWrite == HIGH)
			{
				microprocessor::internalBus::dataBus = MBR;
				microprocessor::internalBus::mbrWrite = LOW;
			}
		}
		//idk how sid and sod work but my intuition says they
		//transmit data at 1 bit per clock falling edge so I'm 
		//making them bools
		static bool SID, SOD;
	};


	//I can't believe I was creating a class for 
	//wrapping a single 16 bit data. I guess I've 
	//fallen deep into the oop rabbit hole
}
