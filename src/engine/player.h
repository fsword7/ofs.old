/*
 * player.h - player (observer) facility
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#pragma once

class Player {
public:
	Player();
	~Player();

	void update(double dt, double scale);

	inline float getFOV() { return fov; }
	inline void  setFOV(float _fov) { fov = _fov; }

private:
	vec3d_t	position;
	quatd_t	orientation;
	float   fov;

	double  realTime;
	double  simTime;
};
