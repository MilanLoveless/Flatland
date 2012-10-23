// CORE.Collision.cpp
///////////////////////////////////////////////////

#include "../GameCore.h"

bool _DRAW_COLLIDERS = false;

#define MAX_COLLIDERS 100
COLLIDER _colliders[MAX_COLLIDERS];
int _num_colliders = 0;

bool _MergeColliders(COLLIDER &c1, COLLIDER &c2)
{
	//horizontally adjacent
	if(c2.y == c1.y && (c2.y + c2.h) == (c1.y + c1.h))
	{
		if(c2.x == (c1.x + c1.w))
		{
			c1.w += c2.w;
			return true;
		}
		if((c2.x + c2.w) == c1.x)
		{
			c1.x -= c2.w;
			c1.w += c2.w;
			return true;
		}
	}
	//vertically adjacent
	if(c2.x == c1.x && (c2.x + c2.w) == (c1.x + c1.w))
	{
		if(c2.y == (c1.y + c1.h))
		{
			c1.h += c2.h;
			return true;
		}
		if((c2.y + c2.h) == c1.y)
		{
			c1.y -= c2.h;
			c1.h += c2.h;
			return true;
		}
	}
	return false;
}

void _RegisterCollider(COLLIDER *pCollider, int option) {
	if(_DRAW_COLLIDERS == false) return;
	if(option & DWO_COLLIDE_STATIC) {
		// This type of collider doesn't move around, so if it sits next to another
		// one that's the same size, the two can be merged into one collider.
		for(int n = 0; n < _num_colliders; n++) {
			if(_MergeColliders(_colliders[n], *pCollider)) return;
		}
	}
	// Add the collider into the collection
	if(_num_colliders < MAX_COLLIDERS) {
		_colliders[_num_colliders] = *pCollider;
		_num_colliders++;
	}
}

void _RegisterCollider(int x, int y, int w, int h, COLLISION_CALLBACK callback, int option) {
	if(_DRAW_COLLIDERS == false) return;
	COLLIDER collider(x, y, w, h, callback);
	_RegisterCollider(&collider, option);
}

void _ClearAllColliders() {
	_num_colliders = 0;
}

void _BeginDrawColliders() {
	if(_num_colliders == 0) {
		_DRAW_COLLIDERS = true;
	}
}

void _EndDrawColliders() {
	_DRAW_COLLIDERS = false;
}

bool _IsPtInRect(int x, int y, int left, int top, int width, int height) {
	return x >= left && y >= top && x <= (left+width) && y <= (top+height);
}

bool _IsRectCollide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	// Is any point of rect 1 inside rect 2 ?
	if(_IsPtInRect(x1,    y1,    x2, y2, w2, h2)) return true;
	if(_IsPtInRect(x1+w1, y1,    x2, y2, w2, h2)) return true;
	if(_IsPtInRect(x1+w1, y1+h1, x2, y2, w2, h2)) return true;
	if(_IsPtInRect(x1,    y1+h1, x2, y2, w2, h2)) return true;

	// Is any point of rect 2 inside rect 1 ?
	if(_IsPtInRect(x2,    y2,    x1, y1, w1, h1)) return true;
	if(_IsPtInRect(x2+w2, y2,    x1, y1, w1, h1)) return true;
	if(_IsPtInRect(x2+w2, y2+h2, x1, y1, w1, h1)) return true;
	if(_IsPtInRect(x2,    y2+h2, x1, y1, w1, h1)) return true;
	return false;
}

struct INTERSECTION {
	int x, y;
};

bool _DoLineSegmentsIntersectAndWhere(int x1, int y1, int vx1, int vy1, int x2, int y2, int vx2, int vy2, INTERSECTION &intersection) {
	// t = (P2 - P1) x V2 / (V1 x V2)
	// a x b = ax*by - ay*bx
	int p2_minus_p1_x = x2 - x1; // -1
	int p2_minus_p1_y = y2 - y1; // -64
	int p2_minus_p1_cross_v2 = p2_minus_p1_x * vy2 - p2_minus_p1_y * vx2; // 8512
	int v1_cross_v2 = vx1 * vy2 - vy1 * vx2; // -640

	// Segments are parallel
	if(v1_cross_v2 == 0) return false;

	float t = p2_minus_p1_cross_v2 / (float)v1_cross_v2;

	// Intersection is outside of our segment's bounds
	if(t < 0.0 || t > 1.0) return false;

	intersection.x = x1 + t * vx1;
	intersection.y = y1 + t * vy1;

	// Intersection is outside of other segment's bounds
	if(intersection.x < x2 || intersection.x > x2+vx2) return false;
	if(intersection.y < y2 || intersection.y > y2+vy2) return false;

	return true;
}

bool _CollideRectangles(int x1, int y1, int w1, int h1, int& vx, int& vy, int x2, int y2, int w2, int h2) {
	INTERSECTION intersection;
	bool b = false;
	if(vy > 0) {
		// If we're moving down...
		// Clip feet with the top of the box...
		if(_DoLineSegmentsIntersectAndWhere(x1, y1+h1, vx, vy, x2, y2, w2, 0, intersection)) {
			if(intersection.x != x2+w2) {
				vx = intersection.x - x1;
				vy = intersection.y - (y1+h1);
				b = true;
			}
		}
		if(_DoLineSegmentsIntersectAndWhere(x1+w1/2, y1+h1, vx, vy, x2, y2, w2, 0, intersection)) {
				vx = intersection.x - (x1+w1/2);
				vy = intersection.y - (y1+h1);
				b = true;
		}
		if(_DoLineSegmentsIntersectAndWhere(x1+w1, y1+h1, vx, vy, x2, y2, w2, 0, intersection)) {
			if(intersection.x != x2) {
				vx = intersection.x - (x1+w1);
				vy = intersection.y - (y1+h1);
				b = true;
			}
		}
	} else if(vy < 0) {
		// If we're moving up...
		// Clip head with the bottom of the box...
		if(_DoLineSegmentsIntersectAndWhere(x1, y1, vx, vy, x2, y2+h2, w2, 0, intersection)) {
			if(intersection.x != x2+w2) {
				vx = intersection.x - x1;
				vy = intersection.y - y1;
				b = true;
			}
		}
		if(_DoLineSegmentsIntersectAndWhere(x1+w1/2, y1, vx, vy, x2, y2+h2, w2, 0, intersection)) {
			vx = intersection.x - (x1+w1/2);
			vy = intersection.y - y1;
			b = true;
		}
		if(_DoLineSegmentsIntersectAndWhere(x1+w1, y1, vx, vy, x2, y2+h2, w2, 0, intersection)) {
			if(intersection.x != x2) {
				vx = intersection.x - (x1+w1);
				vy = intersection.y - y1;
				b = true;
			}
		}
	}
	if(vx > 0) {
		// If we're moving right...
		// Clip right side with the left of the box...
		if(_DoLineSegmentsIntersectAndWhere(x1+w1, y1, vx, vy, x2, y2, 0, h2, intersection)) {
			if(intersection.y != y2+h2) {
				vx = intersection.x - (x1+w1);
				vy = intersection.y - y1;
				b = true;
			}
		}
		if(_DoLineSegmentsIntersectAndWhere(x1+w1, y1+h1/2, vx, vy, x2, y2, 0, h2, intersection)) {
			vx = intersection.x - (x1+w1);
			vy = intersection.y - (y1+h1/2);
			b = true;
		}
		if(_DoLineSegmentsIntersectAndWhere(x1+w1, y1+h1, vx, vy, x2, y2, 0, h2, intersection)) {
			if(intersection.y != y2) {
				vx = intersection.x - (x1+w1);
				vy = intersection.y - (y1+h1);
				b = true;
			}
		}
	} else if(vx < 0) {
		// If we're moving left...
		// Clip left side with the right of the box...
		if(_DoLineSegmentsIntersectAndWhere(x1, y1, vx, vy, x2+w2, y2, 0, h2, intersection)) {
			if(intersection.y != y2+h2) {
				vx = intersection.x - x1;
				vy = intersection.y - y1;
				b = true;
			}
		}
		if(_DoLineSegmentsIntersectAndWhere(x1, y1+h1/2, vx, vy, x2+w2, y2, 0, h2, intersection)) {
			vx = intersection.x - x1;
			vy = intersection.y - (y1+h1/2);
			b = true;
		}
		if(_DoLineSegmentsIntersectAndWhere(x1, y1+h1, vx, vy, x2+w2, y2, 0, h2, intersection)) {
			if(intersection.y != y2) {
				vx = intersection.x - x1;
				vy = intersection.y - (y1+h1);
				b = true;
			}
		}
	}
	return b;
}

void _CollideMotionVector(void *source_reference, int x, int y, int w, int h, int &vx, int &vy, COLLISION_CALLBACK callback) {
	for(int n = 0; n < _num_colliders; n++) {
		COLLIDER &collider = _colliders[n];

		if(collider.x < _VIEW_X || collider.x > _VIEW_X + _VIEW_WIDTH) continue;
		if(collider.y < _VIEW_Y || collider.y > _VIEW_Y + _VIEW_HEIGHT) continue;

		if(_IsRectCollide(x+vx, y+vy, w, h, collider.x, collider.y, collider.w, collider.h)) {

			if(_CollideRectangles(x, y, w, h, vx, vy, collider.x, collider.y, collider.w, collider.h)) {

				// Notify user
				if(callback != NULL) {
					callback(source_reference, collider.reference);
				}

				// Notify entity
				if(collider.callback != NULL) {
					collider.callback(source_reference, collider.reference);
				}

			}
		}
	}
}