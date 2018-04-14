#include "recvbytesfromop.h"
using namespace WONAPI;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
RecvBytesFromOp::RecvBytesFromOp(unsigned short theMaxBytes, AsyncSocket *theSocket) : SocketOp(theSocket)
{
	mSocketEvent[SocketEvent_Read] = true;

	mMaxBytes = theMaxBytes;
	mCurRecv = NULL;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
RecvBytesFromOp::~RecvBytesFromOp()
{
	delete mCurRecv;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void RecvBytesFromOp::RunHook()
{
	if(mCurRecv==NULL)
		mCurRecv = new char[mMaxBytes];

	mRecvBytes = NULL;

	SocketOp::RunHook();
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
WONStatus RecvBytesFromOp::Continue() 
{ 
	mSocket->WaitForRead(TimeLeft());

	int aRecvLen = 0;
	WONStatus aStatus;
	
	if(mSocket->IsConnected())
	{
		mAddr = mSocket->GetDestAddr();
		aStatus = mSocket->RecvBytes(mCurRecv,mMaxBytes,&aRecvLen);
	}
	else
		aStatus = mSocket->RecvBytesFrom(mCurRecv,mMaxBytes,&mAddr,&aRecvLen);
	
	if(aStatus==WS_Success)
	{
		mRecvBytes = new ByteBuffer(mCurRecv,aRecvLen,true);
		mCurRecv = NULL;
	}
	
	return aStatus;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

