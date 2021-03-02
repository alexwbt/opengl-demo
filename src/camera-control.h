#pragma once

class CameraControl
{
private:
	Camera& camera_;
	float camera_speed_;
	float mouse_sensitivity_;

	bool initialized_ = false;
	float mouse_x = 0;
	float mouse_y = 0;

public:
	CameraControl(Camera& camera, float camera_speed, float mouse_sensitivity);

	void Update(const std::vector<bool>& controls);
	void MouseMove(float x, float y);
};

