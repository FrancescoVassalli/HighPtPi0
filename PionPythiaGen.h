//This file is really -*- C++ -*-

#ifndef PionPythiaGen_h
#define PionPythiaGen_h 
#include <Pythia8/Pythia.h>
#include <Pythia8Plugins/HepMC2.h> //added plugin for HepMC, think we will need some new library in pythia for this
#include <TFile.h>
#include <TTree.h>
//#include "Utils.C" 
class Particle;


class PionPythiaGen
{
public:
	PionPythiaGen(const std::string name) : m_name(name){}
	~PionPythiaGen(){
		if (m_initialized)
		{
			if (m_tfile!=nullptr)
			{
				m_ttree->Write();
				m_tfile->Close(); //deletes the ttree
				delete m_tfile;
				m_tfile=nullptr;
			}
			if (m_pythiaengine!=nullptr)
			{
				delete m_pythiaengine;
				m_pythiaengine=nullptr;
			}
			if (m_ToHepMC!=nullptr)
			{
				delete m_ToHepMC;
				delete m_ascii_io;
				m_ToHepMC=nullptr;
				m_ascii_io=nullptr;
			}
		}
	}
	void init(std::string pThat);
	void run(long nEvents, float pTCut);

private:
	TFile *m_tfile=nullptr;
	TTree *m_ttree=nullptr;
	std::string m_name;
	Pythia8::Pythia *m_pythiaengine;
	HepMC::Pythia8ToHepMC *m_ToHepMC;    // Interface for conversion from Pythia8::Event to HepMC event.
    HepMC::IO_GenEvent *m_ascii_io; //file where HepMC events will be stored.
    bool m_initialized=false;
	static const int m_kMAXFINALPARTICLES=300;
  	int m_b_end;
  	int m_b_id[m_kMAXFINALPARTICLES];
  	float m_b_pT[m_kMAXFINALPARTICLES];
  	float m_b_eta[m_kMAXFINALPARTICLES];
  	float m_b_eT[m_kMAXFINALPARTICLES];
	float m_b_e[m_kMAXFINALPARTICLES];

	void pythiaInit(std::string pThat);
	void hepInit();
	void treeInit();
	bool cut(Pythia8::Particle p, float gammaCut);
	
};

#endif //PionPythiaGen_h