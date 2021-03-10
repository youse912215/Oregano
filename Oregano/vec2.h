#pragma once

/// <summary>
/// int型のベクタークラス
/// </summary>
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
};

/// <summary>
/// double型のベクタークラス
/// </summary>
class Vec2d {
public:
	double dx;
	double dy;

	Vec2d(double dx = 0, double dy = 0);

	Vec2d operator +(const Vec2d& other) const;
	Vec2d operator -(const Vec2d& other) const;
	Vec2d operator *(const Vec2d& other) const;
	Vec2d operator /(const Vec2d& other) const;
	Vec2d& operator =(const Vec2d& other);
	Vec2d& operator +=(const Vec2d& other);
	Vec2d& operator -=(const Vec2d& other);

	friend Vec2d operator +(const double& a, Vec2d& other);
	friend Vec2d operator -(Vec2d& other, const double& a);
	friend Vec2d operator *(const double& a, Vec2d& other);
	friend Vec2d operator /(const double& a, Vec2d& other);
};
