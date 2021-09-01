#include "base_character.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath>


/* public methods */

BaseCharacter::BaseCharacter(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 position):
	idle(idleTexture),
	run(runTexture)
{
	texture = idle;
	maxFrame = frames;
	calcTextureDimens();
	setPosition(position);
	setSource();
	setDestination();
}

BaseCharacter::BaseCharacter(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight):
	idle(idleTexture),
	run(runTexture)
{
	texture = idle;
	maxFrame = frames;
	calcTextureDimens();
	setPosition(calcPosition(windowWidth, windowHeight));
	setSource();
	setDestination();
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

Vector2 BaseCharacter::getScreenPos() {
	return Vector2{
		destination.x,
		destination.y
	};
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

void BaseCharacter::calcTextureDimens() {
	textureWidth = static_cast<float>(texture.width) / static_cast<float>(maxFrame);
	textureHeight = static_cast<float>(texture.height);
}

Vector2 BaseCharacter::calcPosition(int windowWidth, int windowHeight) {
	return Vector2{
		windowWidth/2.0f - scale * (0.5f * textureWidth),
		windowHeight/2.0f - scale * (0.5f * textureHeight)
	};
}

void BaseCharacter::setPosition(Vector2 pos) {
	position = pos;
}

void BaseCharacter::setSource() {
	source.width = textureWidth;
	source.height = textureHeight;
}

void BaseCharacter::setDestination() {
	destination.width = scale * textureWidth;
	destination.height = scale * textureHeight;
	destination.x = position.x;
	destination.y = position.y;
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
