#pragma once
#include "vec2.h"
#include <vector>

class DataText {
private:
	Vec2 coinPos; //コインの位置
	Vec2 accumulationPos; //属性耐久値の位置

	const int fontSize; //フォントサイズ
	std::vector<unsigned int> color; //色

	void drawText(); //テキストの描画

public:
	DataText();

	void loadFont(); //フォントのロード
};
