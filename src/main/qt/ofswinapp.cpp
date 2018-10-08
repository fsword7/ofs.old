/*
 * qtwinapp.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */


#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QOpenGLWidget>

#include "main/main.h"
#include "main/coreapp.h"
#include "main/qt/ofscoreapp.h"
#include "main/qt/ofswidget.h"
#include "main/qt/ofswinapp.h"

using namespace qtofs;
using namespace ofs;

const QSize defaultSize(1280, 720);
const QPoint defaultPosition(20, 20);

ofsWindowApp::ofsWindowApp(QWidget *parent)
: QMainWindow(parent),
  appCore(nullptr),
  widget(nullptr)
{

}

ofsWindowApp::~ofsWindowApp()
{
}

void ofsWindowApp::init()
{

	appCore = new ofsCoreApp();

	widget = new ofsWidget(nullptr, appCore);
	widget->makeCurrent();

	setCentralWidget(widget);
	setWindowTitle(APP_FULL_NAME);

	resize(defaultSize);

}
