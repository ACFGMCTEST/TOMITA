#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "../Scene/Vector/CVector4.h"
#include "glut.h"

class CTriangle{
public:
	float v[9];
	float diffuse[4];
	float normal[3];
	float pos[3];
	float w[9];
	float rot[3];

	CTriangle(){
		pos[0] = pos[1] = pos[2] = 0.0f;
	}

	void rotationY(float *x, float *y, float *z, float deg){
		CMatrix44 matrix;
		matrix.rotationY(deg);
		matrix.multi(x, y, z);
	}

	void rotationX(float *x, float *y, float *z, float deg){
		CMatrix44 matrix;
		matrix.rotationX(deg);
		matrix.multi(x, y, z);
	}

	void translate(float *x, float *y, float *z, float pos[]){
		CMatrix44 matrix;
		matrix.translate(pos);
		matrix.multi(x, y, z);
	}

	void setVertexes(float f[]){
		for (int i = 0; i < 9; i++){
			v[i] = f[i];
		}
	}

	void setDiffuse(float r, float g, float b, float a){
		diffuse[0] = r;
		diffuse[1] = g;
		diffuse[2] = b;
		diffuse[3] = a;
	}

	void setNormal(float x, float y, float z){
		normal[0] = x;
		normal[1] = y;
		normal[2] = z;
	}

	void render(){
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glNormal3fv(normal);
		glBegin(GL_TRIANGLES);
		glVertex3f(v[0], v[1], v[2]);
		glVertex3f(v[3], v[4], v[5]);
		glVertex3f(v[6], v[7], v[8]);
		glEnd();
	}

};
#endif