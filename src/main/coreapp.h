/*
 * core.h - OFS core application
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

class Engine;
class Universe;
class Scene;
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

		void run();

		void tick();
		void paint();
		void resize(int w, int h);

	protected:
		int width, height;

	private:
		Player   *player;
		Engine   *engine;
		Universe *universe;
		Scene    *scene;
	};
}
