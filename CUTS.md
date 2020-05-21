# Particle Identification Cuts

All the particle identification cuts are written in `src/Categorize.C`

## Electrons

* Status, EC status, DC status, SC status and CC status
* Charge must be `-1`
* Inner stack energy cut: `E_{in} > 0.06 GeV`
* Momentum, `P > 0.64 GeV`
* EC-SC coincidence time: `5 \sigma`
* CC Number of photoelectrons: sector dependent
* EC Fiducial cut: `40 < U < 400, 0 < V < 360, 0 < W < 390`
* DC Fiducial cut: extensive (read code for more info)
* Sampling fraction cut, there is one for:
  1. Deuterium-Carbon data
  2. Deuterium-Iron data
  3. Deuterium-Lead data
  4. All Simulations
* Distinguish from negative pions,
  * `E_{tot} / 0.27 / 1.15 - 0.2 < P < E_{tot} / 0.27 / 1.15 + 0.4`
  * `0.8 * 0.27 * P < E_{in} + E_{out} < 1.2 * 0.27 * P`
* **(Posterior)** 

## Photons

* Charge must be `0`
* Fiducial cuts: `40 < U < 410, 0 < V < 370, 0 < W < 410`
* Momentum: `P > 0.15 GeV`
* SC mass?

## Positive Pions

For all positive pions:
* Charge must be `+1`
* Status and DC status

For high energy pi+ with `P > 2.7 GeV`:
* CC status
* CC number of photoelectrons, `N_{phe} > 25`
* CC track definition concordance, `Chi2cc < 5/57.3`

And for low energy pi+ with `P < 2.7 GeV`:
* SC status
* Momentum, time and mass dependent cut (read code for more info)

## Negative Pions

For all negative pions:
* Charge must be `-1`
* Status and DC status
* Sampling fraction:
  * ` E_{tot} < 0.15 `
  * ` E_{in} < 0.085 - 0.5*E_{out} `

For low energy negative pions with `P < 2.5 GeV`:
* Momentum and time dependent cut

For high energy negative pions with `P > 2.5 GeV`:
* CC status
* CC number of photoelectrons, `N_{phe} > 25`
* Momentum and time dependent cut
