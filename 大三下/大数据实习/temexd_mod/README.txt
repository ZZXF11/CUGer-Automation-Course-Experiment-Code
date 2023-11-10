See end of file for installation and use instructions.

Contents of this Zip archive:

ADCHEM15_0010.pdf   A paper submitted to ADCHEM 2015 providing details and
                describing advantages of the modified code.

temexd_mod.c    C source code for compiling TEMEX mex file.  Note that this
                version requires the disturbance flags to be input signals, 
                not parameters.  Thus, they can change with time.  See
                comments at the beginning of the source code for details
                of model requirements and options.

teprob_mod.h    C header file needed when compiling.

temexd_mod.mexw64   Mex file ready for use on a Windows 64-bit system.  
                    It was compiled using the MATLAB mex command with the
                    Microsoft Visual Studio 2013 c compiler and tested
                    in MATLAB/Simulink release R2014b.

R12_Example.m	MATLAB test script that runs the plant in an open-loop
                manner.

tesys.mdl       Open-loop Simulink model called by R12_ExampleScript.m.

teplot.m        Script that plots the results at the end of some simulations.
                
MultiLoop_mode1.mdl     Simulink model of the control strategy described in
                "Decentralized control of the Tennessee Eastman Challenge
                Process", N. L. Ricker, J. Proc. Cont., Vol. 6, No. 4, 
                pp. 205-221, 1996.  It is set up to initialize and run with
                constant setpoints at the "Mode 1" operating condition.  NOTE:
                override loops are not included.  
                
                The .mdl file calls two custom scripts (lines 34 and 35):
                
                    PreLoadFcn        "Mode_1_Init"
                    StopFcn           "TEplot"

                These initialize the simulation variables and plot the results
                at the end of the run.  See the files "Mode_1_Init.m" and
                "TEplot.m" for more details.

MultiLoop_mode3.mdl  Similar to MultiLoop_mode1.mdl, but designed to run at
                     Mode 3 conditions.  Includes an additional override
                     that reduces the recycle valve % open when the 
                     separator coolant valve goes above 90%.  If this
                     is not included, the coolant valve saturates and
                     the system loses control of reactor level.

MultiLoop_Skoge_mode1.mdl   Similar to above, but uses the control strategy 
                described in "Self-Optimizing control of a large-scale plant:
                the Tennessee Eastman process" Larsson, T., et al., Ind. Eng.
                Chem. Res., Vol. 40, pp. 4889-4901, 2001.
                
                It automatically runs "Skoge_Mode1_Init.m" and "TEplot.m".

Mode_1_Init.m   Script file executed automatically when you run 
                "MultiLoop_mode1.mdl".  
 
Mode_3_Init.m   Script file executed automatically when you run 
                "MultiLoop_mode3.mdl".
               
Skoge_Mode1_Init.m      As above, but for "MultiLoop_Skoge_mode1.mdl".

Mode1xInitial.mat       Contains initial conditions for "MultiLoop_model.mdl".
                It is loaded by the script file "Mode_1_Init.m", which is 
                executed automatically when "MultiLoop_model.mdl" is opened.

Mode3xInitial.mat       Contains initial conditions for "MultiLoop_mode3.mdl".
                It is loaded by the script file "Mode_3_Init.m", which is 
                executed automatically when "MultiLoop_mode3.mdl" is opened.
                
Mode1SkogeInit.mat      As above, but for "MultiLoop_Skoge_mode1.mdl".

TElib.mdl       A Simulink library containing two controller blocks.  These are
                used in the two "MultiLoop" simulations.
                


System Requirements:

Tested using MATLAB/Simulink release R2014b.  Extent of compatibility with
older releases is unknown.

Installation:

1) Unzip the archive into a new directory.  

2) Start MATLAB and make the above new directory the default.

3) If your system is other than a Windows 64-bit machine, you will need to 
use the MATLAB mex command to compile the C source code and create a mex file.  
See instructions at the beginning of the C source code.  In order to run the 
simulation examples, the mex function must be named temexd_mod.  NOTE:
the code contains ~4000 lines and may take several minutes to compile.

Testing the code:

4) Try running the R12_ExampleScript.m file.  This illustrates a situation in
which the plant is running open-loop.  The specified simulation time is 5 hours
but at about 1 hour the plant, which is open-loop unstable, exceeds the maximum
reactor pressure and the simulation terminates automatically.  Plots show
transients of some key variables.  If this works, your installation should
be OK.

5) Try running one of the closed-loop models.  If you get a "file not found" 
or "variable undefined" error from MATLAB, 
make sure the initialization scripts described above are on the MATLAB
path.  The simplest approach is to put all of the files in a 
single directory and make it the MATLAB default directory.


Mode_3_Init.m        Initial model states needed for the above.

Mode3xInitial.mat    Contains initial conditions for "MultiLoop_mode3.mdl".
                     It is loaded by the script file "Mode_3_Init.m", which is 
                     executed automatically when the model is opened.


