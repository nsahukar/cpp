#include "raylib.h"

int main() {
	// window dimensions
	const int windowWidth = 512;
	const int windowHeight = 380;
	// initialize the window
	InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

	// rectangle dimensions
	const int rectWidth = 50;
	const int rectHeight = 80;
	// rectangle ground position
	const int rectGroundPosY{windowHeight - rectHeight};
	// rectangle jump velocity
	const int rectJumpVel = -20;
	// rectangle position
	int rectPosY{rectGroundPosY};
	// var to check if rectangle is in air
	bool rectIsInAir{};

	// rectangle velocity (pixels/frame)
	int rectVelocity{0};

	// acceleration due to gravity (pixels/frame)/frame
	const int gravity{1};


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// start drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// ground check for rectangle,
		if (rectPosY >= rectGroundPosY) {
			// setting velocity to zero, rectangle is on the ground
			rectVelocity = 0;
			rectIsInAir = false;
		} else {
			// applying gravity, rectangle is in the air
			rectVelocity += gravity;
			rectIsInAir = true;
		}
		// make rectangle jump on spacebar press,
		// only when it is on the ground (avoid air jumping)
		if (IsKeyPressed(KEY_SPACE) && !rectIsInAir) {
			rectVelocity += rectJumpVel;
		}
		// move rectangle with given velocity
		rectPosY += rectVelocity;
		// draw rectangle
		DrawRectangle(windowWidth/2, rectPosY, rectWidth, rectHeight, BLUE);

		// stop drawing
		EndDrawing();
	}
	CloseWindow();
}
