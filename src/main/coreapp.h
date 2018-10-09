/*
 * core.h - OFS core application
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

class Renderer;

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
		Renderer *render;
	};
}
