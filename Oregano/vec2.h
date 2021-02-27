#pragma once

class Vec2 {
public:
	int x;
	int y;
	double dx;
	double dy;

	Vec2(int x = 0, int y = 0, double dx = 0, double dy = 0);
	Vec2 operator +(const Vec2& other) const;
	Vec2 operator -(const Vec2& other) const;
	Vec2 operator *(const Vec2& other) const;
	Vec2 operator /(const Vec2& other) const;

	friend Vec2 operator +(const int& a, Vec2& other);
	friend Vec2 operator +(const double& a, Vec2& other);
	friend Vec2 operator -(Vec2& other, const double& a);
	friend Vec2 operator *(const double& a, Vec2& other);
	friend Vec2 operator /(const double& a, Vec2& other);
};
