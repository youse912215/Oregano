#include "DxLib.h"
#include "Player.h"
#include "constant_declaration.h"

Player::Player() {
	x = WIN_WIDTH / 2 - radius;
	y = WIN_HEIGHT / 2 - radius;
	player_graph = LoadGraph("resource/charactor/Player32.png");
}

Player::~Player() {
	DeleteGraph(player_graph);
}

//ÉvÉåÉCÉÑÅ[ï`âÊ
void Player::draw() {
	DrawGraph(x, y, player_graph, TRUE);
}
