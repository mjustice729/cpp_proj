// include stuff
#include<SDL.h>
#include<stdio.h>
#include<string>

// DECLARATIONS ///////////////////////////////////////////////////////////////////////////
enum AllSurfaces {
	SURFACE_HOME_SCREEN,
	SURFACE_ACCEPT_JOB,
	SURFACE_TOTAL, // keep this at end to keep track of how many surfaces used
};

//Screen dimension constants
const int SCREEN_WIDTH = 820;
const int SCREEN_HEIGHT = 530;

SDL_Surface* gSurfaces[SURFACE_TOTAL];

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

// current displayed images
SDL_Surface* currentSurface = NULL;


// starts up SDL and creates window
bool init();

// loads an image to the surface
SDL_Surface* loadSurface(std::string path);

// loads all media
bool loadMedia();

//frees media and shuts down SDL
void close();

// FUNCTIONS //////////////////////////////////////////////////////////////////////////////

bool init() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

		}
	}

	return success;
}

SDL_Surface* loadSurface(std::string path) {
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

bool loadMedia() {
	bool success = true;
	//std::string cwd = "C:\\Users\\Miles\\Desktop\\Projects\\cpp_proj\\adventures_of_fonn\\x64\\Debug";

	gSurfaces[SURFACE_HOME_SCREEN] = loadSurface("Resource Files/welcometoubc2.bmp");
	if (gSurfaces[SURFACE_HOME_SCREEN] == NULL) {
		printf("Failed to load home screen image\n");
		success = false;
	}

	gSurfaces[SURFACE_ACCEPT_JOB] = loadSurface("Resource Files/acceptjob.bmp");
	if (gSurfaces[SURFACE_ACCEPT_JOB] == NULL) {
		printf("Failed to load accept job image\n");
		success = false;
	}

	return success;
}


void close() {
	//deallocate surface
	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

// MAIN //////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
	// initialize
	if (!init()) {
		printf("failed to init");
	}
	else {
		if (!loadMedia()) {
			printf("failed to load media");
		}
		else {
			printf("media loaded uwu");

			//Set default current surface
			currentSurface = gSurfaces[SURFACE_HOME_SCREEN];
			//apply the image
			SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);

			//update surface
			SDL_UpdateWindowSurface(window);

			SDL_Delay(2000);

			SDL_Rect plcmnt;
			plcmnt.x = 95;
			plcmnt.y = 200;
			plcmnt.w = 630;
			plcmnt.h = 188;

			currentSurface = gSurfaces[SURFACE_ACCEPT_JOB];
			SDL_BlitSurface(currentSurface, NULL, screenSurface, &plcmnt);
			SDL_UpdateWindowSurface(window);
		}
	}

	// run game
	SDL_Delay(5000);

	return 0;
}