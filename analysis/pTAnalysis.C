#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLegend.h"

void analyze(TChain* interest){

  TH1F *frag_pT = new TH1F("frag_pT","",20,10,40); 
  frag_pT->Sumw2();

  int truthID[300];
  float truthpT[300];
  float trutheta[300];
  float truthphi[300];
  int truthend;

  interest->SetBranchAddress("particle_n",&truthend);
  interest->SetBranchAddress("truthID",&truthID);
  interest->SetBranchAddress("truthpT",&truthpT);
  interest->SetBranchAddress("trutheta",&trutheta);
  interest->SetBranchAddress("truthphi",&truthphi);
  
  int cluster_n;
  float cluster_pt[300];
  float cluster_eta[300];
  float cluster_phi[300];
  float iso_eT[300];

  interest->SetBranchAddress("cluster_n",&cluster_n);
  interest->SetBranchAddress("cluster_pt",&cluster_pt);
  interest->SetBranchAddress("cluster_phi",&cluster_phi);
  interest->SetBranchAddress("cluster_eta",&cluster_eta);
  interest->SetBranchAddress("iso_eT",&iso_eT);

  int nEvent = interest->GetEntries();
  for(int i = 0; i < nEvent; i++) //loop over events
  {
    interest->GetEvent(i);
    for(int j = 0; j < truthend; j++)
    {
      if(pT[j]>10 and ID[j]==111 and fabs(eta[j]) < 1.1) //pion in the eta range 
      {
        frag_pT->Fill(pT[j]);
      }
    }
  }
}

void handleG4File(string name, string extension, int filecount){
  TChain *all = new TChain("ttree");
  string temp;
  for (int i = 0; i < filecount; ++i)
  {
    temp = name+to_string(i)+extension;
    all->Add(temp.c_str());
  }
  analyze(all);
  delete all;
}

void pTAnalysis(){
  string fileLocation = "/home/user/Droptemp/Pions/";
  string filename = "pion1_";
  string extension = ".root";
  string temp = fileLocation+filename;
  handleG4File(temp,extension,400);
}