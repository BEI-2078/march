#pragma once

#include "component.hpp"
#include "definitions.hpp"

#include "dataAddressBus.hpp"
#include "controlBus.hpp"


namespace microcontroller 
{

/*choices; 
array, 
hashmap, 
fileHandling
-array and hashmap should behave identically 
since we know the "key"/address but if i use 
a hashmap, i'll only need to allocate memory 
when required using insert

-fileHandling - manually looking up and poking
the memory is easier i guess i should use the 
file handling method because this is an emulator
and i'm trying to recreate all of the hardware 
conditions
*/
	
	//just for testing purposes 
	class memory : public microcontroller::component
	{
	public:
		//the size has to be unsigned and not 
		//twoBytes since 65536 can't fit in it
		memory(unsigned size = 65536);
		~memory();
	
		//memory only works during clock falling edge
		void clockFallingEdge() override;

		//temporary because this isn't technically
		//how dma works
		oneByte dmaOutput(twoBytes address);
		void dmaInput(twoBytes address, oneByte data);

	private:
		void memoryRead();
		void memoryWrite();

		void activeAddress();

		twoBytes m_activeAddress;
		unsigned m_size;
		oneByte *m_ram;
	};

	/*
	//using file handling it would be like the eeprom
	// 8085 uses
	class memoryFile
	{
	public:
		memoryFile();
		~memoryFile();
	};*/

}
