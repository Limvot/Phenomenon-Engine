#include "Node.h"

Node::Node()
{
    //Don't call this. Nodes need unique names.
    name = "no_name";
    parent = NULL;
    tmp_return_child = NULL;
    numChildren = 0;
}

Node::Node(string tmp_name)
{
    name = tmp_name;
    parent = NULL;
    tmp_return_child = NULL;
    numChildren = 0;
}

Node::~Node()
{
    for (int i = 0; i < numChildren;)
    {
        delete children.getArrayMember(i);
        i += 1;
    }

}

int Node::setParent(Node* tempParent)
{
    parent = tempParent;
    return 0;
}

Node* Node::findChild(string child_name)
{
    if (numChildren > 0)                                                                    //Only search if we have children
    {
        for (int i = 0; i < numChildren;)                                                    //Iliterate through the children we have
        {
            if (children.getArrayMember(i)->name == child_name)                             //If the current child is the one we're searching for, return its pointer
                return children.getArrayMember(i);

            tmp_return_child = children.getArrayMember(i)->findChild(child_name);           //If not, tell the child to run a search

            if (tmp_return_child != 0)                                                      //If the child returned the child we're looking for, return its pointer
                return tmp_return_child;

            i += 1;                                                                         //If not, continue on to the next child
        }

    } else {
        return 0;                                                                           //The child is not under us, so return 0.
    }
    return 0;   //Never reaches here, but prevents warnings
}

int Node::addChild(Node* newChild)
{
    children.addArrayMember(newChild);
    newChild->setParent(this);
    numChildren += 1;
    return 0;
}

int Node::deleteChild(string child_name)
{
    for (int i = 0; i < numChildren;)                            //Iterate through our children to find the child named
    {
        if (children.getArrayMember(i)->name == child_name)     //If this child is it
        {
                delete children.getArrayMember(i);          //Delete the child
                return 0;                                       //Success
        }
    }

    return 1; //Failure
}

int Node::draw()
{
    if (numChildren > 0)
    {
        for (int i = 0; i < numChildren;)
        {
            children.getArrayMember(i)->draw();
            i += 1;
        }
    }
    return 0;                       //Base node type has no draw functionality, just calls children's draw() function.
}

Vertex Node::getLocalPosition()
{
    return localPosition;
}

int Node::setLocalPosition(float set_x, float set_y, float set_z)
{
    localPosition.x = set_x;
    localPosition.y = set_y;
    localPosition.z = set_z;

    return 0;
}

int Node::setLocalPosition(Vertex set_position)
{
    localPosition = set_position;

    return 0;
}

Vertex Node::getGlobalPosition()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        globalPosition = localPosition;                                 //Global position is the same as local position
    } else {                                                            //If we do have a parent
        globalPosition = localPosition + parent->getGlobalPosition();   //Add its positon to ours. (note that this is recursive, and will continue back to the root node.)
    }

    return globalPosition;
}
