#include "raylib.h"
#include "raymath.h"
#include "prop.h"
#include "character.h"
#include "enemy.h"


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

	// defining 'prop' textures
	Prop props[2]{
		Prop{
			LoadTexture("nature_tileset/Rock.png"),
			Vector2{600.f, 300.f}
		},
		Prop{
			LoadTexture("nature_tileset/Log.png"),
			Vector2{400.f, 500.f}
		}
	};

	// defining character 'knight' texture
	Character knight{
		LoadTexture("characters/knight_idle_spritesheet.png"),
		LoadTexture("characters/knight_run_spritesheet.png"),
		6,
		windowWidth,
		windowHeight
	};

	// defining enemy 'goblin' texture
	Enemy goblin{
		LoadTexture("characters/goblin_idle_spritesheet.png"),
		LoadTexture("characters/goblin_run_spritesheet.png"),
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

		// draw props
		for (auto prop : props) prop.render(knight.getMovement());

		// make the knight tick
		knight.tick(dT, 1.f/12.f);

		// check for movement off limits (map bounds)
		// undoing knight movement, if so.
		if (knight.getMovement().x < 0.f ||
			knight.getMovement().y < 0.f ||
			knight.getMovement().x + windowWidth > mapScale * map.width ||
			knight.getMovement().y + windowHeight > mapScale * map.height)
		{
			knight.undoMovement();
		}

		// check for collision with props
		// undoing knight movement, if so.
		for (auto prop : props) {
			if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getMovement()))) {
				knight.undoMovement();
			}
		}

		// make the goblin tick
		goblin.tick(dT, 1.f/12.f);

		// end drawing
		EndDrawing();
	}

	UnloadTexture(map);
	for (auto prop : props) prop.unload();
	knight.unload();
	CloseWindow();
}
