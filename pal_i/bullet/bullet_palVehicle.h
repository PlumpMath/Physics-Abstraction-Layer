#ifndef BULLET_PALVEHICLE_H
#define BULLET_PALVEHICLE_H
//(c) Adrian Boeing 2007, see liscence.txt (BSD liscence)
/*
	Abstract:
		PAL - Physics Abstraction Layer. Bullet vehicle implementation.
		This enables the use of bullet vehicles via PAL.
	Author:
		Adrian Boeing
	Revision History:
	Version 0.0.1 : 17/08/07 - Vehicle and wheel
	TODO:
		- motor,gears,etc.
	notes:
*/



#include "bullet_pal.h"
#include "../pal/palVehicle.h"

class palBulletWheel : public palWheel {
public:
	palBulletWheel();
	virtual void Init(const palWheelInfo& wheelInfo);
	virtual palMatrix4x4& GetLocationMatrix();
	btRaycastVehicle*	m_vehicle;
	int m_WheelIndex;
};

class MultiSteppedAction;

class palBulletVehicle : public palVehicle {
public:
	palBulletVehicle();
	virtual ~palBulletVehicle();
	virtual void Init(palBody *chassis, Float MotorForce, Float BrakeForce);

	virtual palWheel* AddWheel();
	virtual void Finalize();

	virtual void Control(Float steering, Float acceleration, bool brakes);
	virtual void Update() {
		//do nothing...
	}

	//bullet code:
	virtual void ForceControl(Float steering, Float accelerationforce, Float brakeforce);

	virtual Float GetEngineForce() const { return m_cEngineForce; };
	virtual Float GetBreakingForce() const { return m_cBreakingForce; };
	virtual Float GetVehicleSteering() const { return m_cVehicleSteering; };

	virtual btRaycastVehicle::btVehicleTuning& BulletGetTuning();
private:
	Float	m_cEngineForce;
	Float	m_cBreakingForce;
	Float	m_cVehicleSteering;

	btRigidBody* m_carChassis;
	btRaycastVehicle::btVehicleTuning	m_tuning;
	btVehicleRaycaster*	m_vehicleRayCaster;
	btRaycastVehicle*	m_vehicle;
	btDynamicsWorld* m_dynamicsWorld;

	MultiSteppedAction* m_multiSteppedAction;

	FACTORY_CLASS(palBulletVehicle,palVehicle,Bullet,1)
};

class MultiSteppedAction: public btActionInterface
{
public:
   MultiSteppedAction(btRaycastVehicle* internalAction)
   : m_pInternalAction(internalAction)
   , m_iSubstepCount(1U)
   , m_vGravity(0.0, 0.0, 0.0)
   {

   }

   virtual ~MultiSteppedAction()
   {
   }

   virtual void updateAction( btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
   {
      btRigidBody* body = m_pInternalAction->getRigidBody();
      btVector3 gravity = body->getGravity();
      int upAxis = m_pInternalAction->getUpAxis();
      // Gravity is active on the body, so set it to really SIMD_EPSILON so it's not zero, but won't
      // do anything and remember the gravity
      if (gravity[upAxis] < -SIMD_EPSILON)
      {
         btVector3 smallGravity(0.0, 0.0, 0.0);
         smallGravity[upAxis] = -SIMD_EPSILON;
         body->setGravity(smallGravity);
         m_vGravity = gravity;
      }

      // gravity is zero on the body, so it's disabled, so clear the saved gravity
      if (gravity[upAxis] == btScalar(0.0))
      {
         m_vGravity = gravity;
      }

      btScalar timestep = deltaTimeStep / btScalar(m_iSubstepCount);

      btVector3 gravityImpulse = m_vGravity * timestep / body->getInvMass() ;
      for (unsigned i = 0; i < m_iSubstepCount; ++i)
      {
         body->applyCentralImpulse(gravityImpulse);
         m_pInternalAction->updateAction(collisionWorld, timestep);
      }
   }

   virtual void debugDraw(btIDebugDraw* debugDrawer)
   {
      m_pInternalAction->debugDraw(debugDrawer);
   }

   virtual unsigned GetSubStepCount() const { return m_iSubstepCount; }
   virtual void SetSubStepCount(unsigned steps) { m_iSubstepCount = steps; }

private:
   btRaycastVehicle* m_pInternalAction;
   unsigned m_iSubstepCount;
   btVector3 m_vGravity;

};


#endif
