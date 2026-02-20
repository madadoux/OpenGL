#ifndef SOUNDENGINE_H_
#define SOUNDENGINE_H_

#include "Sound.h"

#ifdef _WIN32
class SoundEngine
{
	SoundClass *sound;
	HWND hwnd;
public:
	SoundEngine()
	{
		sound = new SoundClass();
	}
	void SetWindowHandler(HWND hwnd)
	{
		this->hwnd = hwnd;
	}
	void StartBackMusic(char* path)
	{
		PlaySound(path,NULL, SND_ASYNC );
	}
	void PlayShortSound(char* path)
	{
			sound->Initialize(hwnd,path);
	}
};
#else
class SoundEngine
{
public:
	SoundEngine() {}
	void SetWindowHandler(void*) {}
	void StartBackMusic(char*) {}
	void PlayShortSound(char*) {}
};
#endif

#endif
