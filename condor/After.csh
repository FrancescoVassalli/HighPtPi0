#!/bin/csh                                                                                                                                                                                                  
source /phenix/u/vassalli/.cshrc
set NJOBS=400
#@ pt20 = ($1 - $NJOBS)

#set all files for pT cut 10
set outfileDST = "/sphenix/user/vassalli/HighpTPion/DST/pion1_DST"$1".root"      #DST.root from Fun4All
set outfileRoot = "/sphenix/user/vassalli/HighpTPion/pion1_"$1".root"  #.root from module (analyze this)

#set all files for pT cut 20                                                                                                                                                                               
#set outfileDST = "/sphenix/user/vassalli/HighpTPion/pion2_DST"$pt20".root"      #DST.root from Fun4All
#set outfileRoot = "/sphenix/user/vassalli/HighpTPion/pion2_"$pt20".root"  #.root from module (analyze this)

set SCRATCH_AREA="$_CONDOR_SCRATCH_DIR"
set AFTERBURNER="run_macro_isolation.C"
mkdir $SCRATCH_AREA/fran_G4pion
cp $AFTERBURNER $SCRATCH_AREA/fran_G4pion/
cd $SCRATCH_AREA/fran_G4pion/
#run pT cut 10 for first NJOBS in queue
echo ---- RUNNING  Analysis Module ----
if ($1 <$NJOBS) then 
    echo root -b -q $AFTERBURNER\(\"$outfileDST\",\"$outfileRoot\"\)
    root -b -q $AFTERBURNER\(\"$outfileDST\",\"$outfileRoot\"\)
endif
#else if (400<=$1<800) then
#    echo ----RUNNING $(FUN)----
#    root -b -q $(FUN)\(50,\"$infile2\",\"$outfileDST2\"\) #-b to run in batch mode which is faster. -q to quit after it runs. FUN is the name of the root macro then cmoes the arguments 
#
#    echo ---- RUNNING  Analysis Module ----
#    root -b -q $(AFTERBURNER)\(\"$outfileDST2\",\"$outfileRoot2\"\)
#    
#endif
