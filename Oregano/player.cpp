#include "DxLib.h"
#include "Player.h"
#include "constant.h"

Player::Player(int graph) :
	graph(graph), status(PLAYER_STATUS_SIZE),
	possessionItem(PLAYER_ITEM_SIZE), possessionAccessory(PLAYER_ACCESSORY_SIZE),
	possessionJewel(PLAYER_JEWEL_SIZE), possessionMineral(PLAYER_MINERAL_SIZE) {
	pos.x = WIN_WIDTH / 2 - BLOCK_SIZE / 2;
	pos.y = WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2;
}

Player::~Player() {
}

//ÉvÉåÉCÉÑÅ[ï`âÊ
void Player::draw() {
	DrawGraph(pos.x, pos.y, graph, TRUE);
}

void Player::initProcess() {
}

void Player::update() {
	draw();
}
