#!/bin/csh                                                                                                                                                                                                  

source /phenix/u/vassalli/.cshrc

@ pt15 = ($1 - 500)
@ pt25 = ($1 - 600)
@ pt35 = ($1 - 650)


#set all files for pTHatMin 5
set infile = "/sphenix/user/chase/XjPhi_separated/XjPhi_pT5_"$1".dat"              #.dat from root
set outfileDST = "/sphenix/user/chase/XjPhi_separated/direct_output/XjPhi_pT5_DST_"$1".root"      #DST.root from Fun4All
set outfileRoot = "/sphenix/user/chase/XjPhi_separated/direct_output/XjPhi_pT5_output_direct_"$1".root"  #.root from module (analyze this)

#set all files for pTHatMin 15                                                                                                                                                                               
set infile2 = "/sphenix/user/chase/XjPhi3_pT5/XjPhi3_pT15_"$pt15".dat"
set outfileDST2 = "/sphenix/user/chase/HEPsimout/XjPhi3_pT5_DST_"$pt15".root"
set outfileRoot2 = "/sphenix/user/chase/HEPsimout/XjPhi3_pT5_output_"$pt15".root"

#set all files for pTHatMin 25                                                                                                                                                                               
set infile3 = "/sphenix/user/chase/XjPhi3_pT5/XjPhi3_pT25_"$pt25".dat"
set outfileDST3 = "/sphenix/user/chase/HEPsimout/XjPhi3_pT25_DST_"$pt25".root"
set outfileRoot3 = "/sphenix/user/chase/HEPsimout/XjPhi3_pT25_output_"$pt25".root"

#set all files for pTHatMin 35                                                                                                                                                                               
set infile4 = "/sphenix/user/chase/XjPhi3_pT5/XjPhi3_pT35_"$pt35".dat"
set outfileDST4 = "/sphenix/user/chase/HEPsimout/XjPhi3_pT35_DST_"$pt35".root"
set outfileRoot4 = "/sphenix/user/chase/HEPsimout/XjPhi3_pT35_output_"$pt35".root"


#run pTHatmin = 5 for first 500 in queue
if ($1 <10000) then 
    echo ----RUNNING Fun4All_G4_sPHENIX.C----
    echo root -b -q Fun4All_G4_sPHENIX.C\(0,\"$infile\",\"$outfileDST\"\)
    root -b -q Fun4All_G4_sPHENIX.C\(0,\"$infile\",\"$outfileDST\"\)
    
    #echo ---- RUNNING  Analysis Module ----
    echo root -b -q run_macro_isolation.C\(\"$outfileDST\",\"$outfileRoot\"\)
    root -b -q run_macro_isolation.C\(\"$outfileDST\",\"$outfileRoot\"\)
    
#run pTHatmin = 15 for next 100 in queue
else if ($1 > 10000 && $1 <16000) then
    echo ----RUNNING Fun4All_G4_sPHENIX.C----
    root -b -q Fun4All_G4_sPHENIX.C\(0,\"$infile2\",\"$outfileDST2\"\)

    echo ---- RUNNING  Analysis Module ----
    root -b -q run_macro_isolation.C\(\"$outfileDST2\",\"$outfileRoot2\"\)
    

#run pTHatmin = 25 for next 500 in queue
else if ($1 > 15909 && $1<16500) then
    echo ----RUNNING Fun4All_G4_sPHENIX.C----
    root -b -q Fun4All_G4_sPHENIX.C\(0,\"$infile3\",\"$outfileDST3\"\)

    echo ---- RUNNING  Analysis Module ----
    root -b -q run_macro_isolation.C\(\"$outfileDST3\",\"$outfileRoot3\"\)
    #rm $outfileDST3

#run pTHatmin = 35 for next 50 in queue
else
    echo ----RUNNING Fun4All_G4_sPHENIX.C----
    root -b -q Fun4All_G4_sPHENIX.C\(0,\"$infile4\",\"$outfileDST4\"\)

    echo ---- RUNNING  Analysis Module ----
    root -b -q run_macro_isolation.C\(\"$outfileDST4\",\"$outfileRoot4\"\)
    #rm $outfileDST4

endif
