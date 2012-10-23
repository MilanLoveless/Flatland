// CORE.Hardware.Drawing.3D.h
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_HARDWARE_DRAWING_3D_H_
#define __CORE_HARDWARE_DRAWING_3D_H_

extern IDirect3DSurface9* g_pBackSurface;

void _InitializeCOREDrawing3D(RECT *rDest);
void _UninitializeCOREDrawing3D();

void _FlipSurface(IDirect3DTexture9 *pSurface);

#endif