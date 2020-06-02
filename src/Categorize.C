TString TIdentificator::GetCategorization(Int_t k, TString tt) {
  
  Int_t number_dc = fCT->GetNRows("DCPB");
  Int_t number_cc = fCT->GetNRows("CCPB");
  Int_t number_sc = fCT->GetNRows("SCPB");
  Int_t number_ec = fCT->GetNRows("ECPB");
  
  TString partId;
  
  partId = "not recognized";
  
  if (number_dc != 0) {
    
    // transformation from xyz to uvw
    TVector3 *ECxyz = new TVector3(XEC(k), YEC(k), ZEC(k));
    TVector3 *ECuvw = XYZToUVW(ECxyz);
    
    // define ID cuts
    Bool_t ID_electron =
      (Charge(k) == -1) &&
      (Nphe(k) > (Sector(k)==0 || Sector(k)==1)*25 + (Sector(k)==2)*26 + (Sector(k)==3)*21 + (Sector(k)==4 || Sector(k)==5)*28) && // sector dependent cut
      (Momentum(k) > 0.64) && // borquez_mod
      (Ein(k) > 0.06) && // inner stack energy cut
      (0.66 - 5*0.34 < TimeEC(k) - TimeSC(k)) && (TimeEC(k) - TimeSC(k) < 0.66 + 5*0.34) && // SC and EC coincidence time, borquez_mod
      SampFracCheck(k, tt) && // added sim cut and iterator dependence, borquez_mod
      (Etot(k) / 0.27 / 1.15 + 0.4 > Momentum(k)) &&
      (Etot(k) / 0.27 / 1.15 - 0.2 < Momentum(k)) &&
      (Ein(k) + Eout(k) > 0.8 * 0.27 * Momentum(k)) &&
      (Ein(k) + Eout(k) < 1.2 * 0.27 * Momentum(k)) &&
      (Eout(k) > 0) && // taya's a-note, borquez_mod
      (40 < ECuvw->X()) && (ECuvw->X() < 400) && // U coordinate in ]40,400[, EC fiducial cuts, borquez_mod
      (0 <= ECuvw->Y()) && (ECuvw->Y() < 360) && // V coordinate in [0,360[
      (0 <= ECuvw->Z()) && (ECuvw->Z() < 390) && // W coordinate in [0,390[
      FidCheckCut(); // DC fiducial cuts
    
    /* deprecated electron cuts:
       Status(0) > 0 && Status(0) < 100 &&
       number_cc != 0 && number_ec != 0 && number_sc != 0 &&
       StatCC(0) > 0 && StatSC(0) > 0 &&
       StatDC(0) > 0 && StatEC(0) > 0 &&
       DCStatus(0) > 0 && SCStatus(0) == 33 */
    
    Bool_t ID_gamma =
      (Charge(k) == 0) &&
      (40 < ECuvw->X()) && (ECuvw->X() < 410) && // U coordinate in ]40,410[, EC fiducial cuts, borquez_mod
      (0 <= ECuvw->Y()) && (ECuvw->Y() < 370) && // V coordinate in [0,370[
      (0 <= ECuvw->Z()) && (ECuvw->Z() < 410) && // W coordinate in [0,410[
      (-2.2 < PathEC(k)/(Betta(k)*30) - PathEC(k)/30) && // speed of light cut, orlando's thesis and taya's a-note, borquez_mod
             (PathEC(k)/(Betta(k)*30) - PathEC(k)/30 < 1.3) &&
      (TMath::Max(Etot(k), Ein(k)+Eout(k))/0.272 > 0.1); // orlando's thesis, borquez_mod

    // just to shorten a little
    Float_t P = Momentum(k);
    Float_t T4 = TimeCorr4(0.1396, k);
    
    Bool_t ID_pim =
      (Charge(k) == -1) &&
      (Etot(k) < 0.15) &&
      (Ein(k) < 0.085 - 0.5*Eout(k)) &&
      ((Nphe(k) < 25 && ((0 < P && P <= 0.5 && T4 > -0.87 && T4 < 0.63) ||
			 (0.5 < P && P <= 1.0 && T4 > -0.55 && T4 < 0.37) ||
			 (1.0 < P && P <= 1.5 && T4 > -0.55 && T4 < 0.38) ||
			 (1.5 < P && P <= 2.0 && T4 > -0.60 && T4 < 0.44) ||
			 (2.0 < P && P <= 2.5 && T4 > -1.00 && T4 < 0.45))) ||
       (2.5 < P && P <= 3.0 && T4 > -1.00 && T4 < 0.40) ||
       (3.0 < P && T4 > -2.00 && T4 < 0.45)
       );

    /* deprecated pim cuts:
       Status(k) > 0 && Status(k) < 100 && StatDC(k) > 0 && DCStatus(k) > 0 */
    /* deprecated low energy pim cuts (P <= 2.5):
       StatCC(k) > 0 */
    
    Bool_t ID_pip =
	      (Charge(k) == 1) &&
	      (((P >= 2.7) && (Nphe(k) > 25)) ||
	       ((P < 2.7) && ((P > 0 && P <= 0.25 && T4 >= -1.45 && T4 <= 1.05) ||
			      (P > 0.25 && P <= 0.5 && T4 >= -1.44 && T4 <= 1.05) || 
			      (P > 0.5 && P <= 0.75 && T4 >= -1.44 && T4 <= 1.05) ||
			      (P > 0.75 && P <= 1 && T4 >= -1.4 && T4 <= 1.05) ||
			      (P > 1 && P <= 1.25 && T4 >= -1.35 && T4 <= 1.03) ||
			      (P > 1.25 && P <= 1.5 && T4 >= -1.35 && T4 <= 0.95) ||
			      (P > 1.5 && P <= 1.75 && T4 >= -1.35 && T4 <= 0.87) ||
			      (P > 1.75 && P <= 2 && T4 >= -1.25 && T4 <= 0.68) ||
			      (P > 2 && P <= 2.25 && T4 >= -0.95 && T4 <= 0.65) ||
			      (P > 2.25 && P <= 2.5 && T4 >= -1.05 && T4 <= 0.61 && Mass2(k) < 0.5) ||
			      (P > 2.5 && P < 2.7 && T4 >= -1.05 && T4 <= 0.61 && Mass2(k) < 0.4))));

    /* deprecated pip cuts:
       Status(k) > 0 && Status(k) < 100 && StatDC(k) > 0 && DCStatus(k) > 0 */
    /* deprecated low energy pip cuts: 
       number_cc != 0 && StatCC(k) > 0 && Chi2CC(k) < 5./57.3 */
    /* deprecated high energy pip cuts:
       number_sc != 0 && StatSC(k) > 0 */
    
    Bool_t ID_positron =
      (Charge(k) == 1) &&
      (Nphe(k) > 25) &&
      (Etot(k)/0.27/1.15 + 0.4 > Momentum(k)) &&
						      (Etot(k)/0.27/1.15 - 0.2 < Momentum(k)) &&
      (Ein(k) + Eout(k) > 0.8 * 0.27 * Momentum(k)) &&
						      (Ein(k) + Eout(k) < 1.2 * 0.27 * Momentum(k));
    
    /* deprecated positron cuts:
       number_cc != 0 && number_ec != 0 && number_sc != 0 &&
       StatCC(k) > 0 && StatSC(k) > 0 && StatDC(k) > 0 && StatEC(k) > 0 && DCStatus(k) > 0 */
    /* commentary:
       all positron cuts should be the same as electron cuts, but the charge */
    
    Bool_t ID_proton =
      (Charge(k) == 1) &&
      ((Momentum(k) >= 1. && Momentum(k) < 2. && TimeCorr4(0.938,k) >= -0.69 && TimeCorr4(0.938,k) <= 1.38) ||
       (Momentum(k) < 1. && TimeCorr4(0.938,k) >= -3.78 && TimeCorr4(0.938,k) <= 6.75));

    /* deprecated proton cuts:
       number_sc != 0 && StatSC(k) > 0 */

    if (ID_electron) { // DC fiducial cuts
      partId = "electron";
    } else if (ID_gamma) {
      partId = "gamma";
    } else if (ID_pim) {
      partId = "pi-";
    } else if (ID_pip) {
      partId = "pi+";      
    } else if (ID_positron) {
      partId = "positron";
    } else if (ID_proton) {
      partId = "proton";
    }
 
  } // end of number_dc != 0 condition
  
  return partId;
}

TString* TIdentificator::GetCategorization()
{
    Int_t number = fCT->GetNRows("EVNT");

    if (fPartIds != 0) delete [] fPartIds;
    fPartIds = new TString[number];

    if (number != 0) {
        for (Int_t i = 0; i < number; i++)
            fPartIds[i] = GetCategorization(i);
    }

    return fPartIds;
}

void TIdentificator::PrintCategorization()
{
    Int_t number = fCT->GetNRows("EVNT");
    fPartIds = GetCategorization();

    if (fPartIds->CompareTo("electron") == 0) {
        for (Int_t i = 0; i < number; i++)
            cout << *(fPartIds+i) << endl;
        cout << endl;
    }
}

void TIdentificator::PrintCategorization(TString* partIds)
{
    Int_t number = fCT->GetNRows("EVNT");

    if (partIds->CompareTo("electron") == 0) {
        for (Int_t i = 0; i < number; i++)
            cout << *(partIds+i) << endl;
        cout << endl;
    }
}

TString TIdentificator::GetCategorizationMin(Int_t k)
{
    Int_t number_dc = fCT->GetNRows("DCPB");
    Int_t number_cc = fCT->GetNRows("CCPB");
    Int_t number_sc = fCT->GetNRows("SCPB");
    Int_t number_ec = fCT->GetNRows("ECPB");

    TString partId;

    partId = "not recognized";

    if (number_dc != 0) 
    {
      if (k == 0 &&
          Status(0) > 0 &&
          Charge(0) == -1 &&
	  //number_cc != 0 &&
	  number_ec != 0 && number_sc != 0 &&
          StatSC(0) > 0 &&
          StatDC(0) > 0 && 
	  StatEC(0) > 0 &&
          DCStatus(0) > 0 &&
	  ECStatus(0) > 0 && SCStatus(0)>0
          )
          {
            partId = "electron";
          }

        //positive particles
      if (k > 0) 
      {
        if (Charge(k) == 1 && Status(k) > 0 && Status(k) < 100 &&
                        StatDC(k) > 0 && DCStatus(k) > 0 && FidCheckCutPiPlus(k) == 1) 
        {
          if (Momentum(k)>=2.7) 
          {
            if (number_cc != 0 && StatCC(k) > 0 && Nphe(k) > 25 && Chi2CC(k) < 5 / 57.3)
                        partId = "high energy pion +";
          }

          if (Momentum(k) < 2.7) 
          {
            if (number_sc != 0 && StatSC(k) > 0 && TimeCorr4(0.139,k) <= 0.55)
              partId = "low energy pion +";
          }

        }
        if (Status(k) > 0 && Status(k) < 100&&
            Charge(k) == 1 && number_cc != 0 && number_ec != 0 && number_sc != 0 &&
            StatCC(k) > 0 && StatSC(k) > 0 &&
            StatDC(k) > 0 && StatEC(k) > 0 &&
            DCStatus(k) > 0)
            partId = "positron";
        // Gamma ID
        if (Charge(k) == 0 )
          { 
            TVector3 *ECxyz = new TVector3(XEC(k),YEC(k),ZEC(k));
            TVector3 *ECuvw = XYZToUVW(ECxyz);
            if(ECuvw->X()>40 && ECuvw->X()<410 && // u coordinate in ]40,410[
              ECuvw->Y()<370 && // v coordinate in [0,370[
              ECuvw->Z()<410 && // w coordinate in [0,410[
              PathEC(k)/(Betta(k)*30) - PathEC(k)/30>-2.2&&
              PathEC(k)/(Betta(k)*30) - PathEC(k)/30<1.3&&
              TMath::Max(Etot(k), Ein(k)+Eout(k))/0.273>0.1
              )
              {
                partId = "gamma";
              }
          
        }
      }
    }

    return partId;
}
    
TString TIdentificator::GetCategorizationGSIM(Int_t k) {
  // recalls the particle ID from the GSIM bank
  TString partId;
  
  switch(int(Id(k,1))) {
  case 22: partId = "gamma"; break;
  case -11: partId = "positron"; break;
  case 11: partId = "electron"; break;
  case 12: partId = "electron neutrino"; break;
  case 13: partId = "muon-"; break;
  case -13: partId = "muon+"; break;
  case 111: partId = "pi0"; break;
  case 211: partId = "pi+"; break;
  case -211: partId = "pi-"; break;
  case 130: partId = "Kaon_L0"; break;
  case 321: partId = "Kaon+"; break;
  case -321: partId = "Kaon-"; break;
  case 2112: partId = "neutron"; break;
  case 2212: partId = "proton"; break;
  case -2212: partId = "antiproton"; break;
  case 310: partId = "Kaon_S0"; break;
  case 221: partId = "eta"; break;
  case 3122: partId = "Lambda"; break;
  case 3222: partId = "Sigma+"; break;
  case 3212: partId = "Sigma0"; break;
  case 3112: partId = "Sigma-"; break;
  case 3322: partId = "Xi0"; break;
  case 3312: partId = "Xi-"; break;
  case 3334: partId = "Omega-"; break;
  case -2112: partId = "antineutron"; break;
  default: partId = "not recognized"; break;
  }
  
  return partId;
}

TString TIdentificator::GetCategorizationEVNT(Int_t k) {
  // recall the particle ID from the EVNT bank
  TString partId;
  
  switch(int(Id(k,0))) {
  case 22: partId = "gamma"; break;
  case -11: partId = "positron"; break;
  case 11: partId = "electron"; break;
  case 12: partId = "electron neutrino"; break;
  case 13: partId = "muon-"; break;
  case -13: partId = "muon+"; break;
  case 111: partId = "pi0"; break;
  case 211: partId = "pi+"; break;
  case -211: partId = "pi-"; break;
  case 130: partId = "Kaon_L0"; break;
  case 321: partId = "Kaon+"; break;
  case -321: partId = "Kaon-"; break;
  case 2112: partId = "neutron"; break;
  case 2212: partId = "proton"; break;
  case -2212: partId = "antiproton"; break;
  case 310: partId = "Kaon_S0"; break;
  case 221: partId = "eta"; break;
  case 3122: partId = "Lambda"; break;
  case 3222: partId = "Sigma+"; break;
  case 3212: partId = "Sigma0"; break;
  case 3112: partId = "Sigma-"; break;
  case 3322: partId = "Xi0"; break;
  case 3312: partId = "Xi-"; break;
  case 3334: partId = "Omega-"; break;
  case -2112: partId = "antineutron"; break;
  default: partId = "not recognized"; break;
  }
  
  return partId;
}

TString TIdentificator::GetCategorizationParticle(Int_t k, Bool_t kind)
{
  TString partId;
  
  if (kind == 0) {
    partId = GetCategorizationEVNT(k);
  } else {
    partId = GetCategorizationGSIM(k);
  }
  
  return partId;
}
