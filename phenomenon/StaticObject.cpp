#include "StaticObject.h"

namespace phen {

StaticObject::StaticObject(std::string tmp_name)                                                             //Please note that the StaticObject inherets the Node class, and all of its node releated functions.
{
    name = tmp_name;                                                                                    //Rest of init is taken care of by the Node constructor
    VBO = 0;
    IBO = 0;
    numIndices = 0;
}

StaticObject::StaticObject(std::string tmp_name, GLuint numVerticesIn, Vertex* VerticesIn, GLuint numIndicesIn, GLuint* IndicesIn)
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
    return 0;
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

    return 0;
}

int StaticObject::draw(Renderer* renderer)
{
    getGlobalPosition();                                                                                //Update our world-space varibles.
    getGlobalRotation();
    getGlobalScale();

    getGlobalPositionMatrix();                                                                                //Update our world-space varibles.
    getGlobalRotationMatrix();
    getGlobalScaleMatrix();

    //Matrix4f Mmatrix = mat_globalScale * mat_globalRotation * mat_globalPosition;                     //Said to be the norm by a tutorial, but dosn't allow for rotation at a set posiiton, which is weird.
    Matrix4f Mmatrix = mat_globalScale * mat_globalPosition * mat_globalRotation;
    Matrix4f MVPmatrix = renderer->VPmatrix * Mmatrix;

    glPushMatrix();                                                                                     //Save state before current object transformations, rotations, scale.

    glTranslatef(globalPosition.x, globalPosition.y, globalPosition.z);                                 //Translate to our position

    glRotatef(globalRotation.x, 1.0f, 0.0f, 0.0f);                                                      //Must be a better way to do this. (rotate each axis the proper ammount.)
    glRotatef(globalRotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(globalRotation.z, 0.0f, 0.0f, 1.0f);

    glScalef(globalScale.x, globalScale.y, globalScale.z);                                              //Scale along each axis the proper ammount.


    if (material != NULL)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);                                 //Apply material
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material->specularHardness);

        material->bindTexture();                                                                        //Bind the material texture, if there is one.
        if (material->material_shader != NULL)                                                          //Enable the material shader, if there is one.
        {
             material->material_shader->enableShader();

             GLuint MmatrixID = glGetUniformLocation(material->material_shader->getShader(), "M");      //Pass in the Model matrix
             glUniformMatrix4fv(MmatrixID, 1, GL_TRUE, &Mmatrix.m[0][0]);

             GLuint VmatrixID = glGetUniformLocation(material->material_shader->getShader(), "V");       //Pass in the View Matrix
             glUniformMatrix4fv(VmatrixID, 1, GL_TRUE, &renderer->Vmatrix.m[0][0]);

             GLuint MVPmatrixID = glGetUniformLocation(material->material_shader->getShader(), "MVP");   //Pass in the ModelViewProjection matrix
             glUniformMatrix4fv(MVPmatrixID, 1, GL_TRUE, &MVPmatrix.m[0][0]);


             GLuint lightPosition_worldspaceID = glGetUniformLocation(material->material_shader->getShader(), "lightPosition_worldspace");
             glUniform3fv(lightPosition_worldspaceID, 1, &renderer->light_position[0][0]);

             GLuint LightColor_inID = glGetUniformLocation(material->material_shader->getShader(), "LightColor_in");
             glUniform3fv(LightColor_inID, 1, &renderer->light_color[0][0]);

             GLuint LightPower_inID = glGetUniformLocation(material->material_shader->getShader(), "LightPower_in");
             glUniform1fv(LightPower_inID, 1, renderer->light_power);
        }
    }

//BEGIN INDEXED VBO DRAW

    #define BUFFER_OFFSET(i) ((char *)NULL + (i))

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //#define PHENOMENON_OPENGL_OLD_WAY
    #ifdef PHENOMENON_OPENGL_OLD_WAY
    //Used for OpenGL 2.1
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));                                     //We're drawing triangles, so we tell it to use sets of 3 floats

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(24));
    //End OpenGL 2.1
    #else
    //This is for OpenGL >2.1
    glEnableVertexAttribArray(0);                                                                       //We like to give vertices on stream 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));                  //We're drawing triangles, so we tell it to use sets of 3 floats

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(12));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(24));
    //End OpenGL >2.1
    #endif

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);                                       //Draw the triangles.

    #ifdef PHENOMEN_OPENGL_OLD_WAY
    //For OpenGL 2.1
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //End OpenGL 2.1
    #else
    //For OpenGL >2.1
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    //End OpenGL >2.1
    #endif
//END INDEXED VBO DRAW

    if(material->material_shader != NULL)
        material->material_shader->disableShader();                                                     //Disable our shader, if there is one.

    glPopMatrix();                                                                                      //Return to state before object's translations, rotations, scale.

    if (numChildren > 0)                                                                                //If we have children, go through and draw them
    {
        for (int i = 0; i < numChildren; i++)
        {
            if (children.getArrayMember(i) != NULL)
                children.getArrayMember(i)->draw(renderer);
        }
    }

    return 0;
}

} //End Namespace

