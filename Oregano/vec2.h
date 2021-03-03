#pragma once

class Vec2 {
public:
	int x;
	int y;

	Vec2(int x = 0, int y = 0);

	Vec2 operator +(const Vec2& other) const;
	Vec2 operator -(const Vec2& other) const;
	Vec2 operator *(const Vec2& other) const;
	Vec2 operator /(const Vec2& other) const;
	Vec2& operator =(const Vec2& other);
	Vec2& operator +=(const Vec2& other);
	Vec2& operator -=(const Vec2& other);


	friend Vec2 operator +(const int& a, Vec2& other);


	Vec2 operator()(const double& dx, const double& dy);
};

class dVec2 {
public:
	double dx;
	double dy;

	dVec2(double dx = 0, double dy = 0);

	dVec2 operator +(const dVec2& other) const;
	dVec2 operator -(const dVec2& other) const;
	dVec2 operator *(const dVec2& other) const;
	dVec2 operator /(const dVec2& other) const;
	dVec2& operator =(const dVec2& other);
	dVec2& operator +=(const dVec2& other);
	dVec2& operator -=(const dVec2& other);

	//dVec2 operator *=(const double& a);

	friend dVec2 operator +(const double& a, dVec2& other);
	friend dVec2 operator -(dVec2& other, const double& a);
	friend dVec2 operator *(const double& a, dVec2& other);
	friend dVec2 operator /(const double& a, dVec2& other);
};
