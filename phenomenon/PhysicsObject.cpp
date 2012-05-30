#include "PhysicsObject.h"

namespace phen {

PhysicsObject::PhysicsObject()
{
    name = "no_name";
    collision_shape = NULL;
    object_rigid_body = NULL;
    object_motion_state = NULL;
}

PhysicsObject::PhysicsObject(std::string tmp_name)
{
    name = tmp_name;
    collision_shape = NULL;
    object_rigid_body = NULL;
    object_motion_state = NULL;
}

PhysicsObject::~PhysicsObject()
{
    delete object_motion_state;
    delete object_rigid_body;
}

btRigidBody* PhysicsObject::getRigidBody()
{
    return object_rigid_body;
}

int PhysicsObject::setShape(btCollisionShape* set_shape)
{
    collision_shape = set_shape;
    return 0;
}

int PhysicsObject::setMotionState(PhenomenonMotionState* set_motion_state)
{
    object_motion_state = set_motion_state;
    return 0;
}

int PhysicsObject::makeRigidBody(GLint mass)
{
    btVector3 inertia(0,0,0);                                   //Init inertia to 0
    if (mass != 0)
        collision_shape->calculateLocalInertia(mass,inertia);   //If we have mass, calculate inertia

    btRigidBody::btRigidBodyConstructionInfo object_rigid_body_CI(mass, object_motion_state, collision_shape, inertia);
    object_rigid_body = new btRigidBody(object_rigid_body_CI);
    return 0;
}

int PhysicsObject::setObjectNode(Node* set_node)
{
    object_node = set_node;
    return 0;
}

} //End Namespace
