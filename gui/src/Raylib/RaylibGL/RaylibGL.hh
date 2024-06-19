/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** RaylibGL
*/

#pragma once
#include "../Raylib.hh"
#include <rlgl.h>
#include <raymath.h>

namespace Raylib {
    class RaylibGL {
        public:
            static void myRlDisableBackfaceCulling();
            static void myRlDisableDepthMask();
            static void myRlEnableBackfaceCulling();
            static void myRlEnableDepthMask();
            static TextureCubemap genTextureCubemap(Shader shader, Texture2D panorama, int size, int format);
        protected:
        private:
    };
}
