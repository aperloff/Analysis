#!/bin/bash

#
# variables from arguments string in jdl
#

echo "Starting job on " `date` #Only to display the starting of production date
echo "Running on " `uname -a` #Only to display the machine where the job is running
echo "System release " `cat /etc/redhat-release` #And the system release
echo "CMSSW on Condor"

CMSSWVER=$1
INDIR=$2
SYSTS=$3
VARS=$4
STORE=$5
SNAME=$6
PROCESS=$7

echo ""
echo "parameter set:"
echo "CMSSWVER:   $CMSSWVER"
echo "INDIR:      $INDIR"
echo "SYSTS:      $SYSTS"
echo "VARS:       $VARS"
echo "STORE:      $STORE"
echo "SNAME:      $SNAMEE"
echo "PROCESS:    $PROCESS"

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
echo "run: root -b -q -l 'MakeAllDCsyst.C+(1,"'"'$SAMPLE'","'$INDIR'","'$SYSTS'","'$VARS'"'")' 2>&1"
root -b -q -l 'MakeAllDCsyst.C+(1,"'$SAMPLE'","'$INDIR'","'$SYSTS'","'$VARS'")' 2>&1

ROOTEXIT=$?

if [[ $ROOTEXIT -ne 0 ]]; then
  rm *.root
  echo "exit code $ROOTEXIT, skipping xrdcp"
  exit $ROOTEXIT
fi

# copy output to eos
echo "xrdcp output for condor"
for FILE in *.root
do
  echo "xrdcp -f ${FILE} ${STORE}/${FILE}"
  stageOut -x "-f" -i ${FILE} -o ${STORE}/${FILE}
  XRDEXIT=$?
  if [[ $XRDEXIT -ne 0 ]]; then
    rm *.root
    echo "exit code $XRDEXIT, failure in xrdcp"
    exit $XRDEXIT
  fi
  rm ${FILE}
done



