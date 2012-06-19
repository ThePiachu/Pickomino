#ifndef GRAPHICSANDPHYSICS_H_
#define GRAPHICSANDPHYSICS_H_

#define THRESHOLD 0.5

#include "Graphics.h"
#include "Physics.h"
#include "random.h"

#include <iostream>
#include <vector>
using namespace std;

class GameObject
{
public:
	ISceneNode* mesh;
	dJointGroupID jointGroup;
	dGeomID geometry;
	dBodyID body;
	dMass mass;
	vector <Bool> bools;

	GameObject():
		mesh(NULL),
		jointGroup(),
		geometry(),
		body(),
		mass(),
		bools()
	{
	}
	~GameObject()
	{
		clear();
		//if(body)dBodyDestroy (body);
		//if(geometry)dGeomDestroy (geometry);
	}
	void clear()
	{
		bools.clear();
	}

	vector3df getrotation()
	{
		if(mesh!=NULL)return this->mesh->getRotation();
		else return vector3df();
	}
	void set(vector3df Position, vector3df AngVelocity, vector3df LinVelocity)
	{
		dBodyEnable(body);
		setposition(Position);
		dBodySetAngularVel(body, AngVelocity.X, AngVelocity.Y, AngVelocity.Z);
		dBodySetLinearVel(body, LinVelocity.X, LinVelocity.Y, LinVelocity.Z);
	}
	void disablebody()
	{
		dBodyDisable(body);
	}
	void setposition(vector3df Position)
	{
		if(mesh!=NULL)this->mesh->setPosition(Position);
		//if(objectisphysical)
		//{
			dBodySetPosition(body, Position.X, Position.Y, Position.Z);
			dBodySetAngularVel(body, 0, 0, 0);
			dBodySetLinearVel(body, 0, 0, 0);
		//}
	}
	bool bodyisenabled()
	{
		return (bool) dBodyIsEnabled(body);
	}
	void printlinearvelocity()
	{
		cout<<*dBodyGetLinearVel(body)<<endl<<flush;
	}
	void printangularvelocity()
	{
		cout<<*dBodyGetAngularVel(body)<<endl<<flush;
	}
	Bool& operator()(const unsigned int Number)
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

	void recalculateposition()
	{//function for recalculating the position based on ODE simulation
		dReal* odePosition = (dReal*)dGeomGetPosition( geometry );
		vector3df newIrrlichtPosition;
		newIrrlichtPosition.set( (f32)odePosition[0], (f32)odePosition[1], (f32)odePosition[2] );
		mesh->setPosition( newIrrlichtPosition );
		dQuaternion result;
		dGeomGetQuaternion(geometry, result);
		vector3df rot;
		QuaternionToEuler(result, rot);			
		mesh->setRotation(rot);	

	}
};





class GameObjectManager
{
	GameObjectManager():
	gameobjects()
	{

	}
	static GameObjectManager& instance;
public:
	vector<GameObject> gameobjects;
	~GameObjectManager()
	{
	}
	GameObject& operator() (const unsigned int& Number)
	{
		preparegameobjectvector(Number);
		return gameobjects.at(Number);
	}

	void preparegameobjectvector(const unsigned int& Number)
	{
		while(gameobjects.size()<=Number)
		{
			gameobjects.push_back(GameObject());
		}
	}
	void clear()
	{
		gameobjects.clear();
	}


	// Based on http://irrlicht.sourceforge.net/tut_ode.html
	unsigned int createCube(const irr::io::path& Path, const vector3df& loc=vector3df(0.0, 0.0, 10.0), const float& Density=40.0) 
	{
		unsigned int anwser=gameobjects.size();
		gameobjects.push_back(GameObject());



		// Load texture and mesh
		gameobjects.back().mesh = smgr->addAnimatedMeshSceneNode(smgr->getMesh(Path)); //ENGINEMANAGER.GetSceneManager()->addCubeSceneNode(); 
		//ITexture *texture = driver->getTexture("media/die-texture.bmp");
		//obj->node->setMaterialTexture(0,texture);
		gameobjects.back().mesh->setMaterialFlag(EMF_LIGHTING, false);

		gameobjects.back().mesh->setPosition(loc);
		gameobjects.back().mesh->setRotation(vector3df(45,45,45));
		
		aabbox3d<f32> box = gameobjects.back().mesh->getBoundingBox();
		vector3df extend = box.getExtent();
		vector3df pos = gameobjects.back().mesh->getPosition(); // get the position of the scenenode

		gameobjects.back().geometry = dCreateBox(space,(dReal)extend.X,(dReal)extend.Y,(dReal)extend.Z); 
		//obj->geom = dCreateSphere( space, 10.0f );	
		dGeomSetPosition(gameobjects.back().geometry, gameobjects.back().mesh->getPosition().X, gameobjects.back().mesh->getPosition().Y, gameobjects.back().mesh->getPosition().Z); // set the position of the ODE geom

		// set a pointer to our Bounceable, 
		// this will come in handy when we do more complicated collisions
		
		//dGeomSetData(obj->geometry,(void*)this);


		gameobjects.back().body = dBodyCreate( world );

		dMassSetBox(&gameobjects.back().mass, Density, (dReal)extend.X, (dReal)extend.Y, (dReal)extend.Z); // setup the mass
		dBodySetMass(gameobjects.back().body, &gameobjects.back().mass); // combine body and mass

		dGeomSetBody( gameobjects.back().geometry, gameobjects.back().body );
		dBodySetPosition( gameobjects.back().body, gameobjects.back().mesh->getPosition().X, gameobjects.back().mesh->getPosition().Y, gameobjects.back().mesh->getPosition().Z );

		dBodySetAutoDisableFlag(gameobjects.back().body, 1);
		dBodySetDamping(gameobjects.back().body, (dReal)0.00001, (dReal)0.001);

		dBodySetAngularVel(gameobjects.back().body, 2, 1, 2);
		dBodySetLinearVel(gameobjects.back().body, -2, 1, 2);
		dBodyEnable(gameobjects.back().body);
		dBodySetAutoDisableSteps (gameobjects.back().body, 60);
		dBodySetAutoDisableLinearThreshold(gameobjects.back().body, 1.0);
		dBodySetAutoDisableAngularThreshold(gameobjects.back().body, 1.0);


		//obj->objectisphysical=true;

		//phyObjects.push_back(obj);
		return anwser;
	}
	unsigned int createmodel(irr::io::path& FileName, vector3df loc=vector3df(0.0, 0.0, 10.0))
	{
		unsigned int anwser=gameobjects.size();
		gameobjects.push_back(GameObject());

		// Load texture and mesh
		gameobjects.back().mesh = smgr->addAnimatedMeshSceneNode(smgr->getMesh(FileName)); //ENGINEMANAGER.GetSceneManager()->addCubeSceneNode();
		gameobjects.back().mesh->setMaterialFlag(EMF_LIGHTING, false);


		gameobjects.back().mesh->setPosition(loc);
		gameobjects.back().mesh->setRotation(vector3df(90,-90,0));
		gameobjects.back().mesh->setScale(vector3df(20.0, 20.0, 20.0));
		return anwser;
	}
	unsigned int whatisrolled(const unsigned int Number)
	{
		vector3df vec=gameobjects.at(Number).getrotation();
		vector3df x(1.0, 0.0, 0.0);
		vector3df y(0.0, 1.0, 0.0);
		vector3df z(0.0, 0.0, 1.0);

		matrix4 mat;

		mat.setRotationDegrees(vec);


		mat.rotateVect(x);
		mat.rotateVect(y);
		mat.rotateVect(z);

		//cout<<x.X<<" "<<x.Y<<" "<<x.Z<<endl<<flush;
		//cout<<y.X<<" "<<y.Y<<" "<<y.Z<<endl<<flush;
		
		if(y.Y>THRESHOLD) return 1;
		if(y.Y<-THRESHOLD) return 2;
		if(x.Y>THRESHOLD) return 3;
		if(x.Y<-THRESHOLD) return 4;
		if(z.Y>THRESHOLD) return 5;
		if(z.Y<-THRESHOLD) return 6;
		return 0;
	}
	unsigned int size()
	{
		return gameobjects.size();
	}
	void recalculatepositions()
	{
		for(unsigned int i=0;i<gameobjects.size();i++)if (gameobjects.at(i).geometry)
		{
			gameobjects.at(i).recalculateposition();
		}
	}
	static
	GameObjectManager& getinstance()
	{
		return instance;
	}
};
GameObjectManager& GameObjectManager::instance=GameObjectManager();

#endif /* GRAPHICSANDPHYSICS_H_ */