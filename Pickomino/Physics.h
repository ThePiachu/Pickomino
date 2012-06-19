#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <vector>
using namespace std;

#include <ode/ode.h>
#pragma comment(lib, "C:\\C++\\ODE\\lib\\DebugSingleLib/ode_singled.lib")

dWorldID world;
dSpaceID space;
dJointGroupID contactJointGroup;
//dGeomID groundGeom;
vector<dGeomID> diceboxwalls;





void initializeode()
{
	// Init ODE
	dInitODE();

	space = dSimpleSpaceCreate(0);
	world = dWorldCreate();
	contactJointGroup = dJointGroupCreate(0);

	dWorldSetGravity(world, 0.0, -10.0, 0.0);

	/*groundGeom = dCreatePlane( space, 0, 1, 0, 0);

	diceboxwalls.push_back(dCreatePlane( space, -1, 0, 0, -10));
	diceboxwalls.push_back(dCreatePlane( space, 1, -0, -0, -10));
	diceboxwalls.push_back(dCreatePlane( space, -0, 0, 1, -10));
	diceboxwalls.push_back(dCreatePlane( space, 0, -0, -1, -10));*/
}





void QuaternionToEuler(const dQuaternion& quaternion, vector3df &euler){
  dReal w,x,y,z;
  w=quaternion[0];
  x=quaternion[1];
  y=quaternion[2];
  z=quaternion[3];
  double sqw = w*w;    
  double sqx = x*x;    
  double sqy = y*y;    
  double sqz = z*z; 
  
  euler.Z = (irr::f32) (atan2(2.0 * (x*y + z*w),(sqx - sqy - sqz + sqw))
                        *RADTODEG);
  
  euler.X = (irr::f32) (atan2(2.0 * (y*z + x*w),(-sqx - sqy + sqz + sqw))
                        *RADTODEG);  
  
  euler.Y = (irr::f32) (asin(-2.0 * (x*z - y*w))
                        *RADTODEG);
}

void phyNearCallback(void *userData, dGeomID geom1, dGeomID geom2)
{
	const int maxPoints = 10;
	dContact contactPoints[maxPoints];
	int numPoints = dCollide( geom1, geom2, maxPoints, &contactPoints[0].geom, sizeof(dContact) );

	if (numPoints > 0)
	{
		for (int i=0; i<numPoints; i++)
		{
			contactPoints[i].surface.mode = dContactBounce;// | dContactSoftCFM;;
			contactPoints[i].surface.mu=dInfinity;
			contactPoints[i].surface.mu2=0;
			contactPoints[i].surface.bounce = (dReal)0.4;
			contactPoints[i].surface.bounce_vel = (dReal)0.05;
			contactPoints[i].surface.soft_cfm=(dReal)0.01;
			//contactPoints[i].surface.bounce = (dReal)1.0;
			//contactPoints[i].surface.bounce_vel = (dReal)0.1;
			//contactPoints[i].surface.soft_cfm=(dReal)0.01;

			dJointID contactJoint = dJointCreateContact( world, contactJointGroup, &contactPoints[i] );
			dJointAttach( contactJoint, dGeomGetBody(contactPoints[i].geom.g1), dGeomGetBody(contactPoints[i].geom.g2));

			
		}
	}
}
// Based on http://l-sim.blogspot.com/2008/07/cuarto-tutorial-el-holamundo-ms-simple.html
void runSimulationODE()
{
	dSpaceCollide( space, NULL, phyNearCallback); // userData hands world, joint, etc. over to callback
    dWorldStep( world, (dReal)0.030 );
	dJointGroupEmpty( contactJointGroup );
}
void endode()
{
	// Inspired by: http://l-sim.blogspot.com/2008/07/cuarto-tutorial-el-holamundo-ms-simple.html
	dJointGroupDestroy(contactJointGroup);
	dSpaceDestroy(space);
	dWorldDestroy(world); 
	dCloseODE();
}


#endif /* PHYSICS_H_ */