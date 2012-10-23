#include <list>
#include "Projectile.h"
#include <math.h>


Projectile::Projectile(void)
{
	velX = 0;
	velY = -8;
	upperOffX = 0;
	upperOffY = 0;
	birth = time(NULL);
	deathtime = birth;
}

Projectile::~Projectile(void)
{
}

int Projectile::getX()
{
	return rect.x;
}

int Projectile::getY()
{
	return rect.y;
}

int Projectile::getWidth()
{
	return rect.w;
}

int Projectile::getHeight()
{
	return rect.h;
}

Rect Projectile::BoundingBox()
{
	return rect;
}

void Projectile::Draw(int upperX, int upperY)
{
}

void Projectile::Update()
{
}

void Projectile::Move()
{
	velX = acceleration*10;
	rect.x += velX;
	if(rect.x < 0)
	{
		rect.x = 0;
	}
	else if(rect.x + rect.w > LEVEL_LENGTH - 7)
	{
		rect.x = LEVEL_LENGTH - rect.w - 7;
	}
	
	//Handle Y movement

	velY += GRAVITY;
	if(velY > 16)
		velY = 16;
	rect.y += velY;
	if(rect.y + rect.h > LEVEL_HEIGHT - 28)
	{
		rect.y = LEVEL_HEIGHT - rect.h - 28;
		velY = 0;
	}
	else if(rect.y < 0)
	{
		rect.y = 0;
		velY = 0;
	}
}

void Projectile::handleGeo(list<auto_ptr<Rect>> &geo)
{
	Rect bb = BoundingBox();
	for(auto i = geo.begin(); i != geo.end(); i++)
	{
		if((*i)->Intersects(rect))
		{
			bool upperLeft = (*i)->Contains(bb.x,bb.y);
			bool lowerLeft = (*i)->Contains(bb.x,bb.y + bb.h);
			bool upperRight = (*i)->Contains(bb.x + bb.w, bb.y);
			bool lowerRight = (*i)->Contains(bb.x + bb.w, bb.y + bb.h);

			if(upperLeft && upperRight)
			{
				rect.y = (*i)->y + (*i)->h + upperOffY;
				velY = 0;
			}
			else if(upperLeft && lowerLeft)
			{
				rect.x = (*i)->x + (*i)->w - upperOffX;
			}
			else if(lowerLeft && lowerRight)
			{
				rect.y = (*i)->y - rect.h + upperOffY;
				velY = 0;
			}
			else if(lowerRight && upperRight)
			{
				rect.x = (*i)->x - rect.w + upperOffX;
			}
			else if(upperLeft)
			{
				int xdiff = (*i)->x + (*i)->w - bb.x;
				int ydiff = (*i)->y + (*i)->h - bb.y;
				if(xdiff > ydiff)
				{
					rect.y = (*i)->y + (*i)->h + upperOffY;
					//velY = 0;
				}
				else
				{
					rect.x = (*i)->x + (*i)->w  - upperOffX;
				}
			}
			else if(upperRight)
			{
				int xdiff = bb.x + bb.w - (*i)->x;
				int ydiff = (*i)->y + (*i)->h - bb.y;
				if(xdiff > ydiff)
				{
					rect.y = (*i)->y + (*i)->h - upperOffY;
					velY = 0;
				}
				else
				{
					rect.x = (*i)->x - rect.w + upperOffX;
				}
			}
			else if(lowerRight)
			{
				int xdiff = (bb.x + bb.w) - (*i)->x;
				int ydiff = (bb.y + bb.h) - (*i)->y;
				if(xdiff > ydiff)
				{
					rect.y = (*i)->y - rect.h + upperOffY;
					velY = 0;
				}
				else
					rect.x = (*i)->x - rect.w + upperOffX;
			}
			else if(lowerLeft)
			{
				int xdiff = (*i)->x + (*i)->w - bb.x;
				int ydiff = (bb.y + bb.h) - (*i)->y;
				if(xdiff > ydiff)
				{
					rect.y = (*i)->y - rect.h + upperOffY;
					velY = 0;
				}
				else
					rect.x = (*i)->x + (*i)->w  - upperOffX;
			}
			else if(bb.y < (*i)->y && (*i)->y < bb.y + bb.h)
			{
				if(bb.x < ((*i)->x + (*i)->w) && (bb.x + bb.w) > ((*i)->x + (*i)->w))
				{
					rect.x = (*i)->x + (*i)->w - upperOffX;
				}
				else if(bb.x < (*i)->x && (bb.x + bb.w) > (*i)->x)
				{
					rect.x = (*i)->x - rect.w + upperOffX;
				}
			}
		}
	}
}
