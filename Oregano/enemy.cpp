#include "enemy.h"
#include "DxLib.h"
#include "constant.h"
#include <cmath>

#include "mapDraw.h"

Enemy::Enemy(int graph, Player& player) : player(player), graph(graph) {
	this->pos.dx = 13000;
	this->pos.dy = 13000;
	this->center = (HALF_PLAYER_SIZE / 2) + pos;
	activity = true;
}

Enemy::~Enemy() {
}

void Enemy::draw() {
	DrawGraph(screenPosX(), screenPosY(), graph, true);
}

void Enemy::move() {
	if (screenPosX() >= 0 && screenPosX() < player.center.dx) {
		this->pos.dx += moveSpeed.dx;
	}
	else if (screenPosX() >= player.center.dx && screenPosX() < WIN_WIDTH) {
		this->pos.dx -= moveSpeed.dx;
	}

	if (screenPosY() >= 0 && screenPosY() < player.center.dy) {
		this->pos.dy += moveSpeed.dy;
	}
	else if (screenPosY() >= player.center.dy && screenPosY() < WIN_HEIGHT) {
		this->pos.dy -= moveSpeed.dy;
	}
}

void Enemy::collision() {
	if (relativeDistanceX() <= ENEMY_COLLISION_RANGE
		&& relativeDistanceY() <= ENEMY_COLLISION_RANGE) {
		activity = false;
	}
}

void Enemy::getMoveSpeed() {
	distance = player.center - this->center;
	distanceSquared = distance * distance;
	distanceNormalized.dx = abs(distance.dx) / sqrt(distanceSquared.dx + distanceSquared.dy);
	distanceNormalized.dy = abs(distance.dy) / sqrt(distanceSquared.dx + distanceSquared.dy);
	moveSpeed = 4 * distanceNormalized;
}

int Enemy::screenPosX() {
	return static_cast<int>(this->pos.dx) - MapDraw::mapX;
}

int Enemy::screenPosY() {
	return static_cast<int>(this->pos.dy) - MapDraw::mapY;
}

int Enemy::relativeDistanceX() {
	return abs(static_cast<int>(distance.dx) + MapDraw::mapX);
}

int Enemy::relativeDistanceY() {
	return abs(static_cast<int>(distance.dy) + MapDraw::mapY);
}

void Enemy::update() {

	collision();

	if (activity) {
		getMoveSpeed();
		//move();
		draw();
	}

	DrawFormatString(200, 200, GetColor(0, 0, 255),
	                 "スクリーン座標：%d, %d",
	                 screenPosX(), screenPosY(), false);
	DrawFormatString(215, 215, GetColor(0, 0, 255),
	                 "相対距離：%d, %d", relativeDistanceX(), relativeDistanceY(), false);
}
