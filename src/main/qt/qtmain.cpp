/*
 * qtmain.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: Tim Stark
 */

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QOpenGLWidget>

#include "main/main.h"
#include "main/qt/ofscoreapp.h"
#include "main/qt/ofswidget.h"
#include "main/qt/ofswinapp.h"
#include "main/coreapp.h"

using namespace qtofs;
using namespace ofs;

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	ofsWindowApp window;

	window.init();
	window.show();

	return app.exec();
}

