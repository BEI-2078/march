//this will also contain definitions and such
#pragma once

#include <cstdint>
#include <unordered_map>

typedef uint8_t oneByte;
typedef uint16_t twoBytes;


//STABLE is basically my version of NULL state
enum signal
{
	STABLE,
	LOW,
	RISING,
	HIGH,
	FALLING,
};

//A machine cycle is defined as movement of 1 byte data anywhere
//in the system, groups of machine cycles is an instruction.
enum machineCycle
{
	//the "standard" machine cycles
	opcodeFetch,
	memoryRead,
	memoryWrite,
	ioRead,
	ioWrite,

	//these are also machine cycles why the hell did no one teach this?
	//do ydu know how much I had to think to come to this conclusion?
	//only difference is that these are async processes and the "standard"
	//ones are synchronous processes
	accumulatorRead,
	accumulatorWrite,
	temRegisterRead,
	flagWrite,
	aluAdd,
	aluDCR,
	aluINR,
	pcToBuffers,
};

class Error;
