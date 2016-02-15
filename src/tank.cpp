#include "tank.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//tank creation
Tank::Tank(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y)
{

//active the plater
	active = true;

	//set the player number 0 or 1
	playerNum = pNum;

	//set float for player speed
	speed = 200.0f;

	//tank to image
	playerPath = filePath + "tank.png";

	//load the surface into the texture
	texture = IMG_LoadTexture(renderer, playerPath.c_str());

	//check that the window was successfully created
	if(texture == NULL){
		//om the case that the window could not be made
		printf("Could not create window: %s\n", SDL_GetError());
	}

	//set the SDL_Rext X and Y for the player
	posRect.x = x;
	posRect.y = y;
	posRect.w = 64;
	posRect.h = 64;

	//set the movments floats to the players original x and y
	pos_X = x;
	pos_Y = y;

	//set the xdir and ydir
	xDir=0;
	yDir=0;


	//center of inamge rectangel
	center.x=32;
	center.y=32;

}


void Tank::Update(float deltaTime)
{
	//get the angle between the tank and the turret
	x=posRect.x = xDir;
	y=posRect.y = yDir;
	tankangle = atan2(yDir, xDir)*180/3.14;

	//ajust position floats based on speed direction of joystick and deltatime
	pos_X += (speed * xDir) * deltaTime;
	pos_Y += (speed * yDir) * deltaTime;


	//uypdate player positon wuth code to account for precision loss
	posRect.x=(int)(pos_X + 0.5f);
	posRect.y=(int)(pos_Y + 0.5f);

}


void Tank::Draw(SDL_Renderer *renderer)
{

	//draw the player texture using the cars texture and posRext
	SDL_RenderCopy(renderer,texture, NULL, &posRect);

}

void Tank::OnControllerButton(const SDL_ControllerButtonEvent event)
{



}

void Tank::OnControllerAxis(const SDL_ControllerAxisEvent event)
{
	// if the players number is 0 and the joystick axis is from joystick 0
	if(event.which == 0 && playerNum == 0)
	{
		//X axis
		if(event.axis ==0)
			{
			if(event.value <- JOYSTICK_DEAD_ZONE)
			{
				xDir = -1.0f;
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				xDir = 1.0f;
			}
			else
			{
			xDir = 0.0f;
			}
		}

		//Y axis
		if(event.axis ==1)
		{
			if(event.value <- JOYSTICK_DEAD_ZONE)
			{
				yDir = -1.0f;
			}
			else if (event.value>JOYSTICK_DEAD_ZONE)
			{
				yDir = 1.0f;
			}else
			{
				yDir = 0.0f;
			}
		}
	}
}
