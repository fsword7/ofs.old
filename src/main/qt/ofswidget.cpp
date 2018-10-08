/*
 * oglwidget.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#include <QWidget>
#include <QOpenGLWidget>

#include "main/main.h"
#include "main/coreapp.h"
#include "main/qt/ofscoreapp.h"
#include "main/qt/ofswidget.h"

using namespace qtofs;

ofsWidget::ofsWidget(QWidget *parent, ofsCoreApp *core)
: QOpenGLWidget(parent)
{
	appCore = core;

}

ofsWidget::~ofsWidget()
{
}

void ofsWidget::initializeGL()
{
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
