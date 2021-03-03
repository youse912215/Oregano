#include "vec2.h"

Vec2::Vec2(int x, int y) : x(x), y(y) {
}

Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 v;
	v.x = this->x + other.x;
	v.y = this->y + other.y;
	return v;
}

Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 v;
	v.x = this->x - other.x;
	v.y = this->y - other.y;
	return v;
}

Vec2 Vec2::operator*(const Vec2& other) const {
	Vec2 v;
	v.x = this->x * other.x;
	v.y = this->y * other.y;
	return v;
}

Vec2 Vec2::operator/(const Vec2& other) const {
	Vec2 v;
	v.x = this->x / other.x;
	v.y = this->y / other.y;
	return v;
}

Vec2& Vec2::operator=(const Vec2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

Vec2& Vec2::operator+=(const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2 operator+(const int& a, Vec2& other) {
	Vec2 v;
	v.x = a + other.x;
	v.y = a + other.y;
	return v;
}

//Vec2d Vec2d::operator*=(const double& a) {
//	Vec2 v;
//	return v;
//}


//------------------------------------------------//

Vec2d::Vec2d(double dx, double dy) : dx(dx), dy(dy) {
}

Vec2d Vec2d::operator+(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx + other.dx;
	v.dy = this->dy + other.dy;
	return v;
}

Vec2d Vec2d::operator-(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx - other.dx;
	v.dy = this->dy - other.dy;
	return v;
}

Vec2d Vec2d::operator*(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx * other.dx;
	v.dy = this->dy * other.dy;
	return v;
}

Vec2d Vec2d::operator/(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx / other.dx;
	v.dy = this->dy / other.dy;
	return v;
}

Vec2d& Vec2d::operator=(const Vec2d& other) {
	dx = other.dx;
	dy = other.dy;
	return *this;
}

Vec2d& Vec2d::operator+=(const Vec2d& other) {
	dx += other.dx;
	dy += other.dy;
	return *this;
}

Vec2d& Vec2d::operator-=(const Vec2d& other) {
	dx -= other.dx;
	dy -= other.dy;
	return *this;
}

Vec2d operator+(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a + other.dx;
	v.dy = a + other.dy;
	return v;
}

Vec2d operator-(Vec2d& other, const double& a) {
	Vec2d v;
	v.dx = other.dx - a;
	v.dy = other.dy - a;
	return v;
}

Vec2d operator*(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a * other.dx;
	v.dy = a * other.dy;
	return v;
}

Vec2d operator/(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a / other.dx;
	v.dy = a / other.dy;
	return v;
}
