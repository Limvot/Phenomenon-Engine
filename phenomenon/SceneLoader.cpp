#include "SceneLoader.h"

namespace phen {

SceneLoader::SceneLoader()
{
}

SceneLoader::~SceneLoader()
{

}

int SceneLoader::loadScene(Scene* scene, std::string file_path)
{

    FILE * file = fopen(file_path.c_str(), "r");
    if (file == NULL)
    {
        std::cout << "Could not open the scene file " << file_path << "\n";
        return false;
    }

    Material* default_material = scene->newMaterial("default");

    char buffer[1024];
    char buffer2 [1024];
    std::string loading_obj_file_path;
    std::string loading_texture_file_path;
    std::string loading_name;
    ModelLoader model_loader;
    StaticObject* loading_obj;
    Material* loading_material;
    Texture* loading_texture;
    Light* loading_light;

    Vector loading_position, loading_rotation, loading_scale;
    Color3f loading_ambient, loading_diffuse;

    while (1)
    {
        char lineHeader[1024];                   //Assuming words are less than 1024 chars, which is pretty bad

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;                              //Reached end of file

        if (strcmp(lineHeader, "o") == 0)       //If its a plain object type
        {
            fscanf(file, "%s %f/%f/%f %f/%f/%f %f/%f/%f\n", buffer, &loading_position.x, &loading_position.y, &loading_position.z, &loading_rotation.x, &loading_rotation.y, &loading_rotation.z, &loading_scale.x, &loading_scale.y, &loading_scale.z);
            loading_obj_file_path = buffer;

            loading_obj = model_loader.loadOBJ(loading_obj_file_path, loading_obj_file_path);
            loading_obj->setMaterial(default_material);

            loading_obj->setLocalPosition(loading_position);
            loading_obj->setLocalRotation(loading_rotation);
            loading_obj->setLocalScale(loading_scale);

            scene->getRootNode()->addChild(loading_obj);

            if(loading_obj)
                std::cout << "Loaded object from " << loading_obj_file_path << "\n";

            loading_obj = NULL;
            loading_obj_file_path = "";
        }

        if (strcmp(lineHeader, "l") == 0)       //If its a plain object type
        {
            fscanf(file, "%s %f/%f/%f %f/%f/%f %f/%f/%f\n", buffer, &loading_position.x, &loading_position.y, &loading_position.z, &loading_ambient.r, &loading_ambient.g, &loading_ambient.b, &loading_diffuse.r, &loading_diffuse.g, &loading_diffuse.b);
            loading_name = buffer;
            loading_light = scene->newLight(loading_name);
            loading_light->setLocalPosition(loading_position);
            loading_light->setAmbient(loading_ambient);
            loading_light->setDiffuse(loading_diffuse);

            loading_light = NULL;
        }

        if (strcmp(lineHeader, "to") == 0)      //If its a textured object type
        {
            fscanf(file, "%s %s %f/%f/%f %f/%f/%f %f/%f/%f\n", buffer, buffer2, &loading_position.x, &loading_position.y, &loading_position.z, &loading_rotation.x, &loading_rotation.y, &loading_rotation.z, &loading_scale.x, &loading_scale.y, &loading_scale.z);
            loading_obj_file_path = buffer;
            loading_texture_file_path = buffer2;

            loading_obj = model_loader.loadOBJ(loading_obj_file_path, loading_obj_file_path);

            loading_material = scene->findMaterial(loading_texture_file_path);
            if (loading_material == NULL)
            {
                loading_material = scene->newMaterial(loading_texture_file_path);
            }

            loading_texture = scene->findTexture(loading_texture_file_path);

            if (loading_texture == NULL)
            {
                loading_texture = scene->newTexture(loading_texture_file_path);
                loading_texture->load(loading_texture_file_path);
                std::cout << "Loading " << loading_texture_file_path << "\n";
            } else {
                std::cout << "Found matching texture, skipping reload of " << loading_texture_file_path << " for " << loading_obj_file_path << "\n";
            }

            loading_material->setTexture(loading_texture);
            loading_obj->setMaterial(loading_material);

            loading_obj->setLocalPosition(loading_position);
            loading_obj->setLocalRotation(loading_rotation);
            loading_obj->setLocalScale(loading_scale);

            scene->getRootNode()->addChild(loading_obj);

            if(loading_obj)
                std::cout << "Loaded object from " << loading_obj_file_path << " with material and texture from " << loading_texture_file_path << "\n";

            loading_obj = NULL;
            loading_material = NULL;
            loading_texture = NULL;
            loading_obj_file_path = "";
            loading_texture_file_path = "";
        }

        if (strcmp(lineHeader, "l") == 0)       //If its a light type
        {

        }
    }

    return 0;
}

} //End Namespace

