#pragma once

void DrawBitmap(int x1, int y1, int *image, int nImageWidth, int nImageHeight);
void DrawBitmapCell(int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);
void DrawAlphaBitmap(int x1, int y1, int *image, int nImageWidth, int nImageHeight);
void DrawAlphaBitmapFlipped(int x1, int y1, int *image, int nImageWidth, int nImageHeight);
void DrawAlphaCell(int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);
void DrawAlphaCellFlipped(int xDest, int yDest, int *image, int nCellColumn, int nCellRow, int nCellWidth, int nCellHeight, int nImageWidth, int nImageHeight);
