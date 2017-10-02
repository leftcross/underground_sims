for i in {61..120}
do

echo "#!/bin/sh" >> ./batch_muon_${i}.sh
echo "#PBS -o /home/shobhit/underground_sims/build/jobs/log/">> ./batch_muon_${i}.sh
echo "#PBS -e /home/shobhit/underground_sims/build/jobs/log/">> ./batch_muon_${i}.sh
echo "source /home/shobhit/underground_sims/build/geant4_env_10.3">> ./batch_muon_${i}.sh
echo "/home/shobhit/underground_sims/build/DAMIC /home/shobhit/underground_sims/build/jobs/macros/muon_${i}.mac">> ./batch_muon_${i}.sh

done
