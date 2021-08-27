#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdlib>

class Character {
	public:
	private:
};

int main() {
	// window dimensions
	const int windowWidth = 384;
	const int windowHeight = 384;

	// initialize window
	InitWindow(windowWidth, windowHeight, "Classy Clash");

	// drawing scale
	const float scale = 4.0f;

	// defining 'map' texture
	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap.png");
	// map position
	Vector2 mapPos{};
	// map speed
	const float mapVel = 4.0;

	// defining 'knight' texture
	Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D knightRun = LoadTexture("characters/knight_run_spritesheet.png");
	Texture2D knight = knightIdle;
	// knight source
	Rectangle knightSrc{
		0.0f,
		0.0f,
		(float)knight.width/6.0f,
		(float)knight.height
	};
	// knight destination
	Rectangle knightDest{
		windowWidth/2.0f - scale * (0.5f * knightSrc.width),
		windowHeight/2.0f - scale * (0.5f * knightSrc.height),
		scale * knightSrc.width,
		scale * knightSrc.height
	};
	// knight position
	Vector2 knightPos{
		knightDest.x,
		knightDest.y
	};
	// knight animation vars
	int knightFrame = 0;
	const int knightMaxFrame = 6;
	float knightRunningTime{};
	const float knightUpdateTime = 1.f/12.f;


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// delta time (time since last frame)
		const float dT = GetFrameTime();

		// begin drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// movement with keys
		Vector2 direction{};
		if (IsKeyDown(KEY_A)) direction.x -= 1.0;
		if (IsKeyDown(KEY_D)) direction.x += 1.0;
		if (IsKeyDown(KEY_W)) direction.y -= 1.0;
		if (IsKeyDown(KEY_S)) direction.y += 1.0;
		
		// configuring vars based on direction
		if (Vector2Length(direction) != 0.f) {
			// set knight to run
			knight = knightRun;
			// moving map
			mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), mapVel));
			// change kight's face direction based on direction
			// +1 -> right
			// -1 -> left
			if (direction.x < 0.f) {
				knightSrc.width = -1.f * abs(knightSrc.width);
			} else {
				knightSrc.width = 1.f * abs(knightSrc.width);
			}
		} else {
			// set knight to idle
			knight = knightIdle;
		}

		// draw map
		DrawTextureEx(map, mapPos, 0.0f, scale, WHITE);

		// animate knight
		knightRunningTime += dT;
		if (knightRunningTime >= knightUpdateTime) {
			// reset running time
			knightRunningTime = 0.f;
			// jump to next frame in sprite
			knightFrame++;
			if (knightFrame > knightMaxFrame) knightFrame = 0;
			knightSrc.x = knightFrame * knightSrc.width;
		}
		// draw knight
		DrawTexturePro(knight, knightSrc, knightDest, Vector2{}, 0.0f, WHITE);

		// end drawing
		EndDrawing();
	}

	UnloadTexture(map);
	UnloadTexture(knightIdle);
	UnloadTexture(knightRun);
	UnloadTexture(knight);
	CloseWindow();
}
