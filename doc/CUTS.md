# Particle Identification Cuts

This document refers to the particle identification cuts (or **pid**) of the **current version** of Analyser.
Be sure to update this document when modifying your PID cuts.

## Source code

All the particle identification cuts located in `src/Categorize.C`

Detailed description of some routines is documented in the `doc/CORR.md` file.

## Electrons

The electrons are always assumed to be located in the first row, hence the index 0.

First, let's start with the **Status cuts**. More information about them can be found at `doc/STATUS.md`

* 0 < Status < 100
* Charge = -1
* StatCC > 0
* StatSC > 0
* StatDC > 0
* StatEC > 0
* DCStatus > 0
* SCStatus == 33

Then,

* Sector-dependent number of photoelectrons in the CC:

	```
	Nphe > (Sector==0 || Sector==1)*25 + (Sector==2)*26 + (Sector==3)*21 + (Sector==4 || Sector==5)*28
	```
	
* (mflag || Nphe>25)
* (!mflag || Momentum>0.75)
* (!mflag || Ein>0.06)
* (!mflag || (TimeEC- TimeSC - (PathEC-PathSC )/30) < 5*0.35 )
* (!mflag || SampFracCheck(tt))
* Etot / 0.27 / 1.15 + 0.4 > Momentum
* Etot / 0.27 / 1.15 - 0.2 < Momentum
* Ein + Eout > 0.8 * 0.27 * Momentum
* Ein + Eout < 1.2 * 0.27 * Momentum
* Eout != 0
* FidCheckCut() == 1

* Status
* EC status
* DC status, SC status and CC status
* Charge must be `-1`
* Inner stack energy cut: `E_{in} > 0.06 GeV`
* Momentum, `P > 0.64 GeV`
* EC-SC coincidence time: `5 \sigma` around a `(t_EC - t_SC)` distribution
* CC Number of photoelectrons: sector dependent
* EC Fiducial cut: `40 < U < 400, 0 < V < 360, 0 < W < 390`
* DC Fiducial cut: extensive *(read code for more info)*
* Sampling fraction cut, there is one for:
  1. Carbon data
  2. Iron data
  3. Lead data
* To distinguish from negative pions, these two cuts are applied:
  * `E_{tot} / 0.27 / 1.15 - 0.2 < P < E_{tot} / 0.27 / 1.15 + 0.4`
  * `0.8 * 0.27 * P < E_{in} + E_{out} < 1.2 * 0.27 * P`

## Photons

* Charge must be `0`
* Fiducial cuts: `40 < U < 410, 0 < V < 370, 0 < W < 410`
* Energy cut: `max{E_{tot}, E_{in} + E_{out}}/0.272 > 0.1`
* Speed of light cut:
  * `-2.2 < PathEC/(30*Betta) - PathEC/30 < 1.3`

## Positive Pions

For all positive pions:
* Charge must be `+1`
* Status and DC status

For high energy pi+ with `P > 2.7 GeV`:
* CC status
* CC number of photoelectrons, `N_{phe} > 25`
* CC track definition concordance, `Chi2cc < 5/57.3` (?)

And for low energy pi+ with `P < 2.7 GeV`:
* SC status
* Momentum, time and mass dependent cut *(read code for more info)*

## Negative Pions

For all negative pions:
* Charge must be `-1`
* Status and DC status
* Sampling fraction:
  * ` E_{tot} < 0.15 `
  * ` E_{in} < 0.085 - 0.5*E_{out} `

For low energy pi- with `P < 2.5 GeV`:
* Momentum and time dependent cut

For high energy pi- with `P > 2.5 GeV`:
* CC status
* CC number of photoelectrons, `N_{phe} > 25`
* Momentum and time dependent cut
