#include "PionAfterModule.h"

#include <phool/getClass.h>
#include <fun4all/Fun4AllServer.h>

#include <phool/PHCompositeNode.h>

#include "TLorentzVector.h"
#include <iostream>

#include <calotrigger/CaloTriggerInfo.h>

#include <calobase/RawClusterContainer.h>
#include <calobase/RawCluster.h>
#include <calobase/RawClusterUtility.h>

#include <calobase/RawTowerGeom.h>
#include <calobase/RawTower.h>
#include <calobase/RawTowerContainer.h>
#include <calobase/RawTowerGeomContainer_Cylinderv1.h>
#include <calobase/RawTowerGeomContainer.h>

//#include <g4jets/JetMap.h>
//#include <g4jets/Jet.h>

#include <g4main/PHG4TruthInfoContainer.h>
#include <g4main/PHG4Particle.h>

#include <jetbackground/TowerBackground.h>

#include <g4vertex/GlobalVertex.h>
#include <g4vertex/GlobalVertexMap.h>

PionAfterModule::PionAfterModule(const std::string &name) : SubsysReco("TRIGGERTEST")
{

  _foutname = name;

}

int PionAfterModule::Init(PHCompositeNode *topNode)
{

  _f = new TFile( _foutname.c_str(), "RECREATE");

  _tree = new TTree("ttree","a succulent orange tree");
  _tree->SetAutoSave(300);
  _tree->Branch("particle_n", &_b_particle_n,"particle_n/I");
  _tree->Branch("particle_pt", _b_particle_pt,"particle_pt[particle_n]/F");
  _tree->Branch("particle_eta", _b_particle_eta,"particle_eta[particle_n]/F");
  _tree->Branch("particle_phi", _b_particle_phi,"particle_phi[particle_n]/F");
  _tree->Branch("particle_pid", _b_particle_pid,"particle_pid[particle_n]/I");
  _tree->Branch("particle_parentID", _b_particle_parentID,"particle_parentID[particle_n]/I");

  _tree->Branch("cluster_n", &_b_cluster_n,"cluster_n/I");
  _tree->Branch("cluster_pt", _b_cluster_pt,"cluster_pt[cluster_n]/F");
  _tree->Branch("cluster_eta",_b_cluster_eta,"cluster_eta[cluster_n]/F");
  _tree->Branch("cluster_phi",_b_cluster_phi,"cluster_phi[cluster_n]/F");
  _tree->Branch("cluster_iso",_b_cluster_iso,"cluster_iso[cluster_n]/F");

  return 0;

}

int PionAfterModule::process_event(PHCompositeNode *topNode)
{

  std::cout << "DVP : at process_event, tree size is: " << _tree->GetEntries() << std::endl;

  RawTowerContainer *towersEM3old = findNode::getClass<RawTowerContainer>(topNode, "TOWER_CALIB_CEMC");
  //RawTowerContainer *towersEM3 = findNode::getClass<RawTowerContainer>(topNode, "TOWER_CALIB_CEMC_RETOWER");
  //RawTowerContainer *towersEM4 = findNode::getClass<RawTowerContainer>(topNode, "TOWER_CALIB_CEMC_RETOWER_SUB1");
  std::cout << "PionAfterModule::process_event: " << towersEM3old->size() << " TOWER_CALIB_CEMC towers" << std::endl;
  //std::cout << "PionAfterModule::process_event: " << towersEM3->size() << " TOWER_CALIB_CEMC_RETOWER towers" << std::endl;
  //std::cout << "PionAfterModule::process_event: " << towersEM4->size() << " TOWER_CALIB_CEMC_RETOWER_SUB1 towers" << std::endl;

  RawTowerContainer *towersIH3 = findNode::getClass<RawTowerContainer>(topNode, "TOWER_CALIB_HCALIN");
  //RawTowerContainer *towersIH4 = findNode::getClass<RawTowerContainer>(topNode, "TOWER_CALIB_HCALIN_SUB1");
  std::cout << "PionAfterModule::process_event: " << towersIH3->size() << " TOWER_CALIB_HCALIN towers" << std::endl;
  //std::cout << "PionAfterModule::process_event: " << towersIH4->size() << " TOWER_CALIB_HCALIN_SUB1 towers" << std::endl;

  RawTowerContainer *towersOH3 = findNode::getClass<RawTowerContainer>(topNode, "TOWER_CALIB_HCALOUT");
  //RawTowerContainer *towersOH4 = findNode::getClass<RawTowerContainer>(topNode, "TOWER_CALIB_HCALOUT_SUB1");
  std::cout << "PionAfterModule::process_event: " << towersOH3->size() << " TOWER_CALIB_HCALOUT towers" << std::endl;
  //std::cout << "PionAfterModule::process_event: " << towersOH4->size() << " TOWER_CALIB_HCALOUT_SUB1 towers" << std::endl;

  _b_particle_n = 0;
  
  PHG4TruthInfoContainer* truthinfo = findNode::getClass<PHG4TruthInfoContainer>(topNode,"G4TruthInfo");
  PHG4TruthInfoContainer::Range range = truthinfo->GetPrimaryParticleRange();

  GlobalVertexMap* vertexmap = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  float vx=0,vy=0,vz=0;
  if (vertexmap&&!vertexmap->empty())
  {
     GlobalVertex* vertex = (vertexmap->begin()->second);
     vx = vertex->get_x();
     vy = vertex->get_y();
     vz = vertex->get_z();
     std::cout<<"Event Vertex Calculated in ClusterIso x:"<<vx<<" y:"<<vy<<" z:"<<vz<<'\n';
  }
  for ( PHG4TruthInfoContainer::ConstIterator iter = range.first; iter != range.second; ++iter ) {
    PHG4Particle* g4particle = iter->second; // You may ask yourself, why second?
    TLorentzVector t; t.SetPxPyPzE( g4particle->get_px(), g4particle->get_py(), g4particle->get_pz(), g4particle->get_e() );
    float truth_pt = t.Pt();
    float truth_eta = t.Eta();
    if (fabs(truth_eta) > 1.1) continue;
    float truth_phi = t.Phi();
    int truth_pid = g4particle->get_pid();

    _b_particle_pt[ _b_particle_n ] = truth_pt;
    _b_particle_eta[ _b_particle_n ] = truth_eta;
    _b_particle_phi[ _b_particle_n ] = truth_phi;
    _b_particle_pid[ _b_particle_n ] = truth_pid;
    PHG4Particle* parent = truthinfo->GetParticle(g4particle->get_parent_id());
    if(parent==nullptr){
       _b_particle_parentID[_b_particle_n] =0;
       std::cout<<"Parent is NULL"<<std::endl;
    }
    else{
      _b_particle_parentID[_b_particle_n] = parent->get_pid();
    }
    _b_particle_n++;
  }

  _b_cluster_n = 0;

  {
    RawClusterContainer *clusters = findNode::getClass<RawClusterContainer>(topNode,"CLUSTER_CEMC");
    RawClusterContainer::ConstRange begin_end = clusters->getClusters();
    RawClusterContainer::ConstIterator rtiter;
    for (rtiter = begin_end.first; rtiter !=  begin_end.second; ++rtiter) {
      RawCluster *cluster = rtiter->second;
      CLHEP::Hep3Vector vertex( vx, vy, vz );
      CLHEP::Hep3Vector E_vec_cluster = RawClusterUtility::GetEVec(*cluster, vertex);
      float cluster_energy = E_vec_cluster.mag();
      float cluster_eta = E_vec_cluster.pseudoRapidity();
      float pt = cluster_energy / cosh( cluster_eta );
      if (pt < 2) continue;
      _b_cluster_eta[ _b_cluster_n ] =  cluster_eta;
      _b_cluster_phi[ _b_cluster_n ] =  cluster->get_phi();
      _b_cluster_pt[ _b_cluster_n ] = pt;
      _b_cluster_iso[ _b_cluster_n ] =  cluster->get_et_iso(3,0,1);
      std::cout << " cluster (CEMC) # " << _b_cluster_n << " pt/eta/phi = " << pt << " / " << cluster_eta << " / " << cluster->get_phi() << std::endl;
      _b_cluster_n++;
    }
  }
  _tree->Fill();
  return 0;
}



int PionAfterModule::End(PHCompositeNode *topNode)
{
  std::cout<<"Pion Analysis Done \n";
  _tree->Write();
  _f->Write();
  _f->Close();

  return 0;
}

