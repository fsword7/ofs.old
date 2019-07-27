/*
 * player.h - player (observer) facility
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#pragma once

class Object;
class Player;

class Camera {
public:
	Camera(Player *player);
	~Camera();

	inline vec3d_t position() { return camPosition; }
	inline quatd_t rotation() { return camRotation; }
	inline vec3d_t getPosition() const { return camPosition; }
	inline quatd_t getRotation() const { return camRotation; }
	inline double getFOV() { return fov; };

	void setFOVrad(double fov);
	void setFOVdeg(double fov);

	void focus(Object *obj);
	void update();

private:
	Player *player;

	vec3d_t camPosition;
	quatd_t camRotation;
	double  fov;
};

class Player {
public:
	Player();
	~Player();

	void update(double dt, double scale);

	inline vec3d_t getPosition() const { return lpos; }
	inline quatd_t getRotation() const { return lqrot; }

	inline vec3d_t getAngularVelocity() { return av; }
	inline vec3d_t getTravelVelocity()  { return tv; }
	inline double  getTravelSpeed()     { return tv.z; }

	void setAngularVelocity(vec3d_t av);
	void setTravelVelocity(vec3d_t tv);
	void setTravelSpeed(double ts);

	Camera *getCamera(int idx) const;

	void focus(Object *obj);

private:
	// Universe position, orientation, and velocity
	vec3d_t	upos, uvec;
	quatd_t	uqrot;

	// Local position, orientation, and velocity in local reference frame
	vec3d_t	lpos, lvec;
	quatd_t	lqrot;

	// Current real time and virtual julian time
	double  realTime;
	double  jdTime;

	// Velocity control
	vec3d_t	av; // Angular velocity
	quatd_t wv; //    Quaternion control
	vec3d_t	tv; // Travel velocity

	vector<Camera *> camera;
};
