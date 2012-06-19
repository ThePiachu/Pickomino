#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Graphics.h"
#include "Physics.h"
#include "GraphicsAndPhysics.h"
#include "Sound.h"
#include "EventReceiver.h"
#include "Players.h"
#include "Scripting.h"

#include <vector>
#include <map>
#include <iostream>
#include <string.h>


using namespace std;




class GameEngine
{
public:
	bool runengine;//, gameended;
	//bool dicesrolling;
	MastEventReceiver mer;
	//unsigned int score;
	//std::string endstr;
	//bool dicepicked, tilepicked;
	GameButtonManager& gbm;
	SoundManager& sm;
	GameObjectManager& gom;
	//PlayerManager& pm;
	GameEngine():
		runengine(true),
		//gameended(false),
		//dicesrolling(true),
		mer(),/*
		score(0),
		endstr(""),
		dicepicked(false),
		tilepicked(false),*/
		gbm(GameButtonManager::getinstance()),
		sm(SoundManager::getinstance()),
		gom(GameObjectManager::getinstance())//,
		//pm(PlayerManager::getinstance())
	{
	}
	~GameEngine()
	{
	}
	void initialize(const std::string& LuaScript)
	{
		mer.init();
		initializeirrlicht(&mer);
		initializeode();

		smgr->addLightSceneNode();

		sm.initialize();

		if(initializelua(LuaScript)) exit(-1);
	}
	void end()
	{
		endirrlicht();
		endode();
	}


	void gameloop()
	{

		//std::map<std::string, GameButton, comparestrings>::iterator it;
		//dicesrolling=true;
		luastartgame();//starting the game with lua
		runengine=true;
		while(device->run()&&runengine)
		{
			if (device->isWindowActive())
			{
				mer.endEventProcess();

				bool tmp=false;
				for(unsigned int i=0;i<gom.size();i++)if(gom(i).body)
				{
					tmp=tmp||gom(i).bodyisenabled();
				}
				if(tmp==false)//ODE is done simulation
				{
					luaendofsimulation();
				}
				luaidlefunction();
				checkkeys();

				driver->beginScene(true, true, SColor(255,100,101,140));
				smgr->drawAll();
				
				luaprint();
				
				guienv->drawAll();
				driver->endScene();

				//simulating ODE and updating positions
				runSimulationODE();
				gom.recalculatepositions();
				mer.startEventProcess();
			}
		}
	}

	void checkkeys()
	{
		if (mer.keyPressed(KEY_KEY_1))
		{//prints position of the mouse
			cout<<mer.mouseX()<<" "<<mer.mouseY()<<endl<<flush;
		}
		if(mer.keyPressed(KEY_ESCAPE))
		{//quits the game
			runengine=false;
		}
		if(mer.leftMousePressed())
		{
			std::map<std::string, GameButton, comparestrings>::iterator it;
			for(it=gbm.buttons.begin();it!=gbm.buttons.end();++it)
			{
				if(it->second.isclicked(mer.mouseX(), mer.mouseY()))
				{
					luabuttonclicked(it->second.name);
				}	
			}
		}
	}
};



#endif /* GAMEENGINE_H_ */