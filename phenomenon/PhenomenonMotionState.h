#ifndef PHENOMENONMOTIONSTATE_H
#define PHENOMENONMOTIONSTATE_H

#include "stdlib.h"
#include <iostream>
#include <string>

#include <btBulletDynamicsCommon.h>

#include "Node.h"

namespace phen {

class PhenomenonMotionState : public btMotionState
{
public:
    PhenomenonMotionState(const btTransform &initialpos, Node* set_node);
    virtual ~PhenomenonMotionState();
    void setNode(Node* set_node);
    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

protected:
    Node* object_node;
    btTransform object_position;
};

} //End Namespace

#endif // PHENOMENONMOTIONSTATE_H
