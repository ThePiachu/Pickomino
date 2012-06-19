#ifndef SCRIPTING_H_
#define SCRIPTING_H_

#include <string>
#include <vector>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include "Graphics.h"
#include "Physics.h"
#include "GraphicsAndPhysics.h"
#include "Sound.h"
#include "EventReceiver.h"
#include "Players.h"

std::string dicerolltranslationfunction; // "callback" string for Lua scripted dice roll translation function
std::string startgamefunction;
std::string endofsimulaitonfunction;
std::string printfunction;
std::string buttonfunction;
std::string idlefunction;


int setsound(lua_State *L)
{//function for setting up sound
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setsound, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  3: if( !lua_isnumber(L,1) || !lua_isstring(L,2) || !lua_isboolean(L, 3)) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setsound"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			//SoundManager::getinstance().initialize();
			SoundManager::getinstance().setsound((unsigned int)lua_tonumber(L, 1), lua_tostring(L, 2), lua_toboolean(L, 3));
	             break;
	    default:
			std::cerr<<"Lua setsound"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}

int playsound(lua_State *L)
{//function for playing sound
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"playsound, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isnumber(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua playsound"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			//SoundManager::getinstance().initialize();
			 SoundManager::getinstance().playsound((unsigned int)lua_tonumber(L, 1));
	             break;
	    default:
			std::cerr<<"Lua playsound"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}

/*int setdiceresultfunction(lua_State *L)
{//function for setting function that will translate dice results
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setdiceresultfunction, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setdiceresultfunction"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 dicerolltranslationfunction=lua_tostring(L, 1);
	             break;
	    default:
			std::cerr<<"Lua setdiceresultfunction"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}*/

int addphysicalplane(lua_State *L)
{//function for adding physical planes
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"addphysicalplane, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  4: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3) || !lua_isnumber(L,4) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua addphysicalplane"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 diceboxwalls.push_back(dCreatePlane( space,
				 (dReal)lua_tonumber(L,1),
				 (dReal)lua_tonumber(L,2),
				 (dReal)lua_tonumber(L,3),
				 (dReal)lua_tonumber(L,4)));
	             break;
	    default:
			std::cerr<<"Lua addphysicalplane"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setwindowcaption(lua_State *L)
{//function for setting the name of the screen
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setwindowcaption, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setwindowcaption"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 device->setWindowCaption(core::stringw(lua_tostring(L, 1)).c_str());
	             break;
	    default:
			std::cerr<<"Lua setwindowcaption"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int createdice(lua_State *L)
{//function for creating a number of dice
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"createdice, numArgs "<<numArgs<<endl<<flush;

	if( !lua_isstring(L,1) || !lua_isnumber(L,2) ) // check the types of the arguments
	{
		std::cerr<<"Lua createdice"<<std::endl;
		lua_error(L);
		return 0;
	}
	GameObjectManager& gom=GameObjectManager::getinstance();
	unsigned int tmp=0;
	for(int i=0;i<lua_tointeger(L,2);i++)
	{
		tmp=gom.createCube(irr::io::path(lua_tostring(L,1)), vector3df(0.0, 0.0, 0.0));
		for(int j=3;j<=numArgs;j++)
		{
			gom(tmp)(j-3)=(bool)lua_toboolean(L,j);
		}
	}
	
	return 0;
}
int createmodel(lua_State *L)
{//function for creating a game object that is not physical
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"createmodel, numArgs "<<numArgs<<endl<<flush;

	if( !lua_isstring(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3) || !lua_isnumber(L,4) ) // check the types of the arguments
	{
		std::cerr<<"Lua createmodel"<<std::endl;
		lua_error(L);
		return 0;
	}
	GameObjectManager& gom=GameObjectManager::getinstance();
	unsigned int tmp=0;
	tmp=gom.createmodel(irr::io::path(lua_tostring(L,1)),
		vector3df((irr::f32)lua_tonumber(L, 2), (irr::f32)lua_tonumber(L, 3), (irr::f32)lua_tonumber(L, 4)));
	for(int i=5;i<=numArgs;i++)
	{
		gom(tmp)(i-5)=lua_toboolean(L,i);
	}
	
	return 0;
}
int createbutton(lua_State *L)
{//function for creating a button without graphics
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"createbutton, numArgs "<<numArgs<<endl<<flush;

	if( numArgs<5 || !lua_isstring(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3) || !lua_isnumber(L,4) || !lua_isnumber(L,5) ) // check the types of the arguments
	{
		std::cerr<<"Lua createbutton"<<std::endl;
		lua_error(L);
		return 0;
	}
	GameButtonManager& gbm=GameButtonManager::getinstance();
	gbm.addbutton(core::rect<s32>(
		lua_tointeger(L,2),
		lua_tointeger(L,3),
		lua_tointeger(L,4),
		lua_tointeger(L,5)),
		lua_tostring(L,1));

	for(int i=6;i<=numArgs;i++)
	{
		//cout<<"gbm(lua_tostring(L,1))(i-6)=lua_toboolean(L,i); "<<lua_toboolean(L,i)<<endl<<flush;
		gbm(lua_tostring(L,1))(i-6)=(bool)lua_toboolean(L,i);
	}
	return 0;
}
int createbuttonwithgraphics(lua_State *L)
{//function for creating a button with graphics
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"createbuttonwithgraphics, numArgs "<<numArgs<<endl<<flush;

	if( numArgs<6 || !lua_isstring(L,1) || !lua_isstring(L,2) || !lua_isnumber(L,3) || !lua_isnumber(L,4) || !lua_isnumber(L,5) || !lua_isnumber(L,6) ) // check the types of the arguments
	{
		std::cerr<<"Lua createbuttonwithgraphics"<<std::endl;
		lua_error(L);
		return 0;
	}
	GameButtonManager& gbm=GameButtonManager::getinstance();
	gbm.addbutton(lua_tostring(L,1), core::rect<s32>(
		lua_tointeger(L,3),
		lua_tointeger(L,4),
		lua_tointeger(L,5),
		lua_tointeger(L,6)),
		lua_tostring(L,2));

	for(int i=7;i<=numArgs;i++)
	{
		//cout<<"gbm(lua_tostring(L,1))(i-6)=lua_toboolean(L,i); "<<lua_toboolean(L,i)<<endl<<flush;
		gbm(lua_tostring(L,2))(i-7)=(bool)lua_toboolean(L,i);
	}
	return 0;}


int setlookatcamera(lua_State *L)
{//function for adding physical planes
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setlookatcamera, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  6: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3) || !lua_isnumber(L,4) || !lua_isnumber(L,5) || !lua_isnumber(L,6) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setlookatcamera"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 smgr->addCameraSceneNode(0,
				 vector3df((dReal)lua_tonumber(L,1), (dReal)lua_tonumber(L,2), (dReal)lua_tonumber(L,3)),
				 vector3df((dReal)lua_tonumber(L,4), (dReal)lua_tonumber(L,5), (dReal)lua_tonumber(L,6)));
	             break;
	    default:
			std::cerr<<"Lua setlookatcamera"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int loadfont(lua_State *L)
{//function for playing sound
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"loadfont, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua loadfont"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 font=device->getGUIEnvironment()->getFont(lua_tostring(L, 1));
	             break;
	    default:
			std::cerr<<"Lua loadfont"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setallphysicalobjectslock(lua_State *L)
{//function for setting bool values from physical objects
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setallphysicalobjectslock, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  2: if( !lua_isnumber(L,1) || !lua_isboolean(L,2) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setallphysicalobjectslock"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			// GameObjectManager& gom=GameObjectManager::getinstance();
			 for(unsigned int i=0;i<GameObjectManager::getinstance().size();i++)
			 {
				 GameObjectManager::getinstance()(i)((unsigned int)lua_tonumber(L,1))=lua_toboolean(L,2);
			 }
	             break;
	    default:
			std::cerr<<"Lua setallphysicalobjectslock"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setphysicalobjectslock(lua_State *L)
{//function for setting bool values from one physical object
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setphysicalobjectslock, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  3: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) || !lua_isboolean(L,3) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setphysicalobjectslock"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
				//GameObjectManager& gom=GameObjectManager::getinstance();
				 GameObjectManager::getinstance()((unsigned int)lua_tonumber(L,1))((unsigned int)lua_tonumber(L,2))=lua_toboolean(L,3);
	             break;
	    default:
			std::cerr<<"Lua setphysicalobjectslock"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int getrandom(lua_State *L)
{//function to generate random integer
	lua_pushnumber(L, random::getinstance()->randomint());
	return 1;
}
int getfloatbetween(lua_State *L)
{//function to generate random float
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"getfloatbetween, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  2: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua getfloatbetween"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 lua_pushnumber(L, random::getinstance()->randomfloatbetween((float)lua_tonumber(L, 1), (float)lua_tonumber(L, 2)));
				return 1;
	             break;
	    default:
			std::cerr<<"Lua getfloatbetween"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setgameobject(lua_State *L)
{//function to set parameters of physical game objects
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setposition, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  10: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3)
				   || !lua_isnumber(L,4) || !lua_isnumber(L,5) || !lua_isnumber(L,6)
				    || !lua_isnumber(L,7) || !lua_isnumber(L,8) || !lua_isnumber(L,9)
					 || !lua_isnumber(L,10)) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setposition"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			  GameObjectManager::getinstance()((unsigned int)lua_tointeger(L, 1)).set
				  (irr::core::vector3df((irr::f32)lua_tonumber(L, 2), (irr::f32)lua_tonumber(L, 3), (irr::f32)lua_tonumber(L, 4)),
				  irr::core::vector3df((irr::f32)lua_tonumber(L, 5), (irr::f32)lua_tonumber(L, 6), (irr::f32)lua_tonumber(L, 7)),
				  irr::core::vector3df((irr::f32)lua_tonumber(L, 8), (irr::f32)lua_tonumber(L, 9), (irr::f32)lua_tonumber(L, 10)));

	             break;
	    default:
			std::cerr<<"Lua setposition"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}

int setstargamefunction(lua_State *L)
{//function for setting function that will translate dice results
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setstargamefunction, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setstargamefunction"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 startgamefunction=lua_tostring(L, 1);
	             break;
	    default:
			std::cerr<<"Lua setstargamefunction"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int getgomhandle(lua_State *L)
{//function to gethandle of game object
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"getgomhandle, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  2: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua getgomhandle"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 lua_pushboolean(L, GameObjectManager::getinstance()((unsigned int)lua_tonumber(L,1))((unsigned int)lua_tonumber(L,2)));
				return 1;
	             break;
	    default:
			std::cerr<<"Lua getgomhandle"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int getgomsize(lua_State *L)
{//function for fetching the amount of Game Objects
	lua_pushnumber(L, GameObjectManager::getinstance().size());
	return 1;
}
int setendofsimulationfunction(lua_State *L)
{//function for setting function that will be run at the end of each ODE simulation
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setendofsimulationfunction, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setendofsimulationfunction"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 endofsimulaitonfunction=lua_tostring(L, 1);
	             break;
	    default:
			std::cerr<<"Lua setendofsimulationfunction"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int whatisrolled(lua_State *L)
{//function that checks what a given dice rolled
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"whatisrolled, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isnumber(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua whatisrolled"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 lua_pushnumber(L, GameObjectManager::getinstance().whatisrolled((unsigned int)lua_tointeger(L, 1)));
				return 1;
	             break;
	    default:
			std::cerr<<"Lua whatisrolled"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int printtext(lua_State *L)
{//function to print text on the screen
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"printtext, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  9: if( !lua_isstring(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3) 
				 || !lua_isnumber(L,4) || !lua_isnumber(L,5) || !lua_isnumber(L,6) 
				 || !lua_isnumber(L,7) || !lua_isnumber(L,8) || !lua_isnumber(L,9) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua printtext"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
				font->draw(lua_tostring(L, 1),
					irr::core::rect<s32>((irr::s32)lua_tointeger(L, 2), (irr::s32)lua_tointeger(L, 3), (irr::s32)lua_tointeger(L, 4), (irr::s32)lua_tointeger(L, 5)),
					irr::video::SColor((irr::u32)lua_tointeger(L, 6), (irr::u32)lua_tointeger(L, 7), (irr::u32)lua_tointeger(L, 8), (irr::u32)lua_tointeger(L, 9)));

	             break;
	    default:
			std::cerr<<"Lua printtext"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setprintfunction(lua_State *L)//TODO: get rid of, replace with idle funciton
{//function for setting function that will print text
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setprintfunction, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setprintfunction"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 printfunction=lua_tostring(L, 1);
	             break;
	    default:
			std::cerr<<"Lua setprintfunction"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setbuttonfunction(lua_State *L)
{//function for setting function that will print text
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setbuttonfunction, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setbuttonfunction"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 buttonfunction=lua_tostring(L, 1);
	             break;
	    default:
			std::cerr<<"Lua setbuttonfunction"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}


int addplayer(lua_State *L)
{//function for adding players
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"addplayer, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  4: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3) || !lua_isnumber(L,4) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua addplayer"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 PlayerManager::getinstance().addplayer(irr::core::rect<s32>((s32)lua_tointeger(L,1),
				(s32)lua_tointeger(L,2),
				(s32)lua_tointeger(L,3),
				(s32)lua_tointeger(L,4)));
	             break;
	    default:
			std::cerr<<"Lua addplayer"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int getcurrentplayernumber(lua_State *L)
{//function for fetching the amount of Game Objects
	lua_pushnumber(L, PlayerManager::getinstance().playernumber);
	return 1;
}
int getgbmhandle(lua_State *L)
{//function to get handle of game button
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"getgbmhandle, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  2: if( !lua_isstring(L,1) || !lua_isnumber(L,2) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua getgbmhandle"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
			 lua_pushboolean(L, GameButtonManager::getinstance()(lua_tostring(L,1))((unsigned int)lua_tonumber(L,2)));
				return 1;
	             break;
			 }
	    default:
			std::cerr<<"Lua getgbmhandle"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int getplayertiles(lua_State *L)
{//function to get all tiles owned by a player
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"getplayertiles, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isnumber(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua getplayertiles"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
			 std::vector<std::string> tiles;
			 tiles=PlayerManager::getinstance()((unsigned int)lua_tonumber(L,1)).givetiles();
			 for(unsigned int i=0;i<tiles.size();i++)
			 {
				 lua_pushstring(L, tiles.at(i).c_str());
			 }
				return tiles.size();
	             break;
			}
	    default:
			std::cerr<<"Lua getplayertiles"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int getplayertile(lua_State *L)
{//function to get last tile owned by the player
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"getplayertile, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isnumber(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua getplayertile"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 lua_pushstring(L, PlayerManager::getinstance()((unsigned int)lua_tonumber(L,1)).backtile().c_str());

				return 1;
	             break;
	    default:
			std::cerr<<"Lua getplayertile"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int pmnextplayer(lua_State *L)
{//function to get the next player
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"pmnextplayer, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isboolean(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua pmnextplayer"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 lua_pushinteger(L, PlayerManager::getinstance().nextplayer(lua_toboolean(L, 1)));
				return 1;
	             break;
	    default:
			std::cerr<<"Lua pmnextplayer"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setbuttoncolour(lua_State *L)
{//function to set the colour of a button
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setbuttoncolour, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  5: if( !lua_isstring(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3)  || !lua_isnumber(L,4) || !lua_isnumber(L,5) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setbuttoncolour"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
				
			 GameButtonManager::getinstance()(lua_tostring(L, 1)).setcolour(irr::video::SColor(
				 (irr::u32) lua_tointeger(L, 2),
				 (irr::u32) lua_tointeger(L, 3),
				 (irr::u32) lua_tointeger(L, 4),
				 (irr::u32) lua_tointeger(L, 5)));

	             break;
	    default:
			std::cerr<<"Lua setbuttoncolour"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setgbmhandle(lua_State *L)
{//function to set a boolean handle on a button
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"getgbmhandle, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  3: if( !lua_isstring(L,1) || !lua_isnumber(L,2) || !lua_isboolean(L,3) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua getgbmhandle"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
				 GameButtonManager::getinstance()(lua_tostring(L, 1))((unsigned int)lua_tointeger(L, 2))=lua_toboolean(L, 3);
	             break;
			 }
	    default:
			std::cerr<<"Lua getgbmhandle"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setgomhandle(lua_State *L)
{//function to set a boolean handle on game object
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setgomhandle, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  3: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) || !lua_isboolean(L,3) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setgomhandle"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
				 GameObjectManager::getinstance()((unsigned int)lua_tointeger(L, 1))((unsigned int)lua_tointeger(L, 2))=lua_toboolean(L, 3);
	             break;
			 }
	    default:
			std::cerr<<"Lua setgomhandle"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setgameobjectposition(lua_State *L)
{//function to set position of physical game object
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setposition, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  4: if( !lua_isnumber(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3)
				   || !lua_isnumber(L,4)) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setposition"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			  GameObjectManager::getinstance()((unsigned int)lua_tointeger(L, 1)).setposition
				  (irr::core::vector3df((irr::f32)lua_tonumber(L, 2), (irr::f32)lua_tonumber(L, 3), (irr::f32)lua_tonumber(L, 4)));

	             break;
	    default:
			std::cerr<<"Lua setposition"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int resetbutton(lua_State *L)
{//function to reset position of a button
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"resetbutton, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua resetbutton"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
				 GameButtonManager::getinstance()(lua_tostring(L, 1)).reset();
	             break;
			 }
	    default:
			std::cerr<<"Lua resetbutton"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int doesplayerhavetile(lua_State *L)
{//function to check if a player has a particular tile
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"doesplayerhavetile, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  2: if( !lua_isnumber(L,1) || !lua_isstring(L,2) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua doesplayerhavetile"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
				 lua_pushboolean(L, PlayerManager::getinstance()((unsigned int)lua_tointeger(L, 1)).doesplayerhavetile(lua_tostring(L, 2)));
				 return 1;
	             break;
			 }
	    default:
			std::cerr<<"Lua doesplayerhavetile"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int pushplayertile(lua_State *L)
{//function to give player a tile
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"pushplayertile, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  2: if( !lua_isnumber(L,1) || !lua_isstring(L,2) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua pushplayertile"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
				 PlayerManager::getinstance()((unsigned int)lua_tointeger(L, 1)).pushtile(lua_tostring(L, 2));
	             break;
			 }
	    default:
			std::cerr<<"Lua pushplayertile"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int popplayertile(lua_State *L)
{//function to take away a tile from a player
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"popplayertile, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  2: if( !lua_isnumber(L,1) || !lua_isstring(L,2) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua popplayertile"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
				 PlayerManager::getinstance()((unsigned int)lua_tointeger(L, 1)).poptile(lua_tostring(L, 2));
	             break;
			 }
	    default:
			std::cerr<<"Lua popplayertile"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int getplayersarea(lua_State *L)
{//function to get the area of a player
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"getplayersarea, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isnumber(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua getplayersarea"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 {
				 irr::core::rect<s32> area=PlayerManager::getinstance()((unsigned int)lua_tointeger(L, 1)).playersarea;
				 lua_pushinteger(L, area.UpperLeftCorner.X);
				 lua_pushinteger(L, area.UpperLeftCorner.Y);
				 lua_pushinteger(L, area.LowerRightCorner.X);
				 lua_pushinteger(L, area.LowerRightCorner.Y);
				 return 4;
	             break;
			 }
	    default:
			std::cerr<<"Lua getplayersarea"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setbuttonarea(lua_State *L)
{//function to set the area of a game tile
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setbuttonarea, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  5: if( !lua_isstring(L,1) || !lua_isnumber(L,2) || !lua_isnumber(L,3) || !lua_isnumber(L,4) || !lua_isnumber(L,5) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setbuttonarea"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			{
				GameButtonManager::getinstance()(lua_tostring(L, 1)).setarea(irr::core::rect<s32>
					((s32)lua_tointeger(L, 2),(s32)lua_tointeger(L, 3),(s32)lua_tointeger(L, 4),(s32)lua_tointeger(L, 5)));
				break;
			}
	    default:
			std::cerr<<"Lua setbuttonarea"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}
int setidlefunction(lua_State *L)
{//function for setting function that will be called each game loop
	// find out how many arguements the function has been sent
	int numArgs = lua_gettop(L);
	//cout<<"setidlefunction, numArgs "<<numArgs<<endl<<flush;

	switch(numArgs) // check the number of arguments
	{
	case  1: if( !lua_isstring(L,1) ) // check the types of the arguments
	             {
	                 std::cerr<<"Lua setidlefunction"<<std::endl;
	                 lua_error(L);
	                 return 0;
	             }
			 idlefunction=lua_tostring(L, 1);
	             break;
	    default:
			std::cerr<<"Lua setidlefunction"<<std::endl;
	        lua_error(L);
	        return 0;
	}
	return 0;
}






#pragma comment(lib, "lua51.lib")

  // Lua State
lua_State *globalL;





int initializelua(const std::string &luaScriptName)
{
	// Create the Lua state. Explanation from Lua 5.1 Ref. Manual:
	/* Creates a new Lua state, calling lua_newstate with an allocation function based on the standard C realloc function and setting a panic function (see lua_atpanic) that prints an error message to the standard error output in case of fatal errors.
	   Returns the new state, or NULL if there is a memory allocation error. */
	globalL = luaL_newstate(); // 5.1 OK - Lua 5.0 or lower will probably require different commands

	if( globalL == NULL )
		return 1;




    // Loads all Lua standard libraries
	luaL_openlibs(globalL);  // 5.1 OK - Lua 5.0 or lower will require different commands


	lua_register(globalL,"setsound",setsound);
	lua_register(globalL,"playsound",playsound);
	//lua_register(globalL,"setdiceresultfunction",setdiceresultfunction);
	lua_register(globalL,"addphysicalplane",addphysicalplane);
	lua_register(globalL,"setwindowcaption",setwindowcaption);
	lua_register(globalL,"createdice",createdice);
	lua_register(globalL,"createbutton",createbutton);
	lua_register(globalL,"createbuttonwithgraphics",createbuttonwithgraphics);
	lua_register(globalL,"setlookatcamera",setlookatcamera);
	lua_register(globalL,"createmodel",createmodel);
	lua_register(globalL,"loadfont",loadfont);
	lua_register(globalL,"setallphysicalobjectslock",setallphysicalobjectslock);
	lua_register(globalL,"setphysicalobjectslock",setphysicalobjectslock);
	lua_register(globalL,"getrandom",getrandom);
	lua_register(globalL,"getfloatbetween",getfloatbetween);
	lua_register(globalL,"setgameobject",setgameobject);
	lua_register(globalL,"setstargamefunction",setstargamefunction);
	lua_register(globalL,"getgomhandle",getgomhandle);
	lua_register(globalL,"getgomsize",getgomsize);
	lua_register(globalL,"setendofsimulationfunction",setendofsimulationfunction);
	lua_register(globalL,"whatisrolled",whatisrolled);
	lua_register(globalL,"printtext",printtext);
	lua_register(globalL,"setprintfunction",setprintfunction);
	lua_register(globalL,"addplayer",addplayer);
	lua_register(globalL,"getcurrentplayernumber",getcurrentplayernumber);
	lua_register(globalL,"getgbmhandle",getgbmhandle);
	lua_register(globalL,"setbuttonfunction",setbuttonfunction);
	lua_register(globalL,"getplayertiles",getplayertiles);
	lua_register(globalL,"getplayertile",getplayertile);
	lua_register(globalL,"pmnextplayer",pmnextplayer);
	lua_register(globalL,"setbuttoncolour",setbuttoncolour);
	lua_register(globalL,"setgbmhandle",setgbmhandle);
	lua_register(globalL,"setgomhandle",setgomhandle);
	lua_register(globalL,"setgameobjectposition",setgameobjectposition);
	lua_register(globalL,"resetbutton",resetbutton); 
	lua_register(globalL,"doesplayerhavetile",doesplayerhavetile);
	lua_register(globalL,"pushplayertile",pushplayertile);
	lua_register(globalL,"popplayertile",popplayertile);
	lua_register(globalL,"setbuttonarea",setbuttonarea);
	lua_register(globalL,"getplayersarea",getplayersarea);
	lua_register(globalL,"setidlefunction",setidlefunction);


	// This lot below could be replaced with luaL_dofile, but that just does: luaL_loadfile(..) || lua_pcall(..), which gives no reporting of error messages etc.
	int initError = luaL_loadfile(globalL,luaScriptName.c_str());
	switch( initError )
	{
		case 0:
			// The file loaded okay, so call it as a protected function - to stop fatal errors from exiting the program
			lua_pcall(globalL,0,0,0);
			break;
		case LUA_ERRFILE:
			std::cerr<<"Cannot find / open lua script file: "<<luaScriptName<<std::endl<<"Skipping Lua init."<<std::endl;
			break;
		case LUA_ERRSYNTAX:
			std::cerr<<"Syntax error during pre-compilation of script file: " <<luaScriptName<<std::endl<<"Skipping Lua init."<<std::endl;
			break;
		case LUA_ERRMEM:
			// Treating this as fatal, since it means other Lua calls are unlikely to work either
			std::cerr<<"Fatal memory allocation error during processing of script file: " <<luaScriptName<<std::endl;
			return 1;
	}



/*	// Loads all Lua standard libraries
	luaL_openlibs(globalL);  // 5.1 OK - Lua 5.0 or lower will require different commands*/

	return 0;
}

bool luaresf(int res)
{
	if( res != 0 ) // did the function call result in an error?
	{
		// upon failure, lua_pcall puts an error message onto the stack
		std::string message = lua_tostring(globalL,1);
		switch( res ) // check the error numbers
		{
			case 0:
					// okay - no error here - this should never be called
					return true;
			case LUA_ERRRUN:
					std::cerr<<"Lua runtime error from Render Function call";
					break;
			case LUA_ERRMEM:
					std::cerr<<"Lua memory error from Render Function call";
					break;
			case LUA_ERRERR:
					std::cerr<<"Lua error handler error from Render Function call";
					break;
			default:
					std::cerr<<"Unknown Lua error from Render Function call";
					break;
		}
		std::cerr<<" - "<<message<<std::endl;
		return false;
	}
	return true;
}



/*unsigned int translateresult(unsigned int WhatIsRolled)
{
	if(dicerolltranslationfunction.empty())return 0;
	lua_getfield(globalL, LUA_GLOBALSINDEX, dicerolltranslationfunction.c_str()); // go to function in Lua script
	int numArgs = 1;
	lua_pushinteger(globalL, WhatIsRolled);
	unsigned int anwser=1;
	int res = lua_pcall(globalL,numArgs,anwser, 0);

	if(!luaresf(res)) // did the function call result in an error?
	{
		return 0;
	}
	anwser=(unsigned int)lua_tonumber(globalL, -1);
	lua_pop(globalL, 1);
	return anwser;
}*/
void luastartgame(void)
{
	if(startgamefunction.empty())return ;
	lua_getfield(globalL, LUA_GLOBALSINDEX, startgamefunction.c_str()); // go to function in Lua script
	int numArgs = 0;
	int res = lua_pcall(globalL,numArgs,0, 0);

	if(!luaresf(res)) // did the function call result in an error?
	{
		return;
	}
}
void luaendofsimulation(void)
{
	if(endofsimulaitonfunction.empty())return ;
	lua_getfield(globalL, LUA_GLOBALSINDEX, endofsimulaitonfunction.c_str()); // go to function in Lua script
	int numArgs = 0;
	int res = lua_pcall(globalL,numArgs,0, 0);

	if(!luaresf(res)) // did the function call result in an error?
	{
		return;
	}
}
void luaprint(void)
{
	if(printfunction.empty())return ;
	lua_getfield(globalL, LUA_GLOBALSINDEX, printfunction.c_str()); // go to function in Lua script
	int numArgs = 0;
	int res = lua_pcall(globalL,numArgs,0, 0);

	if(!luaresf(res)) // did the function call result in an error?
	{
		return;
	}
}
void luabuttonclicked(std::string ButtonName)
{
	if(buttonfunction.empty())return ;
	lua_getfield(globalL, LUA_GLOBALSINDEX, buttonfunction.c_str()); // go to function in Lua script
	lua_pushfstring(globalL, ButtonName.c_str());
	int numArgs = 1;
	int res = lua_pcall(globalL,numArgs,0, 0);

	if(!luaresf(res)) // did the function call result in an error?
	{
		return;
	}
}
void luaidlefunction()
{
	if(idlefunction.empty())return ;
	lua_getfield(globalL, LUA_GLOBALSINDEX, idlefunction.c_str()); // go to function in Lua script
	int numArgs = 0;
	int res = lua_pcall(globalL,numArgs,0, 0);

	if(!luaresf(res)) // did the function call result in an error?
	{
		return;
	}
}

#endif /* SCRIPTING_H_ */