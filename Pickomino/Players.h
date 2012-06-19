#ifndef PLAYERS_H_
#define PLAYERS_H_

#include "Graphics.h"
#include "Physics.h"
#include "GraphicsAndPhysics.h"
#include "Sound.h"
#include "EventReceiver.h"

#include <vector>
#include <map>
#include <iostream>
#include <string.h>


class Player
{
public:
	GameButtonManager& gbm;
	unsigned int number;
	core::rect<s32> playersarea;
	vector<std::string> tiles;

	Player(unsigned int Number=0,
		const core::rect<s32> Area=core::rect<s32>(0, 0, 0, 0)):
		gbm(GameButtonManager::getinstance()),
		number(Number),
		playersarea(Area),
		tiles()
	{
	}
	Player& operator=(const Player& Other)
	{
		number=Other.number;
		playersarea=Other.playersarea;
		tiles=Other.tiles;
		return *this;
	}

	void poptile(std::string Tile)
	{
		for(unsigned int i=0;i<tiles.size();i++)
		{
			if(tiles.at(i).compare(Tile)==0)
			{
				tiles.erase(tiles.begin()+i);
				break;
			}
		}
	}
	void pushtile(std::string Tile)
	{
		tiles.push_back(Tile);
	}

	bool doesplayerhavetile(std::string Tile)
	{
		for(unsigned int i=0;i<tiles.size();i++)
		{
			if(tiles.at(i).compare(Tile)==0)return true;
		}
		return false;
	}
	bool playerhastiles()const
	{
		return tiles.size()>0;
	}
	vector<std::string> givetiles()
	{
		return tiles;
	}
	std::string backtile()
	{
		if(tiles.empty()) return std::string("");
		return tiles.back();
	}
};


class PlayerManager
{
	PlayerManager():
	players(),
	numberofplayers(0),
	playernumber(0)
	{

	}
	static PlayerManager& instance;
public:
	vector<Player> players;
	unsigned int numberofplayers, playernumber;
	~PlayerManager()
	{
	}
	Player& operator() (const unsigned int& Number)
	{
		prepareplayersvector(Number);
		return players.at(Number);
	}
	unsigned int addplayer(const core::rect<s32> Area)
	{
		cout<<"unsigned int addplayer(const core::rect<s32> Area)"<<endl<<flush;
		players.push_back(Player(players.size(), Area));
		numberofplayers=players.size();
		return players.size()-1;
	}
		 
	void prepareplayersvector(const unsigned int& Number)
	{
		while(players.size()<=Number)
		{
			cout<<"void prepareplayersvector(const unsigned int& Number)"<<endl<<flush;
			players.push_back(Player());
		}
		numberofplayers=players.size();
	}
	void clear()
	{
		players.clear();
	}


	unsigned int size()
	{
		return players.size();
	}
	static
	PlayerManager& getinstance()
	{
		return instance;
	}
	unsigned int nextplayer(const bool& Reset=false)
	{
		if(Reset)return playernumber=0;
		else return playernumber=(playernumber+1)%numberofplayers;
	}
};
PlayerManager& PlayerManager::instance=PlayerManager();





#endif /*PLAYERS_H_*/
