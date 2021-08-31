#include "enemy.h"
#include "raylib.h"
#include "raymath.h"


/* public methods */

Enemy::Enemy(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 pos):
	BaseCharacter::BaseCharacter(idleTexture, runTexture, frames, pos)
{
}

void Enemy::setTarget(Character *character) {
	target = character;
}

/* protected methods */

void Enemy::move() {
	BaseCharacter::move();

	// updating the enemy screen position w.r.t target's movement
	Vector2 screenPos = Vector2Subtract(position, target->getMovement());
	destination.x = screenPos.x;
	destination.y = screenPos.y;
}
