/*
 * oglwidget.h
 *
 *  Created on: Oct 8, 2018
 *      Author: fswor
 */

#pragma once

namespace qtofs {
	class ofsWidget : public QOpenGLWidget
	{
	public:
		ofsWidget(QWidget *parent, ofsCoreApp *core);
		~ofsWidget();

		void initializeGL();
		void paintGL();
		void resizeGL(int w, int h);

	private:
		ofsCoreApp *appCore;
	};
}
