#include "CTask.h"


CTask::CTask() :mpNext(0), mpPrev(0), mKillFlag(false),mCharaFlag(false){};


CTask::~CTask(){};
void CTask::Init(){};
void CTask::Update(){};
void CTask::Render(){};
void CTask::BillboardRender(){}
