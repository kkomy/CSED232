#pragma once
#include<vector>
class artist {
protected:
	int width;
	int height;
	std::vector<int> pixel;
public:
	artist();
	~artist();
	artist(int, int, const std::vector<int>&);
	virtual char mapper(int, int);
	int call_width();
	int call_height();
};

class classic : public artist {
public:
	classic();
	~classic();
	classic(int, int, const std::vector<int>&);
	char mapper(int, int);
};

class iclassic : public artist {
public:
	iclassic();
	~iclassic();
	iclassic(int, int, const std::vector<int>&);
	char mapper(int, int);
};

class sobelx : public artist {
public:
	sobelx();
	~sobelx();
	sobelx(int, int, const std::vector<int>&);
	char mapper(int, int);
};

class sobely : public artist {
public:
	sobely();
	~sobely();
	sobely(int, int, const std::vector<int>&);
	char mapper(int, int);
};

class gradient : public artist {
public:
	gradient();
	~gradient();
	gradient(int, int, const std::vector<int>&);
	char mapper(int, int);
};