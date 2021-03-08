#include "sceneEnd.h"

#include "SceneRoad.h"

SceneEnd::SceneEnd(Input& input) : input(input), endFlag(false) {
}

/// <summary>
/// �X�V����
/// </summary>
void SceneEnd::update() {
	//�G���h�V�[���̂Ƃ�
	if (SceneRoad::gameScene == END_SCENE) {
		//VIEW�{�^�����������Ƃ�
		if (input.VIEW) {
			endFlag = true; //�I���t���O��true
		}
		DrawFormatString(0, 0, GetColor(255, 255, 255), "clear", false);
	}
}
