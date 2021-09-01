#include "enemy.h"
#include "raylib.h"
#include "raymath.h"


/* public methods */

Enemy::Enemy(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 pos):
	BaseCharacter::BaseCharacter(idleTexture, runTexture, frames, pos)
{
	speed = 3.f;
}

void Enemy::setTarget(Character *character) {
	target = character;
}

/* protected methods */

void Enemy::move() {
	// enemy AI - move towards target
	velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
	// updating the enemy screen position w.r.t target's movement
	setScreenPos(Vector2Subtract(position, target->getPos()));
	BaseCharacter::move();
}
