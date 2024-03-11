# LSD-Jumper (Latino Salsa Dancer - Jumper)
***
### Welcome to our little SDL project named LSD-Jumper!

Inspired by a game called Icy Tower :-)

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/63593adb-d53d-499c-bd6c-bb981022e431)


We chose SDL because it is a powerful cross-platform development library that provides low-level access to audio, keyboard, mouse, joystick, etc. The challenges were worth it, and with the knowledge that we gained, we can gladly keep working on more projects with SDL and C++.

Adding the libraries to our project went well, except for one confusion that we had with GitHub while both pushing the same things all over again, but eventually, we fixed it. We went through directories and linkers in our OpenGL course, which is why we found it quite easy to do.

We created classes and tried to keep the code as clean as possible. We used headers to declare our functions and the .cpp files to define them. 

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/b25e4f61-83df-4281-b69f-51ae7e4c8b4b)

One of the challenges we had was copying the files multiple times when including the headers. Using forward declaration solved the problem.

Uploading the textures using SDL_Texture*

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/e8334733-c36d-4ac8-a0e2-e76590e73c42)

Finding the path

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/8ba34d0a-4caa-486a-94cb-3fafe5b214b0)

The gravity and the velocity challenge where we tried to make our player jump smoothly and not just to teleport

![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/7285ac0c-1905-4ce0-b8bc-e6418a6d399e)

Utilizing min() and SDL_GetTicks() enables precise time measurement in the game, ensuring smooth and consistent frame rates
![image](https://github.com/forsbergsskola-se/LSD-Jumper/assets/124393021/5a791b12-66b6-4888-a878-2275841285a3)


Randomly spawn clouds to jump on and ensuring that when clouds are spawned, they are positioned close to each other

```c++
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





