#include "DxLib.h"
#include "Player.h"
#include "constant_declaration.h"

Player::Player() {
	x = WIN_WIDTH / 2 - radius;
	y = WIN_HEIGHT / 2 - radius;
}

//ƒvƒŒƒCƒ„[•`‰æ
void Player::draw() {
	int player_graph = LoadGraph("resource/charactor/Player32.png");
	DrawGraph(x, y, player_graph, TRUE);
}
