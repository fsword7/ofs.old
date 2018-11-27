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
		virtual ~CoreApp();

		virtual void init() = 0;
		virtual void clean() = 0;
		virtual void run() = 0;

		void initRenderer();
		void initEngine();

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
