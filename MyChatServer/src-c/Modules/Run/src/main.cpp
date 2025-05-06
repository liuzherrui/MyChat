
#include <iostream>
#include "Server.h"

using namespace MyChat;

int main(int argc, char* argv[])
{

	ServerKernel sk;
	sk.init();
	sk.start();
	
	while (sk.isRunning()) {
		sk.update();
	}

	return 0;
}