#include "character.h"
#include <cstdio>
#include "raylib.h"
#include "raymath.h"
#include <cmath>


/* public methods */

Character::Character(Texture2D idleTexture, Texture2D runTexture, int frames, Texture2D weaponTexture, int windowWidth, int windowHeight):
	BaseCharacter::BaseCharacter(idleTexture, runTexture, frames, windowWidth, windowHeight),
	weapon(weaponTexture)
{
	setWeaponSource();
	setWeaponDestination();
	setWeaponDirection(1.f);
	drawWeapon();
}

void Character::unload() {
	BaseCharacter::unload();
	unloadWeapon();
}

Rectangle Character::getWeaponCollisionRec() const {
	return weaponCollisionRec;
}

float Character::getHealth() const {
	return health;
}

void Character::takeDamage(float damage) {
	health -= damage;
	if (health <= 0.f) setAlive(false);
}

/* protected methods */

void Character::setScreenPos(Vector2 pos) {
	BaseCharacter::setScreenPos(pos);
	setWeaponScreenPos(pos);
}

void Character::setDirection(float leftRight) {
	BaseCharacter::setDirection(leftRight);
	setWeaponDirection(leftRight);
}

void Character::move() {
	// movement with keys
	if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
	if (IsKeyDown(KEY_D)) velocity.x += 1.0;
	if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
	if (IsKeyDown(KEY_S)) velocity.y += 1.0;
	BaseCharacter::move();
	moveWeapon();
}

void Character::draw() {
	BaseCharacter::draw();
	drawWeapon();
}


/* private methods */

void Character::setWeaponScreenPos(Vector2 pos) {
	weaponDestination.x = pos.x + weaponOffset.x;
	weaponDestination.y = pos.y + weaponOffset.y;
}

void Character::setWeaponSource() {
	weaponSource.width = static_cast<float>(weapon.width);
	weaponSource.height = static_cast<float>(weapon.height);
}

void Character::setWeaponDestination() {
	weaponDestination.width = scale * weapon.width;
	weaponDestination.height = scale * weapon.height;
}

void Character::setWeaponDirection(float leftRight) {
	weaponSource.width = leftRight * abs(weaponSource.width);
	if (leftRight < 0.f) {
		// facing left, origin - bottom right
		weaponOrigin = {weapon.width * scale, weapon.height * scale};
		// hit and trial offset
		weaponOffset = {25.f, 55.f};
		// change weapon rotation on left mouse button
		IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? weaponRotation = -35.f : weaponRotation = 0.f;
	} else {
		// facing right, origin - bottom left
		weaponOrigin = {0.f, weapon.height * scale};
		// hit and trial offset
		weaponOffset = {35.f, 55.f};
		// change weapon rotation on left mouse button
		IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? weaponRotation = 35.f : weaponRotation = 0.f;
	}
	setWeaponScreenPos(getScreenPos());
	setWeaponCollisionRec(leftRight);
}

void Character::moveWeapon() {
}

void Character::drawWeapon() {
	DrawTexturePro(weapon, weaponSource, weaponDestination, weaponOrigin, weaponRotation, WHITE);

	// drawing destination rectangle lines
	DrawRectangleLines(
			weaponCollisionRec.x, 
			weaponCollisionRec.y, 
			weaponCollisionRec.width, 
			weaponCollisionRec.height, 
			RED
	);
}

void Character::setWeaponCollisionRec(float leftRight) {
	if (leftRight > 0.f) {
		// right
		weaponCollisionRec = {
			weaponDestination.x,
			weaponDestination.y - weapon.height * scale,
			weaponDestination.width,
			weaponDestination.height
		};
	} else {
		// left
		weaponCollisionRec = {
			weaponDestination.x - weapon.width * scale,
			weaponDestination.y - weapon.height * scale,
			weaponDestination.width,
			weaponDestination.height
		};
	}
}

void Character::unloadWeapon() {
	UnloadTexture(weapon);
}
