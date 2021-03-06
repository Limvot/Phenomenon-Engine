#include "Node.h"

namespace phen {

Node::Node()
{
    //Don't call this. Nodes need unique names. Note that this is called by objects that inherit this class, but they re-assign the name.
    name = "no_name";
    parent = NULL;
    tmp_return_child = NULL;
    numChildren = 0;

    localPosition.x = 0;
    localPosition.y = 0;
    localPosition.z = 0;

    localRotation.x = 0;
    localRotation.y = 0;
    localRotation.z = 0;

    localScale.x = 1;
    localScale.y = 1;
    localScale.z = 1;

    globalScale.x = 1;
    globalScale.y = 1;
    globalScale.z = 1;
}

Node::Node(std::string tmp_name)
{
    name = tmp_name;
    parent = NULL;
    tmp_return_child = NULL;
    numChildren = 0;

    localPosition.x = 0;
    localPosition.y = 0;
    localPosition.z = 0;

    localRotation.x = 0;
    localRotation.y = 0;
    localRotation.z = 0;

    localScale.x = 1;
    localScale.y = 1;
    localScale.z = 1;

    globalScale.x = 1;
    globalScale.y = 1;
    globalScale.z = 1;
}

Node::~Node()
{
    if (numChildren > 0)
    {
        for (int i = 0; i < numChildren; i++)
        {
            if (children.getArrayMember(i) != NULL)
                delete children.getArrayMember(i);
                children.setArrayMember(i, NULL);
        }
        numChildren = 0;
    }
}

int Node::setParent(Node* tempParent)
{
    if (parent != NULL)                                                                     //If we already have a parent, get rid of their reference to us.
    {
        parent->removeChild(name);
    }
    parent = tempParent;
    return 0;
}

Node* Node::findChild(std::string child_name)
{
    if (numChildren > 0)                                                                    //Only search if we have children
    {
        for (int i = 0; i < numChildren; i++)                                                    //Iliterate through the children we have
        {
            if (children.getArrayMember(i)->name == child_name)                             //If the current child is the one we're searching for, return its pointer
                return children.getArrayMember(i);

            tmp_return_child = children.getArrayMember(i)->findChild(child_name);           //If not, tell the child to run a search

            if (tmp_return_child != 0)                                                      //If the child returned the child we're looking for, return its pointer
                return tmp_return_child;                                                    //If not, continue on to the next child
        }

    }
    return 0;   //Couldn't find the child, not under us. Return.
}


int Node::removeChild(std::string child_name)
{
    for (int i = 0; i < numChildren; i++)                           //Iterate through our children to find the child named
    {
        if (children.getArrayMember(i)->name == child_name)         //If this child is it
        {
                children.setArrayMember(i, NULL);                   //Remove our reference
                return 0;                                           //Success
        }
    }

    return 1; //Failure

}

int Node::addChild(Node* newChild)
{
    children.addArrayMember(newChild);
    newChild->setParent(this);
    numChildren += 1;
    return 0;
}

int Node::deleteChild(std::string child_name)
{
    for (int i = 0; i < numChildren; i++)                           //Iterate through our children to find the child named
    {
        if (children.getArrayMember(i)->name == child_name)     //If this child is it
        {
                delete children.getArrayMember(i);              //Delete the child
                children.setArrayMember(i, NULL);
                return 0;                                       //Success
        }
    }

    return 1; //Failure
}

int Node::draw(Renderer* renderer)
{
    if (numChildren > 0)
    {
        for (int i = 0; i < numChildren; i++)
        {
            if (children.getArrayMember(i) != NULL)
                children.getArrayMember(i)->draw(renderer);
        }
    }
    return 0;                       //Base node type has no draw functionality, just calls children's draw() function.
}

int Node::setLocalPosition(float set_x, float set_y, float set_z)
{
    localPosition.x = set_x;
    localPosition.y = set_y;
    localPosition.z = set_z;

    mat_localPosition.m[0][3] = set_x;
    mat_localPosition.m[1][3] = set_y;
    mat_localPosition.m[2][3] = set_z;

    return 0;
}

int Node::setLocalPosition(Vector set_position)
{
    localPosition = set_position;

    mat_localPosition.m[0][3] = set_position.x;
    mat_localPosition.m[1][3] = set_position.y;
    mat_localPosition.m[2][3] = set_position.z;

    return 0;
}

Vector Node::getLocalPosition()
{
    return localPosition;
}

Vector Node::getGlobalPosition()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        globalPosition = localPosition;                                 //Global position is the same as local position
    } else {                                                            //If we do have a parent
        globalPosition = localPosition + parent->getGlobalPosition();   //Add its positon to ours. (note that this will continue back to the root node.)
    }

    return globalPosition;
}

Vector4f Node::getGlobalPositionv4f()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        globalPosition = localPosition;                                 //Global position is the same as local position
    } else {                                                            //If we do have a parent
        globalPosition = localPosition + parent->getGlobalPosition();   //Add its positon to ours. (note that this will continue back to the root node.)
    }

    return Vector4f(globalPosition, 1);                                 //Return with a w component of 1, since it's a position
}


Matrix4f Node::getGlobalPositionMatrix()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        mat_globalPosition = mat_localPosition;                                 //Global position is the same as local position
    } else {                                                            //If we do have a parent
        mat_globalPosition = mat_localPosition * parent->getGlobalPositionMatrix();   //Add its positon to ours. (note that this will continue back to the root node.)
    }

    return mat_globalPosition;
}


int Node::setLocalScale(float tmp_x_scale, float tmp_y_scale, float tmp_z_scale)
{
    localScale.x = tmp_x_scale;
    localScale.y = tmp_y_scale;
    localScale.z = tmp_z_scale;

    mat_localScale.m[0][0] = tmp_x_scale;
    mat_localScale.m[1][1] = tmp_y_scale;
    mat_localScale.m[2][2] = tmp_z_scale;

    return 0;
}

int Node::setLocalScale(Vector set_scale)
{
    localScale = set_scale;

    mat_localScale.m[0][0] = set_scale.x;
    mat_localScale.m[1][1] = set_scale.y;
    mat_localScale.m[2][2] = set_scale.z;

    return 0;
}

Vector Node::getLocalScale()
{
    return localScale;
}

Vector Node::getGlobalScale()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        globalScale = localScale;                                 //Global scale is the same as local scale
    } else {                                                            //If we do have a parent
        globalScale = localScale * parent->getGlobalScale();   //Multiply its scale with ours. (note that this will continue back to the root node.)
    }

    return globalScale;
}


Matrix4f Node::getGlobalScaleMatrix()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        mat_globalScale = mat_localScale;                                 //Global scale is the same as local scale
    } else {                                                            //If we do have a parent
        mat_globalScale = mat_localScale * parent->getGlobalScaleMatrix();   //Multiply its scale with ours. (note that this will continue back to the root node.)
    }

    return mat_globalScale;
}


int Node::setLocalRotation(float tmp_x_rot, float tmp_y_rot, float tmp_z_rot)
{
    localRotation.x = tmp_x_rot;
    localRotation.y = tmp_y_rot;
    localRotation.z = tmp_z_rot;

    GLfloat tmp_x_rot_rad = (tmp_x_rot/180) * PI;
    GLfloat tmp_y_rot_rad = (tmp_y_rot/180) * PI;
    GLfloat tmp_z_rot_rad = (tmp_z_rot/180) * PI;

    Matrix4f tmp_mat_x, tmp_mat_y, tmp_mat_z;

    tmp_mat_x.m[0][0] = 1;                  //The x rotations
    tmp_mat_x.m[1][1] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[1][2] = sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][1] = -sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][2] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[3][3] = 1;

    tmp_mat_y.m[0][0] = cos(tmp_y_rot_rad);     //The y rotations
    tmp_mat_y.m[0][2] = -sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = 1;
    tmp_mat_y.m[2][0] = sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = cos(tmp_y_rot_rad);
    tmp_mat_y.m[3][3] = 1;

    tmp_mat_z.m[0][0] = cos(tmp_z_rot_rad);     //The y rotations
    tmp_mat_z.m[0][1] = sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][0] = -sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][1] = cos(tmp_z_rot_rad);
    tmp_mat_z.m[2][2] = 1;
    tmp_mat_z.m[3][3] = 1;

    mat_localRotation = tmp_mat_x * tmp_mat_y * tmp_mat_z;

    return 0;
}

int Node::setLocalRotation(Vector set_rotation)
{
    localRotation = set_rotation;

    GLfloat tmp_x_rot_rad = (set_rotation.x/180) * PI;
    GLfloat tmp_y_rot_rad = (set_rotation.y/180) * PI;
    GLfloat tmp_z_rot_rad = (set_rotation.z/180) * PI;


    Matrix4f tmp_mat_x, tmp_mat_y, tmp_mat_z;

    tmp_mat_x.m[0][0] = 1;                  //The x rotations
    tmp_mat_x.m[1][1] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[1][2] = sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][1] = -sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][2] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[3][3] = 1;

    tmp_mat_y.m[0][0] = cos(tmp_y_rot_rad);     //The y rotations
    tmp_mat_y.m[0][2] = -sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = 1;
    tmp_mat_y.m[2][0] = sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = cos(tmp_y_rot_rad);
    tmp_mat_y.m[3][3] = 1;

    tmp_mat_z.m[0][0] = cos(tmp_z_rot_rad);     //The y rotations
    tmp_mat_z.m[0][1] = sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][0] = -sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][1] = cos(tmp_z_rot_rad);
    tmp_mat_z.m[2][2] = 1;
    tmp_mat_z.m[3][3] = 1;

    mat_localRotation = tmp_mat_x * tmp_mat_y * tmp_mat_z;

    return 0;
}

Vector Node::getLocalRotation()
{
    return localRotation;
}

Vector Node::getGlobalRotation()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        globalRotation = localRotation;                                 //Global rotation is the same as local rotation
    } else {                                                            //If we do have a parent
        globalRotation = localRotation + parent->getGlobalRotation();   //Add its rotation to ours. (note that this will continue back to the root node.)
    }

    return globalRotation;
}

Matrix4f Node::getGlobalRotationMatrix()
{
    if (parent == NULL)                                                 //If we don't have a parent
    {
        mat_globalRotation = mat_localRotation;                                 //Global rotation is the same as local rotation
    } else {                                                            //If we do have a parent
        mat_globalRotation = mat_localRotation * parent->getGlobalRotationMatrix();   //Add its rotation to ours. (note that this will continue back to the root node.)
    }

    return mat_globalRotation;
}

int Node::increaseLocalPosition(float inc_x, float inc_y, float inc_z)
{
    localPosition.x += inc_x;
    localPosition.y += inc_y;
    localPosition.z += inc_z;

    mat_localPosition.m[0][3] += inc_x;
    mat_localPosition.m[1][3] += inc_y;
    mat_localPosition.m[2][3] += inc_z;

    return 0;
}

int Node::increaseLocalScale(float inc_x, float inc_y, float inc_z)
{
    localScale.x += inc_x;
    localScale.y += inc_y;
    localScale.z += inc_z;

    mat_localScale.m[0][0] += inc_x;
    mat_localScale.m[1][1] += inc_y;
    mat_localScale.m[2][2] += inc_z;

    return 0;
}

int Node::increaseLocalRotation(float inc_x, float inc_y, float inc_z)
{
    localRotation.x += inc_x;
    localRotation.y += inc_y;
    localRotation.z += inc_z;

    if (localRotation.x > 360)              //Keep varibles within reasonable range. May be able to take out, as floats probally loop around when their limits are reached.
        localRotation.x -= 360;
    if (localRotation.x < -360)
        localRotation.x += 360;


    if (localRotation.y > 360)
        localRotation.y -= 360;
    if (localRotation.y < -360)
        localRotation.y += 360;


    if (localRotation.z > 360)
        localRotation.z -= 360;
    if (localRotation.z < -360)
        localRotation.z += 360;


    GLfloat tmp_x_rot_rad = (localRotation.x/180) * PI;
    GLfloat tmp_y_rot_rad = (localRotation.y/180) * PI;
    GLfloat tmp_z_rot_rad = (localRotation.z/180) * PI;


    Matrix4f tmp_mat_x, tmp_mat_y, tmp_mat_z;

    tmp_mat_x.m[0][0] = 1;                  //The x rotations
    tmp_mat_x.m[1][1] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[1][2] = sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][1] = -sin(tmp_x_rot_rad);
    tmp_mat_x.m[2][2] = cos(tmp_x_rot_rad);
    tmp_mat_x.m[3][3] = 1;

    tmp_mat_y.m[0][0] = cos(tmp_y_rot_rad);     //The y rotations
    tmp_mat_y.m[0][2] = -sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = 1;
    tmp_mat_y.m[2][0] = sin(tmp_y_rot_rad);
    tmp_mat_y.m[2][2] = cos(tmp_y_rot_rad);
    tmp_mat_y.m[3][3] = 1;

    tmp_mat_z.m[0][0] = cos(tmp_z_rot_rad);     //The y rotations
    tmp_mat_z.m[0][1] = sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][0] = -sin(tmp_z_rot_rad);
    tmp_mat_z.m[1][1] = cos(tmp_z_rot_rad);
    tmp_mat_z.m[2][2] = 1;
    tmp_mat_z.m[3][3] = 1;

    mat_localRotation = tmp_mat_x * tmp_mat_y * tmp_mat_z;

    return 0;
}

int Node::setMaterial(Material* tmp_mat)
{
    material = tmp_mat;
    return 0;
}

} //End Namespace

