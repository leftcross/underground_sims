#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <iostream>
#include <TCanvas.h>
#include <TBrowser.h>
#include <vector>
#include <stdio.h>      // For sprintf
#include <TStyle.h>
#include <TGaxis.h>
#include <TRandom.h>
#include <TMath.h>
#include <TROOT.h>
#include <TText.h>
#include <TPaveText.h>
#include <TString.h>
#include "TLegend.h"
#include "TCanvas.h"



int PlotDistribution(char const* ifname="./muon_cosmic_1.root")
{
	TFile* fileroot=new TFile(ifname,"READ");

	if (!fileroot || !fileroot->IsOpen())
	{
	 	cerr<<"Either the file is already open or the program can't find the given file!!\n";
	 	return 1;
	}
	else
		std::cout<<"File read successfully\n";

	TTree* inptree=(TTree*)fileroot->Get("tree1");
	if(!inptree)
		std::cerr<<"Tree not found \n";
	else
		std::cout<<"Tree read successfully \n";

	// Entries for the ttree

	Int_t EventID,trackID,stepID,partPDG,stepNsecondaries,partMotherID;
	Double_t primEnergy,primX,primY,primZ,partEtot;
	Double_t partEkin,partX,partY,partZ,stepEdep;
	Double_t stepEdep_nonIon,stepLength;
	Char_t partCreatorProcess[100],stepProcess[100],stepVolume[100],stepNextVolume[100];
	Char_t stepMaterial[100],stepNextMaterial[100];

	inptree->SetBranchAddress("EventID",&EventID);
	inptree->SetBranchAddress("primEnergy",&primEnergy);
	inptree->SetBranchAddress("primX",&primX);
	inptree->SetBranchAddress("primY",&primY);
	inptree->SetBranchAddress("primZ",&primZ);
	inptree->SetBranchAddress("trackID",&trackID);
	inptree->SetBranchAddress("stepID",&stepID);
	inptree->SetBranchAddress("partPDG",&partPDG);
	inptree->SetBranchAddress("partEtot",&partEtot);
	inptree->SetBranchAddress("partEkin",&partEkin);
	inptree->SetBranchAddress("partX",&partX);
	inptree->SetBranchAddress("partY",&partY);
	inptree->SetBranchAddress("partZ",&partZ);
	inptree->SetBranchAddress("partCreatorProcess",partCreatorProcess);
	inptree->SetBranchAddress("stepProcess",stepProcess);
	inptree->SetBranchAddress("stepEdep",&stepEdep);
	inptree->SetBranchAddress("stepEdep_nonIon",&stepEdep_nonIon);
	inptree->SetBranchAddress("stepLength",&stepLength);
	inptree->SetBranchAddress("stepVolume",stepVolume);
	inptree->SetBranchAddress("stepNextVolume",stepNextVolume);
	inptree->SetBranchAddress("stepMaterial",stepMaterial);
	inptree->SetBranchAddress("stepNextMaterial",stepNextMaterial);
	inptree->SetBranchAddress("stepNsecondaries",&stepNsecondaries);
	inptree->SetBranchAddress("partMotherID",&partMotherID);

	// Firt of all, I will find unique event ids
	Int_t nentries=inptree->GetEntries();

	std::vector<int> vec_eventid;
	int NumUniqueEventID=0;

	for(int i=0;i<nentries;i++)
	{
		inptree->GetEntry(i);
		bool foundentry=false;
		for(int j=0;j<vec_eventid.size();j++)
		{
			foundentry=foundentry||(vec_eventid.at(j)==EventID);
		}
		if(!foundentry)
		{
			NumUniqueEventID++;
			vec_eventid.push_back(EventID);
		}
			
	}


	std::cout<<"Number of unique entries are "<<NumUniqueEventID<<" out of " <<nentries<<std::endl;


	return(0);
}