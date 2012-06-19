#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//Irrlicht
#include <irrlicht.h>
#include <driverChoice.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Bool
{
	bool boolean;
public:
	Bool():boolean(false)
	{
	}
	Bool(bool Boolean):boolean(Boolean)
	{
	}
	operator bool()const
	{
		return boolean;
	}
};
struct comparestrings
{
	bool operator() (const std::string& One, const std::string& Two) const
	{
		if(One.compare(Two)<0)return true;
		return false;
	}
};

#pragma comment(lib, "Irrlicht.lib")

IrrlichtDevice *device;
IVideoDriver* driver;
ISceneManager* smgr;
IGUIEnvironment* guienv;
ICameraSceneNode* cameraNode;
gui::IGUIFont* font;

void initializeirrlicht(IEventReceiver* EventReceiver=NULL)
{
device=createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 32,
			false, true, true, EventReceiver);
	if (!device)
		exit(1);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	cameraNode= smgr->addCameraSceneNode();
}


void endirrlicht()
{
	device->drop();
}


class GameButton
{
public:
	IGUIImage* img;
	core::rect<s32> area, defaultarea;
	vector<Bool> bools;
	std::string name;
	GameButton():
		img(),
		area(),
		defaultarea(),
		bools(),
		name()
	{
	}
	GameButton(const io::path& FileName, core::rect<s32> Rectangle):
		img(),
		area(Rectangle),
		defaultarea(Rectangle),
		bools(),
		name(FileName.c_str())
	{
		ITexture* tex;
		tex = driver->getTexture(FileName);

		// Give to addImage() the XY coords of 2 points :
		img = guienv->addImage(Rectangle);
		img->setImage(tex);
		img->setScaleImage(true);
		driver->removeTexture(tex);
	}
	GameButton(core::rect<s32> Rectangle):
		img(),
		area(Rectangle),
		defaultarea(Rectangle),
		bools(),
		name("")
	{
	}
	~GameButton()
	{

	}
	void setbutton(const io::path& FileName, core::rect<s32> Rectangle)
	{
		ITexture* tex;
		tex = driver->getTexture(FileName);

		img=guienv->addImage(Rectangle);
		img->setImage(tex);
		img->setScaleImage(true);
		driver->removeTexture(tex);
		area=Rectangle;
	}
	void setcolour(SColor Colour)
	{
		if(img!=NULL)img->setColor(Colour);
	}
	bool isclicked(const int& X, const int& Y)
	{
		return (area.isPointInside(vector2d<int>(X, Y)));
	}
	std::string setname(const std::string& NewName)
	{
		return name=NewName;
	}
	void setarea(core::rect<s32> Rectangle)
	{
		img->setRelativePosition(Rectangle);
		area=Rectangle;
	}
	void settopposition()
	{
		img->bringToFront(img);
	}
	void reset()
	{
		if(img!=NULL)img->setRelativePosition(defaultarea);
		area=defaultarea;
		if(img!=NULL)img->setColor(SColor(255, 255, 255, 255));
	}
	Bool& operator()(const unsigned int& Number)
	{
		prepareboolvector(Number);
		return bools.at(Number);
	}
	void prepareboolvector(const unsigned int& Number)
	{
		while(bools.size()<=Number)
		{
			bools.push_back(false);
		}
	}
};

class GameButtonManager
{
	static GameButtonManager& instance;
	//static bool instancecreated;
	GameButtonManager():
		buttons()
	{
	}
public:
	std::map<std::string, GameButton, comparestrings> buttons;
	~GameButtonManager()
	{
	}

	GameButton& operator()(const std::string Name)
	{
		std::map<std::string, GameButton, comparestrings>::iterator it;
		it=buttons.find(Name);
		if (it==buttons.end())
		{
			it=buttons.insert(pair<std::string, GameButton> (std::string(""), GameButton())).first;
		}
		return it->second;
	}
	void addbutton(const io::path& FilePath, core::rect<s32> Rectangle, const std::string& Name)
	{//adds a button that has graphics
		std::map<std::string, GameButton, comparestrings>::iterator it;
		it=buttons.insert(pair<std::string, GameButton>
			(Name, GameButton(FilePath, Rectangle))).first;
		it->second.setname(Name);
	}
	void addbutton(core::rect<s32> Rectangle, const std::string& Name)
	{//adds a button that doesn`t have graphics
		std::map<std::string, GameButton, comparestrings>::iterator it;
		it=buttons.insert(pair<std::string, GameButton>
			(Name, GameButton(Rectangle))).first;
		it->second.setname(Name);
	}
	void setallcolour(const SColor& Colour)
	{
		std::map<std::string, GameButton, comparestrings>::iterator it;
		for(it=buttons.begin();it!=buttons.end();++it)
		{
			it->second.setcolour(Colour);
		}
	}
	void clear()
	{
		buttons.clear();
	}
	static GameButtonManager& getinstance()
	{
		return instance;
	}

};

GameButtonManager& GameButtonManager::instance=GameButtonManager();


#endif /* GRAPHICS_H_ */