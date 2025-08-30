#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

Viewport gViewport;

Viewport::Viewport()
{
	//CalculateMatrix();
}

void Viewport::SetFOV(const float& newFOV)
{
	if (newFOV <= 0.0f) return;
	FOV = newFOV;
	CalculateMatrix();
}

void Viewport::SetCoords(const Rect& newCoords)
{
	if (newCoords.x < 0 || newCoords.y < 0) return;
	ViewportCoords = newCoords;
	CalculateMatrix();
	glViewport(ViewportCoords.x, ViewportCoords.y, ViewportCoords.w, ViewportCoords.h);
}

void Viewport::SetNear(const float& newNear)
{
	if (newNear <= 0.0f) return;
	Near = newNear;
	CalculateMatrix();
}

void Viewport::SetFar(const float& newFar)
{
	if (newFar <= 0.0f) return;
	Far = newFar;
	CalculateMatrix();
}

void Viewport::CalculateMatrix()
{
	Projection = glm::perspective(glm::radians(FOV), (float)ViewportCoords.w / (float)ViewportCoords.h, Near, Far);
}