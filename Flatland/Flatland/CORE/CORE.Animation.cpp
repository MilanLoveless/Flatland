// CORE.Animation.cpp
/////////////////////////////////////////////////////////

#include "..\GameCore.h"
#include <math.h>
#include <sys/timeb.h>

	bool g_time_initialized = false;
	float g_fGlobalTime = 0.0;
	timeb g_time_start;
	timeb g_time_current;

	float LINEAR(float fPercent) {
		return fPercent;
	}

	float EASEIN(float fPercent) {
		return fPercent * fPercent;
	}

	float EASEOUT(float fPercent) {
		return (1.0 - fPercent)*(fPercent - 1.0) + 1.0;
	}

	float EASEINOUT(float fPercent) {
		double e = 2.718281828;
		return 1.0 / (1.0 + (float)pow(e, -10.0*(double)fPercent + 5.0));
	}

	Animation::Animation() {
		this->m_pReference = NULL;
		this->m_pValue = NULL;
		this->m_fValFrom = 0.0;
		this->m_fValTo = 0.0;
		this->m_pInterpFunc = NULL;
		this->m_pCompletedEvent = NULL;
		this->m_fGroupStart = 0.0;
		this->m_fGroupEnd = 0.0;
		this->m_fTimeStart = 0.0;
		this->m_fTimeEnd = 0.0;
		this->m_bActive = false;
		this->m_bCompleted = false;
	}

	float __Interpolate_(
		float fStartValue, float fEndValue,
		float fStartTime, float fCurrentTime, float fEndTime,
		InterpFunc pInterpFunc
	){
		if(pInterpFunc == NULL) return fEndValue;
		if(fCurrentTime >= fEndTime) return fEndValue;
		if(fEndTime <= fStartTime) return fEndValue;
		if(fCurrentTime <= fStartTime) return fStartValue;
		float fPercent = (fCurrentTime-fStartTime)/(fEndTime-fStartTime);
		return fStartValue + pInterpFunc(fPercent)*(fEndValue-fStartValue);
	}

	void Animation::_RunAnimation(float fCurrentTime) {
		if(this->m_pValue == NULL) return;
		if(this->m_bActive == false) return;
		if(this->m_bCompleted == true) return;
		*this->m_pValue = __Interpolate_(
			this->m_fValFrom, this->m_fValTo,
			this->m_fTimeStart, fCurrentTime, this->m_fTimeEnd,
			this->m_pInterpFunc
		);
		if(*this->m_pValue == this->m_fValTo) {
			if(this->m_nOption & OPTION_OSCILLATE) {
				float fTemp = this->m_fValFrom;
				this->m_fValFrom = this->m_fValTo;
				this->m_fValTo = fTemp;
				this->m_fTimeEnd = fCurrentTime + (this->m_fTimeEnd - this->m_fTimeStart);
				this->m_fTimeStart = fCurrentTime;
			} else if(this->m_nOption & OPTION_REPEAT) {
				this->m_fTimeEnd = fCurrentTime + (this->m_fTimeEnd - this->m_fTimeStart);
				this->m_fTimeStart = fCurrentTime;
			} else {
				this->m_bCompleted = true;
				if(this->m_pCompletedEvent != NULL) {
					this->m_pCompletedEvent(this);
				}
			}
		}
	}

	AnimationSystem::AnimationSystem() {
		// Nothing to initialize
	}

	void AnimationSystem::_UpdateCurrentTime() {
		if(g_time_initialized == false) {
			ftime(&g_time_start);
			ftime(&g_time_current);
			g_time_initialized = true;
		}
	
		ftime(&g_time_current);
		g_fGlobalTime = (g_time_current.time - g_time_start.time) + ((g_time_current.millitm - g_time_start.millitm)/1000.0);
	}

	Animation* AnimationSystem::_CreateAnimation(char *strGroupName, float *pFloat, InterpFunc pInterpFunc, float fStartValue, float fEndValue, float fStartTime, float fEndTime, int option) {

		// Animation already exists ///////////////////////////////////
		if(_GetAnimation(strGroupName) != NULL) return NULL;


		Animation *pAnimation = new Animation();
		///////////////////////////////////////////////////////////////
		// 0.0 as the start time indicates it will start immediately //
		if(fStartTime == 0.0) {
			fStartTime = g_fGlobalTime;
			fEndTime = g_fGlobalTime + fEndTime;
		}
		///////////////////////////////////////////////////////////////
		pAnimation->m_strGroupName = strGroupName;
		pAnimation->m_pReference = NULL;
		pAnimation->m_pValue = pFloat;
		pAnimation->m_fValFrom = fStartValue;
		pAnimation->m_fValTo = fEndValue;
		pAnimation->m_pInterpFunc = pInterpFunc;
		pAnimation->m_fGroupStart = fStartTime;
		pAnimation->m_fGroupEnd = fEndTime;
		pAnimation->m_fTimeStart = fStartTime;
		pAnimation->m_fTimeEnd = fEndTime;
		pAnimation->m_bActive = true;
		pAnimation->m_nOption = option;
		this->m_Animations._Add(pAnimation);
		return pAnimation;
	}

	void AnimationSystem::_RunAnimations() {
		this->m_Animations._BeginEnumerate();
		Animation* pAnim = this->m_Animations._GetNextData();
		while(pAnim != NULL) {
			pAnim->_RunAnimation(g_fGlobalTime);
			pAnim = this->m_Animations._GetNextData();
		}
	}

	Animation* AnimationSystem::_GetAnimation(char *strGroupName) {
		this->m_Animations._BeginEnumerate();
		Animation* pAnim = this->m_Animations._GetNextData();
		while(pAnim != NULL) {
			if(strcmp(pAnim->m_strGroupName, strGroupName)==0) {
				return pAnim;
			}
			pAnim = this->m_Animations._GetNextData();
		}
		return NULL;
	}

	bool AnimationSystem::_ClearAnimations(char *strGroupName) {
		bool bAnimationsCleared = false;
		this->m_Animations._BeginEnumerate();
		Animation* pAnim = this->m_Animations._GetNextData();
		while(pAnim != NULL) {
			if(strcmp(pAnim->m_strGroupName, strGroupName)==0) {
				this->m_Animations._Remove(pAnim);
				bAnimationsCleared = true;
			}
			pAnim = this->m_Animations._GetNextData();
		}
		return bAnimationsCleared;
	}

	bool AnimationSystem::_ClearAnimations() {
		this->m_Animations._DeleteAll();
		return true;
	}
