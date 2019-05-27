#!/bin/bash
# $1 - workdir
# $2 - catmin
# $3 - catmax 
# $4 - signal strength
cat=$1
mu=$2
combine -M FitDiagnostics  --X-rtd FITTER_NEVER_GIVE_UP --X-rtd FITTER_BOUND --X-rtd ADDNLL_RECURSIVE=0 --X-rtd FITTER_NEW_CROSSING_ALGO -t -1 --expectSignal=${mu} --robustFit 1 --rMin=-14 --rMax=14 --skipBOnlyFit -m 125 datacards_singleb_CAT${cat}.txt --cminDefaultMinimizerTolerance 0.01 --saveNormalizations --saveShapes --saveWithUncertainties --saveNLL -v2
mv fitDiagnostics.root mlfit_cat${cat}_r${mu}.root
mv higgsCombineTest.FitDiagnostics.mH125.root limit_cat${cat}_r${mu}.root
cd ../../
