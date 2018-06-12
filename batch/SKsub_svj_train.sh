#!/bin/bash

source exportProd.sh

JOBDIR=jobs
INPUT=input/input_selection_svj_train.txt
SELTYPE=dijetmthad-train
INDIR=root://cmseos.fnal.gov//store/user/lpcsusyhad/SVJ2017/${RUN2PRODV}/Skims/tree_dijetmthad
OUTDIR=tree
STORE=root://cmseos.fnal.gov//store/user/lpcsusyhad/SVJ2017/${RUN2PRODV}/Skims
CHECKARGS=""

#check arguments
while getopts "k" opt; do
  case "$opt" in
  k) CHECKARGS="${CHECKARGS} -k"
    ;;
  esac
done

./SKcheck.sh ${CHECKARGS}

SAMPLES=(
QCD_Pt_1000to1400 \
QCD_Pt_120to170 \
QCD_Pt_1400to1800 \
QCD_Pt_170to300 \
QCD_Pt_1800to2400 \
QCD_Pt_2400to3200 \
QCD_Pt_300to470 \
QCD_Pt_3200toInf \
QCD_Pt_470to600 \
QCD_Pt_600to800 \
QCD_Pt_800to1000 \
QCD_Pt_80to120 \
SVJ2_mZprime-1000_mDark-20_rinv-0.3_alpha-0.2 \
SVJ2_mZprime-2000_mDark-20_rinv-0.3_alpha-0.2 \
SVJ2_mZprime-3000_mDark-100_rinv-0.3_alpha-0.2 \
SVJ2_mZprime-3000_mDark-1_rinv-0.3_alpha-0.2 \
SVJ2_mZprime-3000_mDark-20_rinv-0.1_alpha-0.2 \
SVJ2_mZprime-3000_mDark-20_rinv-0.3_alpha-0.1 \
SVJ2_mZprime-3000_mDark-20_rinv-0.3_alpha-0.2 \
SVJ2_mZprime-3000_mDark-20_rinv-0.3_alpha-0.5 \
SVJ2_mZprime-3000_mDark-20_rinv-0.3_alpha-1 \
SVJ2_mZprime-3000_mDark-20_rinv-0.5_alpha-0.2 \
SVJ2_mZprime-3000_mDark-20_rinv-0.7_alpha-0.2 \
SVJ2_mZprime-3000_mDark-50_rinv-0.3_alpha-0.2 \
SVJ2_mZprime-4000_mDark-20_rinv-0.3_alpha-0.2 \
)

for SAMPLE in ${SAMPLES[@]}
  do
    ./SKtemp.sh ${JOBDIR} ${INPUT} ${SAMPLE} ${SELTYPE} ${INDIR} ${OUTDIR} ${STORE}
  done