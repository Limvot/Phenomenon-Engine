#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include <string>
#include <stdlib.h>

#define NO_SDL_GLEXT

#include <GL/glew.h>
#include "SDL.h"
//#include "SDL/SDL_opengl.h" //Encapsulates GL/gl.h and GL/glu.h for platform compatibility. (lazyfoo tutorial)

#include <btBulletDynamicsCommon.h>

//Includes from with in engine
#include "Node.h"
#include "PhysicsObject.h"
#include "DataTypes.h"      //Also includes ExpandableArray.h

namespace phen {

class PhysicsManager
{
    public:
        PhysicsManager();
        virtual ~PhysicsManager();
        int setGravity(Vector set_gravity);
        int addPhysicsObject(PhysicsObject* add_object);
        PhysicsObject* findPhysicsObject(std::string object_name);
        int deletePhysicsObject(std::string object_name);

        int addCollisionShape(btCollisionShape* add_shape);
//        btCollisionShape* findCollisionShape(std::string shape_name);
//        int deleteCollisionShapet(std::string shape_name);

        void step(btScalar timeStep, int maxSubSteps=1, btScalar fixedTimeStep=btScalar(1.)/btScalar(60.));

    protected:
    private:

        ExpandableArray<PhysicsObject*> PhysicsObjectArray;
        GLuint numPhysicsObjects;

        ExpandableArray<btCollisionShape*> CollisionShapeArray;
        GLuint numCollisionShapes;

        btBroadphaseInterface* broadphase;

        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;

        btSequentialImpulseConstraintSolver* solver;

        btDiscreteDynamicsWorld* dynamicsWorld;
};

} //End Namespace

#endif // PHYSICSMANAGER_H
