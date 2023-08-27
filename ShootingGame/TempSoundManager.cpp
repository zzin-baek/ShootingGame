#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init(void)
{
    SOUNDMANAGER->addWaveFileWithKey("Loading", "Resources/Image/Loading.wav");
    SOUNDMANAGER->addWaveFileWithKey("Missile", "Resources/Image/Missile.wav");
    SOUNDMANAGER->addWaveFileWithKey("Stage1", "Resources/Image/Stage1.wav");
    
    return S_OK;
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();

    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
    PlaySound(fileName, NULL, SND_ASYNC | SND_ASYNC);
}

void TempSoundManager::playSoundWithKey(string key)
{
    string finalQuery = "seek " + key + " to start";
    mciSendString(finalQuery.c_str(), NULL, 0, NULL);
    string first = "play ";
    finalQuery = first + key;
    mciSendString(finalQuery.c_str(), NULL, 0, NULL);
}

void TempSoundManager::stopMp3WithKey(string key)
{
    string first = "stop ";
    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::CheckAndReplayWithKey(string key)
{
    char ch[128];

    string first = "status ";
    string end = " mode";
    string finalQuery = first + key + end;

    const char* str = finalQuery.c_str();
    mciSendString(str, ch, 128, NULL);

    if (strcmp(ch, "stopped") == 0)
    {
        finalQuery = "seek " + key + " to start";
        mciSendString(finalQuery.c_str(), NULL, 0, NULL);
        first = "play ";
        finalQuery = first + key;
        mciSendString(finalQuery.c_str(), NULL, 0, NULL);
    }
}