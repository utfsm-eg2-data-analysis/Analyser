#!/bin/bash

export PRODIR=$(find ~/ -type d -iname analysis-omega)

export ANALYSER=${PRODIR}/ext/Analyser

export ROOT_INCLUDE_PATH=${ANALYSER}/include:${ROOT_INCLUDE_PATH}
export LD_LIBRARY_PATH=${ANALYSER}/slib:${LD_LIBRARY_PATH}
