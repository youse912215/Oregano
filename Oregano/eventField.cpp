#include "eventField.h"
#include "constant.h"
#include "mapDraw.h"
#include "DxLib.h"

EventField::EventField(Input& input, EventBase& event, Player& player)
	: input(input), event(event), player(player),
	  /*�e�t�B�[���h�I�u�W�F�N�g�̃t���O*/
	  coinFlag(COIN_EVENT_SIZE), itemFlag(ITEM_EVENT_SIZE), accessoryFlag(ACCESSORY_EVENT_SIZE),
	  jewelFlag(JEWEL_EVENT_SIZE), mineralFlag(MINERAL_EVENT_SIZE),
	  /*�R�C���ʔz��*/
	  coinQuantity{5, 10, 50, 100},
	  /*�e�t�B�[���h�I�u�W�F�N�g�̏��i�[�p�̔z��*/
	  coin(COIN_INFORMATION_SIZE), item(ITEM_INFORMATION_SIZE), accessory(ACCESSORY_INFORMATION_SIZE),
	  jewel(JEWEL_INFORMATION_SIZE), mineral(MINERAL_INFORMATION_SIZE) {
	actionFlagX = false; //X�{�^���A�N�V�����t���O
}

EventField::~EventField() {
}

/// <summary>
/// X�{�^�����������Ƃ��A�t�B�[���h��̎w��̏ꏊ�ŃA�C�e����R�C���Ȃǂ����\�ɂ���
/// </summary>
void EventField::getFieldObject(vector<int>& objectName, vector<bool>& eventFlag, vector<int>& saveLocation) {
	for (unsigned int i = 0; i < objectName.size() / EVENT_INFORMATION_SIZE; ++i) {
		if (!( //�C�x���g�����ꏊ�̕����������Ă���Ƃ�
			input.moveDirection == directionReverse(objectName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_])
			//�C�x���g�t���O��false�̂Ƃ�
			&& !eventFlag[objectName[(i * EVENT_INFORMATION_SIZE) + EVENT_NO_]]
			//�C�x���g�����ꏊ�̎��ӂɂ���Ƃ�
			&& event.getEventCoordinate(
				objectName[(i * EVENT_INFORMATION_SIZE) + MAP_X_],
				objectName[(i * EVENT_INFORMATION_SIZE) + MAP_Y_],
				objectName[(i * EVENT_INFORMATION_SIZE) + CURRENT_X_]
				+ directionSignX(objectName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_]),
				objectName[(i * EVENT_INFORMATION_SIZE) + CURRENT_Y_]
				+ directionSignY(objectName[(i * EVENT_INFORMATION_SIZE) + DIRECTION_]))))
			continue; //�����ȊO�̂Ƃ��A�������X�L�b�v����
		{
			eventFlag[objectName[(i * EVENT_INFORMATION_SIZE) + EVENT_NO_]] = true; //���肵���ꏊ�̃C�x���g���ςݏ��(true)�ɂ���

			/* �R�C���̂Ƃ��̂݁A�ۑ����������ύX���� */
			if (objectName == coin)
				saveLocation[coinTypeDecision(objectName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_])]
					+= coinQuantityDecision(objectName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_]); //�R�C���̓���i��ޕʂɒǉ��j
			else
				saveLocation[objectName[(i * EVENT_INFORMATION_SIZE) + ITEM_TYPE_]]++; //���̑��̃A�C�e���̓���
		}
	}
}

/// <summary>
/// �I�u�W�F�N�g�ʂ�ۑ���Ɋi�[����
/// </summary>
/// <param name="saveLocation">�f�[�^�ۑ���</param>
/// <param name="objectVolume">�f�[�^��</param>
void EventField::storingObject(int* saveLocation, const int& objectVolume) {
	if (saveLocation == nullptr) { return; } //null�`�F�b�N
	*saveLocation += objectVolume;
}

/// <summary>
/// �t�B�[���h�A�N�V����
/// </summary>
void EventField::fieldAction() {
	if (input.X) {
		getFieldObject(coin, coinFlag, player.status); //�t�B�[���h�R�C�������
		getFieldObject(item, itemFlag, player.possessionItem); //�t�B�[���h�A�C�e�������
		getFieldObject(accessory, accessoryFlag, player.possessionAccessory); //�t�B�[���h�A�N�Z�T���[�����
		getFieldObject(jewel, jewelFlag, player.possessionJewel); //�t�B�[���h�W���G�������
		getFieldObject(mineral, mineralFlag, player.possessionMineral); //�t�B�[���h�z�������

		actionFlagX = true; //�{�^���������Ă���Ƃ��̓A�N�V�����t���O��true
	}
	else actionFlagX = false; //�{�^���������Ă��Ȃ��Ƃ��̓A�N�V�����t���O��false
}

/// <summary>
/// x�����ɂ���āA-1��1��Ԃ�
/// </summary>
/// <param name="direction">�C�x���g�����ꏊ�Ɨאڂ��Ă������</param>
int EventField::directionSignX(const int& direction) {
	if (direction == LEFT) return -1;
	if (direction == RIGHT) return 1;
	return 0;
}

/// <summary>
///	y�����ɂ���āA-1��1��Ԃ�
/// </summary>
/// <param name="direction">�C�x���g�����ꏊ�Ɨאڂ��Ă������</param>
int EventField::directionSignY(const int& direction) {
	if (direction == UP) return -1;
	if (direction == DOWN) return 1;
	return 0;
}

/// <summary>
/// �R�C���̎�ނɂ���āA�K�؂ȗʂ�Ԃ�
/// </summary>
/// <param name="coinType">�R�C���̎��</param>
int EventField::coinQuantityDecision(const int& coinType) {
	return coinQuantity[coinType];
}

/// <summary>
/// �R�C���̎�ނɂ���āA�K�؂ȐF�̃R�C������Ԃ�
/// </summary>
/// <param name="coinType">�R�C���̎��</param>
int EventField::coinTypeDecision(const int& coinType) {
	if (coinType >= 0 && coinType <= 3) return GREEN_COIN; //�ԖG�K�̃R�C��
	if (coinType >= 4 && coinType <= 7) return YELLOW_COIN; //�������̃R�C��
	if (coinType >= 8 && coinType <= 11) return PURPLE_COIN; //�������̃R�C��
	if (coinType >= 12 && coinType <= 15) return WHITE_COIN; //���S���̃R�C��
	return 0;
}

/// <summary>
/// �����𔽓]������
/// </summary>
/// <param name="direction"></param>
int EventField::directionReverse(const int& direction) {
	if (direction == LEFT) return RIGHT;
	if (direction == RIGHT) return LEFT;
	if (direction == UP) return DOWN;
	if (direction == DOWN) return UP;
	return 0;
}

/// <summary>
/// �X�V����
/// </summary>
void EventField::update() {
	fieldAction(); //�t�B�[���h�A�N�V����

	DrawFormatString(300, 0, GetColor(130, 130, 255), "�C�x���g:%d, ����:%d, T%d",
	                 this->actionFlagX, input.moveDirection,
	                 event.getEventCoordinate(8, 7, 12, 24), false);
	DrawFormatString(100, 0, GetColor(255, 0, 0), "cx:%d, cy:%d,",
	                 event.centralPlayerPosition(MAP_X), event.centralPlayerPosition(MAP_Y), false);
	DrawFormatString(WIN_WIDTH - 100, WIN_HEIGHT - 15, GetColor(255, 0, 0), "TIME:%d",
	                 EventBase::gameTime, false);
}
