// CORE.Collision.h
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
//#ifndef _CORE_COLLISION_H
//#define _CORE_COLLISION_H

typedef void (*COLLISION_CALLBACK)(void *src, void *dest);

struct COLLIDER
{
	COLLIDER() {}
	COLLIDER(int x, int y, int w, int h, COLLISION_CALLBACK callback) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->callback = callback;
		this->reference = NULL;
	}
	int x, y;
	int w, h;
	COLLISION_CALLBACK callback;
	void *reference;
};

void _ClearAllColliders();

void _BeginDrawColliders();

void _RegisterCollider(COLLIDER *pCollider, int option);
void _RegisterCollider(int x, int y, int w, int h, COLLISION_CALLBACK callback, int option);

void _EndDrawColliders();

void _CollideMotionVector(void *source_reference, int x, int y, int w, int h, int &vx, int &vy, COLLISION_CALLBACK callback);

//#endif