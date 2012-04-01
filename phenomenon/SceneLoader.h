#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Phenomenon.h"

namespace phen {

class SceneLoader
{
    public:
        SceneLoader();
        virtual ~SceneLoader();
        int loadScene(Scene* scene, std::string file_path);

    protected:
    private:
};

} //End Namespace

#endif // SCENELOADER_H
