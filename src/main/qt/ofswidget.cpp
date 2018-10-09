/*
 * oglwidget.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#include <GL/glew.h>

#include <QWidget>
#include <QOpenGLWidget>
#include <QMessageBox>

#include <iostream>

#include "main/main.h"
#include "main/coreapp.h"
#include "main/qt/ofscoreapp.h"
#include "main/qt/ofswidget.h"

using namespace qtofs;

ofsWidget::ofsWidget(QWidget *parent, ofsCoreApp *core)
: QOpenGLWidget(parent)
{
	QSurfaceFormat format;

	format.setVersion(4, 5);
	format.setOption(QSurfaceFormat::DeprecatedFunctions);
	format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);
	setFormat(format);

	create();
	makeCurrent();

	appCore = core;
}

ofsWidget::~ofsWidget()
{
}

void ofsWidget::initializeGL()
{
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;
		QMessageBox::critical(nullptr, APP_SHORT_NAME,
			QString("Can't initialize OpenGL extensions\n"));
		exit(1);
	} else
		std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

	appCore->initRenderer();
}

void ofsWidget::paintGL()
{
	appCore->paint();
}

void ofsWidget::resizeGL(int w, int h)
{
	appCore->resize(w, h);
}
