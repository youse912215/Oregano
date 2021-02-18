#include "DxLib.h"
#include "Player.h"
#include "constant.h"

Player::Player(int graph) :
	graph(graph),
	status{
		200, 25, 20, 2, 0, 2, 0, 2, 0, 2, 0, 4
	} {
	pos.x = WIN_WIDTH / 2 - BLOCK_SIZE / 2;
	pos.y = WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2;
}

Player::~Player() {
}

//�v���C���[�`��
void Player::draw() {
	DrawGraph(pos.x, pos.y, graph, TRUE);
}
