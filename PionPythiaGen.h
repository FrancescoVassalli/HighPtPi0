//This file is really -*- C++ -*-

#ifndef PionPythiaGen_h
#define PionPythiaGen_h 
#include "TFile.h"
#include "TTree.h"
#include "Pythia8/Pythia.h"
#include "Utils.C" 



class PionPythiaGen
{
public:
	PionPythiaGen(const string name, string pTHat);
	~PionPythiaGen(){
		ttree->Write();
		file->Close(); //deletes the ttree
		delete file;
		file=nullptr;
		delete pythiaengine
		pythiaengine=nullptr;
		delete ToHepMC
		ToHepMC=nullptr;
		delete ascii_io_direct
		ascii_io_direct=nullptr;
	}
private:
	TFile *m_tfile;
	TTree *m_ttree;
	string m_name;
	Pythia *m_pythiaengine;
	HepMC::Pythia8ToHepMC *ToHepMC;    // Interface for conversion from Pythia8::Event to HepMC event.
    HepMC::IO_GenEvent *ascii_io_direct; //file where HepMC events will be stored.
    bool initialized=false
	static const int m_kMAXFINALPARTICLES=300;
  	int m_b_end;
  	int m_b_id[MAXFINALPARTICLES];
  	float m_b_pT[MAXFINALPARTICLES];
  	float m_b_eta[MAXFINALPARTICLES];
  	float m_b_eT[MAXFINALPARTICLES];
	float m_b_e[MAXFINALPARTICLES];

	void init(string pThat);
	void pythiaInit(string pThat);
	void hepInit();
	void treeInit();

	void run(long nEvents, float pTCut);
	
};
inline bool cut(Particle p, float gammaCut){
	return p.id()==111&&p.pT()>gammaCut&&TMath::Abs(p.eta())<1.1;
}
#endif //PionPythiaGen_h