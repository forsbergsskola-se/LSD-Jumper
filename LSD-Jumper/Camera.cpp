#include "Camera.h"

#include "Player.h"

void Camera::Create(const float windowWidth, const float windowHeight)
{
	cameraRect = {0.0f, 0.0f, windowWidth, windowHeight};
}

void Camera::Update(Player* player, const float deltaTime)
{
	// Smoothly move the camera up towards the player when the player has landed on a cloud platform
	const float positionDifference = (player->GetYPosition() - (cameraRect.h * 0.5f)) - yPosition;
	const float softPosition = yPosition + positionDifference * deltaTime * easeFactor;

	yPosition = softPosition;
	cameraRect.y = yPosition;

	if (cameraRect.y > 0.0f)
		cameraRect.y = 0.0f;
}