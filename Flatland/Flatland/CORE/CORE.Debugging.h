// debug.h is Copyright (c)2000 Jonathan Nix
// All Rights Reserved.

#pragma once

#ifdef NDEBUG
#define DEBUG_LOG_DISABLE
#endif

void _Initialize_CORE_Debug();
void _Uninitialize_CORE_Debug();

extern FILE *g_pDebugLogFile;

#define DECLARE_DEBUG_LOG() FILE *g_pDebugLogFile=NULL;

#define DEBUG_LOG_ERASE(){\
	fclose(fopen("debug.log", "w"));\
}

#ifdef DEBUG_LOG_DISABLE
#define DEBUG_LOG_OPEN()
#define DEBUG_LOG_CLOSE()
#define DEBUG_LOG_WRITE(M)
#else
#define DEBUG_LOG_OPEN(){\
	g_pDebugLogFile = fopen("debug.log", "a+");\
	fprintf(g_pDebugLogFile, "\n----Starting Debug Session----\n");\
}

#define DEBUG_LOG_CLOSE(){\
	fclose(g_pDebugLogFile);\
}

#define DEBUG_LOG_WRITE(M){\
	DEBUG_LOG_OPEN();\
	fprintf(g_pDebugLogFile, "[%s:%d]%s\n", __FILE__, __LINE__, M);\
	DEBUG_LOG_CLOSE();\
}
#endif

#ifdef ASSERT
#undef ASSERT
#endif

#ifdef _DEBUG
#define ASSERT(E) if(!(E)) ::DebugBreak();
#else
#define ASSERT(E) if(!(E)) ErrorMessage(#E, __FILE__, __LINE__);
#endif

#ifdef VERIFY
#undef VERIFY
#endif

#define VERIFY(H) { HRESULT h=(H); if(FAILED(h)) ProcessResult(h, __FILE__, __LINE__); }

extern void ErrorMessage(const char *msg, char *file, int line);
extern void ProcessResult(HRESULT h, char *file, int line);

#ifndef ASSERT
#define ASSERT(E)\
	if(!(E))\
	{\
		char lpszError[256];\
		sprintf(lpszError, "ASSERT(" #E ")\nLINE: %d\nFILE: %s\nDOB: %s\nTOB: %s", __LINE__, __FILE__, __DATE__, __TIME__);\
		DEBUG_LOG_WRITE(lpszError);\
		PostQuitMessage(2);\
	}
#endif


