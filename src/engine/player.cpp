/*
 * player.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/player.h"

Camera::Camera()
: position(0, 0, 0),
  rotation(1, 0, 0, 0),
  fov(0)
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

// ***************************

Player::Player()
: position(0, 0, 0),
  rotation(1, 0, 0, 0),
  realTime(0),
  simTime(0)
{
	camera[0] = new Camera();
}

Player::~Player()
{
}

void Player::update(double dt, double scale)
{
	realTime += dt;

}
