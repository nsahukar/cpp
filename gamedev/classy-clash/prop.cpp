#include "prop.h"
#include "raylib.h"
#include "raymath.h"

Prop::Prop(Texture2D propTexture, Vector2 pos):
	texture(propTexture),
	position(pos)
{
}

void Prop::render(Vector2 knightMove) {
	// update prop screen position w.r.t. knight
	Vector2 screenPos = Vector2Subtract(position, knightMove);
	// draw prop texture
	DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightMove) {
	// update prop screen position w.r.t. knight
	Vector2 screenPos = Vector2Subtract(position, knightMove);
	// return prop collision rectangle
	return Rectangle{
		screenPos.x,
		screenPos.y,
		texture.width * scale,
		texture.height * scale
	};
}

void Prop::unload() {
	UnloadTexture(texture);
}
