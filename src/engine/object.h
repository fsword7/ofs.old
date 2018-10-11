/*
 * object.h
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#pragma once

class Object {
public:
	Object(string name);
	~Object();

private:
	vector<string> names;
};
