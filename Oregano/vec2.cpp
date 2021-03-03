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

//dVec2 dVec2::operator*=(const double& a) {
//	Vec2 v;
//	return v;
//}


//------------------------------------------------//

dVec2::dVec2(double dx, double dy) : dx(dx), dy(dy) {
}

dVec2 dVec2::operator+(const dVec2& other) const {
	dVec2 v;
	v.dx = this->dx + other.dx;
	v.dy = this->dy + other.dy;
	return v;
}

dVec2 dVec2::operator-(const dVec2& other) const {
	dVec2 v;
	v.dx = this->dx - other.dx;
	v.dy = this->dy - other.dy;
	return v;
}

dVec2 dVec2::operator*(const dVec2& other) const {
	dVec2 v;
	v.dx = this->dx * other.dx;
	v.dy = this->dy * other.dy;
	return v;
}

dVec2 dVec2::operator/(const dVec2& other) const {
	dVec2 v;
	v.dx = this->dx / other.dx;
	v.dy = this->dy / other.dy;
	return v;
}

dVec2& dVec2::operator=(const dVec2& other) {
	dx = other.dx;
	dy = other.dy;
	return *this;
}

dVec2& dVec2::operator+=(const dVec2& other) {
	dx += other.dx;
	dy += other.dy;
	return *this;
}

dVec2& dVec2::operator-=(const dVec2& other) {
	dx -= other.dx;
	dy -= other.dy;
	return *this;
}

dVec2 operator+(const double& a, dVec2& other) {
	dVec2 v;
	v.dx = a + other.dx;
	v.dy = a + other.dy;
	return v;
}

dVec2 operator-(dVec2& other, const double& a) {
	dVec2 v;
	v.dx = other.dx - a;
	v.dy = other.dy - a;
	return v;
}

dVec2 operator*(const double& a, dVec2& other) {
	dVec2 v;
	v.dx = a * other.dx;
	v.dy = a * other.dy;
	return v;
}

dVec2 operator/(const double& a, dVec2& other) {
	dVec2 v;
	v.dx = a / other.dx;
	v.dy = a / other.dy;
	return v;
}
