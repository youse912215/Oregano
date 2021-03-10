#pragma once
#include "inputProcess.h"
#include "mapDraw.h"
#include "mapCollision.h"
#include "sceneLoad.h"
#include "player.h"
#include "enemyConclusion.h"
#include "gameUI.h"

class SceneGame {
private:
	Input& input; //���̓N���X
	MapDraw& draw; //�`��N���X
	MapCollision& collision; //�R���W�����N���X
	SceneLoad& load; //���[�h�N���X
	Player& player; //�v���C���[�N���X
	EnemyConclusion& enemy; //�G�܂Ƃ߃N���X
	GameUI& gameUI; //�Q�[��UI�N���X

	const int timeMax; //�ő厞��
	const int popTime; //�o������

	void countTime(); //���Ԃ��J�E���g

public:
	int gameTime; //�Q�[������
	bool enemyFlag; //�G�o���t���O

	SceneGame(Input& input, MapDraw& draw, MapCollision& collision, SceneLoad& load, Player& player,
	          EnemyConclusion& enemy, GameUI& gameUI);

	static void countInterval(int* countTime, const int& maxTime); //�Ԋu���Ԃ��J�E���g

	void update(); //�X�V����
};
