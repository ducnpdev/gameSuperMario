#include "MorningStar.h"


//CMorningStar::CMorningStar() {
//	SetState(mstar_level_1);
//	//ms_level = mstar_level_1;
//}

CAnimation* CMorningStar::getCurrentAnimation() {
	
	if (ms_level == mstar_level_1) {
		if (nx > 0) return animation_set->at(0);
		else return animation_set->at(1);
	}
}

void CMorningStar::resetCurrentFrame() {
	getCurrentAnimation()->setcurrentFrame(-1);
}

void CMorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
}

void CMorningStar::setAttactMS(bool check,int nx) {
	checkAttact_MS = check;
	ms_nx = nx;
}

void CMorningStar::Render() {
	if (checkAttact_MS) {
		int ani = MSTAR_ANI_ATTACT_RIGHT_LEVEL_1;
		if (ms_nx > 0) {
			ani = MSTAR_ANI_ATTACT_RIGHT_LEVEL_1;
		}
		else {
			ani = MSTAR_ANI_ATTACT_LEFT_LEVEL_1;
		}
		animation_set->at(ani)->Render(x, y);
		//RenderBoundingBox();
	}

	//int ani = -1;
	////this->nx = nx_simon;
	//switch (ms_level)
	//{
	//case mstar_level_1:
	//	if (nx > 0) ani = MSTAR_ANI_ATTACT_RIGHT_LEVEL_1;
	//	else ani = MSTAR_ANI_ATTACT_LEFT_LEVEL_1;
	//	break;
	//case mstar_level_2:
	//	break;
	//case mstar_level_3:
	//	break;
	//default:
	//	break;
	//}
	//animation_set->at(ani)->Render(x,y);
	//RenderBoundingBox();
}

void CMorningStar::SetState(int state)
{
	CGameObject::SetState(state);
}

void CMorningStar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MSTAR_BBOX_WIDTH;
	b = y + MSTAR_BBOX_HEIGHT;
}


void CMorningStar::checktest() {
	
	
	//int a = this->nx;
	DebugOut(L"[INFO] checktestchecktest \n");

}