#ifndef COL_LINE_H
#define COL_LINE_H

#include "CColBase.h"


/*当たり判定クラス 線*/
class CColLine : CColBase{
public:
	CVector3 mBegins;//前のモノ
	CVector3 mEnd;//後ろのモノ
};

#endif