#!/bin/csh 
#This is the condor shell script for 10GeV pion, note pTHatMin should be 5GeV
                                                                                                                                            

#-------------------                                                                                                                                 
# Arguments                                                                                                               
#-------------------                                                                                                                                  

@ p = $1

#-------------------                                                                                                                                
# Variable Defs                                                                                                                                      
#-------------------                                                                                                                                  

set OUT_FILE="/sphenix/user/vassalli/HighpTPion"

set SCRATCH_AREA="$_CONDOR_SCRATCH_DIR"                                                                                                              
#set SCRATCH_AREA="/phenix/scratch/chase"

set DRIVER="/direct/phenix+u/vassalli/HighPtPi0/driver"

#-------------------                                                                                                                                
# Export Libraries                                                                                                                                   
#-------------------                                                                                                                                  

source /phenix/u/vassalli/.cshrc

#-------------------                                                                                                                                 
# Set Scratch Area                                                                                                                                   
#-------------------                                                                                                                                  

mkdir $SCRATCH_AREA/fran_pion
cp  $DRIVER $SCRATCH_AREA/fran_pion/

#-------------------                                                                                                                                
# Run Executable  
#-------------------                                                                                                                                  
cd $SCRATCH_AREA/fran_pion
./driver pion1_${1} 5 10 50
ls
cp pion1_${1}* $OUT_FILE

rm -r $SCRATCH_AREA/fran_pion

exit 0
