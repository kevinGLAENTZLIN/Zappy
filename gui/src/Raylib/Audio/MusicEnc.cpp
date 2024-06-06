/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Music
*/

#include "MusicEnc.hh"

Raylib::MusicEnc::MusicEnc(const std::string &musicPath)
{
    loadMusic(musicPath);
}

Raylib::MusicEnc::~MusicEnc()
{
}

float Raylib::MusicEnc::getVolume() const
{
    return _volume;
}

extern "C" {
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
        _volume = volume;
        SetMusicVolume(_music, _volume);
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
