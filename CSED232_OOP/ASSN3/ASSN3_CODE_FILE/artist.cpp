#include "artist.h"

char artist::mapper(int x, int y) {
	return 0;
}

char classic::mapper(int x, int y) {
	int value;
	value = pixel.at(y * width + x); // vector<int>�� �������� �����Ǿ� �����Ƿ� ��ǥ������ vector �󿡼��� ������ ǥ��
	if (value >= 0 && value <= 16) { // �ȼ� �� value�� ���� �����Ǵ� ���ڷ� ��ȯ�Ѵ�.
		 return '@';
	}
	if (value >= 17 && value <= 33) {
		return '&';
	}
	if (value >= 34 && value <= 50) {
		return '%';
	}
	if (value >= 51 && value <= 67) {
		return 'W';
	}
	if (value >= 68 && value <= 84) {
		return 'X';
	}
	if (value >= 85 && value <= 101) {
		return 'A';
	}
	if (value >= 102 && value <= 118) {
		return 'H';
	}
	if (value >= 119 && value <= 135) {
		return 'O';
	}
	if (value >= 136 && value <= 152) {
		return 'T';
	}
	if (value >= 153 && value <= 169) {
		return '*';
	}
	if (value >= 170 && value <= 186) {
		return '^';
	}
	if (value >= 187 && value <= 203) {
		return '+';
	}
	if (value >= 204 && value <= 220) {
		return '-';
	}
	if (value >= 221 && value <= 237) {
		return '.';
	}
	if (value >= 238 && value <= 255) {
		return ' ';
	}
	else return ' ';
}

char iclassic::mapper(int x, int y) {
	int value;
	value = pixel.at(y * width + x);
	if (value >= 0 && value <= 16) { // classic�� ������ �����Ѵ�.
		return ' ';
	}
	if (value >= 17 && value <= 33) {
		return '.';
	}
	if (value >= 34 && value <= 50) {
		return '-';
	}
	if (value >= 51 && value <= 67) {
		return '+';
	}
	if (value >= 68 && value <= 84) {
		return '^';
	}
	if (value >= 85 && value <= 101) {
		return '*';
	}
	if (value >= 102 && value <= 118) {
		return 'T';
	}
	if (value >= 119 && value <= 135) {
		return 'O';
	}
	if (value >= 136 && value <= 152) {
		return 'H';
	}
	if (value >= 153 && value <= 169) {
		return 'A';
	}
	if (value >= 170 && value <= 186) {
		return 'X';
	}
	if (value >= 187 && value <= 203) {
		return 'W';
	}
	if (value >= 204 && value <= 220) {
		return '%';
	}
	if (value >= 221 && value <= 237) {
		return '&';
	}
	if (value >= 238 && value <= 255) {
		return '@';
	}
	else return '@';
}

char sobelx::mapper(int x, int y) {
	int value;
	int comp;
	value = pixel.at(y * width + x);
	if (x < width-1) {
		comp = pixel.at(y * width + x + 1); // x�� ���� �������� ������ pixel���� ����
		int dif = value - comp;
		if (dif >= 50 || dif <= -50) { // ���̰� 50�̻��� ���
			return '|';
		}
		else return ' ';
	}
	else if (x == width-1) { // �����ڸ��� ��� ���� pixel�� �����Ƿ�
		return ' ';
	}
	else return ' ';
}

char sobely::mapper(int x, int y) {
	int value;
	int comp;
	value = pixel.at(y * width + x);
	if (y < height - 1) {
		comp = pixel.at((y + 1) * width + x); // y�� ���� �������� ������ pixel���� ����
		int dif = value - comp;
		if (dif >= 50 || dif <= -50) { // ���̰� 50�̻��� ���
			return '-';
		}
		else return ' ';
	}
	else if (y == height - 1) { // �����ڸ��� ��� ���� pixel�� �����Ƿ�
		return ' ';
	}
	else return ' ';
}

char gradient::mapper(int x, int y) {
	int value;
	int comp;
	char xtemp = 0;
	char ytemp = 0;
	value = pixel.at(y * width + x);
	if (x < width - 1) {
		comp = pixel.at(y * width + x + 1); // x�� ���� �������� ������ pixel���� ����
		int dif = value - comp;
		if (dif >= 50 || dif <= -50) { // ���̰� 50�̻��� ���
			xtemp = '|';
		}
		else xtemp = ' ';
	}
	else if (x == width - 1) { // �����ڸ��� ��� ���� pixel�� �����Ƿ�
		xtemp = ' ';
	}

	if (y < height - 1) {
		comp = pixel .at((y + 1) * width + x); // y�� ���� �������� ������ pixel���� ����
		int dif = value - comp;
		if (dif >= 50 || dif <= -50) { // ���̰� 50�̻��� ���
			ytemp = '-';
		}
		else ytemp =  ' ';
	}
	else if (y == height - 1) { // �����ڸ��� ��� ���� pixel�� �����Ƿ�
		ytemp = ' ';
	}

	if (xtemp == '|' && ytemp == '-') {
		return '+';
	}
	else if (xtemp == '|' && ytemp != '-') {
		return '|';
	}
	else if (xtemp != '|' && ytemp == '-') {
		return '-';
	}
	else return ' ';
}

int artist::call_width() {
	return width;
}

int artist::call_height() {
	return height;
}

artist::artist() {
	width = 0;
	height = 0;
	pixel = {};
}
artist::~artist() {
}

artist::artist(int wid, int hei, const std::vector<int>& pix) {
	width = wid;
	height = hei;
	pixel = pix;

}

classic::classic() {
	width = 0;
	height = 0;
	pixel = {};
}
classic::~classic() {
}

classic::classic(int wid, int hei, const std::vector<int>& pix) {
	width = wid;
	height = hei;
	pixel = pix; 
}

iclassic::iclassic() {
	width = 0;
	height = 0;
	pixel = {};
}
iclassic::~iclassic() {
}

iclassic::iclassic(int wid, int hei, const std::vector<int>& pix) {
	width = wid;
	height = hei;
	pixel = pix;
}

sobelx::sobelx() {
	width = 0;
	height = 0;
	pixel = {};
}
sobelx::~sobelx() {
}

sobelx::sobelx(int wid, int hei, const std::vector<int>& pix) {
	width = wid;
	height = hei;
	pixel = pix;
}

sobely::sobely() {
	width = 0;
	height = 0;
	pixel = {};
}
sobely::~sobely() {
}

sobely::sobely(int wid, int hei, const std::vector<int>& pix) {
	width = wid;
	height = hei;
	pixel = pix;
}

gradient::gradient() {
	width = 0;
	height = 0;
	pixel = {};
}
gradient::~gradient() {
}

gradient::gradient(int wid, int hei, const std::vector<int>& pix) {
	width = wid;
	height = hei;
	pixel = pix;
}


