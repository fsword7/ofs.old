/*
 * player.h - player (observer) facility
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#pragma once

class Camera {
public:
	Camera();
	~Camera();

	inline vec3d_t getPosition() { return position; }
	inline quatd_t getRotation() { return rotation; }
	inline float getFOV() { return fov; };

	void setFOVrad(float fov);
	void setFOVdeg(float fov);

private:
	vec3d_t position;
	quatd_t rotation;
	float   fov;
};

class Player {
public:
	Player();
	~Player();

	void update(double dt, double scale);

	inline vec3d_t getPosition() { return position; }
	inline quatd_t getRotation() { return rotation; }

	Camera *getCamera(int idx) const;

private:
	vec3d_t	position;
	quatd_t	rotation;

	double  realTime;
	double  simTime;

	vector<Camera *> camera;
};
