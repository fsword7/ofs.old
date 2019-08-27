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
#include "render/gl/texture.h"
#include "render/gl/scene.h"
#include "render/gl/shader.h"
#include "render/gl/shadermgr.h"
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
	gl.init();
}

glScene::~glScene()
{
}

//Texture *glScene::createTexture(int w, int h, int lod)
//{
//	return new glTexture(w, h, lod);
//}

void glScene::init(int w, int h)
{

//	glLoadIdentity();
//
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//
//	glDepthFunc(GL_LEQUAL);

	shader = new glShaderManager();

	initStarVertex();

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

void glScene::render(Player &player, Universe &universe)
{
	Camera *cam;
	vec3d_t cpos;
	quatd_t crot;
	double  cfov;
	mat4d_t crotm;

	mat4f_t model;
	mat4f_t mproj;
	mat4f_t mview;
	mat4f_t mvp;

	this->player = &player;

	closeStars.clear();

	if (vobj == nullptr) {
		vobj = new vPlanet(universe.earth, this);
		player.focus(universe.earth);
	}

	// get main camera from player for position and orientation.
	cam   = player.getCamera(0);
	cpos  = cam->position();
	crot  = cam->rotation();
	cfov  = cam->getFOV();
	crotm = glm::mat4_cast(crot);


	// Find closest stars within desired local distance
	universe.findCloseStars(cpos, 1.0, closeStars);

	gl.start();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(cfov, aspect, DIST_NEAR, DIST_FAR);
	glRotate(crot);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
//	glColor3f(1.0, 1.0, 1.0);

	// Calculate current projection/view/model matrix.
	mproj = glm::perspective(cfov, aspect, DIST_NEAR, DIST_FAR);
	mview = glm::translate(mat4f_t(1.0f), vec3f_t(cpos));
	model = glm::mat4_cast(crot);
	mvp   = model * mproj * mview;

//	// Render visible stars
//	renderStars(universe.getStarDatabase(), player, 6.0);
//	// Render constellation lines
//	renderConstellations(universe, player);

	vobj->update(player);

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	vobj->render(mvp);
	glDisable(GL_CULL_FACE);

	gl.finish();
}
