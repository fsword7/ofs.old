/*
 * player.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/player.h"
#include "engine/object.h"

Camera::Camera()
: camPosition(0, 0, 0),
  camRotation(1, 0, 0, 0)
{
	setFOVdeg(OFS_DEFAULT_FOV);
}

Camera::~Camera()
{
}

void Camera::setFOVrad(double _fov)
{
	fov = _fov;
}

void Camera::setFOVdeg(double _fov)
{
	fov = toRadian(_fov);
}

void Camera::focus(Object *obj)
{
	vec3d_t opos = obj->position();
	vec3d_t up   = vec3d_t(0, 1, 0);
	mat4d_t m    = glm::lookAt(camPosition, opos, up);

	camRotation = glm::conjugate(glm::quat_cast(m));

//	cout << "Camera Parameters: " << endl;
//	cout << fixed << setprecision(10) << endl;
//	cout << "Object:   (" << opos.x << ", " << opos.y << ", " << opos.z << ")" << endl;
//	cout << "Camera:   (" << camPosition.x << ", " << camPosition.y << ", " << camPosition.z << ")" << endl;
//	cout << "Rotation: (" << camRotation.w << ", " << camRotation.x << ", " << camRotation.y << ", " << camRotation.z << ")" << endl;

}

// ***************************

Player::Player()
: position(0, 0, 0),
  rotation(1, 0, 0, 0),
  realTime(0),
  simTime(0),
  camera(1)
{
	camera[0] = new Camera();

	// Initialize velocity controls
	trSpeed    = 0.0;
	trVelocity = vec3d_t(0, 0, 0);
	rtVelocity = vec3d_t(0, 0, 0);
}

Player::~Player()
{
	for (auto &old : camera)
		delete old;
	camera.clear();
}

Camera *Player::getCamera(int idx) const
{
	if (idx < camera.size())
		return camera[idx];
	return nullptr;
}

void Player::setRotationVelocity(vec3d_t rv)
{
	rtVelocity = rv;
}

void Player::setTravelSpeed(double ts)
{
	trSpeed = ts;
}

void Player::update(double dt, double scale)
{
	realTime += dt;

}
