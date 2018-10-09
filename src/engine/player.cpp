/*
 * player.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/player.h"

Player::Player()
: position(0, 0, 0),
  orientation(1, 0, 0, 0),
  fov(0),
  realTime(0),
  simTime(0)
{
}

Player::~Player()
{
}

void Player::update(double dt, double scale)
{
	realTime += dt;

}
