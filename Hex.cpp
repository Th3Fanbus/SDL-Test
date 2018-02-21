#include "Hex.h"

Hex::Hex(int _q, int _r, int _s) {
	assert(_q + _r + _s == 0);
	q = _q;
	r = _r;
	s = _s;
}

bool operator == (Hex a, Hex b) {
	return a.q == b.q && a.r == b.r && a.s == b.s;
}

bool operator != (Hex a, Hex b) {
	return !(a == b);
}

Hex operator + (Hex a, Hex b) {
    return Hex(a.q + b.q, a.r + b.r, a.s + b.s);
}

Hex operator - (Hex a, Hex b) {
    return Hex(a.q - b.q, a.r - b.r, a.s - b.s);
}

Hex operator * (Hex a, int k) {
    return Hex(a.q * k, a.r * k, a.s * k);
}

int Hex::hex_length() {
    return (int)(abs(q) + abs(r) + abs(s) / 2);
}

int Hex::hex_distance(Hex a) {
    return (*this - a).hex_length();
}

Hex Hex::hex_direction(int direction /* 0 to 5 */) {
    assert (0 <= direction && direction < 6);
    return hex_directions[direction];
}

Hex Hex::hex_neighbor(int direction) {
    return *this + hex_direction(direction);
}

SDL_Point Hex::hex_center(int _x, int _y) {
	double angle = 2.0 * M_PI / 6.0;
	int x = _x + (hex_size.x * cos(angle) * 3 * q);
	int y = _y + (hex_size.y * sin(angle) * (2 * r + q));
	return {x, y};
}

SDL_Point Hex::hex_corner_offset(int corner, int _x, int _y) {
    double angle = 2.0 * M_PI * (corner) / 6;
    return {(int)(hex_size.x * cos(angle)), (int)(hex_size.y * sin(angle))};
}

vector<SDL_Point> Hex::polygon_corners(int _x, int _y) {
    vector<SDL_Point> corners = {};
    SDL_Point center = hex_center(_x, _y);
    for (int i = 0; i < 6; i++) {
        SDL_Point offset = hex_corner_offset(i, _x, _y);
        corners.push_back({center.x + offset.x, center.y + offset.y});
    }
    return corners;
}

void Hex::draw(SDL_Renderer *& renderer, int _x, int _y) {
	vector<SDL_Point> corners = polygon_corners(_x, _y);
	corners.push_back(corners[0]);
	for (unsigned i = 0; i < 6; i++) {
		SDL_RenderDrawLine(renderer, corners[i].x, corners[i].y, corners[i + 1].x, corners[i + 1].y);
	}
}
