#ifndef SOUND_H_
#define SOUND_H_


#include <vector>
#include <string>
#include <fmod.h>
#include <fmod_errors.h>

using namespace std;
#pragma comment(lib, "C:\\Program Files (x86)\\FMOD SoundSystem\\FMOD Programmers API Win32\\api\\lib\\fmodex_vc.lib")

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


class SoundManager
{
	static SoundManager& instance;
	SoundManager():
			fsystem(NULL),
			soundsvector(),
			fchannel(NULL),
			fresult(),
			fversion(0)
	{
	}
public:
	FMOD_SYSTEM      *fsystem;
    vector<FMOD_SOUND*>		soundsvector;
    FMOD_CHANNEL     *fchannel;
    FMOD_RESULT       fresult;
    unsigned int      fversion;
	~SoundManager()
	{
		clear();
		FMOD_System_Release(fsystem);
	}

	int initialize()
	{
		/*
			Create a System object and initialize.
		*/
		fresult = FMOD_System_Create(&fsystem);
		ERRCHECK(fresult);

		fresult = FMOD_System_GetVersion(fsystem, &fversion);
		ERRCHECK(fresult);

		if (fversion < FMOD_VERSION)
		{
			printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", fversion, FMOD_VERSION);
			return 1;
		}
		fresult = FMOD_System_Init(fsystem, 32, FMOD_INIT_NORMAL, NULL);
		ERRCHECK(fresult);

		return 0;
	}
	void setsound(const unsigned int& Number, const std::string& Path, const bool& Loop=false)
	{
		preparesoundvector(Number);//reserves enough space for the sounds to be stored
		fresult = FMOD_System_CreateSound(fsystem, Path.c_str(), FMOD_HARDWARE, 0, &(soundsvector.at(Number)));
		ERRCHECK(fresult);
		if(Loop)
		{
			fresult = FMOD_Sound_SetMode(soundsvector.at(Number), FMOD_LOOP_NORMAL);
			ERRCHECK(fresult);
		}
		else
		{
			fresult = FMOD_Sound_SetMode(soundsvector.at(Number), FMOD_LOOP_OFF);
			ERRCHECK(fresult);
		}
	}
	void playsound(const unsigned int& Number)
	{
		if(soundsvector.at(Number)!=NULL)
		{
			fresult = FMOD_System_PlaySound(fsystem, FMOD_CHANNEL_FREE, soundsvector.at(Number), 0, &fchannel);
			ERRCHECK(fresult);
		}
	}
	void preparesoundvector(const unsigned int& Number)
	{
		while(soundsvector.size()<=Number)
		{
			soundsvector.push_back(NULL);
		}
	}

	void clear()
	{
		for (unsigned int i=0;i<soundsvector.size();i++)
		{
			if(soundsvector.at(i)!=NULL)
			{
				fresult=FMOD_Sound_Release(soundsvector.at(i));
				ERRCHECK(fresult);
			}
		}
		soundsvector.clear();
	}
	static
	SoundManager& getinstance()
	{
		return instance;
	}
};

SoundManager& SoundManager::instance=SoundManager();





#endif /* SOUND_H_ */