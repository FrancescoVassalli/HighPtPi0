int run_macro_isolation( 
			std::string infile = "XjPhi3_pT5_98_dst.root",
			std::string outfile = "test_output.root"
	       )
{
  
  gSystem->Load("libfun4all.so");
  gSystem->Load("libg4detectors.so");
  gSystem->Load("libphhepmc.so");
  gSystem->Load("libg4testbench.so");
  gSystem->Load("libg4hough.so");

  gSystem->Load("libg4eval.so");
  gSystem->Load("libcalotrigger.so");
  gSystem->Load("libjetbackground.so");
  gSystem->Load("libclusteriso.so");
  gSystem->Load("libHighPionAnalysis.so");

  int verbosity = 0;

  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity( 0 );
  // just if we set some flags somewhere in this macro
  recoConsts *rc = recoConsts::instance();

  Fun4AllInputManager *hitsin = new Fun4AllDstInputManager("DSTin");
  hitsin->fileopen( infile );
  se->registerInputManager(hitsin);
 
  JetReco *truthjetreco = new JetReco();
  TruthJetInput *tji = new TruthJetInput(Jet::PARTICLE);
  //  tji->add_embedding_flag( 1 );
  truthjetreco->add_input(tji);
  truthjetreco->add_algo(new FastJetAlgo(Jet::ANTIKT,0.4),"AntiKt_Truth_r04");
  truthjetreco->set_algo_node("ANTIKT");
  truthjetreco->set_input_node("TRUTH");
  truthjetreco->Verbosity(0);
  se->registerSubsystem(truthjetreco);

  
/*  RetowerCEMC *rcemc = new RetowerCEMC();
  rcemc->Verbosity( 0 );
  se->registerSubsystem( rcemc );

  DetermineTowerBackground *dtb = new DetermineTowerBackground();
  dtb->SetBackgroundOutputName("TowerBackground_Sub1");
  dtb->SetSeedType( 0 );
  dtb->Verbosity( 0 );
  se->registerSubsystem( dtb );

  CopyAndSubtractJets *casj = new CopyAndSubtractJets();
  casj->Verbosity( 0 );
  se->registerSubsystem( casj );

  DetermineTowerBackground *dtb2 = new DetermineTowerBackground();
  dtb2->SetBackgroundOutputName("TowerBackground_Sub2");
  dtb2->SetSeedType( 1 );
  dtb2->Verbosity( 0 );
  se->registerSubsystem( dtb2 );
  
  SubtractTowers *st = new SubtractTowers();
  st->Verbosity( 0 );
  se->registerSubsystem( st );*/

  JetReco *towerjetreco = new JetReco();
  towerjetreco->add_input(new TowerJetInput(Jet::CEMC_TOWER_SUB1));
  towerjetreco->add_input(new TowerJetInput(Jet::HCALIN_TOWER_SUB1));
  towerjetreco->add_input(new TowerJetInput(Jet::HCALOUT_TOWER_SUB1));
  towerjetreco->add_algo(new FastJetAlgoSub(Jet::ANTIKT,0.4,verbosity),"AntiKt_Tower_r04_Sub1");
  towerjetreco->set_algo_node("ANTIKT");
  towerjetreco->set_input_node("TOWER");
  towerjetreco->Verbosity( 0 );
  se->registerSubsystem(towerjetreco);

  ClusterIso * ci = new ClusterIso("ClusterIsolator",1,3,0,1);
  ci->Verbosity( 0 );
  se->registerSubsystem( ci);
  PionAfterModule *tt = new PionAfterModule( outfile );
  se->registerSubsystem( tt );

  se->run();

  se->End();
  std::cout << "All done" << std::endl;
  delete se;

  gSystem->Exit(0);
}
