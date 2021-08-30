#include "character.h"
#include "raymath.h"


/* public methods */

Character::Character(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight) {
	idle = idleTexture;
	run = runTexture;
	texture = idle;

	setSource(frames);
	setDestination(windowWidth, windowHeight);
}


/* protected methods */

void Character::setDestination(int windowWidth, int windowHeight) {
	BaseCharacter::setDestination(windowWidth, windowHeight);
	destination.x = windowWidth/2.0f - scale * (0.5f * source.width);
	destination.y = windowHeight/2.0f - scale * (0.5f * source.height);
}

void Character::move() {
	BaseCharacter::move();

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
