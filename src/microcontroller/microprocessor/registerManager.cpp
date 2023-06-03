#include "registerManager.hpp"

namespace microprocessor
{
	registerManager::registerManager() :
	B(0), C(0), D(0), E(0), H(0), L(0),
	instructionRegister(0),
	m_stackPointer(0), m_programCounter(0),
	W(0), Z(0)
	{
	}

	registerManager::~registerManager()
	{
	}
}
