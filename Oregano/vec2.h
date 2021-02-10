#pragma once

class Vec2 {
public:
	int x;
	int y;

	Vec2(int x = 0, int y = 0);
	Vec2 operator +(const Vec2& other) const;
	friend Vec2 operator +(const int& a, Vec2& other);
};
