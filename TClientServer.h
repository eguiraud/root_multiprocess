#ifndef ROOT_TClientServer
#define ROOT_TClientServer

#include "TMessage.h"
#include "TString.h"
#include "TMonitor.h"
#include "TJob.h"
#include <string>
#include "TNote.h"

class TClientServer {
	//ClassDef(TClientServer, 1);
	public:
	TClientServer();
	~TClientServer();
	
	void Fork(unsigned n_forks = 0);
	void Broadcast(TNote::ECode code, const TString& msg = "");
	void Collect();
	void CollectOne(TSocket* = nullptr);
	void SetMacroPath(const TString&);
	void Send(TNote::ECode code, const TString& msg = "", TSocket * = nullptr) const;
	
	TList* fResList;
	TJob *fJob;
	
	private:
	void Run();
	void ClientHandleInput(TMessage*&, TSocket*);
	void ServerHandleInput(TMessage*&);
	void Send(const TMessage&, TSocket * = nullptr) const;

	bool fIsParent;
	unsigned fPortN;
	unsigned fActiveServerN;
	unsigned fTotServerN;
	unsigned fNWorkers;
	TMonitor fMon;
	TString fMacroPath;
};

#endif
