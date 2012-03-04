#include "StaticObject.h"

StaticObject::StaticObject(string tmp_name)                                                             //Please note that the StaticObject inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                                                                                    //Rest of init is taken care of by the Node constructor
    VBO = 0;
    IBO = 0;
    numIndices = 0;
}

StaticObject::StaticObject(string tmp_name, GLuint numVerticesIn, Vertex* VerticesIn, GLuint numIndicesIn, GLuint* IndicesIn)
{
    name = tmp_name;
    VBO = 0;
    IBO = 0;
    numIndices = 0;

    createVBO(numVerticesIn, VerticesIn);
    createIBO(numIndicesIn, IndicesIn);
}

StaticObject::~StaticObject()
{
    if (VBO)                                                                                            //Delete our buffers
        glDeleteBuffers(1, &VBO);

    if (IBO)
        glDeleteBuffers(1, &IBO);
}

int StaticObject::createVBO(GLuint numVertices, Vertex* Vertices)
{
    if (VBO)                                                                                            //If the buffer exists, delete it before we make a new one.
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex)*numVertices), Vertices, GL_STATIC_DRAW);              //Note that the third parameter is the size of what we're copying, which is found with
                                                                                                        //the size of one vertex (sizeof(Vertex)) times the number of vertices (numVertices)
}

int StaticObject::createIBO(GLuint numIndicesIn, GLuint* Indices)
{
    numIndices = numIndicesIn;

    if (IBO)                                                                                            //If the buffer exists, delete it before we make a new one.
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(GLuint)*numIndices), Indices, GL_STATIC_DRAW);
}

int StaticObject::draw()
{
    getGlobalPosition();                                                                                //Update our world-space varibles.
    getGlobalRotation();
    getGlobalScale();

    glPushMatrix();                                                                                     //Save state before current object transformations, rotations, scale.

    glTranslatef(globalPosition.x, globalPosition.y, globalPosition.z);                                 //Translate to our position

    glRotatef(globalRotation.x, 1.0f, 0.0f, 0.0f);                                                      //Must be a better way to do this. (rotate each axis the proper ammount.
    glRotatef(globalRotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(globalRotation.z, 0.0f, 0.0f, 1.0f);

    glScalef(globalScale.x, globalScale.y, globalScale.z);                                              //Scale along each axis the proper ammount. NOTE: I'm not sure why, for expected results, you have to scale after translation and rotation, but it seems you do.


    if (material != NULL)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);                                 //Apply material
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material->specularHardness);

        material->bindTexture();                                                                        //Bind the material texture, if there is one.
    }

//BEGIN INDEXED VBO DRAW

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    #define PHENOMENON_OPENGL_2_1
    #ifdef PHENOMENON_OPENGL_2_1
    //Used for OpenGL 2.1
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);                                                                 //We're drawing triangles, so we tell it to use sets of 3 floats
    //End OpenGL 2.1
    #else
    //This is for OpenGL >2.1
    glEnableVertexAttribArray(0);                                                                       //We like to give vertices on stream 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);                                              //We're drawing triangles, so we tell it to use sets of 3 floats
    //End OpenGL >2.1
    #endif

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);                                       //Draw the triangles.

    #ifdef PHENOMEN_OPENGL_2_1
    //For OpenGL 2.1
    glDisableClientState(GL_VERTEX_ARRAY);
    //End OpenGL 2.1
    #else
    //For OpenGL >2.1
    glDisableVertexAttribArray(0);
    //End OpenGL >2.1
    #endif
//END INDEXED VBO DRAW

    glPopMatrix();                                                                                      //Return to state before object's translations, rotations, scale.

    if (numChildren > 0)                                                                                //If we have children, go through and draw them
    {
        for (int i = 0; i < numChildren; i++)
        {
            if (children.getArrayMember(i) != NULL)
                children.getArrayMember(i)->draw();
        }
    }

    return 0;
}
