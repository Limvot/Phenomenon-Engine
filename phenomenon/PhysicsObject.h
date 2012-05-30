#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include "stdlib.h"
#include <iostream>
#include <string>

#include <btBulletDynamicsCommon.h>

#include "Node.h"
#include "PhenomenonMotionState.h"


namespace phen {

class PhysicsObject
{
    public:
        PhysicsObject();
        PhysicsObject(std::string tmp_name);
        virtual ~PhysicsObject();

        btRigidBody* getRigidBody();
        int setShape(btCollisionShape* set_shape);
        int setMotionState(PhenomenonMotionState* set_motion_state);
        int makeRigidBody(GLint mass);

        int setObjectNode(Node* set_node);

        std::string name;
    protected:
        Node* object_node;
        PhenomenonMotionState* object_motion_state;
        btRigidBody* object_rigid_body;
        btCollisionShape* collision_shape;

    private:
};

} //End Namespace

#endif // PHYSICSOBJECT_H
