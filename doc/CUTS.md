# Particle Identification Cuts

This document refers to the particle identification cuts (or **pid**) of the **current version** of **Analyser**.
Be sure to update this document when modifying your PID cuts.

## Source code

All the particle identification cuts located in `src/Categorize.C`

Detailed description of some correction routines is documented in the `doc/CORR.md` file.

## Electrons

The electrons are always assumed to be located in the first row, hence the index 0 in every member function.

* **Charge** must be -1.

* Then, the **Status cuts**. More information about them can be found at `doc/STATUS.md`
	* `Status > 0`
    * `StatCC > 0`
	* `StatSC > 0`
	* `StatDC > 0`
	* `StatEC > 0`
	* `DCStatus > 0`
	* `SCStatus == 33`

* Momentum.

	```
	Momentum > 0.75
	```

* Sector-dependent number of **photoelectrons** in the CC:

	```
	Nphe > (Sector==0 || Sector==1)*25 + (Sector==2)*26 + (Sector==3)*21 + (Sector==4 || Sector==5)*28
	```
	
* Cut on the inner stack energy of the EC.

    ```
    Ein > 0.06
    ```

* Cut on the outer stack energy of the EC.

    ```
    Eout > 0
    ```

* Coincidence time between EC and SC.

	```
	-5*0.35 < TimeEC - TimeSC - (PathEC - PathSC)/30) < 5*0.35
	```

* Sampling fraction cut. (more information in `doc/CORR.md`)

	```
	SampFracCheck(target) == 1
	```

* Sampling fraction band to distinguish from negative pions.

	```
	Etot / 0.27 / 1.15 + 0.4 > Momentum
	Etot / 0.27 / 1.15 - 0.2 < Momentum
	Ein + Eout > 0.8 * 0.27 * Momentum
	Ein + Eout < 1.2 * 0.27 * Momentum
	```

* DC fiducial cut. (more information in `doc/CORR.md`)

	```
	FidCheckCut() == 1
	```

## Positive Pions

* Charge must be +1.

* Status and DC status

* For high energy pi+ with P > 2.7 GeV:
	* CC status
	* CC number of photoelectrons, `N_{phe} > 25`
	* CC track definition concordance, `Chi2cc < 5/57.3`

* And for low energy pi+ with P < 2.7 GeV:
	* SC status
	* Momentum, time and mass dependent cut *(read code for more info)*

## Negative Pions

* Charge must be -1.

* Status and DC status.

* Sampling fraction:
    * ` E_{tot} < 0.15 `
    * ` E_{in} < 0.085 - 0.5*E_{out} `

* For low energy pi- with `P < 2.5 GeV`:
    * Momentum and time dependent cut

* For high energy pi- with `P > 2.5 GeV`:
	* CC status
	* CC number of photoelectrons, `N_{phe} > 25`
	* Momentum and time dependent cut

## Photons

* Charge must be 0.

* EC fiducial cuts.

	```
	40 < U < 410, V < 370, W < 410
	```

* Energy cut.

	```
	max{E_{tot}, E_{in} + E_{out}}/0.272 > 0.1
	```

* Speed of light cut.

	```
	-2.2 < PathEC/(30*Betta) - PathEC/30 < 1.3
	```
