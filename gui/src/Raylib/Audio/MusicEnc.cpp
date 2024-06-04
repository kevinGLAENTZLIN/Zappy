/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Music
*/

#include "MusicEnc.hh"

extern "C" {
    Raylib::MusicEnc::MusicEnc(const std::string &musicPath)
    {
        loadMusic(musicPath);
    }

    Raylib::MusicEnc::~MusicEnc()
    {
    }

    void Raylib::MusicEnc::loadMusic(const std::string &musicPath)
    {
        _music = LoadMusicStream(musicPath.c_str());
    }

    void Raylib::MusicEnc::play()
    {
        PlayMusicStream(_music);
    }

    void Raylib::MusicEnc::setVolume(float volume)
    {
        SetMusicVolume(_music, volume);
    }

    void Raylib::MusicEnc::updateMusic()
    {
        UpdateMusicStream(_music);
    }

    Music Raylib::MusicEnc::getMusic() const
    {
        return _music;
    }
}
