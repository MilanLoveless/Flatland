class Vector2
{
public:
	int x, y;
	Vector2() { x =0; y = 0; };
	Vector2(int x, int y) { this->x = x; this->y = y; };
};


class Rect
{
public:
	Rect(int x, int y, int width, int height);
	Rect();
	~Rect(void);
	int x,y,w,h;
	bool Intersects(Rect r);
	Vector2 IntersectionDepth(Rect r);
	bool Contains(int x, int y);
};
