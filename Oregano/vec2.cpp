#include "vec2.h"

/*int型*/

//コンストラクタ
Vec2::Vec2(int x, int y) : x(x), y(y) {
}

//ベクター同士の+演算子
Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 v;
	v.x = this->x + other.x;
	v.y = this->y + other.y;
	return v;
}

//ベクター同士の-演算子
Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 v;
	v.x = this->x - other.x;
	v.y = this->y - other.y;
	return v;
}

//ベクター同士の*演算子
Vec2 Vec2::operator*(const Vec2& other) const {
	Vec2 v;
	v.x = this->x * other.x;
	v.y = this->y * other.y;
	return v;
}

//ベクター同士の/演算子
Vec2 Vec2::operator/(const Vec2& other) const {
	Vec2 v;
	v.x = this->x / other.x;
	v.y = this->y / other.y;
	return v;
}

//ベクター同士の=演算子
Vec2& Vec2::operator=(const Vec2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

//ベクター同士の+=演算子
Vec2& Vec2::operator+=(const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

//ベクター同士の-=演算子
Vec2& Vec2::operator-=(const Vec2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

//ベクターと他の変数との+演算子
Vec2 operator+(const int& a, Vec2& other) {
	Vec2 v;
	v.x = a + other.x;
	v.y = a + other.y;
	return v;
}

//------------------------------------------------//

/* double型 */

//コンストラクタ
Vec2d::Vec2d(double dx, double dy) : dx(dx), dy(dy) {
}

//ベクター同士の+演算子
Vec2d Vec2d::operator+(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx + other.dx;
	v.dy = this->dy + other.dy;
	return v;
}

//ベクター同士の-演算子
Vec2d Vec2d::operator-(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx - other.dx;
	v.dy = this->dy - other.dy;
	return v;
}

//ベクター同士の*演算子
Vec2d Vec2d::operator*(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx * other.dx;
	v.dy = this->dy * other.dy;
	return v;
}

//ベクター同士の/演算子
Vec2d Vec2d::operator/(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx / other.dx;
	v.dy = this->dy / other.dy;
	return v;
}

//ベクター同士の=演算子
Vec2d& Vec2d::operator=(const Vec2d& other) {
	dx = other.dx;
	dy = other.dy;
	return *this;
}

//ベクター同士の+=演算子
Vec2d& Vec2d::operator+=(const Vec2d& other) {
	dx += other.dx;
	dy += other.dy;
	return *this;
}

//ベクター同士の-=演算子
Vec2d& Vec2d::operator-=(const Vec2d& other) {
	dx -= other.dx;
	dy -= other.dy;
	return *this;
}

//ベクターと他の変数との+演算子
Vec2d operator+(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a + other.dx;
	v.dy = a + other.dy;
	return v;
}

//ベクターと他の変数との‐演算子
Vec2d operator-(Vec2d& other, const double& a) {
	Vec2d v;
	v.dx = other.dx - a;
	v.dy = other.dy - a;
	return v;
}

//ベクターと他の変数との*演算子
Vec2d operator*(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a * other.dx;
	v.dy = a * other.dy;
	return v;
}

//ベクターと他の変数との/演算子
Vec2d operator/(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a / other.dx;
	v.dy = a / other.dy;
	return v;
}
