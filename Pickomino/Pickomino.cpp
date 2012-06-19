#include "GameEngine.h"


int main (void)
{

	GameEngine GE;
	GE.initialize(std::string("script.lua"));
	//if(initializelua(std::string("script.lua"))) return 0;

	GE.gameloop();
	GE.end();
	//getchar();

	return 0;
}