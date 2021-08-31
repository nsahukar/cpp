#include "character.h"
#include "raylib.h"
#include "raymath.h"


/* public methods */

Character::Character(Texture2D idleTexture, Texture2D runTexture, int frames, int windowWidth, int windowHeight):
	BaseCharacter::BaseCharacter(idleTexture, runTexture, frames, windowWidth, windowHeight)
{
}


/* protected methods */

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
