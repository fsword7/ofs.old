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
  camRotation(1, 0, 0, 0),
  fov(toRadian(OFS_DEFAULT_FOV))
{
}

Camera::~Camera()
{
}

void Camera::setFOVrad(float _fov)
{
	fov = _fov;
}

void Camera::setFOVdeg(float _fov)
{
	fov = toRadian(_fov);
}

void Camera::focus(Object *obj)
{
	vec3d_t opos = obj->position();
	vec3d_t up   = vec3d_t(0, 1, 0);
	mat4d_t m;

	m = glm::lookAt(camPosition, opos, up);

	camRotation = glm::conjugate(glm::quat_cast(m));

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

void Player::update(double dt, double scale)
{
	realTime += dt;

}
