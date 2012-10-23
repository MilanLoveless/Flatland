// CORE.Debugging.cpp
//////////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

DECLARE_DEBUG_LOG();

void _Initialize_CORE_Debug() {
	DEBUG_LOG_OPEN();
}

void _Uninitialize_CORE_Debug() {
	DEBUG_LOG_CLOSE();
}

void ErrorMessage(const char *msg, char *file, int line) {

}

void ProcessResult(HRESULT hResult, LPSTR lpszFile, int nLine)
{
	DEBUG_LOG_WRITE("[PROCESS RESULT]");
	char szMessage[128];

	switch(hResult)
	{
	case D3D_OK:
		strcpy(szMessage, "[D3D_OK] No error occurred.");
		break;

	case D3DOK_NOAUTOGEN:
		strcpy(szMessage, "[D3DOK_NOAUTOGEN] This is a success code. However, the autogeneration of mipmaps is not supported for this format. This means that resource creation will succeed but the mipmap levels will not be automatically generated.");
		break;
 
	case D3DERR_CONFLICTINGRENDERSTATE:
		strcpy(szMessage, "[D3DERR_CONFLICTINGRENDERSTATE] The currently set render states cannot be used together.");
		break;
 
	case D3DERR_CONFLICTINGTEXTUREFILTER:
		strcpy(szMessage, "[D3DERR_CONFLICTINGTEXTUREFILTER] The current texture filters cannot be used together.");
		break;
 
	case D3DERR_CONFLICTINGTEXTUREPALETTE:
		strcpy(szMessage, "[D3DERR_CONFLICTINGTEXTUREPALETTE] The current textures cannot be used simultaneously.");
		break;
 
	case D3DERR_DEVICEHUNG:
		strcpy(szMessage, "[D3DERR_DEVICEHUNG] The device that returned this code caused the hardware adapter to be reset by the OS. Most applications should destroy the device and quit. Applications that must continue should destroy all video memory objects (surfaces, textures, state blocks etc) and call Reset() to put the device in a default state. If the application then continues rendering in the same way, the device will return to this state. Applies to Direct3D 9Ex only.");
		break;
 
	case D3DERR_DEVICELOST:
		strcpy(szMessage, "[D3DERR_DEVICELOST] The device has been lost but cannot be reset at this time. Therefore, rendering is not possible.A Direct 3D device object other than the one that returned this code caused the hardware adapter to be reset by the OS. Delete all video memory objects (surfaces, textures, state blocks) and call Reset() to return the device to a default state. If the application continues rendering without a reset, the rendering calls will succeed.");
		break;
 
	case D3DERR_DEVICENOTRESET:
		strcpy(szMessage, "[D3DERR_DEVICENOTRESET] The device has been lost but can be reset at this time.");
		break;
 
	case D3DERR_DEVICEREMOVED:
		strcpy(szMessage, "[D3DERR_DEVICEREMOVED] The hardware adapter has been removed. Application must destroy the device, do enumeration of adapters and create another Direct3D device. If application continues rendering without calling Reset, the rendering calls will succeed. Applies to Direct3D 9Ex only.");
		break;
 
	case D3DERR_DRIVERINTERNALERROR:
		strcpy(szMessage, "[D3DERR_DRIVERINTERNALERROR] Internal driver error. Applications should destroy and recreate the device when receiving this error. For hints on debugging this error, see Driver Internal Errors (Direct3D 9).");
		break;
 
	case D3DERR_DRIVERINVALIDCALL:
		strcpy(szMessage, "[D3DERR_DRIVERINVALIDCALL] Not used.");
		break;
 
	case D3DERR_INVALIDCALL:
		strcpy(szMessage, "[D3DERR_INVALIDCALL] The method call is invalid. For example, a method's parameter may not be a valid pointer.");
		break;
 
	case D3DERR_INVALIDDEVICE:
		strcpy(szMessage, "[D3DERR_INVALIDDEVICE] The requested device type is not valid.");
		break;
 
	case D3DERR_MOREDATA:
		strcpy(szMessage, "[D3DERR_MOREDATA] There is more data available than the specified buffer size can hold.");
		break;
 
	case D3DERR_NOTAVAILABLE:
		strcpy(szMessage, "[D3DERR_NOTAVAILABLE] This device does not support the queried technique.");
		break;
 
	case D3DERR_NOTFOUND:
		strcpy(szMessage, "[D3DERR_NOTFOUND] The requested item was not found.");
		break;
 
	case D3DERR_OUTOFVIDEOMEMORY:
		strcpy(szMessage, "[D3DERR_OUTOFVIDEOMEMORY] Direct3D does not have enough display memory to perform the operation. The device is using more resources in a single scene than can fit simultaneously into video memory. Present, PresentEx, or CheckDeviceState can return this error. Recovery is similar to D3DERR_DEVICEHUNG, though the application may want to reduce its per-frame memory usage as well to avoid having the error recur.");
		break;
 
	case D3DERR_TOOMANYOPERATIONS:
		strcpy(szMessage, "[D3DERR_TOOMANYOPERATIONS] The application is requesting more texture-filtering operations than the device supports.");
		break;

	case D3DERR_UNSUPPORTEDALPHAARG:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDALPHAARG] The device does not support a specified texture-blending argument for the alpha channel.");
		break;
 
	case D3DERR_UNSUPPORTEDALPHAOPERATION:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDALPHAOPERATION] The device does not support a specified texture-blending operation for the alpha channel.");
		break;
 
	case D3DERR_UNSUPPORTEDCOLORARG:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDCOLORARG] The device does not support a specified texture-blending argument for color values.");
		break;
 
	case D3DERR_UNSUPPORTEDCOLOROPERATION:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDCOLOROPERATION] The device does not support a specified texture-blending operation for color values.");
		break;
 
	case D3DERR_UNSUPPORTEDFACTORVALUE:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDFACTORVALUE] The device does not support the specified texture factor value. Not used; provided only to support older drivers.");
		break;
 
	case D3DERR_UNSUPPORTEDTEXTUREFILTER:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDTEXTUREFILTER] The device does not support the specified texture filter.");
		break;
 
	case D3DERR_WASSTILLDRAWING:
		strcpy(szMessage, "[D3DERR_WASSTILLDRAWING] The previous blit operation that is transferring information to or from this surface is incomplete.");
		break;
 
	case D3DERR_WRONGTEXTUREFORMAT:
		strcpy(szMessage, "[D3DERR_WRONGTEXTUREFORMAT] The pixel format of the texture surface is not valid.");
		break;
 
	case E_FAIL:
		strcpy(szMessage, "[E_FAIL] An undetermined error occurred inside the Direct3D subsystem.");
		break;
 
	case E_INVALIDARG:
		strcpy(szMessage, "[E_INVALIDARG] An invalid parameter was passed to the returning function.");
		break;
  
	case E_NOINTERFACE:
		strcpy(szMessage, "[E_NOINTERFACE] No object interface is available.");
		break;
 
	case E_NOTIMPL:
		strcpy(szMessage, "[E_NOTIMPL] Not implemented.");
		break;
 
	case E_OUTOFMEMORY:
		strcpy(szMessage, "[E_OUTOFMEMORY] Direct3D could not allocate sufficient memory to complete the call.");
		break;
  
	case S_NOT_RESIDENT:
		strcpy(szMessage, "[S_NOT_RESIDENT] At least one allocation that comprises the resources is on disk. Direct3D 9Ex only.");
		break;

	case S_RESIDENT_IN_SHARED_MEMORY:
		strcpy(szMessage, "[S_RESIDENT_IN_SHARED_MEMORY] No allocations that comprise the resources are on disk. However, at least one allocation is not in GPU-accessible memory. Direct3D 9Ex only.");
		break;
 
	case S_PRESENT_MODE_CHANGED:
		strcpy(szMessage, "[S_PRESENT_MODE_CHANGED] The desktop display mode has been changed. The application can continue rendering, but there might be color conversion/stretching. Pick a back buffer format similar to the current display mode, and call Reset to recreate the swap chains. The device will leave this state after a Reset is called. Direct3D 9Ex only.");
		break;
 
	case S_PRESENT_OCCLUDED:
		strcpy(szMessage, "[S_PRESENT_OCCLUDED] The presentation area is occluded. Occlusion means that the presentation window is minimized or another device entered the fullscreen mode on the same monitor as the presentation window and the presentation window is completely on that monitor. Occlusion will not occur if the client area is covered by another Window. Occluded applications can continue rendering and all calls will succeed, but the occluded presentation window will not be updated. Preferably the application should stop rendering to the presentation window using the device and keep calling CheckDeviceState until S_OK or S_PRESENT_MODE_CHANGED returns. Direct3D 9Ex only.");
		break;
 
	case D3DERR_UNSUPPORTEDOVERLAY:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDOVERLAY] The device does not support overlay for the specified size or display mode. Direct3D 9Ex under Windows 7 only.");
		break;

	case D3DERR_UNSUPPORTEDOVERLAYFORMAT:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDOVERLAYFORMAT] The device does not support overlay for the specified surface format. Direct3D 9Ex under Windows 7 only.");
		break;
 
	case D3DERR_CANNOTPROTECTCONTENT:
		strcpy(szMessage, "[D3DERR_CANNOTPROTECTCONTENT] The specified content cannot be protected. Direct3D 9Ex under Windows 7 only.");
		break;
 
	case D3DERR_UNSUPPORTEDCRYPTO:
		strcpy(szMessage, "[D3DERR_UNSUPPORTEDCRYPTO] The specified cryptographic algorithm is not supported. Direct3D 9Ex under Windows 7 only.");
		break;
 
	case D3DERR_PRESENT_STATISTICS_DISJOINT:
		strcpy(szMessage, "[D3DERR_PRESENT_STATISTICS_DISJOINT] The present statistics have no orderly sequence. Direct3D 9Ex under Windows 7 only.");
		break;
 
	default:
		strcpy(szMessage, "An unknown error has occurred.");
		break;
	}

	char szDlgText[256];
	sprintf(szDlgText, "Fatal Exception Caught:\n%s\nFile:%s\nLine:%d", szMessage, lpszFile, nLine);

	DEBUG_LOG_WRITE(szDlgText);

#ifdef _DEBUG
	MessageBeep(MB_ICONSTOP);
	MessageBox(NULL, szDlgText, "CORE", MB_OK);
#endif

	PostQuitMessage(1);

}