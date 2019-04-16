/*
 * plane.h
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#pragma once

template <typename T>
class Plane
{
	Plane()
	: normal(0, 0, 1), d(0)
	{
	}

	Plane(Plane &plane)
	: normal(plane.normal), d(plane.d)
	{
	}

	Plane(const glm::tvec3<T> &normal, const glm::tvec3<T> &pos)
	: normal(normal)
	{
		d = (normal.x * pos.x) + (normal.y * pos.y) + (normal.z * pos.z);
	}

	~Plane() = default;

	T distanceTo(const glm::tvec3<T> &pos)
	{
		return (normal.x * pos.x) + (normal.y * pos.y) + (normal.z * pos.z);
	}

private:
	glm::tvec3<T> normal;
	T d;
};

typedef Plane<double> planed_t;
