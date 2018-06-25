:: Generate the HWB files for the CCU-USL_MS communication.
:: 
set bld=..\..\bld
set module=uslHwb

del %module%.c
del %module%.h
%bld%\hwbgen -iuslProto.h -o%module%
set bld=
pause