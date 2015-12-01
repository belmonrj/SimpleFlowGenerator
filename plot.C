void plot()
{

  TCanvas *c1 = new TCanvas();

  TFile *file = TFile::Open("out.root");

  TH1D *th1d_v2pT_true = ((TProfile *)file->Get("tp1d_v2pT_true"))->ProjectionX();
  TH1D *th1d_v2pT_reco = ((TProfile *)file->Get("tp1d_v2pT_reco"))->ProjectionX();
  TH1D *th1d_d2pT = ((TProfile *)file->Get("tp1d_d2pT"))->ProjectionX();
  TH1D *th1d_c2 = ((TProfile *)file->Get("tp1d_c2"))->ProjectionX();

  th1d_v2pT_true->SetMaximum(0.25);
  th1d_v2pT_true->SetMinimum(0.0);
  th1d_v2pT_true->GetYaxis()->SetTitle("v_{2}, various methods");
  th1d_v2pT_true->GetYaxis()->SetTitleOffset(1.2);
  th1d_v2pT_true->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  th1d_v2pT_true->SetLineColor(kBlack);
  th1d_v2pT_true->Draw();

  th1d_v2pT_reco->SetLineColor(kRed);
  th1d_v2pT_reco->Draw("same");

  float c2 = th1d_c2->GetBinContent(1);
  th1d_d2pT->Scale(1.0/sqrt(c2));
  th1d_d2pT->SetLineColor(kBlue);
  th1d_d2pT->Draw("same");

  // ---
  TH1D *th1d_p4pT = ((TProfile *)file->Get("tp1d_p4pT"))->ProjectionX();
  TH1D *th1d_p4 = ((TProfile *)file->Get("tp1d_p4"))->ProjectionX();
  float p4 = th1d_p4->GetBinContent(1);
  float c4 = p4 - 2.0*c2*c2;
  if(c4>0){cout << "LOLOMGWTF" << endl; c4 *= -1;}
  float k4 = pow(-c4,0.75);
  th1d_p4pT->Scale(1.0/k4);
  th1d_p4pT->SetLineColor(kGreen+2);
  th1d_p4pT->Draw("same");
  cout << sqrt(c2) << " " << pow(-c4,0.25) << endl;
  // ---

  TLegend *leg = new TLegend(0.68,0.18,0.88,0.38);
  leg->AddEntry(th1d_v2pT_true,"truth","elp");
  leg->AddEntry(th1d_v2pT_reco,"v_{2}{#Psi_{2}}","elp");
  leg->AddEntry(th1d_d2pT,"v_{2}{2}","elp");
  leg->AddEntry(th1d_p4pT,"v_{2}{4}","elp");
  leg->SetTextSize(0.05);
  leg->Draw();

  c1->Print("ohyeah.png");

}