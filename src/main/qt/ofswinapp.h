/*
 * qtwinapp.h - Core Windows Application
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#pragma once

#include <QMainWindow>
#include <QWidget>

#include "main/qt/ofscoreapp.h"
#include "main/qt/ofswidget.h"

namespace qtofs {
	class ofsWindowApp : public QMainWindow
	{
		Q_OBJECT

	public:
		ofsWindowApp(QWidget *parent = nullptr);
		~ofsWindowApp();

		void init();

	public slots:
		void tick();

	private:
		ofsCoreApp *appCore;
		ofsWidget  *widget;

	};
}
