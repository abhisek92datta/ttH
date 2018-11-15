python pileupCalc.py -i '../../data/JSON/2017/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt' --inputLumiJSON '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt' --calcMode 'true' --minBiasXsec 69200 --maxPileupBin 98 --numPileupBins 98  output.root

python pileupCalc.py -i '../../data/JSON/2017/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt' --inputLumiJSON '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt' --calcMode 'true' --minBiasXsec 72383 --maxPileupBin 98 --numPileupBins 98  output_up.root

python pileupCalc.py -i '../../data/JSON/2017/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt' --inputLumiJSON '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt' --calcMode 'true' --minBiasXsec 66017 --maxPileupBin 98 --numPileupBins 98  output_down.root

root -l -q PU_data_hist_prod.C

g++ PU_hist_calc.cc -o PU_hist_calc

./PU_hist_calc

mv PU_weights.txt ../../data/PU_weight/

rm -rf PU_hist_calc PU_Data.txt output.root output_up.root output_down.root
