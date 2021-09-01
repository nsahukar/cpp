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
	// movement with keys
	if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
	if (IsKeyDown(KEY_D)) velocity.x += 1.0;
	if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
	if (IsKeyDown(KEY_S)) velocity.y += 1.0;
	BaseCharacter::move();
}
