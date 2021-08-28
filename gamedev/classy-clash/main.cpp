#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdlib>

class Character {
	public:
		Character(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight, float scale) {
			idle = idleTexture;
			run = runTexture;
			texture = idle;
			setSource(frames);
			setDestination(windowWidth, windowHeight, scale);
		}
		void setSpeed(float val);
		Vector2 getPosition();
		void tick(float dT, float updateTime);
		void draw();
		void unloadTextures();
	private:
		Texture2D idle;
		Texture2D run;
		Texture2D texture;
		Rectangle source{};
		Rectangle destination{};
		Vector2 position{};
		int frame{};
		int maxFrame{};
		float runningTime{};
		float speed{4.f};

		// void setTexture(int type);
		void setIdle(Texture2D idleTexture);
		void setRun(Texture2D runTexture);
		void setSource(int frames);
		void setDestination(int windowWidth, int windowHeight, float scale);
		void setDirection(float leftRight);
		void move();
		void animate(float dT, float updateTime);
};

void Character::setIdle(Texture2D idleTexture) {
	idle = idleTexture;
}

void Character::setRun(Texture2D runTexture) {
	run = runTexture;
}

void Character::setSource(int frames) {
	maxFrame = frames;
	source.width = (float)texture.width/(float)maxFrame;
	source.height = (float)texture.height;
}

void Character::setDestination(int windowWidth, int windowHeight, float scale) {
	destination.x = windowWidth/2.0f - scale * (0.5f * source.width);
	destination.y = windowHeight/2.0f - scale * (0.5f * source.height);
	destination.width = scale * source.width;
	destination.height = scale * source.height;
}

void Character::setDirection(float leftRight) {
	source.width = leftRight * abs(source.width);
}

void Character::setSpeed(float val) {
	speed = val;
}

Vector2 Character::getPosition() {
	return position;
}

void Character::move() {
	// movement with keys
	Vector2 direction{};
	if (IsKeyDown(KEY_A)) direction.x -= 1.0;
	if (IsKeyDown(KEY_D)) direction.x += 1.0;
	if (IsKeyDown(KEY_W)) direction.y -= 1.0;
	if (IsKeyDown(KEY_S)) direction.y += 1.0;
	
	// configuring vars based on direction
	if (Vector2Length(direction) != 0.f) {
		// moving character
		position = Vector2Add(position, Vector2Scale(Vector2Normalize(direction), speed));
		// change kight's face direction based on direction
		// +1 -> right
		// -1 -> left
		if (direction.x < 0.f) {
			setDirection(-1.f);
		} else {
			setDirection(1.f);
		}
		// set knight to run
		texture = run;
	} else {
		// set knight to idle
		texture = idle;
	}
}

void Character::animate(float dT, float updateTime) {
	runningTime += dT;
	if (runningTime >= updateTime) {
		// reset running time
		runningTime = 0.f;
		// jump to next frame in sprite
		frame++;
		if (frame > maxFrame) frame = 0;
		source.x = frame * source.width;
	}
}

void Character::tick(float dT, float updateTime) {
	move();
	animate(dT, updateTime);
}

void Character::draw() {
	DrawTexturePro(texture, source, destination, Vector2{}, 0.0f, WHITE);
}

void Character::unloadTextures() {
	UnloadTexture(idle);
	UnloadTexture(run);
	UnloadTexture(texture);
}

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

	// defining 'knight' texture
	Character knight{
		LoadTexture("characters/knight_idle_spritesheet.png"),
		LoadTexture("characters/knight_run_spritesheet.png"),
		6,
		windowWidth,
		windowHeight,
		scale
	};


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// delta time (time since last frame)
		const float dT = GetFrameTime();

		// begin drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// make the knight tick
		knight.tick(dT, 1.f/12.f);

		// draw map
		mapPos = Vector2Scale(knight.getPosition(), -1.f);
		DrawTextureEx(map, mapPos, 0.0f, scale, WHITE);

		// draw knight
		knight.draw();

		// end drawing
		EndDrawing();
	}

	UnloadTexture(map);
	knight.unloadTextures();
	CloseWindow();
}
