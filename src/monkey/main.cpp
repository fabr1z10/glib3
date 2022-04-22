#include <iostream>
#include <version.h>
#include <monkey/engine.h>
#include "btBulletDynamicsCommon.h"

int main(int argc, char* argv[])
{

	if (argc < 2) {
		std::cout << "The Monkey Engine " << VERSION << "\n";
		std::cout << "Usage: monkey <directory>" << std::endl;
		return 1;
	}
	try {
		std::string gameDir(argv[1]);
		auto& engine = Engine::get();
		engine.init(gameDir);
		engine.MainLoop();
	}
	catch (Error & err) {
		std::cerr << err.what() << std::endl;
		return 1;
	}
	return 0;
}
