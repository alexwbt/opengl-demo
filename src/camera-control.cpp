#include "pch.h"

CameraControl::CameraControl(Camera& camera, float camera_speed, float mouse_sensitivity)
	: camera_(camera), camera_speed_(camera_speed), mouse_sensitivity_(mouse_sensitivity)
{}

void CameraControl::Update(const std::vector<bool>& controls)
{
	if (controls.size() < 5) return;
	if (controls[0]) camera_.position += camera_speed_ * camera_.front;
	if (controls[1]) camera_.position -= camera_speed_ * camera_.front;
	if (controls[2]) camera_.position += camera_speed_ * camera_.right;
	if (controls[3]) camera_.position -= camera_speed_ * camera_.right;
	if (controls[4]) camera_.position += camera_speed_ * glm::vec3(0, 1, 0);
	if (controls[5]) camera_.position -= camera_speed_ * glm::vec3(0, 1, 0);
}

void CameraControl::MouseMove(float x, float y)
{
	if (initialized_)
	{
		camera_.yaw += (x - mouse_x) * mouse_sensitivity_;
		camera_.pitch += (mouse_y - y) * mouse_sensitivity_;
	}
	initialized_ = true;
	mouse_x = x;
	mouse_y = y;

	if (camera_.pitch > 89.0f)
		camera_.pitch = 89.0f;
	if (camera_.pitch < -89.0f)
		camera_.pitch = -89.0f;
}
