/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Shader
*/

#pragma once
#include "../Raylib.hh"
#include <iostream>
#include <rlgl.h>
#include <raymath.h>

namespace Raylib {
    class Skybox {
        public:
            Skybox(const std::string &texturePath, const std::string &skyboxVsFile,
	                const std::string &skyboxFsFile, const std::string &cubemapVsFile, const std::string &cubemapFsFile);
            ~Skybox();
            Shader getShader() const;
            Model3D getSkybox() const;
            void Draw() const;
            void initSkybox(const std::string &texturePath, const std::string &skyboxVsFile,
	                const std::string &skyboxFsFile, const std::string &cubemapVsFile, const std::string &cubemapFsFile);

        protected:
        private:
            Model3D _skybox;
            Shader _shader;
    };
}
