#include "PhenomenonMotionState.h"

namespace phen {

PhenomenonMotionState::PhenomenonMotionState(const btTransform &initialpos, Node* set_node)
{
    object_node = set_node;
    object_position = initialpos;
}

PhenomenonMotionState::~PhenomenonMotionState()
{
}

void PhenomenonMotionState::setNode(Node* set_node)
{
    object_node = set_node;
}

void PhenomenonMotionState::getWorldTransform(btTransform &worldTrans) const
{
    worldTrans = object_position;
}

void PhenomenonMotionState::setWorldTransform(const btTransform &worldTrans)
{
    if (object_node == NULL)
        return;                 //return, we don't have a node
    btQuaternion rot = worldTrans.getRotation();
    object_node->setLocalRotation(rot.x(), rot.y(), rot.z());
    btVector3 pos = worldTrans.getOrigin();
    object_node->setLocalPosition(pos.x(), pos.y(), pos.z());
}

} //End Namespace
