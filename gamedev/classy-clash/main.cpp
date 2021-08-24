#include "raylib.h"
#include "raymath.h"

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
	// map speed
	const float mapVel = 4.0;

	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// begin drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// moving map
		Vector2 direction{};
		if (IsKeyDown(KEY_A)) direction.x -= 1.0;
		if (IsKeyDown(KEY_D)) direction.x += 1.0;
		if (IsKeyDown(KEY_W)) direction.y -= 1.0;
		if (IsKeyDown(KEY_S)) direction.y += 1.0;
		// optimizing direction
		if (Vector2Length(direction) != 0.0) {
			mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), mapVel));
		}
		
		// draw map
		DrawTextureEx(map, mapPos, 0.0, 1.0, WHITE);

		// end drawing
		EndDrawing();
	}

	UnloadTexture(map);
	CloseWindow();
}
