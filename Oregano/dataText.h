#pragma once
#include "vec2.h"
#include <vector>

class DataText {
private:
	Vec2 coinPos; //�R�C���̈ʒu
	Vec2 accumulationPos; //�����ϋv�l�̈ʒu

	const int fontSize; //�t�H���g�T�C�Y
	std::vector<unsigned int> color; //�F

	void drawText(); //�e�L�X�g�̕`��

public:
	DataText();

	void loadFont(); //�t�H���g�̃��[�h
};
