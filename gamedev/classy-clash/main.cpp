#include "raylib.h"

int main() {
	// window dimensions
	const int windowWidth = 384;
	const int windowHeight = 384;

	// initialize window
	InitWindow(windowWidth, windowHeight, "Classy Clash");

	// defining 'map' texture
	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap.png");
	// map position
	Vector2 mapPos{0.0, 0.0};

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// begin drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// draw map
		DrawTextureEx(map, mapPos, 0.0, 1.0, WHITE);

		// end drawing
		EndDrawing();
	}

	UnloadTexture(map);
	CloseWindow();
}
