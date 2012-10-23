#include <list>
#include "MobileEntity.h"
#include <math.h>


MobileEntity::MobileEntity(void)
{
	facing = RIGHT;
	movement = STOP;
	jump = false;
	velX = 0;
	velY = 0;
	upperOffX = 0;
	upperOffY = 0;
}

MobileEntity::~MobileEntity(void)
{
}

int MobileEntity::getX()
{
	return rect.x;
}

int MobileEntity::getY()
{
	return rect.y;
}

int MobileEntity::getWidth()
{
	return rect.w;
}

int MobileEntity::getHeight()
{
	return rect.h;
}

Rect MobileEntity::BoundingBox()
{
	return rect;
}

void MobileEntity::Draw(int upperX, int upperY)
{
}

void MobileEntity::Update()
{
}

void MobileEntity::MoveLeft()
{
	movement = LEFT;
	facing = LEFT;
}

void MobileEntity::MoveRight()
{
	movement = RIGHT;
	facing = RIGHT;
}

void MobileEntity::Jump()
{
	if(velY == 0 && !jump)
	{
		jump = true;
		velY = jumpVel;
	}
}

void MobileEntity::StopMovement()
{
	movement = STOP;
}

void MobileEntity::Move()
{
	switch(movement) {
	case RIGHT:
		velX += acceleration;
		if(velX > maxVelX)
			velX = maxVelX;
		break;
	case LEFT:
		velX -= acceleration;
		if(velX < -1 * maxVelX)
			velX = -1 * maxVelX;
		break;
	case STOP:
		if( velX > 0)
		{
			velX -= acceleration;
			if(velX < 0)
				velX = 0;
		}
		else if(velX < 0)
		{
			velX += acceleration;
			if(velX > 0)
				velX = 0;
		}
		break;
	}
	rect.x += velX;
	if(rect.x < 0)
		rect.x = 0;
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
		jump = false;
	}
	else if(rect.y < 0)
	{
		rect.y = 0;
		velY = 0;
		jump = false;
	}
}

void MobileEntity::invertVelX()
{
	velX = -velX;
}

void MobileEntity::handleGeo(list<auto_ptr<Rect>> &geo)
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
				jump = false;
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
					jump = false;
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
					jump = false;
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
