#include "application.hpp"

int main()
{
	Engine::Application march;
	march.Run();
	return 0;
}

//sanity checks
//for (unsigned i = 0; i<10; i++) std::cout<<march.independentAccess(i);

/*
   microcontroller::memory mem;
   mem.dmaInput(65535, 42);
   std::cout<<unsigned(mem.dmaOutput(65535))<<"\n";
   mem.dmaInput(0, 255);
   std::cout<<unsigned(mem.dmaOutput(0))<<"\n";
   */
