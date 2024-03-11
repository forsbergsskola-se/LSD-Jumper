# LSD-Jumper (Latino Salsa Dancer - Jumper)
***
### Welcome to our little SDL project named LSD-Jumper!

Inspired by a game called Icy Tower :-)

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/63593adb-d53d-499c-bd6c-bb981022e431)

LSD-Jumper is a simple 2D game built using SDL (Simple DirectMedia Layer) library in C++. The game features a character running and jumping across clouds while trying not to fall into her death.

We chose SDL because it is a powerful cross-platform development library that provides low-level access to audio, keyboard, mouse, joystick, etc. The challenges were worth it, and with the knowledge that we gained, we can gladly keep working on more projects with SDL and C++.

Adding the libraries to our project went well, except for one confusion that we had with GitHub while both pushing the same things all over again, but eventually, we fixed it. We went through directories and linkers in our OpenGL course, which is why we found it quite easy to do.

We created classes and tried to keep the code as clean as possible. We used headers to declare our functions and the .cpp files to define them. 
***
One of the challenges we had was copying the files multiple times when including the headers. Using forward declaration solved the problem.

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/b25e4f61-83df-4281-b69f-51ae7e4c8b4b)
***
Uploading the textures using SDL_Texture*

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/e8334733-c36d-4ac8-a0e2-e76590e73c42)
***
Finding the path

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/8ba34d0a-4caa-486a-94cb-3fafe5b214b0)
***
The gravity and the velocity challenge where we tried to make our player jump smoothly and not just to teleport

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/7285ac0c-1905-4ce0-b8bc-e6418a6d399e)
***
Utilizing min() and SDL_GetTicks() enables precise time measurement in the game, ensuring smooth and consistent frame rates

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/5a791b12-66b6-4888-a878-2275841285a3)



***
## Clouds
First thing that we do with the clouds is load a texture
`cloud = application->GetTextureHandler()->CreateTexture("Assets/Textures/cloud.png");`
We are also getting the window's width and height, as well as cloud's dimensions with a little help of `SDL_QueryTexture`

To be complitely honest, we had a lot of difficulties with random cloud spawning. It was a real roller coaster ride with that one.
The original idea was to spawn the clouds in the middle of the screen with a random offset on an X-axis with a set Y-axis offset, but that didn't look or feel good in the game. It was just left and right jumping.
After that we tried to save the position of the last cloud and spawn the next one based on that last clouds position and then assign that newly spawned cloud to be the last cloud and spawn anothe cloud and so on... but that didn't work that well since a lot of clouds were getting stuck to the edge of the screen.
So we tried multiple solutions for it and we came up with this one...
```c++
bool Level::Create(Application* mainApplication)
{
	application = mainApplication;

	cloud = application->GetTextureHandler()->CreateTexture("Assets/Textures/cloud.png");
	if (!cloud)
		return false;

	const float windowWidth = (float)application->GetWindow()->GetWidth();
	const float windowHeight = (float)application->GetWindow()->GetHeight();

	int cloudWidth = 0;
	int cloudHeight = 0;
	SDL_QueryTexture(cloud, nullptr, nullptr, &cloudWidth, &cloudHeight);
	int halfCloudWidth = 0.5 * cloudWidth;
	// Seed the random number generator
	srand(time(0));

	const int numClouds = 5;

	renderRects.resize(numClouds);
	colliders.resize(numClouds);

	const int maxOffset = halfCloudWidth * 3;
	const int minOffset = -maxOffset;
	float previousCloudXPosition = (windowWidth * 0.5f) - (halfCloudWidth);
	float previousCloudYPosition = (float)(windowHeight - (cloudHeight * 2.0f));

	for (int i = 0; i < numClouds; i++)
	{
		const float colliderHeight = cloudHeight * 0.2f;

		if (i == 0)
		{
			renderRects[i] = { previousCloudXPosition, previousCloudYPosition, (float)cloudWidth, (float)cloudHeight };
			colliders[i] = { previousCloudXPosition, previousCloudYPosition + ((cloudHeight * 0.5f) - (colliderHeight * 0.5f)), (float)cloudWidth, colliderHeight };
		}

		else
		{
			const int curMin = std::max(0, (int)previousCloudXPosition + minOffset);
			const int curMax = std::min((int)windowWidth-cloudWidth, (int)previousCloudXPosition + maxOffset);

			const int xPosition = rand() % (curMax - curMin) + curMin;

			std::cout << "Cloud #" << i << " between " << curMin << " and " << curMax << ": " << xPosition << std::endl;

			renderRects[i] = { (float)xPosition, previousCloudYPosition, (float)cloudWidth, (float)cloudHeight };

			colliders[i] = { renderRects[i].x, renderRects[i].y + ((cloudHeight * 0.5f) - (colliderHeight * 0.5f)), (float)cloudWidth, colliderHeight };

			previousCloudXPosition = xPosition;
		}

		previousCloudYPosition -= (float)(cloudHeight * 2.5f);
	}

	return true;
}
```
As you can see, `const int maxOffset` and `const int minOffset` are both one and a half cloud. Which takes a big part in random spawining of the clouds. These values make sure that newly spawned clouds spawn relatively close to each other (maximum distance of 1.5 clouds to exact).
 The function spawns clouds with random X position within the offset limits. The first cloud is positioned at the center of the window, while soon-to-be-spawned clouds are randomly positioned within the limits.
 ***
Now, how did we manage to respawn those 5 clouds over and over again as soon as they leave the camera view? 
The answer is we relocated the first cloud (index 0 cloud) to be spawned based on the position on the last cloud spawned.
 ```c++
 void Level::Update(const SDL_FRect& cameraRect, const float deltaTime)
{
	const float windowWidth = (float)application->GetWindow()->GetWidth();
	bool anyCloudRespawned = false;

	for (int i = 0; i < renderRects.size(); i++)
	{
		SDL_FRect& renderRect = renderRects[i];
		SDL_FRect& collider = colliders[i];

		//CLOUDS FALLING - DOESN'T WORK
		//renderRect.y += cloudFallSpeed * deltaTime;
		//collider.y = (renderRect.y + (renderRect.h * 0.5f)) - (collider.h * 0.5f);

		if (renderRect.y > (cameraRect.y + cameraRect.h))
		{
			int lastIndex = (i - 1 + renderRects.size()) % renderRects.size();
			//std::cout << "Relocating cloud #" << i << " based on position of cloud #" << lastIndex << ".\n";		//debugging stuff
			const SDL_FRect& lastCloud = renderRects[lastIndex ];
			const int maxOffsetX = (lastCloud.w * 0.5f) * 3;
			const int minOffsetX = -maxOffsetX;

			const int curMinX = std::max(0, (int)lastCloud.x + minOffsetX);
			const int curMaxX = std::min((int)(windowWidth - lastCloud.w), (int)lastCloud.x + maxOffsetX);


			//std::cout << "Here, we reposition the cloud with the old code.\n";	//debugging stuff
			const int xPosition = rand() % (curMaxX - curMinX) + curMinX;

			renderRect.x = xPosition;
			renderRect.y = lastCloud.y - (renderRect.h * 2.5f);


			if (renderRect.x < 0.0f)
			{
				renderRect.x = 0.0f;
			}
			else if (renderRect.x > (windowWidth - renderRect.w))
			{
				renderRect.x = windowWidth - renderRect.w;
			}

			collider.x = renderRect.x;
			collider.y = renderRect.y + ((renderRect.h * 0.5f) - (collider.h * 0.5f));

			anyCloudRespawned = true;
		}
	}
```

 At the same time as we are spawning and respawning the clouds, we are also spawning their colliders.


***
## Colliders
In the `Level` class, colliders are used to define the hitboxes or collision areas for the clouds. Each cloud has its own collider, represented as a rectangle.
When the `Level::Create` function is called, colliders are created along with the clouds. For each cloud, a collider rectangle is defined based on its position and size. We are doing the same thing in  the `Player` class.

We are checking for collision and that is checking if collider of one object intersects with another objects collider. For example, if the player character has its own collider, the game would check if the player's collider intersects with any of the cloud colliders to detect collisions. 
If the player is falling ... `(yVelocity > 0.0f)` ... it goes through the list of cloud colliders and it checks for collision for each cloud collider that is below or at the same level as the player.
If a collision is detected, the player's position is set so the player stays on the cloud, player's yVelocity is set to zero, and it is marked as not jumping. This would keep the player on the cloud and allow them to jump again and check for the collision again with another cloud's collider.

```c++
// Only doing collision checking when the player is falling
if(yVelocity > 0.0f)
	{
		for (int i = 0; i < (int)levelColliders.size(); i++)
		{
			const SDL_FRect levelCollider = levelColliders[i];

			// The current level collider is above the player's bottom part so just continue without checking collision against it - jumps through the cloud
			
			if((levelCollider.y + levelCollider.h) < (yPosition + collider.h))
				continue;

			SDL_FRect intersection = {0.0f, 0.0f, 0.0f, 0.0f};
			if(SDL_IntersectFRect(&collider, &levelCollider, &intersection) == SDL_TRUE)
			{

				// Stop the player on top of the current cloud

				yPosition -= intersection.h;
				yVelocity = 0.0f;
				jumping = false;

				SyncColliders();

				break;
			}
		}
	}
```

Another thing that we added is if the player is below the screen (falls off the cloud), it checks where the player posions is and it sets the State to Dead.

```++
if (player->GetYPosition() > cameraRect.h + cameraRect.y - player->collider.h)
	player->IsDead();
```
***
## States
Talking about states, we made out game run in three states: **Menu**, **Game** and **Dead**

We are starting the game in a Menu state where you will find a music playing with a lovely background and two buttons - Start Game and Quit. The logic behind it is quite simple. Input Handler checks for the input of our curser. So if the curser is inside of the button and mouse click is pressed and released, then the state of the game changes.

```c++
case Application::Menu:
	{
		// Check if menu music is playing, if not... start playing it
		if (!Mix_PlayingMusic())
		{
			Mix_HaltMusic();
			Mix_PlayMusic(menuMusic, -1);
			Mix_VolumeMusic(volume);
		}

		if (quitButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
			running = false;

		if (startGameButton.PointInside(inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition()) && inputhandler->MouseButtonPressed(SDL_BUTTON_LEFT))
		{
			curState = State::Play;
			// Halt menu music and start playing game music
			Mix_HaltMusic();
			Mix_PlayMusic(gameMusic, -1);
			Mix_VolumeMusic(volume);
		}

		break;
	}
```
All three states are pretty similar to each other so it's enough to see this code to understand how it works.
There's not much to be said about it, other than when player falls down and gets out of the camera view triggers the Dead state. 

The rendering of each state looks like this:
```c++
case Application::Dead:
{
	SDL_RenderCopyF(window->GetRenderer(), gameOver, nullptr, nullptr);

	quitButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());
	restartGameButton.Render(window->GetRenderer(), inputhandler->GetMouseXPosition(), inputhandler->GetMouseYPosition());

	const std::string highestScoreText = "Highest Score: " + std::to_string((int)highestScore);
	GetWindow()->RenderText(GetFont(), highestScoreText, (GetWindow()->GetWidth() * 0.35f), (GetWindow()->GetHeight() * 0.6f), { 0, 0, 0, 255 });


	break;
}
```
***

This README provides an overview of our SDL-based game project, LSD-Jumper. With detailed explanations and code snippets, we hope to give you insights into our development process and the functionalities of our game components. If you have any questions or suggestions, feel free to reach out!

#### *Created by: Marina Eleni Voukouresli and Branko Zikic*
***
https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/1ebe36f6-801d-4a4a-b7d8-d3fa9db42586





