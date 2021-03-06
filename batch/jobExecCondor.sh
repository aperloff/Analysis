#!/bin/bash

#
# variables from arguments string in jdl
#

echo "Starting job on " `date` #Only to display the starting of production date
echo "Running on " `uname -a` #Only to display the machine where the job is running
echo "System release " `cat /etc/redhat-release` #And the system release
echo "CMSSW on Condor"

CMSSWVER=$1
INPUT=$2
SNAME=$3
PROCESS=$4
SELTYPE=$5
INDIR=$6
OUTDIR=$7
STORE=$8

echo ""
echo "parameter set:"
echo "CMSSWVER:   $CMSSWVER"
echo "INPUT:      $INPUT"
echo "SNAME:      $SNAME"
echo "PROCESS:    $PROCESS"
echo "SELTYPE:    $SELTYPE"
echo "INDIR:      $INDIR"
echo "OUTDIR:     $OUTDIR"
echo "STORE:      $STORE"

#get sample
source export${SNAME}.sh
SAMPLE=${SAMPLES[$PROCESS]}

source stageOut.sh
tar -xzf ${CMSSWVER}.tar.gz
cd ${CMSSWVER}
scram b ProjectRename
source /cvmfs/cms.cern.ch/cmsset_default.sh
# cmsenv
eval `scramv1 runtime -sh`
cd src/Analysis

#run macro
echo "run: root -b -q -l 'KSkimDriver.C+("'"'$SAMPLE'","'$SELTYPE'","'$INDIR'",{"'$INPUT'"},{},"'$OUTDIR'"'")' 2>&1"
root -b -q -l 'KSkimDriver.C+("'$SAMPLE'","'$SELTYPE'","'$INDIR'",{"'$INPUT'"},{},"'$OUTDIR'")' 2>&1

ROOTEXIT=$?

if [[ $ROOTEXIT -ne 0 ]]; then
  echo "exit code $ROOTEXIT, skipping xrdcp"
  exit $ROOTEXIT
fi

# list output
ls ${OUTDIR}*/*.root

# copy output to eos
echo "xrdcp output for condor"
for TREEDIR in ${OUTDIR}*/; do
  for FILE in ${TREEDIR}/*.root; do
    # FILE contains TREEDIR in path
    stageOut -x "-f" -i ${FILE} -o ${STORE}/${FILE}
    XRDEXIT=$?
    if [[ $XRDEXIT -ne 0 ]]; then
      rm -r ${OUTDIR}*
      echo "exit code $XRDEXIT, failure in xrdcp"
      exit $XRDEXIT
    fi
  done
  rm -r ${TREEDIR}
done



