/*
 * player.h - player (observer) facility
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#pragma once

class Object;

class Camera {
public:
	Camera();
	~Camera();

	inline vec3d_t position() { return camPosition; }
	inline quatd_t rotation() { return camRotation; }
	inline double getFOV() { return fov; };

	void setFOVrad(double fov);
	void setFOVdeg(double fov);

	void focus(Object *obj);

private:
	vec3d_t camPosition;
	quatd_t camRotation;
	double  fov;
};

class Player {
public:
	Player();
	~Player();

	void update(double dt, double scale);

	inline vec3d_t getPosition() { return position; }
	inline quatd_t getRotation() { return rotation; }

	inline double  getTravelSpeed()      { return trSpeed; }
	inline vec3d_t getRotationVelocity() { return rtVelocity; }

	void setRotationVelocity(vec3d_t rtVelocity);
	void setTravelSpeed(double trSpeed);

	Camera *getCamera(int idx) const;

private:
	vec3d_t	position;
	quatd_t	rotation;

	double  realTime;
	double  simTime;

	// Velocity control
	vec3d_t	rtVelocity;
	vec3d_t	trVelocity;
	double  trSpeed;


	vector<Camera *> camera;
};
