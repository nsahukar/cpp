#include "enemy.h"
#include "raylib.h"
#include "raymath.h"


/* public methods */

Enemy::Enemy(Texture2D idleTexture, Texture2D runTexture, int frames, Vector2 pos, float speed):
	BaseCharacter::BaseCharacter(idleTexture, runTexture, frames, pos)
{
	this->speed = speed;
}

void Enemy::tick(float dT, float updateTime) {
	BaseCharacter::tick(dT, updateTime);

	// check enemy's collision with target
	// damage target, if so.
	if (isAlive() && CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())) {
		target->takeDamage(damagePerSec * dT);
	}
}

void Enemy::setTarget(Character *character) {
	target = character;
}


/* protected methods */

void Enemy::move() {
	// enemy AI - move towards target
	velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
	// stop enemy chase if velocity length less than chase radius
	if (Vector2Length(velocity) < chaseRadius) velocity = {};
	// updating the enemy screen position w.r.t target's movement
	setScreenPos(Vector2Subtract(position, target->getPos()));
	BaseCharacter::move();
}
