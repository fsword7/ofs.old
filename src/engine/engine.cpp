/*
 * engine.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/engine.h"
#include "engine/player.h"


Engine::Engine(Universe *_univ, Player *_player)
: universe(_univ),
  player(_player),
  realTime(0), scaleTime(1.0)
{
	pdata = "../data/";
}

Engine::~Engine()
{
}

void Engine::start()
{
	// Start julian clock as of now
	realDate.reset();
	realTime = realDate;
}

void Engine::update(double dt)
{
	// Update current julian time
	realTime += dt / SECONDS_PER_DAY;
	if (player != nullptr)
		player->update(dt, scaleTime);

}
