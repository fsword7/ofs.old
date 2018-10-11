/*
 * core.h - OFS core application
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

class Engine;
class Universe;
class Renderer;
class Player;

namespace ofs {
	class CoreApp
	{
	public:
		CoreApp();
		~CoreApp();

		void init();
		void clean();

		void initRenderer();
		void initEngine();

		void tick();
		void paint();
		void resize(int w, int h);

	private:
		Player   *player;
		Engine   *engine;
		Universe *universe;
		Renderer *render;

		int width, height;
	};
}
