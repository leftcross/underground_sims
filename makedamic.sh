source $GEANT4_DIR/bin/geant4.sh
cmake -DGeant4_DIR=$GEANT4_DIR/lib64/Geant4-10.3.2/ ../
make -j5
make install

