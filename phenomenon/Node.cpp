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
        std::cout << "Deleated Children, deleting self\n";
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
        children->draw();
    return 0;                       //Base node type has no draw functionality
}
