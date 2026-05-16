#ifndef BEEP_CONST_H
#define BEEP_CONST_H



//#define MUSIC_BEEP		//“Ù¿÷∑‰√˘∆˜
#define BEEP_VOICE	50 //…˘“Ù¥Û–° 1~100


#define TIME_A						1//*10ms
#define TIME_B						5//*10ms
#define TIME_C						10//*10ms
#define TIME_D						12//*10ms
#define TIME_E						50//*10ms
#define TIME_100MS					10//*10ms
#define TIME_200MS					20//200ms
#define TIME_300MS					30//300ms
#define TIME_H						9//90ms
#define TIME_L						100//*10ms
#define TIME_DELAY					100//*10ms
#define TIME_170MS					17
#define TIME_580MS					58

//num=1000/freq KHz
#define FREQ_A					510//1.96k
#define FREQ_B					476//2.1k
#define FREQ_C					424//2.36k
#define FREQ_D					350//2.86k
#define FREQ_E					500//2k
#define FREQ_F					362//2.762k
#define FREQ_G					322//3.1k
#define BEEP_OFF				0xff
#define FREQ_2K					500//2k

#define FREQ_XIMA_DOU_DOU		488//2.0495K	
#define FREQ_XIMA_DOU			432//2.315K	
#define FREQ_XIMA_RUI			388//2.578K	
#define FREQ_XIMA_MI			364//2.747K	
#define FREQ_XIMA_FA			324//3.087K	

#ifdef MUSIC_BEEP

	#define MAX_BEEP_NO		10

	//0
	const uint TBL_MUSIC_Normal[]
	=
	{
		FREQ_F,		TIME_200MS,
		BEEP_OFF,	TIME_300MS,
		BEEP_OFF,	TIME_L,
		0
	};

	//1
	const uint TBL_MUSIC_PowerOn[]
	=
	{
		FREQ_A,		TIME_C,
		BEEP_OFF,	TIME_C,
		FREQ_B,		TIME_C,
		BEEP_OFF,	TIME_C,
		FREQ_C,		TIME_C,
		BEEP_OFF,	TIME_C,
		FREQ_D,		TIME_C,
		BEEP_OFF,	TIME_C,
		BEEP_OFF,	TIME_L,
		0
	};

	//2
	const uint TBL_MUSIC_PowerOff[]
	=
	{
		FREQ_D,		TIME_C,
		BEEP_OFF,	TIME_C,
		FREQ_C,		TIME_C,
		BEEP_OFF,	TIME_C,
		FREQ_B,		TIME_C,
		BEEP_OFF,	TIME_C,
		FREQ_A,		TIME_C,
		BEEP_OFF,	TIME_C,
		BEEP_OFF,	TIME_L,
		0
	};

	//3
	const uint TBL_MUSIC_Unuse[]
	=
	{
		FREQ_XIMA_DOU,		TIME_B,
		BEEP_OFF,			TIME_H,
		FREQ_XIMA_DOU,		TIME_B,
		BEEP_OFF,			TIME_H,
		FREQ_XIMA_DOU,		TIME_B,
		BEEP_OFF,			TIME_H,
		BEEP_OFF,  			TIME_E,
		0
	};

	//4
	const uint TBL_MUSIC_Back[]
	=
	{
		FREQ_F,		TIME_B,
		BEEP_OFF,	TIME_H,
		FREQ_F,		TIME_B,
		BEEP_OFF,	TIME_H,
		BEEP_OFF,   TIME_E,
		0
	};

	//5
	const uint TBL_MUSIC_DOU[]//1046.5
	=
	{
		FREQ_XIMA_DOU_DOU, TIME_170MS,
		BEEP_OFF,   TIME_580MS,
		0
	};

	//6
	const uint TBL_MUSIC_RUI[]//1174.66
	=
	{
		FREQ_XIMA_DOU, TIME_170MS,
		BEEP_OFF,   TIME_580MS,
		0
	};

	//7
	const uint TBL_MUSIC_MI[]//1318.5
	=
	{
		FREQ_XIMA_RUI, TIME_170MS,
		BEEP_OFF,   TIME_580MS,
		0
	};

	//8
	const uint TBL_MUSIC_FA[]//1396.9
	=
	{
		FREQ_XIMA_MI, TIME_170MS,
		BEEP_OFF,   TIME_580MS,
		0
	};

	//9
	const uint TBL_MUSIC_SOU[]//1567.98
	=
	{
		FREQ_XIMA_FA, TIME_170MS,
		BEEP_OFF,   TIME_580MS,
		0
	};




	const uint *const MusicSoundTab[]
	#ifdef BEEP_CONST_TYPE_PUBLIC
	=
	{
		TBL_MUSIC_Normal,
		TBL_MUSIC_PowerOn,
		TBL_MUSIC_PowerOff,
		TBL_MUSIC_Unuse,
		TBL_MUSIC_Back,

		TBL_MUSIC_DOU,
		TBL_MUSIC_RUI,
		TBL_MUSIC_MI,
		TBL_MUSIC_FA,
		TBL_MUSIC_SOU
	}
	#endif
	;

#else
	#define MAX_BEEP_NO		5
    //0
	const unsigned int TBL_MUSIC_100ms[]
	=
	{
		FREQ_2K,	TIME_100MS,
		0
	};

	//1
	const unsigned int TBL_MUSIC_Normal[]
	=
	{
		FREQ_2K,	TIME_200MS,
		0
	};

	//2
	const unsigned int TBL_MUSIC_300ms[]
	=
	{
		FREQ_2K,	TIME_300MS,
		0
	};

	//3
	const unsigned int TBL_MUSIC_Warn[]
	=
	{
		FREQ_2K,	TIME_200MS,
        BEEP_OFF,   TIME_100MS,
        FREQ_2K,	TIME_200MS,
        BEEP_OFF,   TIME_100MS,
        FREQ_2K,	TIME_200MS,
        BEEP_OFF,   TIME_100MS,
		0
	};

    //4
	const unsigned int TBL_MUSIC_StartOn[]
	=
	{
		FREQ_2K,	TIME_300MS,
        BEEP_OFF,   TIME_100MS,
		0
	};

	const unsigned int *const MusicSoundTab[]
	#ifdef BEEP_CONST_TYPE_PUBLIC
	=
	{
        TBL_MUSIC_100ms,
		TBL_MUSIC_Normal,
		TBL_MUSIC_300ms,
		TBL_MUSIC_Warn,
		TBL_MUSIC_StartOn
	}
	#endif
	;

#endif


#endif
