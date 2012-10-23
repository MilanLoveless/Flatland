// CORE.Hardware.3D.Texture.h
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
// NOTE: Visual Studio bug with Intellisense support
//#ifndef __CORE_HARDWARE_3D_TEXTURE_H_
//#define __CORE_HARDWARE_3D_TEXTURE_H_

#include "CORE.Hardware.3D.h"

struct TEXTUREINFO {
	int _nID;
	char *_pFileName;
	IDirect3DTexture9 *_pSurface;
    D3DSURFACE_DESC _SurfaceDesc;
	int _nWidth;
	int _nHeight;
	int _nActualWidth;
	int *_video;
	RECT _Rect;
};

TEXTUREINFO* _CreateTexture(int nID, int nWidth, int nHeight);
TEXTUREINFO* _LoadTexture(int nID, char *strFilename, int nWidth, int nHeight);

bool _LockTexture(TEXTUREINFO *pImage);
void _ClearTexture(TEXTUREINFO *pImage, int color);

//void _DrawImageFromRGB(TEXTUREINFO *pDest, BYTE *pRGB, int w, int h, int xdest, int ydest);
void _DrawTextureFromWin32BitmapInfo(IDirect3DSurface9 *pDest, LPBITMAPINFO pBmp, int w, int h, int xdest, int ydest);
void _DrawTexture(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xdest, int ydest);

void _DrawTextureWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xdest, int ydest, float alpha);
void _DrawTextureWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xdest, int ydest);

void _DrawTextureCentered(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xoffset, int yoffset);
void _DrawTextureCenteredWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xoffset, int yoffset);

void _DrawTextureCentered(TEXTUREINFO *pDest, TEXTUREINFO *pSrc);
void _DrawTextureCenteredWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc);

void _UnlockTexture(TEXTUREINFO *pImage);

void _UnloadTexture(TEXTUREINFO **ppInfo);
//#endif