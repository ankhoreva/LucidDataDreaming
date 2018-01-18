@echo off
set MATLAB=C:\PROGRA~1\MATLAB\R2013b
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\R2013b\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=TransitiveKNN_part2_mex
set MEX_NAME=TransitiveKNN_part2_mex
set MEX_EXT=.mexw64
call mexopts.bat
echo # Make settings for TransitiveKNN_part2 > TransitiveKNN_part2_mex.mki
echo COMPILER=%COMPILER%>> TransitiveKNN_part2_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> TransitiveKNN_part2_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> TransitiveKNN_part2_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> TransitiveKNN_part2_mex.mki
echo LINKER=%LINKER%>> TransitiveKNN_part2_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> TransitiveKNN_part2_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> TransitiveKNN_part2_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> TransitiveKNN_part2_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> TransitiveKNN_part2_mex.mki
echo BORLAND=%BORLAND%>> TransitiveKNN_part2_mex.mki
echo OMPFLAGS= >> TransitiveKNN_part2_mex.mki
echo OMPLINKFLAGS= >> TransitiveKNN_part2_mex.mki
echo EMC_COMPILER=msvcsdk>> TransitiveKNN_part2_mex.mki
echo EMC_CONFIG=optim>> TransitiveKNN_part2_mex.mki
"C:\Program Files\MATLAB\R2013b\bin\win64\gmake" -B -f TransitiveKNN_part2_mex.mk
