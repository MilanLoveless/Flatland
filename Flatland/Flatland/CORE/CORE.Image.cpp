// CORE.Texture.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

IMAGEINFO* _CreateImage(int nID, int nWidth, int nHeight) {

	IMAGEINFO *pImageInfo = new IMAGEINFO;
	if(pImageInfo == NULL) return NULL;

	pImageInfo->_nActualWidth = nWidth;
	pImageInfo->_nHeight = nHeight;
	pImageInfo->_nID = nID;
	pImageInfo->_nWidth = nWidth;
	pImageInfo->_pFileName = "untitled.dat";
	pImageInfo->_pSurface = NULL;
	pImageInfo->_Rect.top = 0;
	pImageInfo->_Rect.left = 0;
	pImageInfo->_Rect.right = pImageInfo->_nWidth;
	pImageInfo->_Rect.bottom = pImageInfo->_nHeight;
	memset(&pImageInfo->_SurfaceDesc, 0, sizeof(D3DSURFACE_DESC));
	int nNumPixels = pImageInfo->_nActualWidth*pImageInfo->_nHeight;
	pImageInfo->_video = new int[nNumPixels];

	return pImageInfo;
}

IMAGEINFO* _LoadImage(int nID, char *strFilename, int nWidth, int nHeight) {

	IMAGEINFO *pImageInfo = new IMAGEINFO;
	if(pImageInfo == NULL) return NULL;

	TEXTUREINFO *pTexture = _LoadTexture(nID, strFilename, nWidth, nHeight);
	if(pTexture != NULL) {
		if(!_LockTexture(pTexture)) {
			_UnloadTexture(&pTexture);
			return NULL;
		}
		pImageInfo->_nActualWidth = pTexture->_nActualWidth;
		pImageInfo->_nHeight = pTexture->_nHeight;
		pImageInfo->_nID = nID;
		pImageInfo->_nWidth = pTexture->_nWidth;
		pImageInfo->_pFileName = "untitled.dat";
		pImageInfo->_pSurface = NULL;
		pImageInfo->_Rect.top = 0;
		pImageInfo->_Rect.left = 0;
		pImageInfo->_Rect.right = pImageInfo->_nWidth;
		pImageInfo->_Rect.bottom = pImageInfo->_nHeight;
		memset(&pImageInfo->_SurfaceDesc, 0, sizeof(D3DSURFACE_DESC));
		int nNumPixels = pImageInfo->_nActualWidth*pImageInfo->_nHeight;
		pImageInfo->_video = new int[nNumPixels];
		memcpy(pImageInfo->_video, pTexture->_video, nNumPixels*sizeof(int));
		_UnlockTexture(pTexture);
		_UnloadTexture(&pTexture);
		return pImageInfo;
	}

	return NULL;
}

void _UnloadImage(IMAGEINFO **ppInfo) {
	if(ppInfo == NULL) return;
	if(*ppInfo == NULL) return;
	if((*ppInfo)->_video != NULL) {
		delete [] (*ppInfo)->_video;
	}
	delete *ppInfo;
	*ppInfo = NULL;
}

void _ClearImage(IMAGEINFO *pImage, int color) {
	int n = pImage->_nActualWidth * pImage->_nHeight;
	while(--n) {
		pImage->_video[n] = color;
	}
}

void _DrawImage(IMAGEINFO *pDest, IMAGEINFO *pSrc, int xdest, int ydest, float alpha) {
	float oldAlpha = _GetGlobalAlpha();
	_SetGlobalAlpha(alpha);
	_DrawImage(pDest, pSrc, xdest, ydest);
	_SetGlobalAlpha(oldAlpha);
}

void _DrawImage(IMAGEINFO *pDest, IMAGEINFO *pSrc, int xdest, int ydest) {
	for(int x = 0; x < pSrc->_nWidth; x++) {
		for(int y = 0; y < pSrc->_nHeight; y++) {
			int indexSource = y * pSrc->_nActualWidth + x;
			int indexDest = (y+ydest)*pDest->_nActualWidth + (x+xdest);
			int pixelSource = pSrc->_video[indexSource];
			int pixelDest = pDest->_video[indexDest];
			int pixelBlended = _BlendColor(pixelDest, pixelSource, _GetGlobalAlpha());
			pDest->_video[indexDest] = pixelBlended;
		}
	}
}

void _DrawImageCentered(IMAGEINFO *pDest, IMAGEINFO *pSrc, int xoffset, int yoffset) {
	_DrawImage(pDest, pSrc, (pDest->_nWidth/2)-(pSrc->_nWidth/2)+xoffset, (pDest->_nHeight/2)-(pSrc->_nHeight/2)+yoffset);
}

void _DrawImageCentered(IMAGEINFO *pDest, IMAGEINFO *pSrc) {
	_DrawImageCentered(pDest, pSrc, 0, 0);
}