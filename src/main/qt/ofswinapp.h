/*
 * qtwinapp.h - Core Windows Application
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#pragma once

namespace qtofs {
	class ofsWindowApp : public QMainWindow
	{
	public:
		ofsWindowApp(QWidget *parent = nullptr);
		~ofsWindowApp();

		void init();

	private:
		ofsCoreApp *appCore;
		ofsWidget  *widget;

	};
}
