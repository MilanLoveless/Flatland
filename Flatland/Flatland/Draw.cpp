#include "GameCore.h"
#include "Constants.h"

extern TEXTUREINFO *g_pBackBuffer;

void DrawAlphaCell(int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight)
{
	_DrawAlphaCell(g_pBackBuffer->_video, WINDOW_WIDTH, WINDOW_HEIGHT, xDest, yDest, image, nCellColumn, nCellRow, nCellWidth, nCellHeight, nImageWidth, nImageHeight);
}
void DrawAlphaCellFlipped(int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight)
{
	_DrawAlphaCellFlipped(g_pBackBuffer->_video, WINDOW_WIDTH, WINDOW_HEIGHT, xDest, yDest, image, nCellColumn, nCellRow, nCellWidth, nCellHeight, nImageWidth, nImageHeight);
}
void DrawBitmap(int x1, int y1, int *image, int nImageWidth, int nImageHeight)
{
	_DrawBitmap(g_pBackBuffer->_video, WINDOW_WIDTH, WINDOW_HEIGHT, x1, y1, image, nImageWidth, nImageHeight);
}
void DrawBitmapCell(int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight)
{
	_DrawBitmapCell(g_pBackBuffer->_video, WINDOW_WIDTH, WINDOW_HEIGHT, xDest, yDest, image, nCellColumn, nCellRow, nCellWidth, nCellHeight, nImageWidth, nImageHeight);
}
void DrawAlphaBitmap(int x1, int y1, int *image, int nImageWidth, int nImageHeight)
{
	_DrawAlphaBitmap(g_pBackBuffer->_video, WINDOW_WIDTH, WINDOW_HEIGHT, x1, y1, image, nImageWidth, nImageHeight);
}
void DrawAlphaBitmapFlipped(int x1, int y1, int *image, int nImageWidth, int nImageHeight)
{
	_DrawAlphaBitmapFlipped(g_pBackBuffer->_video, WINDOW_WIDTH, WINDOW_HEIGHT, x1, y1, image, nImageWidth, nImageHeight);
}
