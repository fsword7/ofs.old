/*
 * scene.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/player.h"
#include "engine/universe/universe.h"
#include "engine/universe/body.h"
#include "engine/render/scene.h"
#include "engine/render/vobject.h"
#include "engine/render/gl/funcs.h"

Scene::Scene()
: width(1), height(1)
{
}

Scene::~Scene()
{
}

glScene::glScene()
: Scene(), vobj(nullptr)
{
}

glScene::~glScene()
{
}

void glScene::init(int w, int h)
{

//	glLoadIdentity();
//
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//
//	glDepthFunc(GL_LEQUAL);

	resize(w, h);
}

void glScene::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width  = w;
	height = h;
	aspect = float(width)/float(height);
}

void glScene::paint(Player &player, Universe &universe)
{
	Camera *cam;
	vec3d_t cpos;
	quatd_t crot;
	float   cfov;
	mat4d_t crotm;

	// get main camera from player for position and orientation.
	cam   = player.getCamera(0);
	cpos  = cam->position();
	crot  = cam->rotation();
	cfov  = cam->getFOV();
	crotm = glm::mat4_cast(crot);

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cfov, aspect, DIST_NEAR, DIST_FAR);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	gluLookAt(0.0, 0.0, 0.5,
//			  0.0, 0.0, 0.0,
//			  0.0, 1.0, 0.0);
//
//	glTranslatef(0.0, 0.0, -1.0);
//	glBegin(GL_QUADS);
//		glColor3f(0.0f, 1.0f, 0.0f);
//		glNormal3f(0.0f, 0.0f, 1.0f);
//		glVertex3f(0.5f, -0.5f, 0.5f);
//		glVertex3f(0.5f, 0.5f, 0.5f);
//		glVertex3f(-0.5f, 0.5f, 0.5f);
//		glVertex3f(-0.5f, -0.5f, 0.5f);
//	glEnd();

	glRotate(crot);

	if (vobj == nullptr) {
		vobj = new vPlanet(universe.earth, this);
		cam->lookAt(universe.earth);
	}

	glColor4f(1, 1, 1, 1);
	vobj->update(player);
	vobj->paint();
}
