// CORE.Image.h
/////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
// NOTE: Visual Studio bug with Intellisense support
//#ifndef __CORE_IMAGE_H_
//#define __CORE_IMAGE_H_

#include "CORE.Hardware.3D.h"
#include "CORE.Hardware.3D.Texture.h"

typedef TEXTUREINFO IMAGEINFO;

IMAGEINFO* _CreateImage(int nID, int nWidth, int nHeight);

IMAGEINFO* _LoadImage(int nID, char *strFilename, int nWidth, int nHeight);

void _ClearImage(IMAGEINFO *pImage, int color);
void _DrawImage(IMAGEINFO *pDest, IMAGEINFO *pSrc, int xdest, int ydest);
void _DrawImage(IMAGEINFO *pDest, IMAGEINFO *pSrc, int xdest, int ydest, float alpha);
void _DrawImageCentered(IMAGEINFO *pDest, IMAGEINFO *pSrc, int xoffset, int yoffset);
void _DrawImageCentered(IMAGEINFO *pDest, IMAGEINFO *pSrc);

void _UnloadImage(IMAGEINFO **ppInfo);

//#endif