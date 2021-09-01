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
	BaseCharacter::move();

	// enemy AI - move towards target
	// Steps -
	// 	1. Get target position... targetPos = target->screenPos - screenPos
	// 	2. Normalize target position... targetPos = norm(targetPos)
	// 	3. Multiply speed to target position... targetPos = targetPos * speed
	// 	4. Add target position to position... position = position + targetPos
	Vector2 targetPos = Vector2Subtract(target->getScreenPos(), getScreenPos());
	targetPos = Vector2Scale(Vector2Normalize(targetPos), speed);
	position = Vector2Add(position, targetPos);

	// updating the enemy screen position w.r.t target's movement
	Vector2 screenPos = Vector2Subtract(position, target->getMovement());
	destination.x = screenPos.x;
	destination.y = screenPos.y;
}
