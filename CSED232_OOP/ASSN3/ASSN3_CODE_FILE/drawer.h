#pragma once
#include<string>
#include "artist.h"
class drawer {
protected:
	int wid;
	int hei;
	std::vector<char> map;
	artist* art;
public:
	drawer();
	~drawer();
	drawer(artist*);
	virtual std::string draw();
};

class downsample : public drawer {
public:
	downsample();
	~downsample();
	downsample(artist*);
	std::string draw();
};

class upsample : public drawer {
public:
	upsample();
	~upsample();
	upsample(artist*);
	std::string draw();
};

class scale : public drawer {
private:
	int x;
	int y;
public:
	scale();
	~scale();
	scale(artist*, int, int);
	std::string draw();
};