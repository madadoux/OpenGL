///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.h
///////////////////////////////////////////////////////////////////////////////

/////////////
// LINKING //
/////////////
#ifndef SOUND_H_
#define SOUND_H_

#ifdef _WIN32

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//////////////
// INCLUDES //
//////////////
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
 
 
///////////////////////////////////////////////////////////////////////////////
// Class name: SoundClass
///////////////////////////////////////////////////////////////////////////////
class SoundClass
{
private:

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
 
public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();

	bool Initialize(HWND,char*);
	void Shutdown();
 
private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
 
	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);
 
	bool PlayWaveFile();
 
private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;

	IDirectSoundBuffer8* m_secondaryBuffer1;
};

#else

class SoundClass
{
public:
	SoundClass() {}
	SoundClass(const SoundClass&) {}
	~SoundClass() {}

	bool Initialize(void*, char*) { return false; }
	void Shutdown() {}
};

#endif

#endif 
