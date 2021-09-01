#include "raylib.h"
#include "raymath.h"
#include "prop.h"
#include "character.h"
#include "enemy.h"
#include <string>


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
		LoadTexture("characters/weapon_sword.png"),
		windowWidth,
		windowHeight
	};

	// defining enemy 'goblin' texture
	Enemy goblin{
		LoadTexture("characters/goblin_idle_spritesheet.png"),
		LoadTexture("characters/goblin_run_spritesheet.png"),
		6,
		Vector2{600.f, 600.f},
		3.f
	};
	// defining enemy 'slime' texture
	Enemy slime{
		LoadTexture("characters/slime_idle_spritesheet.png"),
		LoadTexture("characters/slime_run_spritesheet.png"),
		6,
		Vector2{800.f, 200.f},
		2.f
	};
	Enemy* enemies[]{
		&goblin,
		&slime
	};
	// set 'knight' as enemy's target
	for (auto enemy: enemies) enemy->setTarget(&knight);


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// delta time (time since last frame)
		const float dT = GetFrameTime();

		// begin drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// draw map
		mapPos = Vector2Scale(knight.getPos(), -1.f);
		DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

		// draw props
		for (auto prop : props) prop.render(knight.getPos());

		// check if knight is alive
		// show knight's health, if alive
		// show GAME OVER!, if dead
		if (knight.isAlive()) {
			// show 'health' text
			std::string knightsHealth = "Health: ";
			knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
			DrawText(knightsHealth.c_str(), 85.f, 30.f, 40, RED);
		} else {
			// show 'GAME OVER!' text
			DrawText("Game Over!", 85.f, windowHeight/2, 40, RED);
			EndDrawing();
			continue;
		}

		// make the knight tick
		knight.tick(dT, 1.f/12.f);

		// check for movement off limits (map bounds)
		// undoing knight movement, if so.
		if (knight.getPos().x < 0.f ||
			knight.getPos().y < 0.f ||
			knight.getPos().x + windowWidth > mapScale * map.width ||
			knight.getPos().y + windowHeight > mapScale * map.height)
		{
			knight.undoMovement();
		}

		// check for knight's collision with props
		// undoing knight movement, if so.
		for (auto prop : props) {
			if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getPos()))) {
				knight.undoMovement();
			}
		}

		for (auto enemy: enemies) {
			// make the goblin tick
			enemy->tick(dT, 1.f/12.f);
		}

		// check for knight's sword collision with enemies
		// make enemy dead, if so.
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			for (auto enemy: enemies) {
				if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec())) {
					enemy->setAlive(false);
				}
			}
		}

		// end drawing
		EndDrawing();
	}

	UnloadTexture(map);
	for (auto prop : props) prop.unload();
	knight.unload();
	goblin.unload();
	CloseWindow();
}
