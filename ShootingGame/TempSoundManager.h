#pragma once
#include "SingletonBase.h"

#include <mmsystem.h>
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")

class TempSoundManager : public SingletonBase <TempSoundManager>
{
public:
	HRESULT init(void);
	void addWaveFileWithKey(string key, string fileName);
	void playEffectSoundWave(char* fileName);
	void playSoundWithKey(string key);
	void CheckAndReplayWithKey(string key);
	void stopMp3WithKey(string key);

	TempSoundManager() {}
	~TempSoundManager() {}
};
