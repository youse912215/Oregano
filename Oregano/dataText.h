#pragma once
#include "vec2.h"
#include <vector>

class DataText {
private:
	Vec2 coinPos;
	Vec2 accumulationPos;

	const int fontSize; //�t�H���g�T�C�Y
	std::vector<unsigned int> color;

public:
	DataText();

	void drawText();
	void roadFont();

};
