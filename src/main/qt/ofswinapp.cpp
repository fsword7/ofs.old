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
#include <QMessageBox>
#include <QTimer>

#include "main/main.h"
#include "main/coreapp.h"
#include "main/qt/ofscoreapp.h"
#include "main/qt/ofswidget.h"
#include "main/qt/ofswinapp.h"

using namespace qtofs;
using namespace ofs;

const QSize defaultSize(OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT);
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

	appCore->initEngine();

	widget = new ofsWidget(nullptr, appCore);
	widget->makeCurrent();

	setCentralWidget(widget);
	setWindowTitle(APP_FULL_NAME);

	resize(defaultSize);

	// Start event loop
	QTimer *timer = new QTimer(dynamic_cast<QObject *>(this));
	QObject::connect(timer, SIGNAL(timeout()), SLOT(tick()));
	timer->start(0);
}

void ofsWindowApp::tick()
{
	appCore->tick();
	widget->update();
}
