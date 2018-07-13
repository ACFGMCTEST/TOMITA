#ifndef STATE_MACHIN_H
#define STATE_MACHIN_H

#include "CStateBase.h"


// ó‘ÔŠÇ—
class CStateMachine
{
private:
	std::unordered_map<std::string, std::shared_ptr<CStateBase>> stateMap;
	std::shared_ptr<CStateBase> nowState;
public:
	CStateMachine() : nowState(),stateMap()
	{

	}
	/*XVˆ—*/
	void Update();

	////// “o˜^‚·‚é
	//void Register(const std::string& name, const std::shared_ptr<CStateBase> state);
	//// “o˜^‚·‚é,e‚Ìİ’è
	void Register(const std::string& name, const std::shared_ptr<CStateBase> state, CTask *parent);

	// Å‰‚©‚çn‚ß‚éó‘Ô‚ğİ’è
	void SetStartState(const std::string& registerName);

	// “o˜^‚µ‚½‚à‚Ì‚ğíœ‚·‚é
	void Deregistration(const std::string& registerName);

	// ‚·‚×‚Ä‚Ì“o˜^‚ğíœ‚·‚é
	void AllDeregistration();

	// ƒXƒe[ƒgŠO‚©‚ç‹­§“I‚É‘JˆÚ‚ğÀs
	void ForceChange(const std::string& registerName);




};
#endif 
