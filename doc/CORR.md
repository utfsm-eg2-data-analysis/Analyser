# Corrections

This document refers to all thecorrection routines that **Analyser** employs.

## Vertex correction

Vertex correction for electrons.

```
TVector3 RotatedVertPos(X(0),Y(0),Z(0));    // vx,xy,vz from EVNT
TVector3 RotatedVertDir(Px(0),Py(0),Pz(0)); // px,py,pz from EVNT
TVector3 TargetPos(0.043,-0.33,0);
	
TVector3 *V_corr = new TVector3();
	
Float_t sect = Sector(0); 
	
RotatedVertPos.RotateZ(-TMath::DegToRad()*60.*sect);
RotatedVertDir.RotateZ(-TMath::DegToRad()*60.*sect);
TargetPos.RotateZ(-TMath::DegToRad()*60.*sect);
	
Float_t ShiftLength = (TargetPos.X()-RotatedVertPos.X())/RotatedVertDir.X();
	
RotatedVertDir = ShiftLength*RotatedVertDir;
RotatedVertPos = RotatedVertPos+RotatedVertDir;
	
V_corr->SetX((RotatedVertPos-TargetPos).X());
V_corr->SetY((RotatedVertPos-TargetPos).Y());
V_corr->SetZ(RotatedVertPos.Z());
	
return V_corr;
```

## Time correction

For pions.

```
return (PathSC(0)/30.) - TimeSC(0) + TimeSC(k) - 0.08 - (PathSC(k) / 30.) * sqrt(pow(mass/Momentum(k),2) + 1);
```

## DC Fiducial cut

For electrons. Very extensive.

```
if (FidTheta(0) > FidThetaMin() && FidPhi(0) > FidPhiMin() && FidPhi(0) < FidPhiMax())
	return 1;
```

## Sampling Fraction cut

For electrons. There is one for:
  1. Carbon data
  2. Iron data
  3. Lead data

```
// strcmp(str1,str2) returns 0 if str1 is equal to str2, very weird function
if ( !strcmp(tt,"") ) return true;

bool ret = false;
Double_t E = TMath::Max(Etot(0),Ein(0)+Eout(0));
Double_t p = Momentum(0);
Int_t s = Sector(0);

Double_t MeanE;
Double_t SigmaE;
if (!strcmp(tt, "Fe")) {
	MeanE = kMeanFePar[s][0] + kMeanFePar[s][1]*p + kMeanFePar[s][2]*p*p;
	SigmaE = TMath::Sqrt(kSigmaFePar[s][0]*kSigmaFePar[s][0] + kSigmaFePar[s][1]*kSigmaFePar[s][1]/p);
} else if (!strcmp(tt, "C")) {
	MeanE = kMeanCPar[s][0] + kMeanCPar[s][1]*p + kMeanCPar[s][2]*p*p;
	SigmaE = TMath::Sqrt(kSigmaCPar[s][0]*kSigmaCPar[s][0] + kSigmaCPar[s][1]*kSigmaCPar[s][1]/p);
} else if (!strcmp(tt, "Pb")) {
	MeanE = kMeanPbPar[s][0] + kMeanPbPar[s][1]*p + kMeanPbPar[s][2]*p*p;
	SigmaE = TMath::Sqrt(kSigmaPbPar[s][0]*kSigmaPbPar[s][0] + kSigmaPbPar[s][1]*kSigmaPbPar[s][1]/p);
} else if (!strcmp(tt, "Sim")) { // borquez_mod, based on TM analysis
	MeanE = 0.2623 + 0.0089*p + 0.0019*p*p;
	SigmaE = TMath::Sqrt(0.0057*0.0057 + 0.0305*0.0305/p);
}

if (TMath::Abs(E/p - MeanE) < 2.5*SigmaE)
	ret = true;
	
return ret;
```
