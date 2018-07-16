#!/bin/csh                                                                                                                                                                                                  
source /phenix/u/vassalli/.cshrc

@ pt20 = ($1 - 400)

#set all files for pT cut 10
set infile = "/sphenix/user/vassalli/HighpTPion/pion1_"$1".dat"              #.dat from pythia
set outfileDST = "/sphenix/user/vassalli/HighpTPion/pion1_DST"$1".root"      #DST.root from Fun4All
set outfileRoot = "/sphenix/user/vassalli/HighpTPion/pion1_"$1".root"  #.root from module (analyze this)

#set all files for pT cut 20                                                                                                                                                                               
#set infile = "/sphenix/user/vassalli/HighpTPion/pion2_"$pt20".dat"              #.dat from pythia
#set outfileDST = "/sphenix/user/vassalli/HighpTPion/pion2_DST"$pt20".root"      #DST.root from Fun4All
#set outfileRoot = "/sphenix/user/vassalli/HighpTPion/pion2_"$pt20".root"  #.root from module (analyze this)

set SCRATCH_AREA="$_CONDOR_SCRATCH_DIR"
set FUN="Fun4All_G4_sPHENIX.C"
set AFTERBURNER="run_macro_isolation.C"
set FUNFRIENDS="/direct/phenix+u/vassalli/sphenix/FunFriends"
set path = ($FUNFRIENDS $path)
mkdir $SCRATCH_AREA/fran_G4pion
cp $FUN $SCRATCH_AREA/fran_G4pion/
cp $AFTERBURNER $SCRATCH_AREA/fran_G4pion/

#run pT cut 10 for first 400 in queue
if ($1 <400) then 
    echo ----RUNNING $FUN----
    echo root -b -q $FUN\(50,\"$infile\",\"$outfileDST\"\)
    root -b -q $FUN\(50,\"$infile\",\"$outfileDST\"\)
    
    echo ---- RUNNING  Analysis Module ----
    echo root -b -q $AFTERBURNER\(\"$outfileDST\",\"$outfileRoot\"\)
    root -b -q $AFTERBURNER\(\"$outfileDST\",\"$outfileRoot\"\)
    
#run pT cut 20 for next 400 in queue
#else if (400<=$1<800) then
#    echo ----RUNNING $(FUN)----
#    root -b -q $(FUN)\(50,\"$infile2\",\"$outfileDST2\"\)
#
#    echo ---- RUNNING  Analysis Module ----
#    root -b -q $(AFTERBURNER)\(\"$outfileDST2\",\"$outfileRoot2\"\)
    
endif
