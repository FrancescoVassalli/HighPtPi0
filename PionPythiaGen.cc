#include "PionPythiaGen.h"
#include <string>

using namespace std;
using namespace Pythia8;


void PionPythiaGen::pythiaInit(string pTHat){
	m_pythiaengine = new Pythia();
	m_pythiaengine->readString("Beams:eCM = 200."); //LHC VS RHIC
  	m_pythiaengine->readString("HardQCD:gg2gg = on");
  	m_pythiaengine->readString("HardQCD:gg2qqbar = on");
  	m_pythiaengine->readString("HardQCD:qg2qg = on");
  	m_pythiaengine->readString("HardQCD:qq2qq = on");
  	m_pythiaengine->readString("HardQCD:qqbar2gg = on");
  	m_pythiaengine->readString("HardQCD:qqbar2qqbarNew = on");
  	//m_pythiaengine->readString("PromptPhoton:qg2qgamma = on");
  	//m_pythiaengine->readString("PromptPhoton:qqbar2ggamma = on");
  	m_pythiaengine->readString("Random::setSeed = on");
  	m_pythiaengine->readString("Random::seed =0");
  	pTHat = "PhaseSpace:pTHatMin = "+pTHat+".";
  	m_pythiaengine->readString(pTHat);
  	m_pythiaengine->init();
}

void PionPythiaGen::treeInit(){
	string name = m_name+"root";
	m_tfile = new TFile(name.c_str(),"RECREATE");
  m_ttree = new TTree(m_name.c_str(),m_name.c_str());
  m_ttree->SetAutoSave(3000);
  m_ttree->Branch("m_b_end",&m_b_end);
  m_ttree->Branch("id",m_b_id,"m_b_[m_b_end]/F");
  m_ttree->Branch("pT",m_b_pT,"m_b_[m_b_end]/F");
  m_ttree->Branch("eta",m_b_eta,"m_b_[m_b_end]/F");
  m_ttree->Branch("eT",m_b_eT,"m_b_[m_b_end]/F");
	m_ttree->Branch("e",m_b_e,"m_b_[m_b_end]/F");
}

void PionPythiaGen::hepInit(){
  m_ToHepMC = new HepMC::Pythia8ToHepMC();    // Interface for conversion from Pythia8::Event to HepMC event.
  string name = m_name+".dat";
  m_ascii_io = new HepMC::IO_GenEvent(name, std::ios::out);
}

void PionPythiaGen::init(string pThat){
	pythiaInit(pThat);
  hepInit();
	//treeInit(); no tree for now
	m_initialized=true;
}

void PionPythiaGen::run(long nEvents, float pTCut){
  int iEvent=0;
	 while (iEvent < nEvents)
  	{
  		if (!m_pythiaengine->next()){
      		cout<<"pythia.next() failed"<<"\n";
      		iEvent--;
      		continue;
    	}

    	for (int i = 0; i < m_pythiaengine->event.size(); ++i)
    	{
    		int finalcount=0;
    		if (cut(m_pythiaengine->event[i],pTCut)) //cut
    		{
    			
    			HepMC::GenEvent* hepmcevt = new HepMC::GenEvent(); //create HepMC "event" for frag photons
          		m_ToHepMC->fill_next_event(*m_pythiaengine, hepmcevt ); //convert event from pythia to HepMC
          		*m_ascii_io << hepmcevt;//write event to file
          		delete hepmcevt; //delete event so it can be redeclared next time
    			
    			/*fill the tree*/ 
  				//no tree for now
  				//m_ttree->Fill();
          iEvent++;
     			break;
    		}
    	}
  	}
}

bool PionPythiaGen::cut(Pythia8::Particle p, float gammaCut){
	return p.id()==111&&p.pT()>gammaCut&&TMath::Abs(p.eta())<1.1;
}
