/*
 * engine.h
 *
 *  Created on: Oct 9, 2018
 *      Author: Tim Stark
 */

#pragma once

class Universe;

class Engine
{
public:
	Engine(Universe *universe);
	~Engine();

private:
	Universe *universe;

};
