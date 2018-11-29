/*
 * scene.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/player.h"
#include "universe/universe.h"
#include "universe/body.h"
#include "render/scene.h"
#include "render/vobject.h"
#include "render/gl/funcs.h"

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
	aspect = double(width)/double(height);
	cout << "Width: " << w << " Height: " << h << " Aspect: " << aspect << endl;
}

void glScene::paint(Player &player, Universe &universe)
{
	Camera *cam;
	vec3d_t cpos;
	quatd_t crot;
	double  cfov;
	mat4d_t crotm;

	// get main camera from player for position and orientation.
	cam   = player.getCamera(0);
	cpos  = cam->position();
	crot  = cam->rotation();
	cfov  = cam->getFOV();
	crotm = glm::mat4_cast(crot);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(cfov, aspect, DIST_NEAR, DIST_FAR);
	glRotate(crot);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);


	if (vobj == nullptr) {
		vobj = new vPlanet(universe.earth, this);
		cam->focus(universe.earth);
	}

	vobj->update(player);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	vobj->paint();
	glDisable(GL_CULL_FACE);
}
