#include "CBeam.h"
#include "CVector.h"
#include "CCollision.h"
#include "CBeamManager.h"
#include "CEBeamManager.h"
#include <windows.h>

//ƒr[ƒ€‚Ìõ–½ ‘å‚«‚¢‚Ù‚Çõ–½‚ª‘‚¢
#define BEAM_LIFE_TIME 0.04f


void CBeam::Start(const CVector3D& pos, const CVector3D& target) {
	CVector3D fwd(0.0f, 0.0f, 1.0f);
	m_pos = pos;
	target_pos = target;
	m_alive = true;

	m_rotMtx.RotationAxis(fwd, m_pos, target_pos);

	m_life = BEAM_RANGE;
}

void CBeam::Render() {
	if (m_alive)
		CModelObj::Render();
}




void CBeam::Update()
{
	if (!m_alive)
		return;

	if (m_trail <= 0.0f) {
  		CBeam *b = new CBeam();
		*b = *this;
		b->setArray(*this);
		b->m_trail = BEAM_LIFE_TIME;
		switch (b->sbt) {
		case CBeam::SBT::PLAYER:
			CBeamManager::GetInstance()->Add(b);
			break;
		case CBeam::SBT::ENEMY:
			CEBeamManager::GetInstance()->Add(b);
			break;
		}
		CVector3D diff = target_pos - m_pos;
		/*
		if (diff.Length() < 1.0f) {
			m_alive = false;
			return;
		}
		*/
		diff.Normalize();
		m_pos += diff * BEAM_SPEED;
		m_life -= 1.0f * BEAM_SPEED;
		if (m_life < 0.0f) {
			m_alive = false;
			return;
		}
	}
	else
	{
		m_material.m_diffuse[3] -= m_trail;
		if (m_material.m_diffuse[3] <= 0.0f) {
			m_alive = false;
		}
	}
}

void CBeam::UpdateMatrix()
{

	CMatrix translate;
	translate.SetIndentity();
	translate.m03 = m_pos.x;
	translate.m13 = m_pos.y;
	translate.m23 = m_pos.z;

	m_matrix = translate * m_rotMtx;
}

void CBeam::setDiffuse(float r, float g, float b, float a) {
	m_material.m_diffuse[0] = r;
	m_material.m_diffuse[1] = g;
	m_material.m_diffuse[2] = b;
	m_material.m_diffuse[3] = a;
}

/*
bool CBeam::IntersectTriangleRay(CVector3D *corss,const CVector3D &p1, const CVector3D &p2,float *pt ) {
	for(int i = 0; i < m_vertexNum; i+=3) {
		if(CCollision::IntersectTriangleRay(corss, p1, p2, m_pVertexAry[i], m_pVertexAry[i+1], m_pVertexAry[i+2],pt)) {
			return true;
		}
	}
	return false;
}
*/

float* CBeam::getDiffuse() {
	return m_material.m_diffuse;
}
/*
CVector3D CBeam::GetEuler(CVector3D &v) {
	float rx, ry, rz;
	rx = atan2f(v.y, v.Dot(CVector3D(1.0f, 0.0f, 0.0f)));
	ry = atan2f(v.z, v.x);
	rz = 0.0f;
	if (v.x >= 0.0f) {
		return CVector3D(rx, -ry, rz);
	}
	else {
		if (v.y >= 0.0f) {
			return CVector3D(rx, ry, rz);
			if (v.z >= 0.0f) {

			}
		}
		else {
			return CVector3D(rx, ry, rz);
		}
	}
}
*/

//‘ã“ü‰‰Zq
