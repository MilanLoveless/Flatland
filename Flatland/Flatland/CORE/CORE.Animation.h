// CORE.Animation.h
/////////////////////////////////////////////////////////

#ifndef __CORE_ANIMATION_H_
#define __CORE_ANIMATION_H_

#include "CORE.Collection.h"

	class Animation;

	typedef float (*InterpFunc)(float fPercent); 
	typedef void (*CompletedFunc)(Animation *pSender);

	#define OPTION_NORMAL 0
	#define OPTION_REPEAT 1
	#define OPTION_OSCILLATE 2

	float LINEAR(float fPercent);
	float EASEIN(float fPercent);
	float EASEOUT(float fPercent);
	float EASEINOUT(float fPercent);

	class Animation {
	public:
		Animation();

		char* m_strGroupName;

		void* m_pReference;
		float* m_pValue;

		float m_fValFrom;
		float m_fValTo;
		InterpFunc m_pInterpFunc;
		CompletedFunc m_pCompletedEvent;
		float m_fTimeStart;
		float m_fTimeEnd;

		float m_fGroupStart;
		float m_fGroupEnd;

		int m_nOption;

		void _RunAnimation(float fCurrentTime);

		bool m_bActive;
		bool m_bCompleted;
	};

	class AnimationSystem {
		Collection<Animation> m_Animations;
	public:
		AnimationSystem();

		void _UpdateCurrentTime();
		Animation* _CreateAnimation(char *strGroupName, float *pFloat, InterpFunc pInterpFunc, float fStartValue, float fEndValue, float fStartTime, float fEndTime, int option);
		void _RunAnimations();

		Animation* _GetAnimation(char *strGroupName);

		bool _ClearAnimations(char *strGroupName);
		bool _ClearAnimations();
	};

#endif