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

## From the `DCPB` bank

### `DCStatus`

## From the `ECPB` bank

### `ECStatus`

## From the `SCPB` bank

### `SCStatus`

## From the `CCPB` bank

### `CCStatus`
