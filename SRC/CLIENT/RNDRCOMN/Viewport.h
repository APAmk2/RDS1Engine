#pragma once

#include "Common.h"
#include <glm/glm.hpp>

class Viewport
{
public:
	Viewport();

	Vector3f Position = { 0.0f, 0.0f, 0.0f };

	void SetFOV(const float& newFOV);
	float GetFOV() { return FOV; }

	void SetCoords(const Rect& newCoords);
	Rect GetCoords() { return ViewportCoords; }

	void SetNear(const float& newNear);
	float GetNear() { return Near; }

	void SetFar(const float& newFar);
	float GetFar() { return Far; }

	glm::mat4 GetMatrix() { return Projection; }
private:
	float FOV = 90.0f;
	Rect ViewportCoords;
	float Near = 0.1f;
	float Far = 100.0f;

	glm::mat4 Projection;

	void CalculateMatrix();
};

extern Viewport gViewport;