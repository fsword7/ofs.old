/*
 * qtwinapp.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#include <QApplication>
#include <QMainWindow>
#include <QWidget>

#include "main/main.h"
#include "main/coreapp.h"
#include "main/qt/ofscoreapp.h"
#include "main/qt/qtwinapp.h"

using namespace qtofs;
using namespace ofs;

ofsWindowApp::ofsWindowApp(QWidget *parent)
: QMainWindow(parent),
  appCore(nullptr)
{

}

ofsWindowApp::~ofsWindowApp()
{
}

void ofsWindowApp::init()
{

	appCore = new ofsCoreApp();
}

