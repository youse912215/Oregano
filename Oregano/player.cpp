#include "DxLib.h"
#include "Player.h"
#include "constant.h"

Player::Player(int x, int y, int graph) : Human(x, y), graph(graph) {

}

Player::~Player() {
}

//ƒvƒŒƒCƒ„[•`‰æ
void Player::draw() {
	DrawGraph(x, y, graph, TRUE);
}
