#include "character.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>

Character::Character(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight):
	idle(idleTexture),
	run(runTexture)
{
	texture = idle;
	setSource(frames);
	setDestination(windowWidth, windowHeight);
}

void Character::setIdle(Texture2D idleTexture) {
	idle = idleTexture;
}

void Character::setRun(Texture2D runTexture) {
	run = runTexture;
}

void Character::setScale(float val) {
	scale = val;
}

void Character::setSource(int frames) {
	maxFrame = frames;
	source.width = static_cast<float>(texture.width) / static_cast<float>(maxFrame);
	source.height = static_cast<float>(texture.height);
}

void Character::setDestination(int windowWidth, int windowHeight) {
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

Vector2 Character::getMovement() {
	return movement;
}

void Character::move() {
	// save last movement
	lastMovement = movement;

	// movement with keys
	Vector2 direction{};
	if (IsKeyDown(KEY_A)) direction.x -= 1.0;
	if (IsKeyDown(KEY_D)) direction.x += 1.0;
	if (IsKeyDown(KEY_W)) direction.y -= 1.0;
	if (IsKeyDown(KEY_S)) direction.y += 1.0;
	
	// configuring vars based on direction
	if (Vector2Length(direction) != 0.f) {
		// moving character
		movement = Vector2Add(movement, Vector2Scale(Vector2Normalize(direction), speed));
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

void Character::draw() {
	DrawTexturePro(texture, source, destination, Vector2{}, 0.0f, WHITE);
}

void Character::tick(float dT, float updateTime) {
	move();
	animate(dT, updateTime);
	draw();
}

void Character::undoMovement() {
	movement = lastMovement;
}

Rectangle Character::getCollisionRec() {
	return Rectangle{
		destination.x,
		destination.y,
		destination.width,
		destination.height
	};
}

void Character::unload() {
	UnloadTexture(idle);
	UnloadTexture(run);
	UnloadTexture(texture);
}
