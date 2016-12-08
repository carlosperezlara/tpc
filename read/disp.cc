#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TEllipse.h"

int main(int,char**) {
  TFile *file = new TFile("OutFileTPC.root");
  file->ls();
  TTree *t = (TTree*) file->Get("Hits");
  std::vector<double> *xx, *yy, *zz, *ee;
  TBranch *bx=0, *by=0, *bz=0, *be=0;
  t->SetBranchAddress("x",&xx,&bx);
  t->SetBranchAddress("y",&yy,&by);
  t->SetBranchAddress("z",&zz,&bz);
  t->SetBranchAddress("edep",&ee,&be);
  TH2F *hXYG1 = new TH2F("hXYG1",";X;Y",140,-82,+82,100,-82,+82);
  TH2F *hXYG2 = new TH2F("hXYG2",";x/r2;y/r2",200,-0.04,+0.04,200,-0.04,+0.04);
  TH2F *hXY1 = new TH2F("hXY1",";X;Y",140,-82,+82,100,-82,+82);
  TH2F *hXY2 = new TH2F("hXY2",";x/r2;y/r2",200,-0.04,+0.04,200,-0.04,+0.04);
  //t->Print();
  //t->Scan();
  TEllipse *eli = new TEllipse();
  TCanvas *canvas = new TCanvas("canvas","canvas",1200,600);
  canvas->Divide(2,1);
  canvas->SaveAs("output.pdf[","pdf");
  Long64_t en = t->GetEntries();
  for(Long64_t i=0; i<en; ++i) {
    std::cout << 100*i/en << std::endl;
  	Long64_t ii = t->LoadTree(i);
    std::cout << "Reading " << en << std::endl;
  	bx->GetEntry(ii);
    std::cout << "Reading " << en << std::endl;
  	by->GetEntry(ii);
    std::cout << "Reading " << en << std::endl;
  	bz->GetEntry(ii);
    std::cout << "Reading " << en << std::endl;
  	be->GetEntry(ii);
    std::cout << "Reading " << en << std::endl;
  	t->GetEntry(i);
    std::cout << "Reading " << en << std::endl;
    int size = xx->size();
    std::cout << "Reading " << size << std::endl;
    hXY1->Reset();
    hXY2->Reset();
  	for(UInt_t k=0; k!=size; ++k) {
      double x = xx->at(k);
      double y = yy->at(k);
      double z = zz->at(k);
      double r = sqrt(x*x+y*y);
      double tant = y/x;
      double xp = x/r/r;
      double yp = y/r/r;
      hXY1->Fill(x,y);
      hXYG1->Fill(x,y);
      hXY2->Fill(xp,yp);
      hXYG2->Fill(xp,yp);
    }
    canvas->cd(1);
    hXY1->Draw("colz");
    eli->DrawEllipse(0,0,80,80,0,360,0);
    eli->DrawEllipse(0,0,30,30,0,360,0);
    hXY1->Draw("colz same");
    canvas->cd(2);
    hXY2->Draw("colz");
    canvas->SaveAs("output.pdf","pdf");
  }
  canvas->cd(1);
  hXYG1->Draw("colz");
  eli->DrawEllipse(0,0,80,80,0,360,0);
  eli->DrawEllipse(0,0,30,30,0,360,0);
  hXYG1->Draw("colz same");
  canvas->cd(2);
  hXYG2->Draw("colz");
  canvas->SaveAs("output.pdf","pdf");
  canvas->SaveAs("output.pdf]","pdf");
  return 0;
}
