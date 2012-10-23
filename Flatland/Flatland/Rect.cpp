#include "Rect.h"
#include <math.h>

using namespace std;

Rect::Rect(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
}

Rect::Rect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::~Rect(void)
{
}

bool Rect::Contains(int x1, int y1)
{
	if(x1 < x || x1 > (x + w))
		return false;
	if(y1 < y || y1 > (y + h))
		return false;
	return true;
}

bool Rect::Intersects(Rect r)
{
	return (x < (r.x+r.w)) && ((x + w) > r.x) && (y < (r.y + r.h)) && ((y + h) > r.y);
}

Vector2 Rect::IntersectionDepth(Rect r)
{
	Vector2 retVector;
	int halfWidth = w/2;
	int halfHeight = h/2;
	int halfWidthR = r.w/2;
	int halfHeightR = r.h/2;

	Vector2 centerA(x + halfWidth,y + halfHeight);
	Vector2 centerB(r.x + halfWidthR, r.y + halfHeightR);

	int distX = centerA.x - centerB.x;
	int distY = centerA.y - centerB.y;
	int minDistX = halfWidth + halfWidthR;
	int minDistY = halfHeight + halfHeightR;

	if(abs(distX) >= minDistX || abs(distY) >= minDistY)
	{
		return retVector;
	}
	retVector.x = distX > 0 ? minDistX - distX : -minDistX - distX;
	retVector.y = distY > 0 ? minDistY - distY : -minDistY - distY;
	return retVector;
}