#include "raylib.h"

int main() {
	// Window dimensions
	int width = 400;
	int height = 200;
	// Initialize window
	InitWindow(width, height, "Daiper Dasher");

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);


		EndDrawing();
	}
}
