#ifndef CMODELOBJ_H
#define CMODELOBJ_H

#include "../Vector\CVector3.h"
#include "CTriangle.h"
#include <vector>

class CModelObj {
public:
	std::vector<CVector3> mVectorV;
	std::vector<CVector3> mVectorN;
	std::vector<CTriangle> mTriangle;
	void LoadFile(char* filename);
	void Render();
	void AddCollisionManager();
};

#endif
