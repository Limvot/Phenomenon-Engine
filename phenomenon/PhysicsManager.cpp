#include "PhysicsManager.h"

namespace phen {

PhysicsManager::PhysicsManager()
{
    numPhysicsObjects = 0;
    numCollisionShapes = 0;

    broadphase = new btDbvtBroadphase();

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0,-10,0));

}

PhysicsManager::~PhysicsManager()
{
    if (numPhysicsObjects > 0)
    {
        for (GLuint i = 0; i < numPhysicsObjects; i++)
        {
            if (PhysicsObjectArray.getArrayMember(i) != NULL)
            {
                dynamicsWorld->removeRigidBody(PhysicsObjectArray.getArrayMember(i)->getRigidBody());
                delete PhysicsObjectArray.getArrayMember(i);    //Should also delete their motion state
                PhysicsObjectArray.setArrayMember(i, NULL);
            }
        }
        numPhysicsObjects = 0;
    }

    if (numCollisionShapes > 0)
    {
        for (GLuint i = 0; i < numCollisionShapes; i++)
        {
            if (CollisionShapeArray.getArrayMember(i) != NULL)
            {
                delete CollisionShapeArray.getArrayMember(i);
                CollisionShapeArray.setArrayMember(i, NULL);
            }
        }
        numCollisionShapes = 0;
    }

    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;
}


int PhysicsManager::setGravity(Vector set_gravity)
{
    dynamicsWorld->setGravity(btVector3(set_gravity.x, set_gravity.y, set_gravity.z));
    return 0;
}


int PhysicsManager::addPhysicsObject(PhysicsObject* add_object)
{
    PhysicsObjectArray.addArrayMember(add_object);
    dynamicsWorld->addRigidBody(add_object->getRigidBody());
    numPhysicsObjects += 1;
    return 0;
}

PhysicsObject* PhysicsManager::findPhysicsObject(std::string object_name)
{
    if (numPhysicsObjects > 0)
    {
        for (GLuint i = 0; i < numPhysicsObjects; i++)
        {
            if (PhysicsObjectArray.getArrayMember(i)->name == object_name)
                return PhysicsObjectArray.getArrayMember(i);
        }

        return NULL;
    }
    return NULL;
}

int PhysicsManager::deletePhysicsObject(std::string object_name)
{
    if (numPhysicsObjects > 0)
    {
        for (GLuint i = 0; i < numPhysicsObjects; i++)
        {
            if (PhysicsObjectArray.getArrayMember(i)->name == object_name)
            {
                delete PhysicsObjectArray.getArrayMember(i);
                PhysicsObjectArray.setArrayMember(i, NULL);
                return 0;
            }
        }
        return 1;               //Couldn't find PhysicsObject
    }
    return 1;                   //No PhysicsObjects
}

int PhysicsManager::addCollisionShape(btCollisionShape* add_shape)
{
    CollisionShapeArray.addArrayMember(add_shape);
    numCollisionShapes += 1;
    return 0;
}
/*
btCollisionShape* PhysicsManager::findCollisionShape(std::string shape_name)
{
    if (numCollisionShapes > 0)
    {
        for (GLuint i = 0; i < numCollisionShapes; i++)
        {
            if (CollisionShapeArray.getArrayMember(i)->name == shape_name)
                return CollisionShapeArray.getArrayMember(i);
        }

        return NULL;
    }
    return NULL;
}

int PhysicsManager::deleteCollisionShape(std::string object_name)
{
    if (numCollisionShapes > 0)
    {
        for (GLuint i = 0; i < numCollisionShapes; i++)
        {
            if (CollisionShapeArray.getArrayMember(i)->name == shape_name)
            {
                delete CollisionShapeArray.getArrayMember(i);
                CollisionShapeArray.setArrayMember(i, NULL);
                return 0;
            }
        }
        return 1;               //Couldn't find CollisionShape
    }
    return 1;                   //No CollisionShapes
}
*/
void PhysicsManager::step(btScalar timeStep, int maxSubSteps, btScalar fixedTimeStep)
{
    dynamicsWorld->stepSimulation(timeStep, maxSubSteps, fixedTimeStep);
}

} //End Namespace


