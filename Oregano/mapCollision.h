#pragma once
#include "mapDraw.h"
#include <vector>

using namespace std;

class MapCollision {
private:
	MapDraw& map; //�}�b�v�`��N���X����

	vector<bool> collisionFlag; //�Փ˃t���O
	vector<bool> boundaryCriteria; //�e�����̋��E����

	const int needCoin; //�i����̏��ʉ߂Ɂj�K�v�ȃR�C��

	int collisionRange(); //�Փ˔͈͂�Ԃ�

	//������s���}�b�v�Ƃ��̃}�b�v�̍��W�̑g�ݍ��킹�ŏՓ˔�����Ƃ�
	bool collisionDetection(const int& dirXY, const int& dirX, const int& dirY);

	/* �p������4�����̏Փ˃t���O */
	bool leftUpCollisionFlag(); //����
	bool rightUpCollisionFlag(); //�E��
	bool leftDownCollisionFlag(); //����
	bool rightDownCollisionFlag(); //�E��

	/* �e�������Ƃ̏Փ˔��� */
	void collisionDetectionLeftUp(); //����
	void collisionDetectionRightUp(); //�E��
	void collisionDetectionLeftDown(); //����
	void collisionDetectionRightDown(); //�E��
	void collisionDetectionCenterLeft1(); //������1�i����ƒ������̊ԁj
	void collisionDetectionCenterLeft2(); //������2�i�����ƒ������̊ԁj
	void collisionDetectionCenterRight1(); //�E����1�i�E��ƒ����E�̊ԁj
	void collisionDetectionCenterRight2(); //�E����2�i�E���ƒ����E�̊ԁj
	void collisionDetectionCenterUp1(); //������1�i����ƒ�����̊ԁj
	void collisionDetectionCenterUp2(); //������2�i�E��ƒ�����̊ԁj
	void collisionDetectionCenterDown1(); //������1�i�����ƒ������̊ԁj
	void collisionDetectionCenterDown2(); //������2�i�E���ƒ������̊ԁj

	void initialize(); //������

public:
	MapCollision(MapDraw& map);
	~MapCollision();

	void update(); //�X�V����

	/* �㉺���E4�����̏Փ˃t���O */
	bool leftCollisionFlag(); //��
	bool rightCollisionFlag(); //�E
	bool upCollisionFlag(); //��
	bool downCollisionFlag(); //��
};
