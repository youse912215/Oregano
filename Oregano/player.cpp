#include "DxLib.h"
#include "player.h"
#include "constant.h"
#include "mapDraw.h"
#include "eventBase.h"
#include <algorithm>

Player::Player(Input& input) :
	input(input), cooldown(3), cooldownFlag(3),

	coin{50, 0, 0, 0}, attributeAccumulation{0, 0, 0, 0},

	/* �f�[�^�� */
	status(PLAYER_STATUS_SIZE), possessionItem(PLAYER_ITEM_SIZE),
	possessionAccessory(PLAYER_ACCESSORY_SIZE), possessionJewel(PLAYER_JEWEL_SIZE),
	possessionMineral(PLAYER_MINERAL_SIZE) {

	this->pos.dx = static_cast<int>(WIN_WIDTH / 2 - BLOCK_SIZE / 2); //�v���C���[x���W
	this->pos.dy = static_cast<int>(WIN_HEIGHT / 2 - BLOCK_SIZE / 2 - 2); //�v���C���[y���W
	center = HALF_BLOCK_SIZE + pos; //�v���C���[�̒��S���W

	knifePos = 0; //�i�C�t���W
	knifeAddPos = 0; //�i�C�t�̉��Z���̍��W
	knifeCenter = 0; //�i�C�t�̒��S���W
	knife = false; //�i�C�t�t���O

	slashPos = this->pos - HALF_BLOCK_SIZE; //�n���W
	slashCenter = 0; //�n�̒��S���W
	slash = false; //�n�t���O

	shieldPos = this->pos; //�V�[���h�̍��W
	shieldValue = 15;
	shield = false; //�V�[���h�t���O

	coin0 = 100;

	battleStyle = 0;
}

Player::~Player() {
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::draw() {
	//�i�C�t
	if (knife)
		DrawGraph(static_cast<int>(knifePos.dx), static_cast<int>(knifePos.dy), source.knifeGraph, true);

	//�n
	if (slash)
		DrawGraph(static_cast<int>(slashPos.dx), static_cast<int>(slashPos.dy), source.slashGraph, true);

	//�V�[���h
	if (shield)
		DrawGraph(static_cast<int>(shieldPos.dx), static_cast<int>(shieldPos.dy), source.shieldGraph, true);

	//�v���C���[
	DrawRectGraph(static_cast<int>(this->pos.dx),
	              static_cast<int>(this->pos.dy),
	              0, 0, BLOCK_SIZE, BLOCK_SIZE,
	              source.player, true, false);


	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy),
	                 GetColor(255, 0, 0), "%lf, %lf, %lf, %lf",
	                 this->pos.dx, this->pos.dy, center.dx, center.dy, false);
	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy) - 15,
	                 GetColor(255, 0, 0), "X%lf, Y%lf",
	                 knifePos.dx, knifePos.dy, false);
	DrawFormatString(static_cast<int>(this->pos.dx), static_cast<int>(this->pos.dy) - 30,
	                 GetColor(255, 0, 0), "X%lf, Y%lf",
	                 slashPos.dx, slashPos.dy, false);
}

/// <summary>
/// �A�N�V�����R�}���h����
/// </summary>
void Player::actionCommand() {
	/* �i�C�t���� */
	if (input.A && cooldown[KNIFE] == 0 && input.anySTICK()) {
		knife = true; //�i�C�t����
		cooldownFlag[KNIFE] = true; //�N�[���_�E���t���O��true
	}
	/* �n���� */
	if (input.B && cooldown[SLASH] == 0) {
		slash = true; //�n����]
		cooldownFlag[SLASH] = true; //�N�[���_�E���t���O��true
	}
	/* �V�[���h */
	if (input.X && !cooldownFlag[SHIELD]) {
		shield = true; //�V�[���h��t�^
		shieldValue = 15;
		cooldownFlag[SHIELD] = true; //�N�[���_�E���t���O��true
	}

	//L�{�^��
	if (input.LB && battleStyle != 0)
		changeBattleStyle(LEFT);
	//R�{�^��
	if (input.RB && battleStyle != 3)
		changeBattleStyle(RIGHT);
}

/// <summary>
/// �i�C�t�̃N�[���_�E������
/// </summary>
void Player::knifeCooldown() {
	if (cooldownFlag[KNIFE]) cooldown[KNIFE]++; //�N�[���_�E���J�n

	//�N�[���_�E����30�b
	if (cooldown[KNIFE] >= 30) {
		cooldown[KNIFE] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[KNIFE] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �i�C�t�̃|�W�W�������Z�b�g����
/// </summary>
void Player::setKnifePosition() {
	/* x���� */
	if (knifePos.dx < pos.dx) knifeAddPos.dx -= KNIFE_SPEED;
	else if (knifePos.dx > pos.dx) knifeAddPos.dx += KNIFE_SPEED;
	else knifeAddPos.dx = 0;
	/* y���� */
	if (knifePos.dy < pos.dy) knifeAddPos.dy -= KNIFE_SPEED;
	else if (knifePos.dy > pos.dy)knifeAddPos.dy += KNIFE_SPEED;
	else knifeAddPos.dy = 0;
}

/// <summary>
/// �i�C�t�̃|�W�W���������Z�b�g����
/// </summary>
void Player::resetKnifePosition() {
	if (deleteKnife()) {
		knife = false;
		knifeAddPos.dx = 0.0;
		knifeAddPos.dy = 0.0;
	}
}

/// <summary>
/// �i�C�t�̉����i�W���C�p�b�h���ƋȂ��邱�Ƃ��\�j
/// </summary>
void Player::accelKnife() {
	/* x���� */
	if (input.STICK[LEFT]) knifeAddPos.dx -= KNIFE_SPEED / 2.0;
	else if (input.STICK[RIGHT]) knifeAddPos.dx += KNIFE_SPEED / 2.0;
	/* y���� */
	if (input.STICK[UP]) knifeAddPos.dy -= KNIFE_SPEED / 2.0;
	else if (input.STICK[DOWN]) knifeAddPos.dy += KNIFE_SPEED / 2.0;
}

/// <summary>
/// �i�C�t�̍X�V����
/// </summary>
void Player::knifeUpdate() {
	knifePos = pos + knifeAddPos; //�i�C�t�̍��W�̍X�V
	knifeCenter = HALF_BLOCK_SIZE + knifePos; //�i�C�t�̒��S�ʒu�̍X�V

	//�i�C�t���͂��������Ƃ�
	if (knife) {
		setKnifePosition(); //�i�C�t�̃|�W�W�����Z�b�g
		accelKnife(); //�i�C�t�̉���
		resetKnifePosition(); //�i�C�t�̃|�W�W�������Z�b�g
	}
}

/// <summary>
/// �i�C�t�̍폜����
/// </summary>
/// <returns></returns>
bool Player::deleteKnife() {
	//�v���C���[����̋�����3�}�X������Ă��邩
	return abs(knifePos.dx + HALF_BLOCK_SIZE - center.dx) >= BLOCK_SIZE * 3.0
		|| abs(knifePos.dy + HALF_BLOCK_SIZE - center.dy) >= BLOCK_SIZE * 3.0;
}

/// <summary>
/// �n�̃N�[���_�E������
/// </summary>
void Player::slashCooldown() {
	if (cooldownFlag[SLASH]) cooldown[SLASH]++; //�N�[���_�E���J�n

	if (cooldown[SLASH] >= 20 && cooldown[SLASH] < 60) {
		slash = false; //�n�����߂�
	}
		//�N�[���_�E����60�b
	else if (cooldown[SLASH] >= 60) {
		cooldown[SLASH] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[SLASH] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �V�[���h�̃N�[���_�E������
/// </summary>
void Player::shieldCooldown() {
	if (cooldownFlag[SHIELD] && !shield) cooldown[SHIELD]++; //�N�[���_�E���J�n

	if (cooldown[SHIELD] >= 120) {
		cooldown[SHIELD] = 0; //�N�[���_�E�������Z�b�g
		cooldownFlag[SHIELD] = false; //�N�[���_�E���t���O��false
	}
}

/// <summary>
/// �V�[���h�X�V����
/// </summary>
void Player::shieldUpdate() {
	if (shieldValue == 0) shield = false; //�V�[���h�ʂ�0�ɂȂ�����A�V�[���h����
}

/// <summary>
/// �R�C���X�V����
/// </summary>
void Player::coinUpdate() {
}

/// <summary>
/// �퓬�X�^�C����؂�ւ���
/// </summary>
void Player::changeBattleStyle(const int& dir) {
	//L�{�^�����͂��A�퓬�X�^�C�����ԖG�K�ł͂Ȃ��Ƃ�
	if (dir == LEFT && battleStyle != 0)
		//�O�̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ�
		battleStyle = coin[battleStyle - 1] != 0 ? --battleStyle : battleStyle; //�O�̃X�^�C���ɐ؂�ւ�

		//R�{�^�����͂��A�퓬�X�^�C�������g�Ԃł͂Ȃ��Ƃ�
	else if (dir == RIGHT && battleStyle != 3)
		//�O�̃X�^�C���̃R�C����0�ł͂Ȃ��Ƃ�
		battleStyle = coin[battleStyle + 1] != 0 ? ++battleStyle : battleStyle; //���̃X�^�C���ɐ؂�ւ�

}

/// <summary>
/// �R�C���̑�������
/// </summary>
/// <param name="attackPower">�G�̍U����</param>
void Player::lostPlayerCoin(const int& attackPower) {
	if (!shield)
		coin[battleStyle] -= attackPower;
	else
		shieldValue -= attackPower;
}

/// <summary>
/// �R�C���̒ǉ�����
/// </summary>
/// <param name="enemyCoin">�G�̏����R�C��</param>
/// <param name="attribute">�G�̑���</param>
void Player::addPlayerCoin(const int& attribute, const int& enemyCoin) {
	coin[attribute] += enemyCoin;
}

/// <summary>
/// �����~�ϒl���ő�l�łȂ��Ƃ��A���Z����
/// </summary>
/// <param name="attribute">�G�̑���</param>
/// <param name="attributeValue">�G�̑����l</param>
void Player::addAttributeAccumulation(const int& attribute, const int& attributeValue) {
	//�V�[���h���Ȃ��Ƃ����A���݂̐퓬�X�^�C���ƓG�̑������قȂ�Ƃ�
	if (!shield && battleStyle != attribute) {
		if (attributeAccumulation[attribute] < 100)
			attributeAccumulation[attribute] += attributeValue; //�����~�ϒl�����Z
		else if (attributeAccumulation[attribute] >= 100)
			attributeAccumulation[attribute] = 100; //100�ȏ�͑����~�ϒl���ő�l�ɂ���
	}
}

/// <summary>
/// �퓬�X�^�C���̐�����Ԃ��X�V
/// </summary>
void Player::battleStyleUpdate() {
	if (coin[battleStyle] <= 0) {
		//�S�ẴR�C���̒���0�łȂ��v�f��T���A���������ŏ��̗v�f�̃C�e���[�^�[��Ԃ�
		auto itr = find_if(coin.begin(), coin.end(),
		                   [](int x) { return x != 0; });
		//0�ȊO�̗v�f��������΁A���̗v�f��battleStyle�ɑ��
		if (itr != coin.end())
			battleStyle = distance(coin.begin(), itr); //�퓬�X�^�C����؂�ւ���
		else
			EventBase::gameScene = END_SCENE; //�S�ẴR�C����0�ɂȂ�A�Q�[���I�[�o�[�V�[����
	}
}

/// <summary>
/// �X�V����
/// </summary>
void Player::update() {
	knifeCooldown(); //�i�C�t�̃N�[���_�E������
	slashCooldown(); //�n�̃N�[���_�E������
	shieldCooldown(); //�V�[���h�̃N�[���_�E������

	actionCommand(); //�A�N�V�����R�}���h����

	knifeUpdate(); //�i�C�t�X�V����
	shieldUpdate(); //�V�[���h�X�V����

	coinUpdate();
	battleStyleUpdate();

	draw(); //�`�揈��

	DrawFormatString(0, 450, GetColor(0, 255, 0), "�i�C�t�@�@TF:%d, CDR:%d", knife, cooldown[0], false);
	DrawFormatString(0, 465, GetColor(0, 255, 0), "�@�n�@�@�@TF:%d, CDR:%d", slash, cooldown[1], false);
	DrawFormatString(0, 480, GetColor(0, 255, 0), "�V�[���h�@TF:%d, CDR:%d, Value:%d",
	                 shield, cooldown[2], shieldValue, false);
	DrawFormatString(0, 550, GetColor(255, 100, 100), "�R�C��0:%d, �X�^�C��:%d", coin0, battleStyle, false);
	DrawFormatString(0, 565, GetColor(0x00, 0x8d, 0x56), "�ԖG�K:%d, �R�C��:%d", attributeAccumulation[0], coin[0], false);
	DrawFormatString(0, 580, GetColor(0xef, 0xbb, 0x2c), "�[�x�q:%d, �R�C��:%d", attributeAccumulation[1], coin[1], false);
	DrawFormatString(0, 595, GetColor(0x4b, 0x5e, 0xaa), "���q��:%d, �R�C��:%d", attributeAccumulation[2], coin[2], false);
	DrawFormatString(0, 610, GetColor(0xee, 0x86, 0x9a), "���g��:%d, �R�C��:%d", attributeAccumulation[3], coin[3], false);

	/*DrawFormatString(0, 500, GetColor(120, 0, 100), "�g���W���[�����N:%d, �ԖG�K:%d, ������:%d, ������:%d, ���S��:%d",
	                 status[TREASURE_RANK], status[GREEN_COIN], status[YELLOW_COIN],
	                 status[PURPLE_COIN], status[WHITE_COIN], false);
	DrawFormatString(0, 515, GetColor(120, 0, 100), "���ݐ�����:%d, �ő吶����:%d, �U����:%d, ����:%d",
	                 status[CURRENT_LIFE], status[MAX_LIFE],
	                 status[ATTACK], status[BARGAINING_POWER], false);
	DrawFormatString(0, 530, GetColor(120, 0, 100), "�ғőϐ�:%d, �ғő����l:%d, �ғŒ~��:%d,  ��ბϐ�:%d, ��ბ����l:%d, ��გ~��:%d",
	                 status[DEADLY_POISON_RESISTANCE], status[DEADLY_POISON_VALUE],
	                 status[DEADLY_POISON_ACCUMULATION],
	                 status[PARALYSIS_RESISTANCE], status[PARALYSIS_VALUE],
	                 status[PARALYSIS_ACCUMULATION], false);
	DrawFormatString(0, 545, GetColor(120, 0, 100), "�Ö��ϐ�:%d, �Ö������l:%d, �Ö��~��:%d, �o���ϐ�:%d, �o�������l:%d, �o���~��:%d",
	                 status[HYPNOSIS_RESISTANCE], status[HYPNOSIS_VALUE],
	                 status[HYPNOSIS_ACCUMULATION],
	                 status[BLOODING_RESISTANCE], status[BLOODING_VALUE],
	                 status[BLOODING_ACCUMULATION], false);
	DrawFormatString(0, 630, GetColor(0, 0, 0), "���H:%d, �p��:%d, ��:%d, ��:%d�A��:%d, �n�}:%d, �{�g����:%d, �{�g����:%d",
	                 possessionItem[0], possessionItem[1], possessionItem[2],
	                 possessionItem[3], possessionItem[4], possessionItem[5],
	                 possessionItem[6], possessionItem[7], false);
	DrawFormatString(0, 645, GetColor(0, 0, 0),
	                 "�s�v�c�ȃ{�g��:%d, �ő�:%d, ��ő�:%d, ���N��:%d�A�`���[���b�v:%d, �A���G:%d, �}���[�S�[���h:%d, ������:%d",
	                 possessionItem[8], possessionItem[9], possessionItem[10],
	                 possessionItem[11], possessionItem[12], possessionItem[13],
	                 possessionItem[14], possessionItem[15], false);
	DrawFormatString(0, 660, GetColor(0, 0, 0),
	                 "�K�N:%d, �Q��:%d, �X�R�b�v:%d, �s�b�P��:%d�A�i�C�t:%d, ���C:%d, �A���}�L�m�R:%d, �~����:%d",
	                 possessionItem[16], possessionItem[17], possessionItem[18],
	                 possessionItem[19], possessionItem[20], possessionItem[21],
	                 possessionItem[22], possessionItem[23], false);
	DrawFormatString(0, 675, GetColor(0, 0, 0),
	                 "���N�H:%d, �ғŖ�:%d, ������:%d, �Î���:%d�A���s�i�X:%d, �^���|�|:%d, �}�b�X���_�P:%d, �L����:%d",
	                 possessionItem[24], possessionItem[25], possessionItem[26],
	                 possessionItem[27], possessionItem[28], possessionItem[29],
	                 possessionItem[30], possessionItem[31], false);
	DrawFormatString(0, 690, GetColor(0, 0, 0),
	                 "�Ԏ�:%d, �o�[�i�[:%d, ������:%d, �V�[�p���[:%d�A�u���b�h�G�L�X:%d, �u���b�h�|�[�V����:%d�A�����_�P:%d, �X���[�v�W�F��:%d",
	                 possessionItem[32], possessionItem[33], possessionItem[34],
	                 possessionItem[35], possessionItem[36], possessionItem[37],
	                 possessionItem[38], possessionItem[39], false);
	DrawFormatString(0, 720, GetColor(0, 0, 0), "B�l�b�N:%d, B�`���[:%d, B�y���_:%d, B�����O:%d�AB�s�A�X:%d, �e���T:%d, �}�`���_:%d, �i�K�^��:%d",
	                 possessionAccessory[0], possessionAccessory[1], possessionAccessory[2],
	                 possessionAccessory[3], possessionAccessory[4], possessionAccessory[5],
	                 possessionAccessory[6], possessionAccessory[7], false);
	DrawFormatString(0, 735, GetColor(0, 0, 0), "S�l�b�N:%d, S�`���[:%d, S�y���_:%d, S�����O:%d�AS�s�A�X:%d, �������:%d, G�l�b�N:%d, G�y���_:%d",
	                 possessionAccessory[8], possessionAccessory[9], possessionAccessory[10],
	                 possessionAccessory[11], possessionAccessory[12], possessionAccessory[14],
	                 possessionAccessory[15], possessionAccessory[16], false);
	DrawFormatString(0, 770, GetColor(0, 0, 0), "�G�������h:%d, T�K�[�l�b�g:%d, C�g���}����:%d, �y��D:%d�A�ԖG�K���[�hN:%d",
	                 possessionJewel[0], possessionJewel[1], possessionJewel[2],
	                 possessionJewel[3], possessionJewel[20], false);
	DrawFormatString(0, 800, GetColor(0, 0, 0), "�y��:%d, ���h��:%d, ��h��:%d, ���h��:%d�A�k�h��:%d, ��������:%d",
	                 possessionMineral[0], possessionMineral[1], possessionMineral[2],
	                 possessionMineral[3], possessionMineral[4], possessionMineral[4], false);*/
}
