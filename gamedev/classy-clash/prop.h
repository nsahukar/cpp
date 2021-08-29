#include "raylib.h"

class Prop {
	public:
		Prop(Texture2D propTexture, Vector2 pos);
		void render(Vector2 knightMove);
		Rectangle getCollisionRec(Vector2 knightMove);
		void unload();
	private:
		Texture2D texture;
		Vector2 position{};
		float scale{4.f};
};
