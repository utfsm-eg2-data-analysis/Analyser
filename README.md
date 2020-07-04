# Analyser

Analysis tool, developed by Hayk Hakobyan, that filters "ClasTool-formatted" .root files.

It includes the C++ class **TIdentificator**, which is in charge of the particle identification cuts.

## Installation

### Requirements

* xutils-dev

### Environment variables

In sumary, you must define the following environment variables:
* `CLASTOOL` as the current ClasTool directory
* `CLAS_LIB` as the current clas_lib directory
* `CLAS_PACK` as the current clas_pack directory
* `ANALYSER` as the current Analyser directory

These next two variables should have these values:
```
OS_NAME=`uname`
OSNAME=${OS_NAME}
```

And, also:
* add `${CLASTOOL}/bin/${OSNAME}` to your `PATH` variable
* add `${ANALYSER}/include` and `${CLASTOOL}/include` to your `ROOT_INCLUDE_PATH` variable
* add `${ANALYSER}/slib` and `${CLASTOOL}/slib/${OS_NAME}` to your `LD_LIBRARY_PATH`

#### Example for Bash

If you're using Bash as your Unix shell, you only need to add the following lines at the end of your `.bashrc` file located in
your home directory. 

**Note:** here I previously defined another environment variable called `TOPDIR`, which stands for a directory
where all the related repositories are located.
```
export OS_NAME=`uname`
export OSNAME=${OS_NAME}

export CLASTOOL=${TOPDIR}/ClasTool
export CLAS_LIB=${TOPDIR}/clas_lib
export CLAS_PACK=${TOPDIR}/clas_pack
export ANALYSER=${TOPDIR}/Analyser

export PATH=${CLASTOOL}/bin/${OSNAME}:${PATH}
export ROOT_INCLUDE_PATH=${ANALYSER}/include:${CLASTOOL}/include:${ROOT_INCLUDE_PATH}
export LD_LIBRARY_PATH=${CLASTOOL}/slib/${OS_NAME}:${ANALYSER}/slib:${LD_LIBRARY_PATH}
```
For this to make effect, remember to reload your bash session: by closing and opening your terminal session or by executing:
```
source .bashrc
```

## Compilation

Compile by running Makefile.

## Integration with ROOT command console

Create an empty text file called `rootlogon.C` in your home directory.
This file contains the instructions to run at the beginning of each ROOT console session.
Inside the file, you should add this content:

```
{
  gSystem->Load("libMathMore");
  gSystem->Load("libClasTool");
  gSystem->Load("libTIdentificator");
}
```

After saving the `rootlogon.C` file, for this to make effect
you need to create another empty text file called `.rootrc` in your home directory aswell.
Which you will fill with this only line:

```
Rint.Logon: ~/rootlogon.C
```

### Debug for ROOT

From ROOT v6.14 onwards, it has become necessary to copy all dictionary files into the dynamic libraries folders `slib`.
To fix the annoying warning message, you should run these commands:

* Inside ClasTool directory, run:
```
find . -name *.pcm -exec cp -t ./slib/Linux {} +
```

* Inside Analyser directory, run:
```
find . -name *.pcm -exec cp -t ./slib {} +
```

## Documentation

More information can be found inside the directory `doc/`.

* `CUTS.md`, description of the particle identification cuts.

* `CORR.md`, description of the corrections that Analyser employs.

* `STATUS.md`, description of the status cuts that are extracted from the `ClasTool` root files.
