#include "raylib.h"
#include "raymath.h"
#include "character.h"

int main() {
	// window dimensions
	const int windowWidth = 384;
	const int windowHeight = 384;

	// initialize window
	InitWindow(windowWidth, windowHeight, "Classy Clash");

	// defining 'map' texture
	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap.png");
	// map position
	Vector2 mapPos{};
	// drawing scale
	const float mapScale = 4.0f;

	// defining 'knight' texture
	Character knight{
		LoadTexture("characters/knight_idle_spritesheet.png"),
		LoadTexture("characters/knight_run_spritesheet.png"),
		6,
		windowWidth,
		windowHeight
	};


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// delta time (time since last frame)
		const float dT = GetFrameTime();

		// begin drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// draw map
		mapPos = Vector2Scale(knight.getMovement(), -1.f);
		DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

		// make the knight tick
		knight.tick(dT, 1.f/12.f);

		// checking for movement off limits (map bounds)
		// undoing movement, if so.
		if (knight.getMovement().x < 0.f ||
			knight.getMovement().y < 0.f ||
			knight.getMovement().x + windowWidth > mapScale * map.width ||
			knight.getMovement().y + windowHeight > mapScale * map.height)
		{
			knight.undoMovement();
		}

		// end drawing
		EndDrawing();
	}

	UnloadTexture(map);
	knight.unloadTextures();
	CloseWindow();
}
