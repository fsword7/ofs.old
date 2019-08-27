/*
 * context.h
 *
 *  Created on: Aug 11, 2019
 *      Author: Tim Stark
 */

#pragma once

#include <GL/glew.h>

class glContext
{
public:
	enum bType {
		glVAO, glVBO, glEBO
	};

	glContext() = default;
	~glContext();

	inline void glMatrix(const mat4d_t& m)
	{
		mat4d_t trans = glm::transpose(m);
		glMultMatrixd(&trans[0].x);
	}

	template<class T>
	inline void glFrustum(T fovy, T aspect, T near, T far)
	{
		T fw, fh;

		fh = tan(fovy / 2.0) * near;
		fw = fh * aspect;

		glFrustum( -fw, fw, -fh, fh, near, far);
	}

	inline void glRotate(const quatd_t& q)
	{
		glMatrix(glm::mat4_cast(q));
	}

	inline void glTranslate(const vec3d_t& v)
	{
		glTranslated(v.x, v.y, v.z);
	}

	void init();
	void start();
	void finish();

	void assign(bType type, void *data, uint32_t size) const;

private:
	uint32_t vao = 0;
	uint32_t vbo = 0;
	uint32_t ebo = 0;
};
