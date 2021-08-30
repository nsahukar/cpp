#include "base_character.h"
#include "raymath.h"
#include <cmath>


/* public methods */

BaseCharacter::BaseCharacter() {
}

void BaseCharacter::setScale(float val) {
	scale = val;
}

void BaseCharacter::setSpeed(float val) {
	speed = val;
}

Vector2 BaseCharacter::getMovement() {
	return movement;
}

void BaseCharacter::tick(float dT, float updateTime) {
	move();
	animate(dT, updateTime);
	draw();
}

void BaseCharacter::undoMovement() {
	movement = lastMovement;
}

Rectangle BaseCharacter::getCollisionRec() {
	return Rectangle{
		destination.x,
		destination.y,
		destination.width,
		destination.height
	};
}

void BaseCharacter::unload() {
	UnloadTexture(idle);
	UnloadTexture(run);
	UnloadTexture(texture);
}


/* protected methods */

void BaseCharacter::setSource(int frames) {
	maxFrame = frames;
	source.width = static_cast<float>(texture.width) / static_cast<float>(maxFrame);
	source.height = static_cast<float>(texture.height);
}

void BaseCharacter::setDestination(int windowWidth, int windowHeight) {
	// destination.x = windowWidth/2.0f - scale * (0.5f * source.width);
	// destination.y = windowHeight/2.0f - scale * (0.5f * source.height);
	destination.width = scale * source.width;
	destination.height = scale * source.height;
}

void BaseCharacter::setDirection(float leftRight) {
	source.width = leftRight * abs(source.width);
}

void BaseCharacter::move() {
	// save last movement
	lastMovement = movement;
}

void BaseCharacter::animate(float dT, float updateTime) {
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

void BaseCharacter::draw() {
	DrawTexturePro(texture, source, destination, Vector2{}, 0.0f, WHITE);
}
