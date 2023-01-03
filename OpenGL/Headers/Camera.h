#pragma once
#include "myMaths.hpp"
#include "GameObject.h"

namespace lowRenderer
{
	enum class ViewType
	{
		VT_ORTHOGRAPHIC,
		VT_PERSPECTIVE
	};

	struct Inputs
	{
		bool forward, backward;
		bool left, right;
		bool up, down;
		bool accelerate, slowDown;

		double mouseX = 0.0;
		double mouseY = 0.0;
		float mouseDeltaX = 0.0;
		float mouseDeltaY = 0.0;
	};


	class Camera : public GameObject
	{
	private:
		float right, left;
		float top, bottom;
		float far, near;
		float FOV, aspect;

		myMaths::Mat4 projectionMatrix;

		myMaths::Mat4 VPMatrix;

	public:
		Camera(const unsigned int width, const unsigned int height, float speed, float l = -1.f, float r = 1.f, float b = -1.f, float t = 1.f, float n = 0.1f, float f = 10.f, float _fov = 60.f);

		float speed = 0.1f;

		void setProjection(ViewType view);
		void setParameters(float l, float r, float b, float t, float n, float f);

		void setRenderDistance(float n, float f);
		void setFov(float _fov);

		void CalcVP();
		myMaths::Mat4 getVP();

		void Update(const Inputs cameraInputs);

		void setSpeed(float _speed) { speed = _speed; }
	};
}