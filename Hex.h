#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include <math.h>

using namespace std;

class Hex {
private:
	SDL_Point hex_size{50, 50};
public:
	int q;
	int r;
	int s;
	Hex(int _q, int _r, int _s);
	int hex_length();
	int hex_distance(Hex a);
	static Hex hex_direction(int direction);
	Hex hex_neighbor(int direction);
	SDL_Point hex_center(int _x, int _y);
	SDL_Point hex_corner_offset(int corner, int _x, int _y);
	vector<SDL_Point> polygon_corners(int _x, int _y);
	void draw(SDL_Renderer *& renderer, int _x, int _y);
};

const vector<Hex> hex_directions = {
	Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
	Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
};
