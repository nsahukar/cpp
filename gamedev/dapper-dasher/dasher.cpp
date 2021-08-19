#include "raylib.h"

int main() {
	// window dimensions
	const int windowWidth = 512;
	const int windowHeight = 380;
	// initialize the window
	InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

	// defining 'scarfy' texture
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	Rectangle scarfyRec;
	scarfyRec.width = scarfy.width/6;
	scarfyRec.height = scarfy.height;
	scarfyRec.x = 0;
	scarfyRec.y = 0;
	Vector2 scarfyPos;
	scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
	scarfyPos.y = windowHeight - scarfyRec.height;
	// scarfy ground position
	const int scarfyGroundPosY = windowHeight - scarfyRec.height;
	// sacrfy jump velocity (pixels/sec)
	const int scarfyJumpVel = -600;
	// var to check if scarfy is in air
	bool scarfyIsInAir;
	// scarfy velocity (pixels/frame)
	int scarfyVelocity = 0;
	// scarfy texture animation frame
	int scarfyRecFrame = 0;
	// update time for scarfy animation frame
	const float scarfyUpdateTime = 1.0 / 10.0;
	// running time for scarfy animation frame
	float scarfyRunningTime = 0;

	// acceleration due to gravity (pixels/sec)/sec
	const int gravity = 1000;


	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		// start drawing
		BeginDrawing();
		ClearBackground(WHITE);

		// delta time (time since last frame)
		const float dT = GetFrameTime();

		// ground check for sacrfy,
		if (scarfyPos.y >= scarfyGroundPosY) {
			// setting velocity to zero, sacrfy is on the ground
			scarfyVelocity = 0;
			scarfyIsInAir = false;
		} else {
			// applying gravity, sacrfy is in the air
			scarfyVelocity += gravity * dT;
			scarfyIsInAir = true;
		}
		// make scarfy jump on spacebar press,
		// only when it is on the ground (avoid air jumping)
		if (IsKeyPressed(KEY_SPACE) && !scarfyIsInAir) {
			scarfyVelocity += scarfyJumpVel;
		}
		// move scarfy with given velocity
		scarfyPos.y += scarfyVelocity * dT;

		// animating scarfy by updating animation frame
		scarfyRunningTime += dT;
		if (scarfyRunningTime >= scarfyUpdateTime) {
			// reset scarfy running time
			scarfyRunningTime = 0.0;
			// jump to next frame in sprite
			scarfyRec.x = scarfyRecFrame * scarfyRec.width;
			scarfyRecFrame++;
			// reset frame to zero if it crosses its maximum
			if (scarfyRecFrame > 5) {
				scarfyRecFrame = 0;
			}
		}

		// draw 2D texture scarfy
		DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

		// stop drawing
		EndDrawing();
	}
	UnloadTexture(scarfy);
	CloseWindow();
}
