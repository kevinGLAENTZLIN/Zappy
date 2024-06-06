/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Music
*/

#pragma once
#include <iostream>
#include <raylib.h>

namespace Raylib {
    class MusicEnc {
        public:
            MusicEnc(const std::string &musicPath);
            ~MusicEnc();
            void loadMusic(const std::string &musicPath);
            void play();
            void setVolume(float volume);
            void updateMusic();
            Music getMusic() const;
            float getVolume() const;
        protected:
        private:
            Music _music;
            float _volume;
    };
}
