#ifndef __CLIENT_TRACKEDNODEMGR_H__
#define __CLIENT_TRACKEDNODEMGR_H__

#include "trackednodemgr.h"

class CClientTrackedNodeMgr;
extern CClientTrackedNodeMgr* g_pClientTrackedNodeMgr;

class CClientTrackedNodeMgr : public CTrackedNodeMgr
{
public:
	 CClientTrackedNodeMgr();
	~CClientTrackedNodeMgr();
};


#endif

