#include "Hex.h"
#include <unordered_map>
#include <SDL2/SDL.h>
#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

int main(/*int argc, char** argv*/) {
	SDL_Point WINDOW_SIZE = {1280, 600};
	SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
	//SDL_Surface* surface = NULL;	
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		return -1;
	}
	window = SDL_CreateWindow(
		"SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_SIZE.x,
		WINDOW_SIZE.y,
		SDL_WINDOW_SHOWN |
		SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_MAXIMIZED
	);
	
	if(window == NULL) {
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return -1;
	}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
		cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return -1;
	}
	
	//surface = SDL_GetWindowSurface(window);
	SDL_GetWindowSize(window, &WINDOW_SIZE.x, &WINDOW_SIZE.y);
	int i = 0;
	int inc = 1;
	SDL_bool done = SDL_FALSE;
	
	/*unordered_map<Hex, float> heights;
	heights[Hex(1, -2, 3)] = 4.3;
	cout << heights[Hex(1, -2, 3)];
	unordered_set<Hex> map;
	for (int q = -map_radius; q <= map_radius; q++) {
	    int r1 = max(-map_radius, -q - map_radius);
	    int r2 = min(map_radius, -q + map_radius);
	    for (int r = r1; r <= r2; r++) {
	        map.insert(Hex(q, r, -q-r));
	    }
	}*/
	
	/*unordered_set<Hex> map;
	for (int r = 0; r < map_height; r++) {
	    int r_offset = floor(r/2); // or r>>1
	    for (int q = -r_offset; q < map_width - r_offset; q++) {
	        map.insert(Hex(q, r, -q-r));
	    }
	}*/
	
	Hex h(0, 0, 0);
	//cout << h.hex_center().x << ", " << h.hex_center().y << endl;
	
	while (!done) {
		SDL_Event event;
		//SDL_SetWindowSize(window, i, i);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		
		//SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
		//SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
		//SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
		SDL_RenderDrawLine(renderer, i, WINDOW_SIZE.y - i, WINDOW_SIZE.x - i, i);
		SDL_RenderDrawLine(renderer, i, i, WINDOW_SIZE.x - i, WINDOW_SIZE.y - i);
		
		h.draw(renderer, WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
		for (int k = 0; k < 6; k++) {
			h.hex_neighbor(k).draw(renderer, WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
			for (int j = 0; j < 6; j++) {
				h.hex_neighbor(k).hex_neighbor(j).draw(renderer, WINDOW_SIZE.x / 2, WINDOW_SIZE.y / 2);
			}
		}
		
		SDL_RenderPresent(renderer);
		
		i += inc;
		if (i > WINDOW_SIZE.y || i < 0) {
			inc = -inc;
			i += inc;
		}
		
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				cout << "Exiting!\n";
				done = SDL_TRUE;
			}
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
				WINDOW_SIZE = {event.window.data1, event.window.data2};
            }
		}
		
		/*SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		
		SDL_UpdateWindowSurface(window);
		SDL_Delay(1000/150);*/
	}
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
