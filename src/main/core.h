/*
 * core.h - OFS core application
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

namespace ofs {
	class Core
	{
	public:
		Core();
		~Core();

		void onInit();
		void onClean();
	};
}
