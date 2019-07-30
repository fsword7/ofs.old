/*
 * astrerism.h
 *
 *  Created on: Jul 29, 2019
 *      Author: Tim Stark
 */

#pragma once

class Asterism
{
public:
	Asterism() = default;
	~Asterism() = default;

private:
	std::string abbName; // Abbreviated name
	int nSegements;
	int *hipStars;
};

class AsterismManager
{
public:
	AsterismManager() = default;
	~AsterismManager() = default;

private:
};
