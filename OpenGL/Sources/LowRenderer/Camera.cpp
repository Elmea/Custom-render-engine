#include "Camera.h"

#include <cmath>

using namespace lowRenderer;

Camera::Camera(const unsigned int width, const unsigned int height, float _speed, float l, float r, float b, float t, float n, float f, float _fov)
{
	aspect = (float)width / (float)height;

	far = f;
	near = n;
	right = r;
	left = l;
	top = t;
	bottom = b;

	speed = _speed;

	FOV = _fov;
}

void Camera::setProjection(ViewType view)
{
	switch (view)
	{
	case(ViewType::VT_ORTHOGRAPHIC):
	{
		float temp[4][4] = {
			{2.f / (right - left), 0.f, 0.f, -(right + left) / (right - left)},
			{0.f, 2.f / (top - bottom), 0.f, -(top + bottom) / (top - bottom)},
			{0.f, 0.f, -2.f / (far - near), -(far + near) / (far - near)},
			{0.f, 0.f, 0.f, 1.f}
		};

		projectionMatrix = temp;
		break;
	}

	case(ViewType::VT_PERSPECTIVE):
	{
		float a = 1.f / tanf(DEG2RAD * FOV / 2.f);

		float temp[4][4] = {
			{a / aspect, 0.f, 0.f, 0.f},
			{0.f, a, 0.f, 0.f},
			{0.f, 0.f, -(far + near) / (far - near), -(2 * far * near) / (far - near)},
			{0.f, 0.f, -1.f, 0.f}
		};

		projectionMatrix = temp;
		break;
	}

	default:
		break;
	}
}

void Camera::setParameters(float l, float r, float b, float t, float n, float f)
{
	far = f;
	near = n;
	right = r;
	left = l;
	top = t;
	bottom = b;
}

void Camera::setRenderDistance(float n, float f)
{
	far = f;
	near = n;
}

void Camera::setFov(float _fov)
{
	FOV = _fov;
}

void Camera::CalcVP()
{
	myMaths::Float3 scale(1.f, 1.f, 1.f);
	VPMatrix = projectionMatrix * myMaths::Mat4::CreateTransformMatrix(position, rotation, scale).getInverseMatrix();
}

myMaths::Mat4 Camera::getVP()
{
	return VPMatrix;
}

void Camera::Update(const Inputs cameraInputs)
{
	rotation.y -= cameraInputs.mouseDeltaX / 6;
	rotation.x -= cameraInputs.mouseDeltaY / 6;

	if (rotation.x < -90)
		rotation.x = -90;

	if (rotation.x > 90)
		rotation.x = 90;

	if (rotation.y > 360)
		rotation.y = -360;

	if (rotation.y < -360)
		rotation.y = 360;

	if (cameraInputs.backward)
	{
		position.x -= speed * cosf(DEG2RAD * (rotation.y + 90));
		position.z += speed * sinf(DEG2RAD * (rotation.y + 90));
	}
	if (cameraInputs.forward)
	{
		position.x += speed * cosf(DEG2RAD * (rotation.y + 90));
		position.z -= speed * sinf(DEG2RAD * (rotation.y + 90));
	}

	if (cameraInputs.right)
	{
		position.x += speed * cosf(DEG2RAD * (rotation.y));
		position.z -= speed * sinf(DEG2RAD * (rotation.y));
	}
	if (cameraInputs.left)
	{
		position.x -= speed * cosf(DEG2RAD * (rotation.y));
		position.z += speed * sinf(DEG2RAD * (rotation.y));
	}

	if (cameraInputs.up)
		position.y += speed;

	if (cameraInputs.down)
		position.y -= speed;

	if (cameraInputs.accelerate)
		speed += 0.01f;

	if (cameraInputs.slowDown)
	{
		if (speed > 0)
			speed -= 0.01f;
	}

	if (speed < 0)
		speed = 0;
}