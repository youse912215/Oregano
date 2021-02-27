#include "vec2.h"

Vec2::Vec2(int x, int y, double dx, double dy) :
	x(x), y(y), dx(dx), dy(dy) {
}

Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 v;
	v.x = this->x + other.x;
	v.y = this->y + other.y;
	v.dx = this->dx + other.dx;
	v.dy = this->dy + other.dy;
	return v;
}

Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 v;
	v.x = this->x - other.x;
	v.y = this->y - other.y;
	v.dx = this->dx - other.dx;
	v.dy = this->dy - other.dy;
	return v;
}

Vec2 Vec2::operator*(const Vec2& other) const {
	Vec2 v;
	v.x = this->x * other.x;
	v.y = this->y * other.y;
	v.dx = this->dx * other.dx;
	v.dy = this->dy * other.dy;
	return v;
}

Vec2 Vec2::operator/(const Vec2& other) const {
	Vec2 v;
	v.x = this->x / other.x;
	v.y = this->y / other.y;
	v.dx = this->dx / other.dx;
	v.dy = this->dy / other.dy;
	return v;
}

Vec2 operator+(const int& a, Vec2& other) {
	Vec2 v;
	v.x = a + other.x;
	v.y = a + other.y;
	return v;
}

Vec2 operator+(const double& a, Vec2& other) {
	Vec2 v;
	v.dx = a + other.dx;
	v.dy = a + other.dy;
	return v;
}

Vec2 operator-(Vec2& other, const double& a) {
	Vec2 v;
	v.dx = other.dx - a;
	v.dy = other.dy - a;
	return v;
}

Vec2 operator*(const double& a, Vec2& other) {
	Vec2 v;
	v.dx = a * other.dx;
	v.dy = a * other.dy;
	return v;
}

Vec2 operator/(const double& a, Vec2& other) {
	Vec2 v;
	v.dx = a / other.dx;
	v.dy = a / other.dy;
	return v;
}
