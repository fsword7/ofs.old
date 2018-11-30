/*
 * engine.h
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "main/date.h"

class Universe;
class Player;

class Engine
{
public:
	Engine(Universe *universe, Player *player);
	~Engine();

	inline Date *getRealTime() { return &realDate; }

	void start();
	void update(double dt);

private:
	Universe *universe;
	Player   *player;

	Date 	realDate;	// current Julian clock
	double	realTime;	// System time in Julian clock
	double	scaleTime;	// Time-travel scale time [Julian date]
};
