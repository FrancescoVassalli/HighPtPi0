


void PionPythiaGen::pythiaInit(string pThat){
	m_pythiaengine = new Pythia();
	ythiaengine->readString("Beams:eCM = 200."); //LHC VS RHIC
  	pythiaengine->readString("HardQCD:gg2gg = on");
  	pythiaengine->readString("HardQCD:gg2qqbar = on");
  	pythiaengine->readString("HardQCD:qg2qg = on");
  	pythiaengine->readString("HardQCD:qq2qq = on");
  	pythiaengine->readString("HardQCD:qqbar2gg = on");
  	pythiaengine->readString("HardQCD:qqbar2qqbarNew = on");
  	pythiaengine->readString("PromptPhoton:qg2qgamma = on");
  	pythiaengine->readString("PromptPhoton:qqbar2ggamma = on");
  	pythiaengine->readString("Random::setSeed = on");
  	pythiaengine->readString("Random::seed =0");
  	pTHat = "PhaseSpace:pTHatMin = "+pTHat+".";
  	pythiaengine->readString(pTHat);
  	pythiaengine->init();
}

void PionPythiaGen::treeInit(){
	string name = m_name."root";
	m_tfile = new TFile(name.c_str(),"RECREATE");
  	m_ttree = new TTree(m_name.c_str(),m_name.c_str());
  	m_ttree->SetAutoSave(3000);
  	ttree->Branch("m_b_end",&m_b_end);
  	ttree->Branch("id",m_b_id,"m_b_[m_b_end]/F");
  	ttree->Branch("pT",m_b_pT,"m_b_[m_b_end]/F");
  	ttree->Branch("eta",m_b_eta,"m_b_[m_b_end]/F");
  	ttree->Branch("eT",m_b_eT,"m_b_[m_b_end]/F");
	ttree->Branch("e",m_b_e,"m_b_[m_b_end]/F");
}

void PionPythiaGen::hepInit(){
	ToHepMC = new HepMC::Pythia8ToHepMC();   
    ascii_io_direct =new HepMC::IO_GenEvent(m_name+".dat", std::ios::out); 

}

void PionPythiaGen::init(string pThat){
	pythiaInit(pThat);
	//treeInit(); no tree for now
	hepInit();
}

void PionPythiaGen::run(long nEvents, float pTCut){
	 for (int iEvent = 0; iEvent < nEvents; ++iEvent)
  	{
  		if (!pythiaengine->next()){
      		cout<<"pythia.next() failed"<<"\n";
      		iEvent--;
      		continue;
    	}

    	for (int i = 0; i < pythiaengine->event.size(); ++i)
    	{
    		int finalcount=0;
    		if (cut(pythiaengine->event[i])) //cut
    		{
    			
    			HepMC::GenEvent* hepmcevtfrag = new HepMC::GenEvent(); //create HepMC "event" for frag photons
          		ToHepMC_frag->fill_next_event( pythiaengine, hepmcevtfrag ); //convert event from pythia to HepMC
          		ascii_io_frag << hepmcevtfrag;//write event to file
          		delete hepmcevtfrag; //delete event so it can be redeclared next time
    			
    			/*fill the tree*/ 
  				//no tree for now
  				//ttree->Fill();
     			break;
    		}
    	}
  	}
}
