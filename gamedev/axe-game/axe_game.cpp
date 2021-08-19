#include "raylib.h"

int main()
{
	// window dimensions
	int width = 800;
	int height = 540;
	InitWindow(width, height, "Nikhil's Window");

	// circle coordinates
	int circle_x{200};
	int circle_y{200};
	// circle radius
	int circle_radius{25};
	// circle edges
	int l_circle_x{circle_x - circle_radius};
	int r_circle_x{circle_x + circle_radius};
	int u_circle_y{circle_y - circle_radius};
	int b_circle_y{circle_y + circle_radius};

	// axe coordinates
	int axe_x{width/2};
	int axe_y{0};
	// axe length
	int axe_length{50};
	// axe edges
	int l_axe_x{axe_x};
	int r_axe_x{axe_x + axe_length};
	int u_axe_y{axe_y};
	int b_axe_y{axe_y + axe_length};
	// axe direction
	int axe_direction{10};

	// collision var
	bool collision_with_axe = 
		b_axe_y >= u_circle_y && 
		u_axe_y <= b_circle_y && 
		l_axe_x <= r_circle_x && 
		r_axe_x >= l_circle_x;

	// setting FPS to 60
	SetTargetFPS(60);
	// Window operations and drawing on canvas
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		if (collision_with_axe) {
			DrawText("Game Over!", width/2 - 55, height/2, 20, RED);
		} else {
			// Game logic begins

			// CIRCLE
			// Update cirlce edges
			l_circle_x = circle_x - circle_radius;
			r_circle_x = circle_x + circle_radius;
			u_circle_y = circle_y - circle_radius;
			b_circle_y = circle_y + circle_radius;
			// Drawing a circle of radius 25
			DrawCircle(circle_x, circle_y, circle_radius, BLUE);
			// Moving the circle to right by 10 point on pressing 'D' key
			if (IsKeyDown(KEY_D) && circle_x < width) {
				circle_x += 10;
			}
			// Moving the circle to left by 10 point on pressing 'A' key
			if (IsKeyDown(KEY_A) && circle_x > 0) {
				circle_x -= 10;
			}

			// AXE
			// Updating axe edges
			l_axe_x = axe_x;
			r_axe_x = axe_x + axe_length;
			u_axe_y = axe_y;
			b_axe_y = axe_y + axe_length;
			// Drawing a rectangle (axe) of width and height 50
			DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);
			// Moving the axe
			axe_y += axe_direction;
			if (axe_y > height || axe_y < 0) {
				axe_direction = -axe_direction;
			}

			// Updating collision var
			collision_with_axe = 
				b_axe_y >= u_circle_y && 
				u_axe_y <= b_circle_y && 
				l_axe_x <= r_circle_x && 
				r_axe_x >= l_circle_x;
			
			// Game logic ends
		}

		EndDrawing();
	}
	CloseWindow();
}
