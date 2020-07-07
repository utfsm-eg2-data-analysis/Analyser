# Status

This document explains the meaning of the different **Status variables** that you can find in **Analyser**.

## Introduction

The **Status variables** (also known as **status word**) are variables that refer to the quality or goodness of the particle detection.

They are defined for every detector system with different numbering schemes.

**Analyser** extracts this information from different **ClasTool** banks.

The status extracted by **Analyser** variables are as follows:

* From the **EVNT** bank: `Status`, `StatDC`, `StatEC`, `StatSC`, `StatCC`

* From the **ECBP** bank: `Status`

* From the **DCPB** bank: `DCStatus`

* From the **SCPB** bank: `SCStatus`

* From the **CCPB** bank: `CCStatus`

**It is important to remark that the -1000 value corresponds to the null value.**

## From the `EVNT` bank

### `Status`

* **Possible values**: {-4, -3, -2, -1, 0, 1, 2, 3, 4}

* **Source**: `seb/define_id.F`

* **Definition**:

	If the charge of the particle is negative, `Status` will never be 0 and its definition will depend on the sign of the `DCStatus` value.

	* If `DCStatus` is positive, `Status` will start by having a value of 1, and it will get updated by the following steps:

        * if there was a SC hit, `Status++`
		* if CC hit timing coincides with SC timing, `Status++`
		* if EC hit timing coincides with SC timing, `Status++`

	* If `DCStatus` is negative, `Status` will start by having a value of -1, and it will get updated by the following steps:

		* if there was a SC hit, `Status--`
		* if CC hit timing coincides with SC timing, `Status--`
		* if EC hit timing coincides with SC timing, `Status--`
	
	If the charge of the particle is zero, there are two possible options.

	* If `beta > 1.99`, `Status = 0`

	* If `0 < beta < 1.99` **and** there was no SC hit **and** there was no CC hit, then `Status = 1`

### `StatDC`, `StatEC`, `StatSC`, `StatCC`

* **Source**: `Analyser/include/TIdentificator.icc`

* **Definition**:

    These variables are indices or *keys* that allows us to search each corresponding **XXStatus** value.

## From the `DCPB` bank

### `DCStatus`

* **Possible values**: {-1000, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

* **Source**: `seb/trk_2_dc.F` & `seb/time_tracking.F`

* **Definition**:

    **HB:** hit based tracking, **TB:** time based tracking. 

	* If the hit passed the HB, then `DCStatus = -1`

	* If the hit passed the TB, then `DCStatus = <number of tracks that passed TB>`

## From the `ECPB` bank

### `ECStatus`

* **Possible values**: {-1000, X0Y0Z} (where X,Y,Z = integers)

* **Source**: `seb/trk_2_ec.F` & `seb/ec_do_match.F` & `seb/fill_trks.F`

* **Definition**:

	```
    ECStatus = 10000*<number of hits in WHOLE> + 100*<number of hits in INNER> + 1*<number of hits in OUTER>
	```

## From the `SCPB` bank

### `SCStatus`

* **Possible values**: {-1000, 11, 22, 33}

* **Source**: `seb/read_rbanks.F` & `seb/trk_2_sc.F`

* **Definition**:

	* If only the left phototube status is ok, then `SCStatus = 11`
	
	* If only the right phototube status is ok, then `SCStatus = 22`
		
	* If both phototubes status are ok, then `SCStatus = 33`

## From the `CCPB` bank

### `CCStatus`

* **Possible values**: {-1000, 0XYZ, 1XYZ, 2XYZ} (where X,Y,Z = integers)

* **Source**: `seb/trk_2_cc.F`

* **Definition**:

	```
    CCStatus = 1000*(1 + <PHY_INDEX>) + 10*<CC segment number>
	```

	Where,
	
	* if the hit is located in left PMT, then `PHY_INDEX = -1`
	
	* if the hit is located in right PMT, then `PHY_INDEX = +1`
	
	* if the hit is located in both PMT, then `PHY_INDEX = 0`
