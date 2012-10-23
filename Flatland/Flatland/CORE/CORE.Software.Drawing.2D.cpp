// CORE.Drawing.2D.cpp
/////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

float g_fGlobalAlpha = 1.0;

int _CreateColor(int a, int r, int g, int b) {
	int c = (a << 24) + (r << 16) + (g << 8) + (b);
	return c;
}

void _SetGlobalAlpha(float alpha) {
	if(alpha < 0.0) alpha = 0.0;
	if(alpha > 1.0) alpha = 1.0;
	g_fGlobalAlpha = alpha;
}

float _GetGlobalAlpha() {
	return g_fGlobalAlpha;
}


int _GetAlpha(unsigned int color) {
	return color >> 24;
}

int _GetRed(unsigned int color) {
	return (color << 8) >> 24;
}

int _GetGreen(unsigned int color) {
	return (color << 16) >> 24;
}

int _GetBlue(unsigned int color) {
	return (color << 24) >> 24;
}

void _PutPixel(int *video, int nWidth, int nHeight, int x, int y, int color)
{
	if(x < 0 || y < 0) return;
	if(x >= nWidth || y >= nHeight) return;

	int index = y * nWidth + x;
	video[index] = color;
}

void _ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b) {
	a = pixel >> 24;
	r = (pixel << 8) >> 24;
	g = (pixel << 16) >> 24;
	b = (pixel << 24) >> 24;
}

int _BlendColor(int dest, int src, float fGlobalAlpha) {

	unsigned int a1, r1, g1, b1;
	_ExtractColor((unsigned int)src, a1, r1, g1, b1);

	unsigned int a2, r2, g2, b2;
	_ExtractColor((unsigned int)dest, a2, r2, g2, b2);

	unsigned int a3, r3, g3, b3;
	a3 = a1;
	float pixel_alpha = (float)a3 / 255.0;
	fGlobalAlpha *= pixel_alpha;

	r3 = r2 + (unsigned int)(fGlobalAlpha * ((int)r1 - (int)r2));
	g3 = g2 + (unsigned int)(fGlobalAlpha * ((int)g1 - (int)g2));
	b3 = b2 + (unsigned int)(fGlobalAlpha * ((int)b1 - (int)b2));

	// Need to use the destination alpha at this point
	return _CreateColor(a2, r3, g3, b3);
}

void _PutAlphaPixel(int *video, int nWidth, int nHeight, int x, int y, int color)
{
	if(x < 0 || y < 0) return;
	if(x >= nWidth || y >= nHeight) return;

	int index = y * nWidth + x;
	int screen_color = video[index];
	video[index] = _BlendColor(screen_color, color, 1.0);
}

bool _IsColorKey(unsigned int color, unsigned int colorKey) {
	// A color key is a specific color (such as white) that we use
	// to indicate full transparency in situations where we want
	// a faster image blitting that doesn't use alpha blending.

	// Set the alpha maximum
	color = color | 0xFF000000;
	colorKey = colorKey | 0xFF000000;

	// Is the color white with zero alpha?
	if(color == colorKey) {
		return true;
	}
	return false;
}

void _DrawBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight) {
	for(int y = 0; y < nImageHeight; y++) {
		for(int x = 0; x < nImageWidth; x++) {
			int color = image[y * nImageWidth + x];
			if(!_IsColorKey(color, 0xFFFFFFFF)) {
				_PutPixel(video, nWidth, nHeight, x + x1, y + y1, color);
			}
		}
	}
}

void _DrawBitmapOffset(int *video, int nWidth, int nHeight, int x1, int y1, int x2, int y2, int *image, int xOffset, int yOffset, int nImageWidth, int nImageHeight)
{
	for(int y = 0; y < y2; y++) {
		for(int x = 0; x < x2; x++) {
			int color = image[(y+ yOffset) * nImageWidth + x + xOffset];
			_PutPixel(video, nWidth, nHeight, x + x1, y + y1, color);
		}
	}
}

void _DrawBitmapCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight) {

	int x1 = nCellWidth * nCellColumn;
	int y1 = nCellHeight * nCellRow;
	int x2 = x1 + nCellWidth;
	int y2 = y1 + nCellHeight;

	for(int y = y1; y < y2; y++) {
		for(int x = x1; x < x2; x++) {
			int color = image[y * nImageWidth + x];
			if(!_IsColorKey(color, 0xFFFFFFFF)) {
				_PutPixel(video, nWidth, nHeight, (x - x1) + xDest, (y - y1) + yDest, color);
			}
		}
	}
}

void _DrawAlphaBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight) {
	for(int y = 0; y < nImageHeight; y++) {
		for(int x = 0; x < nImageWidth; x++) {
			int color = image[y * nImageWidth + x];
			_PutAlphaPixel(video, nWidth, nHeight, x + x1, y + y1, color);
		}
	}
}

void _DrawAlphaBitmapFlipped(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight) {
	int n = 0;
	for(int y = 0; y < nImageHeight; y++) {
		for(int x = nImageWidth -1 ; x >= 0; x--) {
			int color = image[y * nImageWidth + x];
			_PutAlphaPixel(video, nWidth, nHeight, n + x1, y + y1, color);
			n++;
		}
	}
}

void _DrawAlphaCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight) {

	int x1 = nCellWidth * nCellColumn;
	int y1 = nCellHeight * nCellRow;
	int x2 = x1 + nCellWidth;
	int y2 = y1 + nCellHeight;

	for(int y = y1; y < y2; y++) {
		for(int x = x1; x < x2; x++) {
			int color = image[y * nImageWidth + x];
			if(!_IsColorKey(color, 0xFFFFFFFF)) {
				_PutAlphaPixel(video, nWidth, nHeight, (x - x1) + xDest, (y - y1) + yDest, color);
			}
		}
	}
}

void _DrawAlphaCellFlipped(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight) {

	int x1 = nCellWidth * nCellColumn;
	int y1 = nCellHeight * nCellRow;
	int x2 = x1 + nCellWidth;
	int y2 = y1 + nCellHeight;

	for(int y = y1; y < y2; y++) {
		for(int x = x1; x < x2; x++) {
			int color = image[y * nImageWidth + (x2 + x1 - x)];
			if(!_IsColorKey(color, 0xFFFFFFFF)) {
				_PutAlphaPixel(video, nWidth, nHeight, (x - x1) + xDest, (y - y1) + yDest, color);
			}
		}
	}
}

void _ClearScreen(IMAGEINFO *pImg, int color) {
	_ClearScreen(pImg->_video, pImg->_nActualWidth, pImg->_nHeight, color);
}

void _ClearScreen(int *video, int w, int h, int color) {
	for(int x = 0; x < w; x++) {
		for(int y = 0; y < h; y++) {
			video[y*w+x] = color;
		}
	}
}


void _DrawCircle(IMAGEINFO *pImg, int cx, int cy, int r, int color) {
	_DrawCircle(pImg->_video, pImg->_nActualWidth, pImg->_nHeight, cx, cy, r, color);
}

void _DrawCircle(int *video, int w, int h, int cx, int cy, int r, int color) {
	for(int y2 = cy-r; y2 < cy+r; y2++) {
		for(int x2 = cx-r; x2 < cx+r; x2++) {
			int index = y2*w+x2;
			int dist2 = (x2-cx)*(x2-cx)+(y2-cy)*(y2-cy);
			if(r*r >= dist2) {
				if(index < 0) continue;
				if(index >= w*h) continue;
				video[index] = color;
			}
		}
	}
}

void _DrawBox(int *video, int nWidth, int nHeight, int x1, int y1, int x2, int y2, int color)
{
	for(int dy=y1; dy<y2; dy++) {
		for(int dx=x1; dx<x2; dx++) {
			_PutPixel(video, nWidth, nHeight, dx, dy, color);
		}
	}
}

