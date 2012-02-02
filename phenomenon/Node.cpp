#include "Node.h"

Node::Node()
{
    parent = NULL;
    children = NULL;
}

Node::~Node()
{
    if (children != NULL)
    {
        delete children;
        std::cout << "Deleted Children, deleting self\n";
    }
}

int Node::setParent(Node* tempParent)
{
    parent = tempParent;
    return 0;
}

int Node::getIndex()
{
    return index;
}

int Node::addChild(Node* newChild)
{
    children = newChild;            //Temporary Functionality
    children->setParent(this);
    return 0;
}

int Node::draw()
{
    if (children != NULL)
    {
        children->draw();
    }
    return 0;                       //Base node type has no draw functionality, just translates and then calls children.
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
