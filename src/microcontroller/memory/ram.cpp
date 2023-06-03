#include "ram.hpp"
#include <iostream>

namespace microcontroller 
{
	memory::memory(unsigned size) 
		:
			m_size(size),
			m_ram(new oneByte [m_size])
	{
		for(unsigned i = 0; i<m_size; i++)
		{
			//default value is 0
			m_ram[i] = 0;
		}
	}

	memory::~memory()
	{
		delete [] m_ram; 	
	}

	void memory::activeAddress()
	{
		m_activeAddress = static_cast<twoBytes>(systemBus::dataAddressBus::MAR) << 8;  
		m_activeAddress |= systemBus::dataAddressBus::addressLatch;
	}

	void memory::memoryRead()
	{
		systemBus::dataAddressBus::MBR = m_ram[m_activeAddress];
		//this is where the infamous propagation delay happens ^
	}

	void memory::memoryWrite()
	{
		*(m_ram+m_activeAddress) = systemBus::dataAddressBus::MBR;
	}

	oneByte memory::dmaOutput(twoBytes address)
	{
		return *(m_ram+address);
	}


	void memory::dmaInput(twoBytes address, oneByte data)
	{
		//std::cout<<"Data added "<<(unsigned)data<<" to "<<(unsigned)address<<" as ";
		*(m_ram+address) = static_cast<oneByte>(data);
		//std::cout<<(unsigned)m_ram[address]<<"\n";
	}

	//let this be the blueprint,
	//when clock falling edge is called for a component,
	//it checks every signal on the systemBus that's relevant to
	//it and does stuff based on it
	void memory::clockFallingEdge()
	{
		if(systemBus::controlBus::IO_M == LOW)
		{
			activeAddress();
			if(systemBus::controlBus::READ_0 == LOW)
			{
				this->memoryRead();
			}
			else if(systemBus::controlBus::WRITE_0 == LOW)
			{
				this->memoryWrite();
			}
		}
	}

}
