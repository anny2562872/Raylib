#include <raylib.h> 
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" 
#include <stdio.h> 
#include <string.h>

int main(void){

typedef struct {
	Vector2 postion;
	float speed;
} actor;

const float Height = GetMonitorHeight(0);
const float Width = GetMonitorWidth(0);
float VertVel = 0;
float HoriVel = 0;
actor Player = {{0,0}, 60};
float stamina = 0;
float Damping = 0.9;
Camera2D camera = {0};
camera.zoom = 1.0f;
bool showCords = 0;
bool usingSprint;
InitWindow(Width, Height, "Test window");
SetTargetFPS(60);
while (!WindowShouldClose()){
	// TO-DO:
	// - make the camera drag behind the player
	camera.target = (Vector2){Player.postion.x,Player.postion.y};
	camera.offset = (Vector2){GetMonitorWidth(0)/2.0f - 25.0f,GetMonitorHeight(0)/2.0f - 25.0f};
	// Checking for player input
	if (IsKeyDown(KEY_W)){VertVel -= 1;}
	if (IsKeyDown(KEY_S)){VertVel += 1;}
	if (IsKeyDown(KEY_D)){HoriVel += 1;}
	if (IsKeyDown(KEY_A)){HoriVel -= 1;}
	usingSprint = false;
	Player.speed = 60;
	if (IsKeyDown(KEY_LEFT_SHIFT)){
		usingSprint = true;
		if (stamina>0){ stamina -= 0.5; Player.speed += 20;}
	}

	// Apply velocity to player postion
	Player.postion.x += GetFrameTime()*HoriVel*Player.speed; //Move player in the Vertical direction with deltatime
	Player.postion.y += GetFrameTime()*VertVel*Player.speed; //Move player in the Horizontal direction with deltatime
	// Damping the velocities
	VertVel *= Damping;
	HoriVel *= Damping;

	if ((stamina<5) & !usingSprint){stamina += 0.1;}
	else if((stamina<25) & !usingSprint){stamina += 0.25;}
	//Show cords when tab is pressed
	if (IsKeyPressed(KEY_TAB)){ showCords = !showCords; }
	// Drawing to the screen
	BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);
			DrawRectangle(0,0,100,100,GRAY);
			DrawRectangle(Player.postion.x,Player.postion.y,50,50,RED);
		EndMode2D();

		if (showCords){
			char StrPosX[128];
			char StrPosY[128];
			char StrSpeed[128];
			char StrStamina[128];
			snprintf(StrSpeed,sizeof(StrSpeed),"Speed: %.2f",Player.speed);
			snprintf(StrStamina,sizeof(StrStamina),"Stamina: %.2f",stamina);
			snprintf(StrPosX,sizeof(StrPosX),"x: %.2f",Player.postion.x);
			snprintf(StrPosY,sizeof(StrPosY),"y: %.2f",Player.postion.y);
			DrawText(StrSpeed,10,120,50,BLACK);
			DrawText(StrStamina,10,180,50,BLACK);
			DrawText(StrPosY,10,60,50,BLACK);
			DrawText(StrPosX,10,10,50,BLACK);
		}
		GuiToggle((Rectangle){GetMonitorWidth(0)-120-10,10,120,50},TextFormat("Show Cordinates"), &showCords);

	EndDrawing();
} // Runtime


} // Main
