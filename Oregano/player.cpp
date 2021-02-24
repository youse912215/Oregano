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

//vC[`æ
void Player::draw() {
	DrawGraph(pos.x, pos.y, graph, TRUE);
}

void Player::initProcess() {
}

void Player::update() {
	draw();

	DrawFormatString(0, 500, GetColor(120, 0, 100), "gW[N:%d, ÔGK:%d, à:%d, ¸õ:%d, S:%d",
	                 status[TREASURE_RANK], status[GREEN_COIN], status[YELLOW_COIN],
	                 status[PURPLE_COIN], status[WHITE_COIN], false);
	DrawFormatString(0, 515, GetColor(120, 0, 100), "»Ý¶½Í:%d, Åå¶½Í:%d, UÍ:%d, ðÂÍ:%d",
	                 status[CURRENT_LIFE], status[MAX_LIFE],
	                 status[ATTACK], status[BARGAINING_POWER], false);
	DrawFormatString(0, 530, GetColor(120, 0, 100), "ÒÅÏ«:%d, ÒÅ®«l:%d, ÒÅ~Ï:%d,  áÏ«:%d, á®«l:%d, á~Ï:%d",
	                 status[DEADLY_POISON_RESISTANCE], status[DEADLY_POISON_VALUE],
	                 status[DEADLY_POISON_ACCUMULATION],
	                 status[PARALYSIS_RESISTANCE], status[PARALYSIS_VALUE],
	                 status[PARALYSIS_ACCUMULATION], false);
	DrawFormatString(0, 545, GetColor(120, 0, 100), "Ã°Ï«:%d, Ã°®«l:%d, Ã°~Ï:%d, oÏ«:%d, o®«l:%d, o~Ï:%d",
	                 status[HYPNOSIS_RESISTANCE], status[HYPNOSIS_VALUE],
	                 status[HYPNOSIS_ACCUMULATION],
	                 status[BLOODING_RESISTANCE], status[BLOODING_VALUE],
	                 status[BLOODING_ACCUMULATION], false);

	DrawFormatString(0, 630, GetColor(0, 0, 0), "ñíH:%d, p:%d, ÷:%d, :%dA¤:%d, n}:%d, {g¬:%d, {gå:%d",
	                 possessionItem[0], possessionItem[1], possessionItem[2],
	                 possessionItem[3], possessionItem[4], possessionItem[5],
	                 possessionItem[6], possessionItem[7], false);
	DrawFormatString(0, 645, GetColor(0, 0, 0),
	                 "svcÈ{g:%d, Å:%d, ðÅ:%d, N:%dA`[bv:%d, AG:%d, }[S[h:%d, Ô:%d",
	                 possessionItem[8], possessionItem[9], possessionItem[10],
	                 possessionItem[11], possessionItem[12], possessionItem[13],
	                 possessionItem[14], possessionItem[15], false);
	DrawFormatString(0, 660, GetColor(0, 0, 0),
	                 "åKåN:%d, QÜ:%d, XRbv:%d, sbP:%dAiCt:%d, ·C:%d, A}LmR:%d, ~Ü:%d",
	                 possessionItem[16], possessionItem[17], possessionItem[18],
	                 possessionItem[19], possessionItem[20], possessionItem[21],
	                 possessionItem[22], possessionItem[23], false);
	DrawFormatString(0, 675, GetColor(0, 0, 0),
	                 "NH:%d, ÒÅò:%d, ò:%d, Ã:%dAsiX:%d, ^||:%d, }bX_P:%d, L÷:%d",
	                 possessionItem[24], possessionItem[25], possessionItem[26],
	                 possessionItem[27], possessionItem[28], possessionItem[29],
	                 possessionItem[30], possessionItem[31], false);
	DrawFormatString(0, 690, GetColor(0, 0, 0),
	                 "ÔÀ:%d, o[i[:%d, Ñ:%d, V[p[:%dAubhGLX:%d, ubh|[V:%dAõ°_P:%d, X[vWF:%d",
	                 possessionItem[32], possessionItem[33], possessionItem[34],
	                 possessionItem[35], possessionItem[36], possessionItem[37],
	                 possessionItem[38], possessionItem[39], false);

	DrawFormatString(0, 720, GetColor(0, 0, 0), "BlbN:%d, B`[:%d, By_:%d, BO:%dABsAX:%d, eT:%d, }`_:%d, iK^:%d",
	                 possessionAccessory[0], possessionAccessory[1], possessionAccessory[2],
	                 possessionAccessory[3], possessionAccessory[4], possessionAccessory[5],
	                 possessionAccessory[6], possessionAccessory[7], false);
	DrawFormatString(0, 735, GetColor(0, 0, 0), "SlbN:%d, S`[:%d, Sy_:%d, SO:%dASsAX:%d, äÍ:%d, GlbN:%d, Gy_:%d",
	                 possessionAccessory[8], possessionAccessory[9], possessionAccessory[10],
	                 possessionAccessory[11], possessionAccessory[12], possessionAccessory[14],
	                 possessionAccessory[15], possessionAccessory[16], false);

	DrawFormatString(0, 770, GetColor(0, 0, 0), "Gh:%d, TK[lbg:%d, Cg}:%d, yD:%dAÔGK[hN:%d",
	                 possessionJewel[0], possessionJewel[1], possessionJewel[2],
	                 possessionJewel[3], possessionJewel[20], false);

	DrawFormatString(0, 800, GetColor(0, 0, 0), "yÎ:%d, hÎ:%d, ìhÎ:%d, ¼hÎ:%dAkhÎ:%d, ©à´Î:%d",
	                 possessionMineral[0], possessionMineral[1], possessionMineral[2],
	                 possessionMineral[3], possessionMineral[4], possessionMineral[4], false);
}
