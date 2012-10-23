// CORE.Hardware.3D.Texture.cpp
/////////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

IDirect3DTexture9 *_CreateTexture(int nWidth, int nHeight) {
	IDirect3DTexture9 *pTexture;

	HRESULT hResult = D3DXCreateTexture(
		g_pD3DDevice, nWidth, nHeight, 1, 0, 
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pTexture
	);
	if(FAILED(hResult))
	{
		VERIFY(hResult);
		return NULL;
	}

	return pTexture;
}

IDirect3DTexture9 *_LoadTexture(char *strFileName, int nWidth, int nHeight)
{
    IDirect3DTexture9 *pTexture;
    D3DXIMAGE_INFO srcInfo;
	D3DCOLOR colorkey = 0x00000000;
    if (FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, strFileName, nWidth, nHeight, 1, 0, 
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 
		colorkey, &srcInfo, NULL, &pTexture)))
    {
        return NULL;
    }

    return pTexture;
}

TEXTUREINFO* _CreateTexture(int nID, int nWidth, int nHeight) {

	TEXTUREINFO *pImageInfo = new TEXTUREINFO;
	if(pImageInfo == NULL) return NULL;

	pImageInfo->_pSurface = _CreateTexture(nWidth, nHeight);
	if(pImageInfo->_pSurface == NULL) {
		delete pImageInfo;
		return NULL;
	}

	pImageInfo->_nID = nID;
	pImageInfo->_pFileName = "untitled.dat"; 
	pImageInfo->_pSurface->GetLevelDesc(0, &pImageInfo->_SurfaceDesc);
    pImageInfo->_nWidth = pImageInfo->_SurfaceDesc.Width;
	pImageInfo->_nActualWidth = 0;
	pImageInfo->_video = NULL;
    pImageInfo->_nHeight = pImageInfo->_SurfaceDesc.Height;
	pImageInfo->_Rect.top = 0;
	pImageInfo->_Rect.left = 0;
	pImageInfo->_Rect.right = pImageInfo->_nWidth;
	pImageInfo->_Rect.bottom = pImageInfo->_nHeight;

	return pImageInfo;
}

TEXTUREINFO* _LoadTexture(int nID, char *strFilename, int nWidth, int nHeight) {

	TEXTUREINFO *pImageInfo = new TEXTUREINFO;
	if(pImageInfo == NULL) return NULL;

	pImageInfo->_pSurface = _LoadTexture(strFilename, nWidth, nHeight);
	if(pImageInfo->_pSurface == NULL) {
		delete pImageInfo;
		return NULL;
	}

	pImageInfo->_nID = nID;
	pImageInfo->_pFileName = strFilename; 
	pImageInfo->_pSurface->GetLevelDesc(0, &pImageInfo->_SurfaceDesc);
    pImageInfo->_nWidth = pImageInfo->_SurfaceDesc.Width;
	pImageInfo->_nActualWidth = 0;
	pImageInfo->_video = NULL;
    pImageInfo->_nHeight = pImageInfo->_SurfaceDesc.Height;
	pImageInfo->_Rect.top = 0;
	pImageInfo->_Rect.left = 0;
	pImageInfo->_Rect.right = pImageInfo->_nWidth;
	pImageInfo->_Rect.bottom = pImageInfo->_nHeight;

	return pImageInfo;
}

void _UnloadTexture(TEXTUREINFO **ppInfo) {
	if(ppInfo == NULL) return;
	if(*ppInfo == NULL) return;
	if((*ppInfo)->_pSurface != NULL) {
		(*ppInfo)->_pSurface->Release();
	}
	delete *ppInfo;
	*ppInfo = NULL;
}

bool _LockTexture(TEXTUREINFO *pImage) {
	D3DLOCKED_RECT lock;
	if(pImage == NULL) {
		// Your texture was not loaded properly. Check the file name.
		return false;
	}
	HRESULT hResult = pImage->_pSurface->LockRect(0, &lock, &pImage->_Rect, D3DLOCK_NOSYSLOCK);
	if(!FAILED(hResult)) {
		pImage->_video = (int*)lock.pBits;
		pImage->_nActualWidth = ((unsigned int)lock.Pitch) >> 2;
	} else {
		// The texture could not be locked, possibly because it was already locked.
		VERIFY(hResult);
		pImage->_video = NULL;
		return false;
	}
	return true;
}

void _UnlockTexture(TEXTUREINFO *pImage) {
	pImage->_pSurface->UnlockRect(0);
	pImage->_video = NULL;
	pImage->_nActualWidth = 0;
}

void _ClearTexture(TEXTUREINFO *pImage, int color) {
	int n = pImage->_nActualWidth * pImage->_nHeight;
	while(--n) {
		pImage->_video[n] = color;
	}
}

void _DrawTextureWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xdest, int ydest, float alpha) {
	float oldAlpha = _GetGlobalAlpha();
	_SetGlobalAlpha(alpha);
	_DrawTextureWithLock(pDest, pSrc, xdest, ydest);
	_SetGlobalAlpha(oldAlpha);
}

void _DrawTextureWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xdest, int ydest) {
	_LockTexture(pSrc);
	_DrawImage(pDest, pSrc, xdest, ydest);
	_UnlockTexture(pSrc);
}

void _DrawTextureFromWin32BitmapInfo(IDirect3DSurface9 *pDest, LPBITMAPINFO pBmp, int w, int h, int xdest, int ydest) {

	if(pDest == NULL) return;
	if(pBmp == NULL) return;

	LPBITMAPINFO pBmpInfo = (LPBITMAPINFO)pBmp;
	LPBITMAPINFOHEADER pBmpInfoHeader = (LPBITMAPINFOHEADER)pBmpInfo;
		
	HDC hdc;
	VERIFY(pDest->GetDC(&hdc));
		
	LPBYTE pBmpBits = ((LPBYTE)pBmpInfo) + pBmpInfo->bmiHeader.biSize;
		
	LPBYTE pGDIBits;
	HBITMAP hBmp = CreateDIBSection(hdc, pBmpInfo, DIB_RGB_COLORS, (LPVOID*)&pGDIBits, NULL, 0);
		
	memcpy(pGDIBits, pBmpBits, pBmpInfoHeader->biSizeImage);
		
	HDC hBmpDC = CreateCompatibleDC(hdc);
		
	HGDIOBJ pOldObj = SelectObject(hBmpDC, hBmp);
	BitBlt(hdc, xdest, ydest, pBmpInfoHeader->biWidth, pBmpInfoHeader->biHeight, hBmpDC, 0, 0, SRCCOPY);
		
	if(pOldObj) SelectObject(hBmpDC, pOldObj);
	DeleteObject(hBmp);
		
	pDest->ReleaseDC(hdc);
}

void _DrawTexture(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xdest, int ydest) {
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

void _DrawTextureCenteredWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xoffset, int yoffset) {
	_LockTexture(pSrc);
	_DrawImageCentered(pDest, pSrc, xoffset, yoffset);
	_UnlockTexture(pSrc);
}

void _DrawTextureCenteredWithLock(TEXTUREINFO *pDest, TEXTUREINFO *pSrc) {
	_LockTexture(pSrc);
	_DrawImageCentered(pDest, pSrc);
	_UnlockTexture(pSrc);
}

void _DrawTextureCentered(TEXTUREINFO *pDest, TEXTUREINFO *pSrc, int xoffset, int yoffset) {
	_DrawTexture(pDest, pSrc, (pDest->_nWidth/2)-(pSrc->_nWidth/2)+xoffset, (pDest->_nHeight/2)-(pSrc->_nHeight/2)+yoffset);
}

void _DrawTextureCentered(TEXTUREINFO *pDest, TEXTUREINFO *pSrc) {
	_DrawTextureCentered(pDest, pSrc, 0, 0);
}