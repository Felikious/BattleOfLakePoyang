#pragma once
#include <sgg/graphics.h>
#include <iostream>
#include <string>
//#include <unordered_map>

class Audio
{
    static Audio* instance;
    //std::unordered_map<std::string, std::string> sounds;//stores sound file paths
  //std::unordered_map<std::string, std::string> songs;//stores song file paths

    
    float m_press_time = 0.0f;
    bool m_pressed = false;
    const float cooldown = 0.3f;
    std::string m_asset_path = "assets\\";
    graphics::Brush m_brush_mute;

    /*std::string getFullAssetPath(const std::string asset)//debug sircular include
    {
        return m_asset_path + asset;
    }*/

public:
    static Audio* getInstance() {
        if (instance == nullptr) {
            instance = new Audio;
        }
        return instance;
    }
    bool is_music_playing = false;
    bool is_muted = false;
    void init() {
    }
    //std::string defaultMusic = GameState::getState()->getFullAssetPath(sounds[soundfile]);

    //std::string defaultMusic = getFullAssetPath("song1.mp3");
    //playMusic(defaultMusic, 0.5f, false,0)


/*void loadSoundFile(const std::string& name, const std::string& filePath)
{
    sounds[name] = filePath;//store file name or path
}*/


/*void loadMusicFile(const std::string& name, const std::string& filePath)
{
    songs[name] = filePath;
}*/


    void playMySound(std::string soundfile, float volume, bool looping = false)
    {
        graphics::playSound(GET_FULL_ASSET_PATH(soundfile), volume, looping);//allagi 
    }

    void playMyMusic(std::string songfile, float volume, bool looping = true, int fade_time = 0)//na balw random
    {
        graphics::playMusic(GET_FULL_ASSET_PATH(songfile), volume, looping);

    }

    void stopMyMusic(int fade_time = 0)
    {
        graphics::stopMusic(fade_time);
    }

    void drawMuteButton()
    {
        SETCOLOR(m_brush_mute.fill_color, 1.0f, 1.0f, 1.0f);
        m_brush_mute.fill_opacity = 1.0f;
        m_brush_mute.outline_opacity = 0.0f;
        m_brush_mute.outline_opacity = 0.0f;
        if (is_muted)
        {
            m_brush_mute.texture = GET_FULL_ASSET_PATH(IMG_MUTE);
        }
        else
        {
            m_brush_mute.texture = GET_FULL_ASSET_PATH(IMG_UNMUTE);
        }
        graphics::drawRect(38, 2, 2, 2, m_brush_mute);

    }



    //mute
    void mute(float dt)//kaleitai apo gameState
    {
        m_press_time += dt;

        if (graphics::getKeyState(graphics::SCANCODE_M) && (!m_pressed) && (m_press_time >= cooldown))//bgalto
        {

            if (!is_muted)
            {
                Audio::getInstance()->playMyMusic("song1.mp3", 0.0f, true);
                is_muted = true;
            }
            else
            {
                Audio::getInstance()->playMyMusic("song1.mp3", 0.1f, true);
                is_muted = false;
            }
            //OR: to volume ginetai 0
            //turn sound off
            m_pressed = true;
            m_press_time = 0.0f;
        }
        else if (!graphics::getKeyState(graphics::SCANCODE_M)) {
            m_pressed = false;
        }
    }
    Audio() //constructor
    {

    }


    ~Audio() //destructor
    {

    }

    /*AudioManager(const std::unordered_map<std::string, std::string>& sounds, const std::unordered_map<std::string, std::string>& songs)
        : sounds(sounds), songs(songs)
    {
    }*/
};
