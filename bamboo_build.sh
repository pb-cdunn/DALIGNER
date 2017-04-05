#!/bin/bash -ex

type module >& /dev/null || source /mnt/software/Modules/current/init/bash

set -vex
module load gcc/4.9.2
module load git/2.8.3
module load ccache

#echo "## Clean"
#git clean -fdx

ls -l
make -C DAZZ_DB clean
make -C DALIGNER clean
make -C DAZZ_DB -j
make -C DALIGNER -j

make -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile clean
PATH=.:${PATH} make -C DALIGNER -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile
make -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile clean
