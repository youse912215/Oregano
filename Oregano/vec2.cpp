#include "vec2.h"

/*int�^*/

//�R���X�g���N�^
Vec2::Vec2(int x, int y) : x(x), y(y) {
}

//�x�N�^�[���m��+���Z�q
Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 v;
	v.x = this->x + other.x;
	v.y = this->y + other.y;
	return v;
}

//�x�N�^�[���m��-���Z�q
Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 v;
	v.x = this->x - other.x;
	v.y = this->y - other.y;
	return v;
}

//�x�N�^�[���m��*���Z�q
Vec2 Vec2::operator*(const Vec2& other) const {
	Vec2 v;
	v.x = this->x * other.x;
	v.y = this->y * other.y;
	return v;
}

//�x�N�^�[���m��/���Z�q
Vec2 Vec2::operator/(const Vec2& other) const {
	Vec2 v;
	v.x = this->x / other.x;
	v.y = this->y / other.y;
	return v;
}

//�x�N�^�[���m��=���Z�q
Vec2& Vec2::operator=(const Vec2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

//�x�N�^�[���m��+=���Z�q
Vec2& Vec2::operator+=(const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

//�x�N�^�[���m��-=���Z�q
Vec2& Vec2::operator-=(const Vec2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

//�x�N�^�[�Ƒ��̕ϐ��Ƃ�+���Z�q
Vec2 operator+(const int& a, Vec2& other) {
	Vec2 v;
	v.x = a + other.x;
	v.y = a + other.y;
	return v;
}

//------------------------------------------------//

/* double�^ */

//�R���X�g���N�^
Vec2d::Vec2d(double dx, double dy) : dx(dx), dy(dy) {
}

//�x�N�^�[���m��+���Z�q
Vec2d Vec2d::operator+(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx + other.dx;
	v.dy = this->dy + other.dy;
	return v;
}

//�x�N�^�[���m��-���Z�q
Vec2d Vec2d::operator-(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx - other.dx;
	v.dy = this->dy - other.dy;
	return v;
}

//�x�N�^�[���m��*���Z�q
Vec2d Vec2d::operator*(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx * other.dx;
	v.dy = this->dy * other.dy;
	return v;
}

//�x�N�^�[���m��/���Z�q
Vec2d Vec2d::operator/(const Vec2d& other) const {
	Vec2d v;
	v.dx = this->dx / other.dx;
	v.dy = this->dy / other.dy;
	return v;
}

//�x�N�^�[���m��=���Z�q
Vec2d& Vec2d::operator=(const Vec2d& other) {
	dx = other.dx;
	dy = other.dy;
	return *this;
}

//�x�N�^�[���m��+=���Z�q
Vec2d& Vec2d::operator+=(const Vec2d& other) {
	dx += other.dx;
	dy += other.dy;
	return *this;
}

//�x�N�^�[���m��-=���Z�q
Vec2d& Vec2d::operator-=(const Vec2d& other) {
	dx -= other.dx;
	dy -= other.dy;
	return *this;
}

//�x�N�^�[�Ƒ��̕ϐ��Ƃ�+���Z�q
Vec2d operator+(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a + other.dx;
	v.dy = a + other.dy;
	return v;
}

//�x�N�^�[�Ƒ��̕ϐ��Ƃ́]���Z�q
Vec2d operator-(Vec2d& other, const double& a) {
	Vec2d v;
	v.dx = other.dx - a;
	v.dy = other.dy - a;
	return v;
}

//�x�N�^�[�Ƒ��̕ϐ��Ƃ�*���Z�q
Vec2d operator*(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a * other.dx;
	v.dy = a * other.dy;
	return v;
}

//�x�N�^�[�Ƒ��̕ϐ��Ƃ�/���Z�q
Vec2d operator/(const double& a, Vec2d& other) {
	Vec2d v;
	v.dx = a / other.dx;
	v.dy = a / other.dy;
	return v;
}
