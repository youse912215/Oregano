#include "sceneGame.h"

SceneGame::SceneGame(Input& input, MapDraw& draw, MapCollision& collision, SceneLoad& load, Player& player,
                     EnemyConclusion& enemy, GameUI& gameUI) :
	input(input), draw(draw), collision(collision), load(load), player(player), enemy(enemy), gameUI(gameUI) {
}

/// <summary>
/// �Ԋu���Ԃ��J�E���g
/// </summary>
/// <param name="countTime">�J�E���g���鎞��</param>
/// <param name="maxTime">�ő厞��</param>
void SceneGame::countInterval(int* countTime, const int& maxTime) {
	if (countTime == nullptr) { return; } //null�`�F�b�N

	*countTime = (*countTime <= maxTime) ? ++(*countTime) : 0; //���Ԃ��J�E���g���A�ő厞�Ԃ��߂����0�ɖ߂�
}

void SceneGame::update() {
	if (SceneLoad::gameScene == GAME_SCENE) {
		draw.update(load.roadingMap()); //�}�b�v�X�V����

		collision.update(); //�R���W�����X�V����

		input.menuProcess(); //���j���[����
		input.movement(collision, draw); //�ړ�����

		player.update(); //�v���C���[�X�V����

		//enemy.update(); //�G�X�V����

		gameUI.update(); //UI�X�V����
	}
}
