// CORE.Software.Drawing.2D.h
///////////////////////////////////////////////////////////////////////////

//#pragma once
#ifndef __CORE_SOFTWARE_DRAWING_2D_
#define __CORE_SOFTWARE_DRAWING_2D_

int _CreateColor(int a, int r, int g, int b);

void _SetGlobalAlpha(float alpha);
float _GetGlobalAlpha();

int _GetAlpha(unsigned int color);
int _GetRed(unsigned int color);
int _GetGreen(unsigned int color);
int _GetBlue(unsigned int color);
void _ExtractColor(unsigned int pixel, unsigned int &a, unsigned int &r, unsigned int &g, unsigned int &b);

void _PutPixel(int *video, int nWidth, int nHeight, int x, int y, int color);
int _BlendColor(int dest, int src, float fGlobalAlpha);

void _PutAlphaPixel(int *video, int nWidth, int nHeight, int x, int y, int color);

void _DrawBox(int *video, int nWidth, int nHeight, int x1, int y1, int x2, int y2, int color);

void _DrawBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight);
void _DrawBitmapOffset(int *video, int nWidth, int nHeight, int x1, int y1, int x2, int y2, int *image, int xOffset, int yOffset, int nImageWidth, int nImageHeight);
void _DrawBitmapCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);
void _DrawBitmapCellFlipped(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);
void _DrawAlphaBitmap(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight);
void _DrawAlphaBitmapFlipped(int *video, int nWidth, int nHeight, int x1, int y1, int *image, int nImageWidth, int nImageHeight);
void _DrawAlphaCell(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);
void _DrawAlphaCellFlipped(int *video, int nWidth, int nHeight, int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);


void _DrawCircle(int *video, int w, int h, int cx, int cy, int r, int color);
void _DrawCircle(IMAGEINFO *pImg, int cx, int cy, int r, int color);

void _ClearScreen(IMAGEINFO *pImg, int color);
void _ClearScreen(int *video, int w, int h, int color);

#endif