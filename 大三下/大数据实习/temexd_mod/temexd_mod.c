/*=========================================================================
=                                                                         =
=           T E N N E S S S E E   E A S T M A N   P R O C E S S           =
=                 C O N T R O L   T E S T   P R O B L E M                 =
=                                                                         =
=                            Original Model by                            =
=                   James J. Downs and Ernest F. Vogel                    =
=                                                                         =
=                               Revision by                               =
=                Andreas Bathelt* and N. Lawrence Ricker**                =
=                                                                         =
=           * Laboratory of Control Engineering and Mechatronics          =
=                  Cologne University of Applied Science                  =
=                           Betzdorfer Strasse 2                          =
=                          50679 Cologne, Germany                         =
=                   e-mail: andreas.bathelt@fh-koeln.de                   =
=                                                                         =
=                          ** Professor Emeritus                          =
=                   Department of Chemical Engineering                    =
=                        University of Washington                         =
=                       Seattle, WA 98195-1750, USA                       =
=                     e-mail: ricker@u.washington.edu                     =
===========================================================================
Description
  This s-function contains the model of the Tennessee Eastman Process which
  was originally published by Downs & Vogel in [1]. Later the FORTRAN 
  source of [1] was converted into a C-s-function and made available by 
  [2], in order to use it in conjunction with MATLAB(R)/Simulink(R). This 
  present version is the result of a revision of the original C source. 
  This revision was necessary, since the simulation engine of MATLAB(R)/
  Simulink(R) and the orginal structure of the model (the way it was de-
  vised to be used) didn't match anymore. A description of the problems
  found out and the subsequent changes made is available in [3].
 
  There are two models of the revised version. The difference between the 
  two models is the way the activation of the disturbances is handled. This
  model treats the activation vector as an additional input (the other mo-
  del uses a parameter for the purpose of passing the activation).
 
  Since this is only the source code of the model, it is necessary to com-
  pile the model before using it. Please refer to the installation instruc-
  tions given in the following section.
  
  Please Note:
    Since this revision was made during the time of the PhD studies at the 
    Cologne University of Applied Science it is highly likely that A. Ba-
    thelt can't answer your questions using the given e-mail-address 
    from 2016/2017 onwards. In this case please contact his supervisor 
    Mohieddine Jelali (mohieddine.jelali@fh-koeln.de) or use the e-mail-
    address andreas.bathelt@t-online.de. If you encounter any problems or 
    have ideas for the improvement of the model, feel free to send a
    message.
 
 
Installation Instructions
 Informtion regarding the compilation using the command mex
   If you are using a 64-Bit version of MATLAB, there is no default C com-
   piler shipped with the release. A list of compatible comiliers is given 
   under "Supported and Compatible Compilers - Release R20XXa/b" (website 
   (R2014b): http://de.mathworks.com/support/compilers/R2014b/index.html).
   The Microsoft Windows SDK is compatible and available at no charge.
 
 Compilation 
 1.  Copy the source AND THE HEADER-FILE "teprob_mod.h" into a directory of
     your choice - there is no need for the directory to be the directory 
     of the final simulation model.
  2. Set this directory to be the the current directory (folder) MATLAB(R)
     is working with (the window "Current Folder" needs to show the direc-
     tory consisting the model's files).
  3. Change to the command line and type "mex temexd_mod.c". This command
     starts the compiling of the model. After the compiling is (success-
     fully) completed, there should be a file named "temexd_mod.mexw32" or 
     "temexd_mod.mex64" (depending on the system). However, the file identi-
     tifier following the last dot should contain "mex", which stands for 
     MATLAB executable.
  
  Simulation using Simulink
  4. Copy the MEX-File into the directory in which the simulation will be
     run and make it the default directory.  NOTE:  the source code is not
     needed for simulations.
  5. Use the "S-Function" block from the Simulink Library Browser to
     include the plant model in your simulation.  Place this block in
     your Simulink model and connect the required input and output signals
     (see more about these below).    
  6. Open the dialog "Function Block Parameters" of this block and type 
     "temexd_mod" into the field "S-function name". In the field "S-func-
     tion parameters" specify the 3 parameters of this model (separated 
     by commas and in the usual MATLAB-style); the description of the 
     parameters is given below.
  7. See [2] for some example simulations.
 
  
References
 [1]   J. J. Downs, E. F. Vogel, "A Plant-Wide Industrial Process Control 
       Problem", Computers & Chemical Engineering, Vol. 17, Nr. 3, 
       S. 245–255 (1993)
 [2]   N. L. Ricker, "Tennessee Eastman Challenge archive", 2005. [Online]
       Available:http://depts.washington.edu/control/LARRY/TE/download.html
 [3]   A. Bathelt, N. L. Ricker, M. Jelali, "Revision of the Tennessee 
       Eastman Process Model", International Symposium on Advanced Control
       of Chemical Processes (ADCHEM) 2015, Submitted


Units
  When Downs & Vogel build the model, they chose to use the imperial unit 
  system. Thus all the internal values, that is states, constants, etc., 
  are given in imperial units. In the following these units are given along
  with the respective counterpart of the SI unit system. Furthermore other
  units are given (for the sake of clarification).
    ft³:      Cubic foot; 1 ft³ = 0.028317 m³
    lb-mol:   Pound-mole; 1 lb-mol = 453.59237 mol
	Torr:     Pressure in millimeter of mercury; 1 Torr = 101325/760 Pa
              760 Torr = 1 atm; 1 atm = 101325 Pa
	gpm:      US gallon per minute; 1 gpm = 0.2271 m³/h
    MM BTU:   Million (10^6) British Thermal Unit (heat needed to increase 
              the tempreature of one british Pound of water by 1 degree 
              Fahrenheit); 1 MM BTU = 1055.05685262 MJ
	
    Pa gauge: Pressure relative to ambient (air) pressure (1 bar)
    scmh:     Standard cubic meters per hour; the amount of substance of 
              one standard cubic meter is independent of the substance un-
              der consideration and always 44.615 mol (assumption of ideal
              gas). The values of pressure, temperature and relativ humi-
              dity of the assumed standard condition are 
                p_n = 101325 Pa (760 Torr, 1 atm)
                T_n = 273.15 K (DIN* 1343) / 288.15 K (ISO 2533)
                phi = 0%
              * DIN - German Institute for Standardization (Deutsches In-
                      stitut für Normung e.V.)
              Used within the model, the relation between standard cubic 
              foot (scf) and standard cubic meter (m³ i. N.) is 
              35.30834 scf = 1 m³ i. N.
              NOTE: Actually, a standard cubic meter is not a unit of vol-
                    ume, but a unit of amount of substance, which occupies
                    a volume of one cubic meter given standard conditions.

Parameters (3)
  The parameters are optional, i.e., each can be ommited, in which case
  a default value is used.  If any are supplied, the parameters must be
  listed in the correct sequence.  To omit a parameter while still 
  supplying one later in the sequence, replace it with "[]" (a MATLAB
  empty matrix).
  Number|Description
  ------|------------------------------------------------------------------
  1     |Vector of 52 initial states; if empty, default values of Mode 1 
        |(see [1]) are used.
  2     |Scalar for seed of Random generator; if empty, default value is 
        |used.
  3     |Structure parameter; by means of this parameter, the features of
        |the revised model can be activated. The base version is the one
        |C-s-function of [2]. The value of this parameter is evaluated bi- 
        |nary. That is, every bit of this parameter (given in integer re- 
        |presentation) represents a switch for one feature. Setting one bit
        |to changes the model in comparison to the original model. Thus, if
        |the parameter is 0, the model is the model equals the original mo-
        |del (except for the change, which allow for a faster computation;
        |turned of by setting bit 15 to 1). 
        |  Bit  | Description
        |  -----|----------------------------------------------------------
        |  0    |Activation of additional process measurments
        |  1    |Activation of the monitoring output for the values which 
        |       |are subject to process disturbances of the type "random"
        |       |(random variation); Output 2
        |  2    |Activation of the monitoring output for the internal 
        |       |values of the reaction anf process; Output 3 
        |  3    |Activation of the monitoring output for the concentrations
        |       |of the components of in the process units; Output 4
        |  4    |Deactivation of the measurement noise
        |  5    |Set random number generator to use two states, one for the
        |       |generation of the measurment noise and one for the gene-
        |       |ration of the process disturbances
        |  6    |Activation of the recalculation of the process disturban-
        |       |ces based on the pre-determined time
        |  7    |Activation of the scaling of the disturbances between 0
        |       |and 100% (0 and 1) using the disturbance activation flags
        |  15   |Reset of the model to the original structure, including 
        |       |the adaption of the program flow of the model to the pro-
        |       |gram flow of the simulation

  
States (50)
  Number|Description                                              |Unit
  ------|---------------------------------------------------------|--------
  1     |Holdup of component A in vapor phase of reactor          |lb-mol
  2     |Holdup of component B in vapor phase of reactor          |lb-mol
  3     |Holdup of component C in vapor phase of reactor          |lb-mol
  4     |Holdup of component D in liquid phase of reactor         |lb-mol
  5     |Holdup of component E in liquid phase of reactor         |lb-mol
  6     |Holdup of component F in liquid phase of reactor         |lb-mol
  7     |Holdup of component G in liquid phase of reactor         |lb-mol
  8     |Holdup of component H in liquid phase of reactor         |lb-mol
  9     |Internal energy of reactor                               |MM BTU
  10    |Holdup of component A in vapor phase of seperator        |lb-mol
  11    |Holdup of component B in vapor phase of seperator        |lb-mol
  12    |Holdup of component C in vapor phase of seperator        |lb-mol
  13    |Holdup of component D in liquid phase of seperator       |lb-mol
  14    |Holdup of component E in liquid phase of seperator       |lb-mol
  15    |Holdup of component F in liquid phase of seperator       |lb-mol
  16    |Holdup of component G in liquid phase of seperator       |lb-mol
  17    |Holdup of component H in liquid phase of seperator       |lb-mol
  18    |Internal energy of seperator                             |MM BTU
  19    |Holdup of component A in liquid phase of stripper (sump) |lb-mol
  20    |Holdup of component B in liquid phase of stripper (sump) |lb-mol
  21    |Holdup of component C in liquid phase of stripper (sump) |lb-mol
  22    |Holdup of component D in liquid phase of stripper (sump) |lb-mol
  23    |Holdup of component E in liquid phase of stripper (sump) |lb-mol
  24    |Holdup of component F in liquid phase of stripper (sump) |lb-mol
  25    |Holdup of component G in liquid phase of stripper (sump) |lb-mol
  26    |Holdup of component H in liquid phase of stripper (sump) |lb-mol
  27    |Internal energy of stripper (sump)                       |MM BTU
  28    |Holdup of component A in vapor phase of header (stream 6)|lb-mol
  29    |Holdup of component B in vapor phase of header (stream 6)|lb-mol
  30    |Holdup of component C in vapor phase of header (stream 6)|lb-mol
  31    |Holdup of component D in vapor phase of header (stream 6)|lb-mol
  32    |Holdup of component E in vapor phase of header (stream 6)|lb-mol
  33    |Holdup of component F in vapor phase of header (stream 6)|lb-mol
  34    |Holdup of component G in vapor phase of header (stream 6)|lb-mol
  35    |Holdup of component H in vapor phase of header (stream 6)|lb-mol
  36    |Internal energy of header (stream 6)                     |MM BTU
  37    |Temperature cooling water outlet of reactor              |°C
  38    |Temperature cooling water outlet of separator            |°C
  39    |Valve position feed component D (stream 2)               |%
  40    |Valve position feed component E (stream 3)               |%
  41    |Valve position feed component A (stream 1)               |%
  42    |Valve position feed component A & C (stream 4)           |%
  43    |Valve position compressor re-cycle                       |%
  44    |Valve position purge (stream 9)                          |%
  45    |Valve position underflow separator (stream 10)           |%
  46    |Valve position underflow stripper (stream 11)            |%
  47    |Valve position stripper steam                            |%
  48    |Valve position cooling water outlet of reactor           |%
  49    |Valve position cooling water outlet of separator         |%
  50    |Rotation of agitator of reactor                          |%
 
Inputs (12 manipulated variables + 28 disturbance flags)
  Number|Description
  ------|------------------------------------------------------------------
  1     |Valve position feed component D (stream 2)               
  2     |Valve position feed component E (stream 3)               
  3     |Valve position feed component A (stream 1)               
  4     |Valve position feed component A & C (stream 4)           
  5     |Valve position compressor re-cycle                       
  6     |Valve position purge (stream 9)                          
  7     |Valve position underflow separator (stream 10)           
  8     |Valve position underflow stripper (stream 11)            
  9     |Valve position stripper steam                            
  10    |Valve position cooling water outlet of reactor           
  11    |Valve position cooling water outlet of separator         
  12    |Rotation of agitator of reactor                          

  Number|Type       |Disturbed Value
  ------|-----------|------------------------------------------------------
  1     |Step       |A/C-ratio of stream 4, B composition constant
  2     |Step       |B composition of stream 4, A/C-ratio constant
  3     |Step       |D feed (stream 2) temperature
  4     |Step       |Cooling water inlet temperature of reactor
  5     |Step       |Cooling water inlet temperature of separator
  6     |Step       |A feed loss (stream 1)
  7     |Step       |C header pressure loss (stream 4)
  8     |Random     |A/B/C composition of stream 4
  9     |Random     |D feed (stream 2) temperature
  10    |Random     |C feed (stream 4) temperature
  11    |Random     |Cooling water inlet temperature of reactor
  12    |Random     |Cooling water inlet temperature of separator
  13    |Drift      |Reaction kinetics
  14    |Stiction   |Cooling water outlet valve of reactor
  15    |Stiction   |Cooling water outlet valve of separator
  16    |Random     |(unknown); deviations of heat transfer within stripper
        |           |(heat exchanger)
  17    |Random     |(unknown); deviations of heat transfer within reactor
  18    |Random     |(unknown); deviations of heat transfer within conden-
        |           |ser
  19    |Stiction   |(unknown); re-cycle valve of compressor, underflow
        |           |separator (stream 10), underflow stripper (stream 11)
        |           |and steam valve stripper 
  20    |Random     |(unknown)
  -------------------------------------------------------------------------
        a d d i t i o n a l   p r o c e s s   d i s t u r b a n c e s      
  -------------------------------------------------------------------------
  21    |Random     |A feed (stream 1) temperature
  22    |Random     |E feed (stream 3) temperature
  23    |Random     |A feed (stream 1) pressure ( = flow)
  24    |Random     |D feed (stream 2) pressure ( = flow)
  25    |Random     |E feed (stream 3) pressure ( = flow)
  26    |Random     |A & C feed (stream 4) pressure ( = flow)
  27    |Random     |Cooling water pressure ( = flow) of reactor
  28    |Random     |Cooling water pressure ( = flow) of condenser
  
Outputs
  The number of active outputs depends on the value of the structure para-
  meter of the model. Output 1 with outputs 1 through 41 is the default 
  output. The other outputs (values) are additional.
  Output 1 - Measured Values
    Number|Description                                        |Unit
    ------|---------------------------------------------------|------------
    1     |Feed flow component A (stream 1)                   |kscmh
    2     |Feed flow component D (stream 2)                   |kg/h
    3     |Feed flow component E (stream 3)                   |kg/h
    4     |Feed flow components A & C (stream 4)              |kscmh
    5     |Recycle flow to reactor from separator (stream 8)  |kscmh
    6     |Reactor feed (stream 6)                            |kscmh
    7     |Reactor pressure                                   |kPa gauge
    8     |Reactor level                                      |%
    9     |Reactor temperature                                |°C
    10    |Purge flow (stream 9)                              |kscmh
    11    |Separator temperature                              |°C
    12    |Separator level                                    |%
    13    |Separator pressure                                 |kPa gauge
    14    |Sperator underflow (liquid phase)                  |m³/h
    15    |Stripper level                                     |%
    16    |Stripper pressure                                  |kPa gauge
    17    |Stripper underflow (stream 11)                     |m³/h
    18    |Stripper temperature                               |°C
    19    |Stripper steam flow                                |kg/h
    20    |Compressor work                                    |kW
    21    |Reactor cooling water outlet temperature           |°C
    22    |Condenser cooling water outlet temperature         |°C
    23    |Concentration of A in Reactor feed (stream 6)      |mol %
    24    |Concentration of B in Reactor feed (stream 6)      |mol %
    25    |Concentration of C in Reactor feed (stream 6)      |mol %
    26    |Concentration of D in Reactor feed (stream 6)      |mol %
    27    |Concentration of E in Reactor feed (stream 6)      |mol %
    28    |Concentration of F in Reactor feed (stream 6)      |mol %
    29    |Concentration of A in Purge (stream 9)             |mol %
    30    |Concentration of B in Purge (stream 9)             |mol %
    31    |Concentration of C in Purge (stream 9)             |mol %
    32    |Concentration of D in Purge (stream 9)             |mol %
    33    |Concentration of E in Purge (stream 9)             |mol %
    34    |Concentration of F in Purge (stream 9)             |mol %
    35    |Concentration of G in Purge (stream 9)             |mol %
    36    |Concentration of H in Purge (stream 9)             |mol %
    37    |Concentration of D in stripper underflow (stream   |mol %
          |11)                                                |
    38    |Concentration of E in stripper underflow (stream   |mol %
          |11)                                                |
    39    |Concentration of F in stripper underflow (stream   |mol %
          |11)                                                |
    40    |Concentration of G in stripper underflow (stream   |mol %
          |11)                                                |
    41    |Concentration of H in stripper underflow (stream   |mol %
          |11)                                                |
    -----------------------------------------------------------------------
                a d d i t i o n a l   o u t p u t   v a l u e s            
    -----------------------------------------------------------------------
    42    |Feed component A temperature (stream 1)            |°C
    43    |Feed component D temperature (stream 2)            |°C
    44    |Feed component E temperature (stream 3)            |°C
    45    |Feed component A & C temperature (stream 4)        |°C
    46    |Reactor cooling water inlet temperature            |°C
    47    |Reactor cooling water flow                         |m³/h
    48    |Condenser cooling water inlet temperature          |°C
    49    |Condenser cooling water flow                       |m³/h
    50    |Concentration of A in stream 1                     |mol %
    51    |Concentration of B in stream 1                     |mol %
    52    |Concentration of C in stream 1                     |mol %
    53    |Concentration of D in stream 1                     |mol %
    54    |Concentration of E in stream 1                     |mol %
    55    |Concentration of F in stream 1                     |mol %
    56    |Concentration of A in stream 2                     |mol %
    57    |Concentration of B in stream 2                     |mol %
    58    |Concentration of C in stream 2                     |mol %
    59    |Concentration of D in stream 2                     |mol %
    60    |Concentration of E in stream 2                     |mol %
    61    |Concentration of F in stream 2                     |mol %
    62    |Concentration of A in stream 3                     |mol %
    63    |Concentration of B in stream 3                     |mol %
    64    |Concentration of C in stream 3                     |mol %
    65    |Concentration of D in stream 3                     |mol %
    66    |Concentration of E in stream 3                     |mol %
    67    |Concentration of F in stream 3                     |mol %
    68    |Concentration of A in stream 4                     |mol %
    69    |Concentration of B in stream 4                     |mol %
    70    |Concentration of C in stream 4                     |mol %
    71    |Concentration of D in stream 4                     |mol %
    72    |Concentration of E in stream 4                     |mol %
    73    |Concentration of F in stream 4                     |mol %

 Output 2 - Monitoring of Random-Variation-Disturbances
    The values given by this output are not subject to measurement noise.
    Thus it is not a duplication of the afore listed measured values.
    Number|Flag     |Value                                    |Unit
    ------|---------|-----------------------------------------|------------
    1     |IDV(8)   |Concentration of component A in stream 4 |mol %
    2     |IDV(8)   |Concentration of component B in stream 4 |mol %
    3     |IDV(8)   |Concentration of component C in stream 4 |mol %
    4     |IDV(9)   |Feed component D temperature (stream 2)  |°C
    5     |IDV(10)  |Feed components A & C temperature (stream|°C
          |         |4)                                       |
    6     |IDV(11)  |Reactor cooling water inlet tempreature  |°C
    7     |IDV(12)  |Condenser cooling water inlet tempreature|°C
    8     |IDV(13)  |Deviations of reaction kinetics of first |1
          |         |reaction (A + C + D -> G)                |
    9     |IDV(13)  |Deviations of reaction kinetics of second|1
          |         |reaction (A + C + E -> F)                | 
    10    |IDV(16)  |(unknown); deviations of heat transfer   |1
          |         |of stripper                              |
    11    |IDV(17)  |(unknown); deviations of heat transfer   |1
          |         |reactor                                  | 
    12    |IDV(18)  |(unknown); deviations of heat transfer   |1
          |         |condenser                                | 
    13    |IDV(20)  |(unknown)                                |
    -----------------------------------------------------------------------
         a d d i t i o n a l   p r o c e s s   d i s t u r b a n c e s     
    -----------------------------------------------------------------------
    14    |IDV(21)  |Feed component A temperature (stream 1)  |°C
    15    |IDV(22)  |Feed component E temperature (stream 3)  |°C
    16    |IDV(23)  |Feed component A pressure (stream 1);    |kmol/h
          |         |deviation of base value of flow          |
    17    |IDV(24)  |Feed component D pressure (stream 2);    |kmol/h
          |         |deviation of base value of flow          |
    18    |IDV(25)  |Feed component A pressure (stream 3);    |kmol/h 
          |         |deviation of base value of flow          |
    19    |IDV(26)  |Feed components A & C pressure  (stream  |kmol/h
          |         |4); deviation of base value of flow      |
    20    |IDV(27)  |Reactor cooling water supply pressure;   |m³/h
          |         |deviation of base value of flow          |
    21    |IDV(28)  |Condenser cooling water supply pressure; |m³/h
          |         |deviation of base value of flow          | 

  Output 3 - Monitoring of Reaction and Analyzers
    Number|Value                                              |Unit
    ------|---------------------------------------------------|------------
    1     |Consumption of component A (reator) (value < 0)    |kmol/h
    2     |Consumption of component C (reator) (value < 0)    |kmol/h
    3     |Consumption of component D (reator) (value < 0)    |kmol/h
    4     |Consumption of component E (reator) (value < 0)    |kmol/h
    5     |Creation of component F (reator) (value > 0)       |kmol/h
    6     |Creation of component G (reator) (value > 0)       |kmol/h
    7     |Creation of component H (reator) (value > 0)       |kmol/h
    8     |Partial pressure of component A (reactor)          |kPa abs
    9     |Partial pressure of component B (reactor)          |kPa abs
    10    |Partial pressure of component C (reactor)          |kPa abs
    11    |Partial pressure of component D (reactor)          |kPa abs
    12    |Partial pressure of component E (reactor)          |kPa abs
    13    |Partial pressure of component F (reactor)          |kPa abs
    14    |Partial pressure of component G (reactor)          |kPa abs
    15    |Partial pressure of component H (reactor)          |kPa abs
    16    |Delay-free concentration of A in reactor feed      |mol % 
          |(stream 6)                                         |
    17    |Delay-free concentration of B in reactor feed      |mol % 
          |(stream 6)                                         |
    18    |Delay-free concentration of C in reactor feed      |mol % 
          |(stream 6)                                         |
    19    |Delay-free concentration of D in reactor feed      |mol % 
          |(stream 6)                                         |
    20    |Delay-free concentration of E in reactor feed      |mol % 
          |(stream 6)                                         |
    21    |Delay-free concentration of F in reactor feed      |mol % 
          |(stream 6)                                         |
    22    |Delay-free concentration of A in purge (stream 9)  |mol % 
    23    |Delay-free concentration of B in purge (stream 9)  |mol % 
    24    |Delay-free concentration of C in purge (stream 9)  |mol % 
    25    |Delay-free concentration of D in purge (stream 9)  |mol % 
    26    |Delay-free concentration of E in purge (stream 9)  |mol % 
    27    |Delay-free concentration of F in purge (stream 9)  |mol % 
    28    |Delay-free concentration of G in purge (stream 9)  |mol % 
    29    |Delay-free concentration of H in purge (stream 9)  |mol % 
    30    |Delay-free concentration of H in product stream    |mol % 
          |strom (stream 11)                                  |
    31    |Delay-free concentration of D in product stream    |mol % 
          |(stream 11)                                        |
    32    |Delay-free concentration of E in product stream    |mol % 
          |(stream 11)                                        |
    33    |Delay-free concentration of F in product stream    |mol % 
          |(stream 11)                                        |
    34    |Delay-free concentration of G in product stream    |mol % 
          |(stream 11)                                        |
    35    |Delay-free concentration of A in feed A (stream 1) |mol % 
    36    |Delay-free concentration of B in feed A (stream 1) |mol % 
    37    |Delay-free concentration of C in feed A (stream 1) |mol % 
    38    |Delay-free concentration of D in feed A (stream 1) |mol % 
    39    |Delay-free concentration of E in feed A (stream 1) |mol % 
    40    |Delay-free concentration of F in feed A (stream 1) |mol % 
    41    |Delay-free concentration of A in feed D (stream 2) |mol % 
    42    |Delay-free concentration of B in feed D (stream 2) |mol % 
    43    |Delay-free concentration of C in feed D (stream 2) |mol % 
    44    |Delay-free concentration of D in feed D (stream 2) |mol % 
    45    |Delay-free concentration of E in feed D (stream 2) |mol % 
    46    |Delay-free concentration of F in feed D (stream 2) |mol % 
    47    |Delay-free concentration of A in feed E (stream 3) |mol % 
    48    |Delay-free concentration of B in feed E (stream 3) |mol % 
    49    |Delay-free concentration of C in feed E (stream 3) |mol % 
    50    |Delay-free concentration of D in feed E (stream 3) |mol % 
    51    |Delay-free concentration of E in feed E (stream 3) |mol % 
    52    |Delay-free concentration of F in feed E (stream 3) |mol % 
    53    |Delay-free concentration of A in feed A & C (stream|mol % 
          |4)                                                 |
    54    |Delay-free concentration of A in feed A & C (stream|mol % 
          |4)                                                 |
    55    |Delay-free concentration of A in feed A & C (stream|mol % 
          |4)                                                 |
    56    |Delay-free concentration of A in feed A & C (stream|mol % 
          |4)                                                 |
    57    |Delay-free concentration of A in feed A & C (stream|mol % 
          |4)                                                 |
    58    |Delay-free concentration of A in feed A & C (stream|mol % 
          |4)                                                 |
    59    |Production costs, based on the measured (noise-cor-|ct/(kmol 
          |rupted) values relative to the amount of product   |    product)
    60    |Calculation of 59 based on the internal (noise-    |ct/(kmol 
          |free) values                                       |    product)
    61    |Production costs, based on the measured (noise-cor-|$/h
          |rupted) values relative to time                    |
    62    |Calculation of 61 based on the internal (noise-    |$/h
          |free) values (see [1])                             |
 
 Output 4 - Concentration within the process units
    Every group of eight values gives the concentrations of the components
    A through H within different sections of the process.
    Number |Section                                            |Unit
    -------|---------------------------------------------------|-----------
    1 - 8  |Feed component D (stream 2)                        |mol %   
    9 - 16 |Feed component E (stream 3)                        |mol %   
    17 - 24|Feed component A (stream 1)                        |mol %   
    25 - 32|Feed components A & C (stream 4)                   |mol %   
    33 - 40|Stripper overhead (stream 5)                       |mol %   
    41 - 48|Reactor feed (stream 6)                            |mol %   
    49 - 56|Reactor effluent (stream 7)                        |mol %   
    57 - 64|Recycle to reactor from separator (stream 8)       |mol %   
    65 - 72|Purge (stream 9)                                   |mol %   
    73 - 80|Separator underflow (stream 10)                    |mol %   
    81 - 88|Stripper; Liquid entering sump                     |mol %   
    89 - 96|Stripper underflow (stream 11)                     |mol %   

Version 
  1.3.3
 
Latest Change
  12/18/2014
 
S-Function Change-Log
  Version |Date       |Description
  --------|-----------|----------------------------------------------------
  1.0.0   |12/31/1998 |Base version of the Tennessee Eastman Process model
          |           |for MATLAB by N. L. Ricker (ricker@u.washington.edu)
  1.1.0   |10/29/2013 |Extensions of the paramter list
          |           |  1. Initial value for the random number generation
          |           |     The parameter list was extended by another 
          |           |     (scalar) parameter, which inititializes the 
          |           |     state of the random number generator. This fa-
          |           |     cilitates the simulation of the model with 
          |           |     diffrent disturbance characteristics (evolu-
          |           |     tions).
          |           |  2. Deactivarion of measurement noise
          |           |     The second new parameter (third overall) is 
          |           |     used to switch off the measurement noise. That
          |           |     is the amplitudes of the measurment noise will
          |           |     be set to 0, if the parmater has the value 1
          |           |Extension of the values returned by the model
          |           |  In addition to the 41 return values described in
          |           |  [1] (process measurments), the 13 values subject
          |           |  to (random walk) process disturbances are retur-
          |           |  ned. These values are mere monitoring values.
  1.1.1   |11/12/2013 |Extension of the usage of the IDV flags
          |           |  The values of the IDV flags (activation of process
          |           |  disturbances) are now used to scale the amplitudes
          |           |  of the disturbances between 0 and 1 (100%).
  1.2.0   |03/20/2014 |Matching of the release level of "temexd_mod.c" and 
          |           |"temex_mod.c"
          |           |  The release level of "temexd_mod.c" and 
          |           |  "temex_mod.c" was matched in terms of the code and
          |           |  annotations.
          |           |Allocation of (local) memory cell for the model data 
          |           |  The model data, which is made of the genuine pro-
          |           |  cess data and the control data (e.g. state of the
          |           |  random generator), had been one global memory 
          |           |  cell. Thus the operating of two (or more) proces-
          |           |  ses within one simulation model was not possible, 
          |           |  since the process models mutally overwrote their
          |           |  data. A correct simulation is than impossible.
          |           |  Now, the model data was encapsulated within one
          |           |  data structure, which is used to allocate memory
          |           |  of appropriate size for the model data. That is,
          |           |  at the beginning of the simulation each processes
          |           |  model allocates memory for its model data and is 
          |           |  thus independend from the other process models.
          |           |  The addressing of the memory is made using the
          |           |  pointer to the memory and the Pwork vector of the
          |           |  s-function.
  1.3.0   |03/31/2014 |Independence of solver
          |           |  By adding another state for the random number ge-
          |           |  nerator and a slight change of the recalculation 
          |           |  of the (random walk) process disturbance poly-
          |           |  nomials, the calculation and simulation of the 
          |           |  process disturbance is now independend from the 
          |           |  choice of the solver and simulation time incre-
          |           |  ment. That is, the evolution of the process dis-
          |           |  turbances is always the same, irrespective of the
          |           |  solver. A complete description is given in [3].
          |           |Reduced program flow
          |           |  Since 'tefunc' calculates the whole process model,
          |           |  i.e. the state of the processes as well as the 
          |           |  outputs and derivatives of the simulation states,
          |           |  and is called twice per simulation time step (cal-
          |           |  (culation of the outputs in 'mdlOutputs' and cal-
          |           |  culation of the derivaties in 'mdlDerivatives'),
          |           |  unnecessary calculations are performed (the calcu-
          |           |  lation of the derivatives in 'mdlOutputs' is not 
          |           |  needed and vice versa). Introducing a program flow
          |           |  flag, which indicates the current position of the
          |           |  simulation run, the not needed caluclation are 
          |           |  omited. See also [3]
          |           |Additional outputs
          |           |  The outputs are extended by another set of moni-
          |           |  toring outputs and by addiional process measur-
          |           |  ments. Furthermore the outputs are structured in 
          |           |  order to group all the outputs logically. There is
          |           |  now an output (vector) for the measured values, 
          |           |  for monitored process disturbances, for internal
          |           |  process values and for the component concentra-
          |           |  tions.
          |           |  (The last output is created, but not yet "connec-
          |           |  ted with the respective values.)
          |           |Model structure parameter
          |           |  The third parameter of the parameter list has been
          |           |  changed to a parameter, which determines the acti-
          |           |  vation of the changes made to the original process 
          |           |  model and thus the structure of the model. It is 
          |           |  one parameter (integer value) whose binary struc-
          |           |  ture determines the activation (each bit is as-
          |           |  signed to one modification).
  1.3.1   |10/20/2014 |The forth output group is now operating.
  1.3.2   |11/19/2014 |Changes of the declaration of variables in 'mdl-
          |           |CheckParameters' (Bug-fix)
          |           |  The array and one auxillary variable which were
          |           |  declared as 'int_T' but used in connection with 
          |           |  the method 'mxGetNumberOfElements' which returns
          |           |  values of type 'size_t' caused a compiler warning.
          |           |  Depending of the compiler setup, this warning 
          |           |  could cause an abortion of the compilation.
          |           |Changes of the disturbance recalculation
          |           |  In order to switch the process model back to the 
          |           |  original one (version 1.0), all the changes need 
          |           |  to be ignored. This also includes the recalcula-
          |           |  tion of the 7 new (random walk) process disturban-
          |           |  ces using the original recaulculation procedure.
          |           |  These 7 disturbance are now skipped in this case
          |           |  to keep the random number generator from additio-
          |           |  nal runs which wouldn't occur in the original mo-
          |           |  del.
          |           |Optional parameter list
          |           |  The parameters are no longer a requiered element
          |           |  for the simulation. If all or some are omited, the
          |           |  respective value will be replace by a default 
          |           |  value.
   1.3.3  |12/18/2014 |Revised Feed-through-property
          |           |  The internal handling of the input (done by 'get-
          |           |  Curr()') is changed according to the calculation 
          |           |  of the process in  'mdlOutputs' and 'mdlDeriva-
          |           |  tives'. The inputs (manipulated variables and IDV)
          |           |  are exclusively read in during the execution of 
          |           |  'mdlDerivatives' and not anymore with the execu-
          |           |  tion of 'mdlOutputs'. Thus the input can be set to
          |           |  be an non-feed-through-input. This eases the use 
          |           |  of the model in conjunction with a controller. In
          |           |  fact, this property was just a remnant of the ori-
          |           |  ginal code, since the valves already possess first
          |           |  order characteristics.
          |           |Changes of the span of the cooling water flow dis-  
          |           |turbances
          |           |  The maximal span of the deviations of the nominal
          |           |  (100%) flow of the reactor and condenser cooling
          |           |  water is changed from 5 (gpm) to 5% of the re-
          |           |  spective nominal values.
          |           |Bug-fixes
          |           |  - Inserting of missing break statements at the
          |           |    switch-case-command of the call of 'teinit()'
          |           |    for different parameter sets.
          |           |  - Correction of the conditions of if-statements 
          |           |    masking the first bit of the structure parameter
          |           |    (comparison with respect to equality to one and 
          |           |    great than one)
          |           |  - Usage of wrong base index while calculating the 
          |           |    outputs of the input stream analyzers
 */

/**************************************************************************
*                                                                         *
*               S - F U N C T I O N   D E S C R I P T I O N               *
*                                                                         *
**************************************************************************/
#define S_FUNCTION_NAME  temexd_mod
#define S_FUNCTION_LEVEL 2


/**************************************************************************
*                                                                         *
*                             I N C L U D E S                             *
*                                                                         *
**************************************************************************/
#include "math.h"
#include "simstruc.h"
#include "teprob_mod.h"
 

/**************************************************************************
*                                                                         *
*                          D E F I N I T I O N S                          *
*                                                                         *
**************************************************************************/
#define IS_PARAM_DOUBLE(pVal) (mxIsNumeric(pVal)  && !mxIsLogical(pVal) &&\
                               !mxIsEmpty(pVal)   && !mxIsSparse(pVal) &&\
                               !mxIsComplex(pVal) && mxIsDouble(pVal))    

/*-------------------------------------------------------------------------
-     A c t i v a t i o n   o f   S - f u n c t i o n - m e t h o d s     -
-------------------------------------------------------------------------*/
#define MDL_CHECK_PARAMETERS
#undef  MDL_PROCESS_PARAMETERS
#undef  MDL_SET_INPUT_PORT_FRAME_DATA
#undef  MDL_SET_INPUT_PORT_WIDTH
#undef  MDL_SET_OUTPUT_PORT_WIDTH
#undef  MDL_SET_INPUT_PORT_DIMENSION_INFO
#undef  MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#undef  MDL_SET_DEFAULT_PORT_DIMENSION_INFO
#undef  MDL_SET_INPUT_PORT_SAMPLE_TIME
#undef  MDL_SET_OUTPUT_PORT_SAMPLE_TIME
#undef  MDL_SET_INPUT_PORT_DATA_TYPE
#undef  MDL_SET_OUTPUT_PORT_DATA_TYPE
#undef  MDL_SET_DEFAULT_PORT_DATA_TYPES
#undef  MDL_SET_INPUT_PORT_COMPLEX_SIGNAL
#undef  MDL_SET_OUTPUT_PORT_COMPLEX_SIGNAL
#undef  MDL_SET_DEFAULT_PORT_COMPLEX_SIGNALS
#undef  MDL_SET_WORK_WIDTHS
#define MDL_INITIALIZE_CONDITIONS
#define MDL_START
#undef  MDL_SIM_STATE
#undef  MDL_GET_TIME_OF_NEXT_VAR_HIT
#undef  MDL_ZERO_CROSSINGS
#undef  MDL_UPDATE
#define MDL_DERIVATIVES
#undef  MDL_RTW


/**************************************************************************
*                                                                         *
*        D E F I N I T I O N S   O F   I N T E R N A L   T Y P E S        *
*                                                                         *
***************************************************************************

---------------------------------------------------------------------------
-                        P r o c e s s V a l u e s                        -
-------------------------------------------------------------------------*/
struct ProcessValues {
    doublereal xmeas[41], xmeasadd[32], xmeasdist[21], xmeasmonitor[62], 
               xmeascomp[96], xmv[12];
};


/*-------------------------------------------------------------------------
-                           D i s t V e c t o r                           -
-------------------------------------------------------------------------*/
struct DistVector{
    doublereal idv[29];
};


/*-------------------------------------------------------------------------
-                            R a n d S t a t e                            -
-------------------------------------------------------------------------*/
struct RandState {
    doublereal g;
	doublereal measnoise;
	doublereal procdist;
};


/*-------------------------------------------------------------------------
-                        C o m p o n e n t D a t a                        -
-------------------------------------------------------------------------*/
struct ComponentData{
	doublereal avp[8], bvp[8], cvp[8], ah[8], bh[8], ch[8], ag[8], bg[8], 
		cg[8], av[8], ad[8], bd[8], cd[8], xmw[8];
};


/*-------------------------------------------------------------------------
-                              P r o c e s s                              -
-------------------------------------------------------------------------*/
struct Process{
	doublereal    uclr[8]  ,    ucvr[8]  ,    utlr     ,    utvr     , 
                   xlr[8]  ,     xvr[8]  ,     etr     ,     esr     ,
   			       tcr     ,     tkr     ,     dlr     ,     vlr     ,  
                   vvr     ,     vtr     ,     ptr     ,     ppr[8]  ,
			      crxr[8]  ,      rr[4]  ,      rh     ,     fwr     ,
                   twr     ,     qur     ,     hwr     ,     uar     , 
                 ucls[8]   ,    ucvs[8]  ,    utls     ,    utvs     , 
                  xls[8]   ,     xvs[8]  ,     ets     ,     ess     ,  
                  tcs      ,     tks     ,     dls     ,     vls     ,
                  vvs      ,     vts     ,     pts     ,     pps[8]  ,
	 	          fws      ,     tws     ,     qus     ,     hws     , 
                 uclc[8]   ,    utlc     ,     xlc[8]  ,     etc     ,
                  esc      ,     tcc     ,     dlc     ,     vlc     , 
                  vtc      ,     quc     ,    
                 ucvv[8]   ,    utvv     ,     xvv[8]  ,     etv     ,    
                  esv      ,     tcv     ,     tkv     ,     vtv     , 
                  ptv      ,     vcv[12] ,    vrng[12] ,    vtau[12] , 
                  ftm[13]  ,     fcm[104],     xst[104],    xmws[13] , 
         	   	  hst[13]  ,     tst[13] ,     sfr[8]  ,  cpflmx     , 
               cpprmx      ,    cpdh     ,    tcwr     ,    tcws     , 
   		          htr[3]   ,    agsp     ,    xdel[41] , xdeladd[24]  ,  
                  xns[41]  ,  xnsadd[34] ,    tgas     ,   tprod     ,     
                  vst[12]  ,    ivst[12];
};


/*-------------------------------------------------------------------------
-                          R a n d P r o c e s s                          -
-------------------------------------------------------------------------*/
struct RandProcess {
	doublereal adist[20], bdist[20], cdist[20], ddist[20], tlast[20], 
               tnext[20], hspan[20], hzero[20], sspan[20], szero[20], 
               spspan[20];
	doublereal idvwlk[20];
	doublereal rdumm;
};


/*-------------------------------------------------------------------------
-                          s t M o d e l D a t a                          -
-------------------------------------------------------------------------*/
struct stModelData {
  struct ProcessValues pv_;
  struct DistVector dvec_;
  struct RandState randsd_;
  struct ComponentData const_;
  struct Process teproc_;
  struct RandProcess wlk_;
  char msg[256];
  doublereal code_sd;  
  doublereal tlastcomp;
  integer MSFlag;
};


/**************************************************************************
*                                                                         *
*             D E F I N I T I O N S   O F   C O N S T A N T S             *
*                                                                         *
***************************************************************************

---------------------------------------------------------------------------
-                 S - F u n c t i o n - C o n s t a n t s                 -
-------------------------------------------------------------------------*/
const integer NX     = 50;
const int NU         = 12;
const int NIDV       = 28;
const int NY         = 41;
const int NYADD      = 32;
const int NYDIST     = 21;
const int NYMONITOR  = 62;
const int NYCOMP     = 96;
const int NPAR       = 3;

/*-------------------------------------------------------------------------
-            C o n s t a n t s   o f   P r o c e s s m o d e l            -
-------------------------------------------------------------------------*/
const integer c__50 = 50;
const integer c__12 = 12;
const integer c__21 = 21;
const integer c__153 = 153;
const integer c__586 = 586;
const integer c__139 = 139;
const integer c__6 = 6;
const integer c__1 = 1;
const integer c__0 = 0;
const integer c__41 = 41;
const integer c__2 = 2;
const integer c__3 = 3;
const integer c__4 = 4;
const integer c__5 = 5;
const integer c__7 = 7;
const integer c__8 = 8;
const doublereal c_b73 = 1.1544;
const doublereal c_b74 = .3735;
const integer c__9 = 9;
const integer c__10 = 10;
const integer c__11 = 11;
const doublereal c_b123 = 4294967296.;
const integer c__13 = 13;
const integer c__14 = 14;
const integer c__15 = 15;
const integer c__16 = 16;
const integer c__17 = 17;
const integer c__18 = 18;
const integer c__19 = 19;
const integer c__20 = 20;


/**************************************************************************
*                                                                         *
*                  S - F U N C T I O N - M E T H O D S                    *
*                                                                         *
***************************************************************************
 * Level 2 S-function methods
 * --------------------------
 *    Notation:  "=>" indicates method is required.
 *                [method] indicates method is optional.
 *
 *    Note, many of the methods below are only available for use in level 2 
 *    C-MEX S-functions.
 *
 * Model Initialization in Simulink
 * --------------------------------
 *=> mdlInitializeSizes         -  Initialize SimStruct sizes array
 *
 *   [mdlSetInputPortFrameData] -  Optional method. Check and set input and
 *                                 output port frame data attributes.
 *
 *       NOTE: An S-function cannot use mdlSetInput(Output)PortWidth and
 *       mdlSetInput(Output)PortDimensionInfo at the same time. It can use
 *       either a width or dimension method, but not both.
 * 
 *   [mdlSetInputPortWidth]     -  Optional method. Check and set input and
 *                                 optionally other port widths. 
 *   [mdlSetOutputPortWidth]    -  Optional method. Check and set output
 *                                 and optionally other port widths. 
 *
 *   [mdlSetInputPortDimensionInfo]
 *                              -  Optional method. Check and set input and
 *                                 optionally other port dimensions. 
 *   [mdlSetOutputPortDimensionInfo]    
 *                              -  Optional method. Check and set output
 *                                 and optionally other port dimensions. 
 *   [mdlSetDefaultPortDimensionInfo]
 *                               - Optional method. Set dimensions of all 
 *                                 input and output ports that have unknown 
 *                                 dimensions. 
 *
 *   [mdlSetInputPortSampleTime] - Optional method. Check and set input
 *                                 port sample time and optionally other
 *                                 port sample times.
 *   [mdlSetOutputPortSampleTime]- Optional method. Check and set output
 *                                 port sample time and optionally other
 *                                 port sample times.
 *=> mdlInitializeSampleTimes   -  Initialize sample times and optionally
 *                                 function-call connections. 
 *
 *   [mdlSetInputPortDataType]    - Optional method. Check and set input 
 *                                  port data type. See SS_DOUBLE to 
 *                                  SS_BOOEAN in simstruc_types.h for 
 *                                  built-in data types.
 *   [mdlSetOutputPortDataType]   - Optional method. Check and set output 
 *                                  port data type. See SS_DOUBLE to 
 *                                  SS_BOOLEAN in simstruc_types.h for 
 *                                  built-in data types.
 *   [mdlSetDefaultPortDataTypes] - Optional method. Set data types of all 
 *                                  dynamically typed input and output 
 *                                  ports.
 *
 *   [mdlInputPortComplexSignal]  - Optional method. Check and set input
 *                                  port complexity attribute (COMPLEX_YES,
 *                                  COMPLEX_NO).
 *   [mdlOutputPortComplexSignal] - Optional method. Check and set output
 *                                  port complexity attribute (COMPLEX_YES,
 *                                  COMPLEX_NO).
 *   [mdlSetDefaultPortComplexSignals]
 *                                - Optional method. Set complex signal 
 *                                  flags of all input and output ports who
 *                                  have their complex signals set to
 *                                  COMPLEX_INHERITED (dynamic complexity).
 * 
 *   [mdlSetWorkWidths]         -  Optional method. Set the state, iwork,
 *                                 rwork, pwork, dwork, etc sizes. 
 *
 *   [mdlStart]                 -  Optional method. Perform actions such
 *                                 as allocating memory and attaching to 
 *                                 pwork elements.  
 *
 *   [mdlInitializeConditions]  -  Initialize model parameters (usually
 *                                 states). Will not be called if your
 *                                 S-function does not have an initialize
 *                                 conditions method.
 *
 *   ['constant' mdlOutputs]    -  Execute blocks with constant sample
 *                                 times. These are only executed once
 *                                 here.
 *
 *   [mdlSetSimState]           -  Optional method. Load the complete simu-
 *                                 lation state for this block, which is 
 *                                 called when starting the simulation from
 *                                 an initial simulation state and this s-
 *                                 function has set its ssSetSimStateCom-
 *                                 pliance to USE_CUSTOM_SIM_STATE. See 
 *                                 also mdlGetSimState
 * 
 * Model simulation loop in Simulink
 * ---------------------------------
 *   [mdlCheckParameters]       -  Optional method. Will be called at
 *                                 any time during the simulation loop when
 *                                 parameters change. 
 *   SimulationLoop:
 *        [mdlProcessParameters]   -  Optional method. Called during
 *                                    simulation after parameters have been
 *                                    changed and verified to be okay by
 *                                    mdlCheckParameters. The processing is
 *                                    done at the "top" of the simulation 
 *                                    loop when it is safe to process the 
 *                                    changed parameters. 
 *        [mdlGetTimeOfNextVarHit] -  Optional method. If your S-function
 *                                    has a variable step sample time, then
 *                                    this method will be called.
 *        [mdlInitializeConditions]-  Optional method. Only called if your
 *                                    S-function resides in an enabled
 *                                    subsystem configured to reset states,
 *                                    and the subsystem has just enabled.
 *     => mdlOutputs               -  Major output call (usually updates
 *                                    output signals).
 *        [mdlUpdate]              -  Update the discrete states, etc.
 *
 *        Integration (Minor time step)
 *          [mdlDerivatives]         -  Compute the derivatives.
 *          Do
 *            [mdlOutputs]
 *            [mdlDerivatives]
 *          EndDo - number of iterations depends on solver
 *          Do 
 *            [mdlOutputs]
 *            [mdlZeroCrossings]
 *          EndDo - number of iterations depends on zero crossings signals
 *        EndIntegration
 *
 *   EndSimulationLoop
 *   
 *   [mdlGetSimState]  -  Optional method. Called to get the complete 
 *                        simulation state for this block if the model is 
 *                        configured to save its final simulation state and 
 *                        this S-Function has set its ssSetSimStateCompli-
 *                        ance to USE_CUSTOM_SIM_STATE. See also mdlSetSim-
 *                        State
 *
 *   => mdlTerminate   -  End of model housekeeping - free memory, etc.
 *
 * Model initialization for code generation (rtwgen)
 * -------------------------------------------------
 *   <Initialization. See "Model Initialization in Simulink" above>
 *
 *   [mdlRTW]                   -  Optional method.  Only called when
 *                                 generating code to add information to 
 *                                 the model.rtw file which is used by the
 *                                 Real-Time Workshop.
 *
 *   mdlTerminate               -  End of model housekeeping - free memory,
 *                                 etc.
 *
 * Noninlined S-function execution in Real-Time Workshop
 * -----------------------------------------------------
 *   1) The results of most initialization methods are 'compiled' into
 *      the generated code and many methods are not called.
 *   2) Noninlined S-functions are limited in several ways, for example 
 *      parameter must be real (non-complex) double vectors or strings.  
 *      More capability is provided via the Target Language Compiler.  See  
 *      the Target Language Compiler Reference Guide.
 *
 * => mdlInitializeSizes        -  Initialize SimStruct sizes array
 * => mdlInitializeSampleTimes  -  Initialize sample times and optionally
 *                                 function-call connections. 
 *   [mdlInitializeConditions]  -  Initialize model parameters (usually
 *                                 states). Will not be called if your
 *                                 S-function does not have an initialize
 *                                 conditions method.
 *   [mdlStart]                 -  Optional method. Perform actions such
 *                                 as allocating memory and attaching to 
 *                                 pwork elements.  
 *   ExecutionLoop:
 *     => mdlOutputs            -  Major output call (usually updates
 *                                 output signals).
 *        [mdlUpdate]           -  Update the discrete states, etc.
 *
 *        Integration (Minor time step)
 *          [mdlDerivatives]         -  Compute the derivatives.
 *          Do
 *            [mdlOutputs]
 *            [mdlDerivatives]
 *          EndDo - number of iterations depends on solver
 *          Do 
 *            [mdlOutputs]
 *            [mdlZeroCrossings]
 *          EndDo - number of iterations depends on zero crossings signals
 *   EndExecutionLoop
 *   mdlTerminate               -  End of model housekeeping - free memory,
 *                                 etc.
 */


/*====================================================================*
 * Parameter handling methods. These methods are not supported by RTW *
 *====================================================================*/


/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g ----------------

---------------------------------------------------------------------------
-                  m d l C h e c k P a r a m e t e r s                    -
-------------------------------------------------------------------------*/
static void mdlCheckParameters(SimStruct *S){
  /*----------------------------- Variables -----------------------------*/
  static char msg[256];
  size_t Plen[3];
  size_t nEls;
  int_T i;
    
  
  /*--------------------------- Function Body ---------------------------*/
  Plen[0] = NX;
  Plen[1] = 1;
  Plen[2] = 1;
  for (i=0; i < ssGetSFcnParamsCount(S); i++){
	if (!mxIsEmpty(ssGetSFcnParam(S,i))){
      if (!IS_PARAM_DOUBLE(ssGetSFcnParam(S,i))){
	    sprintf(msg,"Error in parameter %i:  %s",i+1,
	  	  	        "Parameter must be a real, non-sparse vector.");
  	    ssSetErrorStatus(S,msg);
	    return;
      } //if (!IS_PARAM_DOUBLE(ssGetSFcnParam(S,i)){

      nEls = mxGetNumberOfElements(ssGetSFcnParam(S,i));
    
      if (nEls != Plen[i]){
  	    sprintf(msg,"Error in parameter %i:  Length = %i"
                	".  Expecting length = %i", i+1, nEls, Plen[i]);
 	    ssSetErrorStatus(S,msg);
	    return;
      } //if (nEls != Plen[i]){
    } //if (!mxIsEmpty(ssGetSFcnParam(S,i))){
  } //for (i=0; i < ssGetSFcnParamsCount(S); i++){
}

/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#endif //#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/


/*=====================================*
 * Configuration and execution methods *
 *=====================================*/

/*-------------------------------------------------------------------------
-                  m d l I n i t i a l i z e S i z e s                    -
-------------------------------------------------------------------------*/
static void mdlInitializeSizes(SimStruct *S){
  /*----------------------------- Variables -----------------------------*/
  integer MSFlag;
  integer i__;
  
  /*--------------------------- Function Body ---------------------------*/
  if((ssGetSFcnParamsCount(S) < 3) || (mxIsEmpty(ssGetSFcnParam(S,2)))){
    MSFlag = 0;
  }else{
    MSFlag = (integer)*mxGetPr(ssGetSFcnParam(S,2));
  } //if((ssGetSFcnParamsCount(S) < 3) || (mxIsEmpty(ssGetSFcnParam(S,2))))

  if((MSFlag & 0x8000) > 0){
     MSFlag = (integer)0x8000;
  } //if((*tcModelData).MSFlag & 0x8000) > 0){
    
  if (NPAR >= ssGetSFcnParamsCount(S)){
    ssSetNumSFcnParams(S, ssGetSFcnParamsCount(S));
    mdlCheckParameters(S);
	if (ssGetErrorStatus(S) != NULL){
      return;
    } //if (ssGetErrorStatus(S) != NULL){
  }else{
    ssSetNumSFcnParams(S, NPAR);
 
    return;     /*Simulink will report a parameter mismatch error */
  } //if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)){

  ssSetNumContStates(S, NX);
  ssSetNumDiscStates(S, 0); 

  if (!ssSetNumInputPorts(S, 1)){
    return;
  } //if (!ssSetNumInputPorts(S, 1)){
  ssSetInputPortWidth(S, 0, NU+NIDV);
  ssSetInputPortDirectFeedThrough(S, 0, 1);

  if (!ssSetNumOutputPorts(S, 1 + ((MSFlag & 0x2) >> 1)
                                + ((MSFlag & 0x4) >> 2)
                                + ((MSFlag & 0x8) >> 3))){
    return;
  } //if (!ssSetNumOutputPorts(S, 1)){ 
  ssSetOutputPortWidth(S, 0, NY + NYADD*(MSFlag & 0x1));
  
  //Beobachterausgänge Störungen
  if((MSFlag & 0x2) > 0){
    ssSetOutputPortWidth(S, 1, NYDIST);  
  } //if((MSFlag & 0x2) > 0){
  
  //Beobachterausgänge Prozess (Reaktor)
  if((MSFlag & 0x4) > 0){
    ssSetOutputPortWidth(S, 1 + ((MSFlag & 0x2) >> 1), NYMONITOR);
  } //if((MSFlag & 0x4) > 0){

  //Beobachterausgänge Stoffkonzentrationen (Prozess)
  if((MSFlag & 0x8) > 0){
    ssSetOutputPortWidth(S, 1 + ((MSFlag & 0x2) >> 1) + 
                                ((MSFlag & 0x4) >> 2), NYCOMP);
  } //if((MSFlag & 0x8) > 0){

  ssSetNumSampleTimes(S, 1);

  ssSetNumRWork(S, 0);
  ssSetNumIWork(S, 0);
  ssSetNumPWork(S, 1);
  ssSetNumModes(S, 0);
  ssSetNumNonsampledZCs(S, 0);

  ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

  for(i__ = 0; i__ < ssGetSFcnParamsCount(S) - 1; i__++){
    ssSetSFcnParamNotTunable(S, i__);
  } //for(i__ = 0; i__ < ssGetSFcnParamsCount(S) - 1; i__++){
}/* end mdlInitializeSizes */


/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#if defined(MDL_SET_WORK_WIDTHS) && defined(MATLAB_MEX_FILE)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g ----------------

---------------------------------------------------------------------------
-                    m d l S e t W o r k W i d t h s                      -
-------------------------------------------------------------------------*/
static void mdlSetWorkWidths(SimStruct *S){
    
}
  
/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#endif /* MDL_SET_WORK_WIDTHS */
/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/


/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#if defined(MDL_START)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g ----------------

---------------------------------------------------------------------------
-                            m d l S t a r t                              -
-------------------------------------------------------------------------*/
static void mdlStart(SimStruct *S){
  /*----------------------------- Variables -----------------------------*/
   void** PWorkVecs;

  /*--------------------------- Function Body ---------------------------*/
  PWorkVecs = ssGetPWork(S);
  PWorkVecs[0] = calloc(1,sizeof(struct stModelData));
}

/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#endif //#if defined(MDL_START)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/


/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#if defined(MDL_INITIALIZE_CONDITIONS)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g ----------------

---------------------------------------------------------------------------
-             m d l I n i t i a l i z e C o n d i t i o n s               -
-------------------------------------------------------------------------*/
static void mdlInitializeConditions(SimStruct *S){
  /*----------------------------- Variables -----------------------------*/
  real_T *x0;
  real_T *pr;
  integer nx;
  real_T dxdt[50];
  real_T rt;
  struct stModelData *ModelData;
  int_T i;

  /*Retrieving and Typcast of Dataset Pointer*/
  ModelData = (struct stModelData *)ssGetPWorkValue(S,0);
  
  /*--------------------------- Function Body ---------------------------*/
  x0 = ssGetContStates(S);
  nx = NX;
  rt = 0;

  if (ssIsFirstInitCond(S)){ 
    switch(ssGetSFcnParamsCount(S)){
      case 3: teinit(ModelData, &nx, &rt, x0, dxdt, 
                     mxGetPr(ssGetSFcnParam(S,1)),
                     mxGetPr(ssGetSFcnParam(S,2)));
              break;
      case 2: teinit(ModelData, &nx, &rt, x0, dxdt, 
                     mxGetPr(ssGetSFcnParam(S,1)),NULL);
              break;
      default: teinit(ModelData, &nx, &rt, x0, dxdt, NULL, NULL);
               break;
    } //switch(ssGetSFcnParamsCount(S)){
  } //if (ssIsFirstInitCond(S)){      
      
  if ((ssGetSFcnParamsCount(S) == 0) || (mxIsEmpty(ssGetSFcnParam(S,0)))){
    x0[0] = (float)10.40491389;
	x0[1] = (float)4.363996017;
	x0[2] = (float)7.570059737;
	x0[3] = (float).4230042431;
	x0[4] = (float)24.15513437;
	x0[5] = (float)2.942597645;
	x0[6] = (float)154.3770655;
	x0[7] = (float)159.186596;
	x0[8] = (float)2.808522723;
	x0[9] = (float)63.75581199;
	x0[10] = (float)26.74026066;
	x0[11] = (float)46.38532432;
	x0[12] = (float).2464521543;
	x0[13] = (float)15.20484404;
	x0[14] = (float)1.852266172;
	x0[15] = (float)52.44639459;
	x0[16] = (float)41.20394008;
	x0[17] = (float).569931776;
	x0[18] = (float).4306056376;
	x0[19] = .0079906200783;
	x0[20] = (float).9056036089;
	x0[21] = .016054258216;
	x0[22] = (float).7509759687;
	x0[23] = .088582855955;
	x0[24] = (float)48.27726193;
	x0[25] = (float)39.38459028;
	x0[26] = (float).3755297257;
	x0[27] = (float)107.7562698;
	x0[28] = (float)29.77250546;
	x0[29] = (float)88.32481135;
	x0[30] = (float)23.03929507;
	x0[31] = (float)62.85848794;
	x0[32] = (float)5.546318688;
	x0[33] = (float)11.92244772;
	x0[34] = (float)5.555448243;
	x0[35] = (float).9218489762;
	x0[36] = (float)94.59927549;
	x0[37] = (float)77.29698353;
	x0[38] = (float)63.05263039;
	x0[39] = (float)53.97970677;
	x0[40] = (float)24.64355755;
	x0[41] = (float)61.30192144;
	x0[42] = (float)22.21;
	x0[43] = (float)40.06374673;
 	x0[44] = (float)38.1003437;
	x0[45] = (float)46.53415582;
	x0[46] = (float)47.44573456;
	x0[47] = (float)41.10581288;
	x0[48] = (float)18.11349055;
	x0[49] = (float)50.;
  }else{
	pr = mxGetPr(ssGetSFcnParam(S,0));
	for (i=0; i<nx; i++){
	  x0[i] = pr[i];
	} //for (i=0; i<nx; i++){
  } //if (mxIsEmpty(ssGetSFcnParam(S,0))){
      
  (*ModelData).dvec_.idv[28] = (float)0.;
  (*ModelData).code_sd = (float)0.;
  setidv(S);
}

/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#endif /* MDL_INITIALIZE_CONDITIONS */
/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/


/*-------------------------------------------------------------------------
-            m d l I n i t i a l i z e S a m p l e T i m e s              -
-------------------------------------------------------------------------*/
static void mdlInitializeSampleTimes(SimStruct *S){
  ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
  ssSetOffsetTime(S, 0, 0.0);
}


/*-------------------------------------------------------------------------
-                          m d l O u t p u t s                            -
-------------------------------------------------------------------------*/
static void mdlOutputs(SimStruct *S, int_T tid){
  /*----------------------------- Variables -----------------------------*/
  real_T *y[4];
  doublereal rx[50];
  doublereal dx[50];
  doublereal rt;
  struct stModelData *ModelData;
  int i;

  /*Retrieving and Typcast of Dataset Pointer*/
  ModelData = (struct stModelData *)ssGetPWorkValue(S,0);
  
  /*--------------------------- Function Body ---------------------------*/
  // Get current time, states, and inputs
  rt = getcurr(rx, S, 1);
  
  // Call TEFUNC to update everything
  tefunc(ModelData, &NX, &rt, rx, dx, 1);

  y[0] = ssGetOutputPortRealSignal(S,0);
  y[1] = ssGetOutputPortRealSignal(S,(((*ModelData).MSFlag & 0x2) >> 1));
  y[2] = ssGetOutputPortRealSignal(S,(((*ModelData).MSFlag & 0x2) >> 1) +
                                     (((*ModelData).MSFlag & 0x4) >> 2));
  y[3] = ssGetOutputPortRealSignal(S,(((*ModelData).MSFlag & 0x2) >> 1) +
                                     (((*ModelData).MSFlag & 0x4) >> 2) +
                                     (((*ModelData).MSFlag & 0x8) >> 3));
  
  for (i = 0; i < NY; i++){
	y[0][i] = (*ModelData).pv_.xmeas[i];
  } //for (i=0; i<NY; i++){
  for (i = 0; i < NYADD * ((*ModelData).MSFlag & 0x1); i++){
	y[0][NY + i] = (*ModelData).pv_.xmeasadd[i];
  } //for (i=0; i<NYDIST; i++){
  
  for(i = 0; i < NYDIST * (((*ModelData).MSFlag & 0x2) >> 1); i++){
    y[1][i] = (*ModelData).pv_.xmeasdist[i];
  } //for(i = 0; i < NYDIST * (((*ModelData).MSFlag & 0x2) >> 1); i++){

  for(i = 0; i < NYMONITOR * (((*ModelData).MSFlag & 0x4) >> 2); i++){
    y[2][i] = (*ModelData).pv_.xmeasmonitor[i];    
  } //for(i = 0; i < NYMONITOR * (((*ModelData).MSFlag & 0x4) >> 2); i++){

  for(i = 0; i < NYCOMP * (((*ModelData).MSFlag & 0x8) >> 3); i++){
    y[3][i] = (*ModelData).pv_.xmeascomp[i];    
  } //for(i = 0; i < NYMONITOR * (((*ModelData).MSFlag & 0x4) >> 2); i++){
  

  // Shut down the simulation if ISD is non-zero.
  if ((*ModelData).dvec_.idv[28] != (float)0. && rt > (float) 0.1){
	(*ModelData).code_sd = (*ModelData).dvec_.idv[28];
	ssSetStopRequested(S,1);
  } //if ((*ModelData).dvec_.idv[28] != (float)0. && rt > (float) 0.1){
} /* end mdlOutputs */

/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#if defined(MDL_UPDATE)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g ----------------


---------------------------------------------------------------------------
-                           m d l U p d a t e                             -
-------------------------------------------------------------------------*/
static void mdlUpdate(SimStruct *S, int_T tid){
    
}

/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#endif /* MDL_UPDATE */
/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/


/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#if defined(MDL_DERIVATIVES)
/*-------------- P r ä p r o z e s s o r a n w e i s u n g ----------------

---------------------------------------------------------------------------
-                      m d l D e r i v a t i v e s                        -
-------------------------------------------------------------------------*/
static void mdlDerivatives(SimStruct *S){
  /*----------------------------- Variables -----------------------------*/
  doublereal x[50];
  doublereal *dx;
  doublereal rt;
  void* ModelData;

  /*--------------------------- Function Body ---------------------------*/
  // Call TEFUNC to update dx
  rt = getcurr(x, S, 2);
  dx = ssGetdX(S);
  ModelData = ssGetPWorkValue(S,0);

  tefunc(ModelData, &NX, &rt, x, dx, 2);
}

/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/
#endif /* MDL_DERIVATIVES */
/*-------------- P r ä p r o z e s s o r a n w e i s u n g --------------*/


/*-------------------------------------------------------------------------
-                        m d l T e r m i n a t e                          -
-------------------------------------------------------------------------*/
static void mdlTerminate(SimStruct *S){
  /*Variables*/
  struct stModelData *ModelData;
  
  /*Retrieving and Typcast of Dataset Pointer*/
  ModelData = (struct stModelData *)ssGetPWorkValue(S,0);
  
  /*--------------------------- Function Body ---------------------------*/
  if ((*ModelData).code_sd != (float)0. ){
    strcat((*ModelData).msg, "\n in ");
    strcat((*ModelData).msg, ssGetPath(S));
    
	mexWarnMsgTxt((*ModelData).msg);
  } //if (code_sd != (float)0. ){
  
  free(ModelData);
}


/**************************************************************************
*                                                                         *
*                   T R A N S F E R F U N C T I O N S                     *
*                                                                         *
***************************************************************************

---------------------------------------------------------------------------
-                              g e t c u r r                              -
-------------------------------------------------------------------------*/
static doublereal getcurr(doublereal x[], SimStruct *S, shortint Callflag){
  /*----------------------------- Variables -----------------------------*/
  doublereal rt;
  real_T *xPtr;
  InputRealPtrsType uPtrs;
  struct stModelData *ModelData;
  int i;

  /*Retrieving and Typcast of Dataset Pointer*/
  ModelData = (struct stModelData *)ssGetPWorkValue(S,0);

  /*--------------------------- Function Body ---------------------------*/
  rt = ssGetT(S);
  xPtr = ssGetContStates(S);
  
  if(Callflag == 2){
    setidv(S);
    
    uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    for (i=0; i<NU; i++){
	  (*ModelData).pv_.xmv[i] = *uPtrs[i];
    } //for (i=0; i<NU; i++){
  } //if(Callflag == 2){

  for (i=0; i<NX; i++){
 	x[i] = xPtr[i];
  } //for (i=0; i<NX; i++){
  return rt;
}


/*-------------------------------------------------------------------------
-                               s e t i d v                               -
-------------------------------------------------------------------------*/
static void setidv(SimStruct *S){
  /*----------------------------- Variables -----------------------------*/
  InputRealPtrsType uPtrs;
  struct stModelData *ModelData;
  int i;

  /*Retrieving and Typcast of Dataset Pointer*/
  ModelData = (struct stModelData *)ssGetPWorkValue(S,0);

  /*--------------------------- Function Body ---------------------------*/
  uPtrs = ssGetInputPortRealSignalPtrs(S,0);

  /*Assinging of Disturbance Activations (and Disturbance Scaling)*/
  for (i=0; i<NIDV; i++){
    if (((*ModelData).MSFlag & 0x80) > 1){
  	  (*ModelData).dvec_.idv[i] = (float)*uPtrs[i + NU];
    }else{
  	  (*ModelData).dvec_.idv[i] = (float)(*uPtrs[i + NU] >= 0.5);
    } //if (((*ModelData).MSFlag & 0x80) > 1){
  } //for (i=0; i<NIDV; i++){
}


/**************************************************************************
*                                                                         *
*         T E N N E S S E E - E A S T M A N - F U N C T I O N S           *
*                                                                         *
***************************************************************************

---------------------------------------------------------------------------
-                               t e i n i t                               -
-------------------------------------------------------------------------*/
static int teinit(void *ModelData, 
                  const integer *nn, doublereal *time, doublereal *yy, 
                  doublereal *yp, doublereal *rseed, doublereal *MSFlag){
  /*----------------------------- Variables -----------------------------*/
  struct stModelData *tcModelData;
  #define isd ((doublereal *)&(*tcModelData).dvec_ + 28)
  integer i__;

  /*Typcast of Dataset Pointer*/
  tcModelData = ModelData;

  /*Parameter adjustments*/
  --yp;
  --yy;

  /*--------------------------- Function Body ---------------------------*/
  /*Evaluation of Structure Parameter*/
  if (MSFlag == NULL){
    (*tcModelData).MSFlag = 0;
  }else{
    (*tcModelData).MSFlag = (integer)*MSFlag;
  } //if (MSFlag == NULL){
  
  if(((*tcModelData).MSFlag & 0x8000) > 0){
    (*tcModelData).MSFlag = (integer)0x8000;
  } //if((*tcModelData).MSFlag & 0x8000) > 0){
  
  /*Component Data*/
  (*tcModelData).const_.xmw[0] = (float)2.;           //in g/mol / kg/kmol
  (*tcModelData).const_.xmw[1] = (float)25.4;         //in g/mol / kg/kmol
  (*tcModelData).const_.xmw[2] = (float)28.;          //in g/mol / kg/kmol
  (*tcModelData).const_.xmw[3] = (float)32.;          //in g/mol / kg/kmol
  (*tcModelData).const_.xmw[4] = (float)46.;          //in g/mol / kg/kmol
  (*tcModelData).const_.xmw[5] = (float)48.;          //in g/mol / kg/kmol
  (*tcModelData).const_.xmw[6] = (float)62.;          //in g/mol / kg/kmol
  (*tcModelData).const_.xmw[7] = (float)76.;          //in g/mol / kg/kmol  

  (*tcModelData).const_.avp[0] = (float)0.;           //in ln(Torr)
  (*tcModelData).const_.avp[1] = (float)0.;           //in ln(Torr)
  (*tcModelData).const_.avp[2] = (float)0.;           //in ln(Torr)
  (*tcModelData).const_.avp[3] = (float)15.92;        //in ln(Torr)
  (*tcModelData).const_.avp[4] = (float)16.35;        //in ln(Torr)
  (*tcModelData).const_.avp[5] = (float)16.35;        //in ln(Torr)
  (*tcModelData).const_.avp[6] = (float)16.43;        //in ln(Torr)
  (*tcModelData).const_.avp[7] = (float)17.21;        //in ln(Torr)
  (*tcModelData).const_.bvp[0] = (float)0.;           //in ln(Torr)*°C
  (*tcModelData).const_.bvp[1] = (float)0.;           //in ln(Torr)*°C
  (*tcModelData).const_.bvp[2] = (float)0.;           //in ln(Torr)*°C
  (*tcModelData).const_.bvp[3] = (float)-1444.;       //in ln(Torr)*°C
  (*tcModelData).const_.bvp[4] = (float)-2114.;       //in ln(Torr)*°C
  (*tcModelData).const_.bvp[5] = (float)-2114.;       //in ln(Torr)*°C
  (*tcModelData).const_.bvp[6] = (float)-2748.;       //in ln(Torr)*°C
  (*tcModelData).const_.bvp[7] = (float)-3318.;       //in ln(Torr)*°C
  (*tcModelData).const_.cvp[0] = (float)0.;           //in °C
  (*tcModelData).const_.cvp[1] = (float)0.;           //in °C
  (*tcModelData).const_.cvp[2] = (float)0.;           //in °C
  (*tcModelData).const_.cvp[3] = (float)259.;         //in °C
  (*tcModelData).const_.cvp[4] = (float)265.5;        //in °C
  (*tcModelData).const_.cvp[5] = (float)265.5;        //in °C
  (*tcModelData).const_.cvp[6] = (float)232.9;        //in °C
  (*tcModelData).const_.cvp[7] = (float)249.6;        //in °C
  
  (*tcModelData).const_.ad[0] = (float)1.;            //in ?
  (*tcModelData).const_.ad[1] = (float)1.;            //in ?
  (*tcModelData).const_.ad[2] = (float)1.;            //in ?
  (*tcModelData).const_.ad[3] = (float)23.3;          //in ?
  (*tcModelData).const_.ad[4] = (float)33.9;          //in ?
  (*tcModelData).const_.ad[5] = (float)32.8;          //in ?
  (*tcModelData).const_.ad[6] = (float)49.9;          //in ?
  (*tcModelData).const_.ad[7] = (float)50.5;          //in ?
  (*tcModelData).const_.bd[0] = (float)0.;            //in ?
  (*tcModelData).const_.bd[1] = (float)0.;            //in ?
  (*tcModelData).const_.bd[2] = (float)0.;            //in ?
  (*tcModelData).const_.bd[3] = (float)-.07;          //in ?
  (*tcModelData).const_.bd[4] = (float)-.0957;        //in ?
  (*tcModelData).const_.bd[5] = (float)-.0995;        //in ?
  (*tcModelData).const_.bd[6] = (float)-.0191;        //in ?
  (*tcModelData).const_.bd[7] = (float)-.0541;        //in ?
  (*tcModelData).const_.cd[0] = (float)0.;            //in ?
  (*tcModelData).const_.cd[1] = (float)0.;            //in ?
  (*tcModelData).const_.cd[2] = (float)0.;            //in ?
  (*tcModelData).const_.cd[3] = (float)-2e-4;         //in ?
  (*tcModelData).const_.cd[4] = (float)-1.52e-4;      //in ?
  (*tcModelData).const_.cd[5] = (float)-2.33e-4;      //in ?
  (*tcModelData).const_.cd[6] = (float)-4.25e-4;      //in ?
  (*tcModelData).const_.cd[7] = (float)-1.5e-4;       //in ?

  (*tcModelData).const_.ah[0] = 1e-6;                 //in ?
  (*tcModelData).const_.ah[1] = 1e-6;                 //in ?
  (*tcModelData).const_.ah[2] = 1e-6;                 //in ?
  (*tcModelData).const_.ah[3] = 9.6e-7;               //in ?
  (*tcModelData).const_.ah[4] = 5.73e-7;              //in ?
  (*tcModelData).const_.ah[5] = 6.52e-7;              //in ?
  (*tcModelData).const_.ah[6] = 5.15e-7;              //in ?
  (*tcModelData).const_.ah[7] = 4.71e-7;              //in ?
  (*tcModelData).const_.bh[0] = (float)0.;            //in ?
  (*tcModelData).const_.bh[1] = (float)0.;            //in ?
  (*tcModelData).const_.bh[2] = (float)0.;            //in ?
  (*tcModelData).const_.bh[3] = 8.7e-9;               //in ?
  (*tcModelData).const_.bh[4] = 2.41e-9;              //in ?
  (*tcModelData).const_.bh[5] = 2.18e-9;              //in ?
  (*tcModelData).const_.bh[6] = 5.65e-10;             //in ?
  (*tcModelData).const_.bh[7] = 8.7e-10;              //in ?
  (*tcModelData).const_.ch[0] = (float)0.;            //in ?
  (*tcModelData).const_.ch[1] = (float)0.;            //in ?
  (*tcModelData).const_.ch[2] = (float)0.;            //in ?
  (*tcModelData).const_.ch[3] = 4.81e-11;             //in ?
  (*tcModelData).const_.ch[4] = 1.82e-11;             //in ?
  (*tcModelData).const_.ch[5] = 1.94e-11;             //in ?
  (*tcModelData).const_.ch[6] = 3.82e-12;             //in ?
  (*tcModelData).const_.ch[7] = 2.62e-12;             //in ?
  
  (*tcModelData).const_.av[0] = 1e-6;                 //in ?
  (*tcModelData).const_.av[1] = 1e-6;                 //in ?
  (*tcModelData).const_.av[2] = 1e-6;                 //in ?
  (*tcModelData).const_.av[3] = 8.67e-5;              //in ?
  (*tcModelData).const_.av[4] = 1.6e-4;               //in ?
  (*tcModelData).const_.av[5] = 1.6e-4;               //in ?
  (*tcModelData).const_.av[6] = 2.25e-4;              //in ?
  (*tcModelData).const_.av[7] = 2.09e-4;              //in ?
  (*tcModelData).const_.ag[0] = 3.411e-6;             //in ?
  (*tcModelData).const_.ag[1] = 3.799e-7;             //in ?
  (*tcModelData).const_.ag[2] = 2.491e-7;             //in ?
  (*tcModelData).const_.ag[3] = 3.567e-7;             //in ?
  (*tcModelData).const_.ag[4] = 3.463e-7;             //in ?
  (*tcModelData).const_.ag[5] = 3.93e-7;              //in ?
  (*tcModelData).const_.ag[6] = 1.7e-7;               //in ?
  (*tcModelData).const_.ag[7] = 1.5e-7;               //in ?
  (*tcModelData).const_.bg[0] = 7.18e-10;             //in ?
  (*tcModelData).const_.bg[1] = 1.08e-9;              //in ?
  (*tcModelData).const_.bg[2] = 1.36e-11;             //in ?
  (*tcModelData).const_.bg[3] = 8.51e-10;             //in ?
  (*tcModelData).const_.bg[4] = 8.96e-10;             //in ?
  (*tcModelData).const_.bg[5] = 1.02e-9;              //in ?
  (*tcModelData).const_.bg[6] = 0.;                   //in ?
  (*tcModelData).const_.bg[7] = 0.;                   //in ?
  (*tcModelData).const_.cg[0] = 6e-13;                //in ?
  (*tcModelData).const_.cg[1] = -3.98e-13;            //in ?
  (*tcModelData).const_.cg[2] = -3.93e-14;            //in ?
  (*tcModelData).const_.cg[3] = -3.12e-13;            //in ?
  (*tcModelData).const_.cg[4] = -3.27e-13;            //in ?
  (*tcModelData).const_.cg[5] = -3.12e-13;            //in ?
  (*tcModelData).const_.cg[6] = 0.;                   //in ?
  (*tcModelData).const_.cg[7] = 0.;                   //in ?
  
  /*Initial State of Process (Mode 1)*/
  yy[1] = (float)10.40491389;                         //in lb-mol
  yy[2] = (float)4.363996017;                         //in lb-mol
  yy[3] = (float)7.570059737;                         //in lb-mol
  yy[4] = (float).4230042431;                         //in lb-mol
  yy[5] = (float)24.15513437;                         //in lb-mol
  yy[6] = (float)2.942597645;                         //in lb-mol
  yy[7] = (float)154.3770655;                         //in lb-mol
  yy[8] = (float)159.186596;                          //in lb-mol
  yy[9] = (float)2.808522723;                         //in ?
  yy[10] = (float)63.75581199;                        //in lb-mol
  yy[11] = (float)26.74026066;                        //in lb-mol
  yy[12] = (float)46.38532432;                        //in lb-mol
  yy[13] = (float).2464521543;                        //in lb-mol
  yy[14] = (float)15.20484404;                        //in lb-mol
  yy[15] = (float)1.852266172;                        //in lb-mol
  yy[16] = (float)52.44639459;                        //in lb-mol
  yy[17] = (float)41.20394008;                        //in lb-mol
  yy[18] = (float).569931776;                         //in ?
  yy[19] = (float).4306056376;                        //in ?
  yy[20] = .0079906200783;                            //in ?
  yy[21] = (float).9056036089;                        //in ?
  yy[22] = .016054258216;                             //in ?
  yy[23] = (float).7509759687;                        //in ?
  yy[24] = .088582855955;                             //in ?
  yy[25] = (float)48.27726193;                        //in ?
  yy[26] = (float)39.38459028;                        //in ?
  yy[27] = (float).3755297257;                        //in ?
  yy[28] = (float)107.7562698;                        //in ?
  yy[29] = (float)29.77250546;                        //in ?
  yy[30] = (float)88.32481135;                        //in ?
  yy[31] = (float)23.03929507;                        //in ?
  yy[32] = (float)62.85848794;                        //in ?
  yy[33] = (float)5.546318688;                        //in ?
  yy[34] = (float)11.92244772;                        //in ?
  yy[35] = (float)5.555448243;                        //in ?
  yy[36] = (float).9218489762;                        //in ?
  /*Cooling Water Outlet Temperatures*/
  yy[37] = (float)94.59927549;                        //in °C
  yy[38] = (float)77.29698353;                        //in °C
  /*Valve Positions*/
  yy[39] = (float)63.05263039;                        //in %
  yy[40] = (float)53.97970677;                        //in %
  yy[41] = (float)24.64355755;                        //in %
  yy[42] = (float)61.30192144;                        //in %
  yy[43] = (float)22.21;                              //in %
  yy[44] = (float)40.06374673;                        //in %
  yy[45] = (float)38.1003437;                         //in %
  yy[46] = (float)46.53415582;                        //in %
  yy[47] = (float)47.44573456;                        //in %
  yy[48] = (float)41.10581288;                        //in %
  yy[49] = (float)18.11349055;                        //in %
  yy[50] = (float)50.;                                //in %
  

  for (i__ = 1; i__ <= 12; ++i__){
    (*tcModelData).pv_.xmv[i__ - 1] = yy[i__ + 38];
    
    (*tcModelData).teproc_.vcv[i__ - 1] = (*tcModelData).pv_.xmv[i__ - 1];
    (*tcModelData).teproc_.vst[i__ - 1] = 2.;         //in %
    
    (*tcModelData).teproc_.ivst[i__ - 1] = (float)0.; //in 1
/* L200: */
  }

  /*Nominal Flowrate through Valves*/
  (*tcModelData).teproc_.vrng[0] = (float)400.;       //in lb-mol/h
  (*tcModelData).teproc_.vrng[1] = (float)400.;       //in lb-mol/h
  (*tcModelData).teproc_.vrng[2] = (float)100.;       //in lb-mol/h
  (*tcModelData).teproc_.vrng[3] = (float)1500.;      //in lb-mol/h
  (*tcModelData).teproc_.vrng[6] = (float)1500.;      //in lb-mol/h
  (*tcModelData).teproc_.vrng[7] = (float)1e3;        //in lb-mol/h
  (*tcModelData).teproc_.vrng[8] = (float).03;        //in ?
  (*tcModelData).teproc_.vrng[9] = (float)1e3;        //in gpm
  (*tcModelData).teproc_.vrng[10] = (float)1200.;     //in gpm
  
  /*Volumes of Vessels*/
  (*tcModelData).teproc_.vtr = (float)1300.;          //in ft³
  (*tcModelData).teproc_.vts = (float)3500.;          //in ft³
  (*tcModelData).teproc_.vtc = (float)156.5;          //in ft³  
  (*tcModelData).teproc_.vtv = (float)5e3;            //in ?
  
  (*tcModelData).teproc_.htr[0] = .06899381054;       //in ?
  (*tcModelData).teproc_.htr[1] = .05;                //in ?
  (*tcModelData).teproc_.hwr = (float)7060.;          //in ?
  (*tcModelData).teproc_.hws = (float)11138.;         //in ?
  (*tcModelData).teproc_.sfr[0] = (float).995;        //in 1
  (*tcModelData).teproc_.sfr[1] = (float).991;        //in 1
  (*tcModelData).teproc_.sfr[2] = (float).99;         //in 1
  (*tcModelData).teproc_.sfr[3] = (float).916;        //in 1
  (*tcModelData).teproc_.sfr[4] = (float).936;        //in 1
  (*tcModelData).teproc_.sfr[5] = (float).938;        //in 1
  (*tcModelData).teproc_.sfr[6] = .058;               //in 1
  (*tcModelData).teproc_.sfr[7] = .0301;              //in 1
  
  /*Stream 2*/
  (*tcModelData).teproc_.xst[0] = (float)0.;          //in mol%
  (*tcModelData).teproc_.xst[1] = (float)1e-4;        //in mol%
  (*tcModelData).teproc_.xst[2] = (float)0.;          //in mol%
  (*tcModelData).teproc_.xst[3] = (float).9999;       //in mol%
  (*tcModelData).teproc_.xst[4] = (float)0.;          //in mol%
  (*tcModelData).teproc_.xst[5] = (float)0.;          //in mol%
  (*tcModelData).teproc_.xst[6] = (float)0.;          //in mol%
  (*tcModelData).teproc_.xst[7] = (float)0.;          //in mol%
  (*tcModelData).teproc_.tst[0] = (float)45.;         //in °C
  
  /*Stream 3*/
  (*tcModelData).teproc_.xst[8] = (float)0.;          //in mol%
  (*tcModelData).teproc_.xst[9] = (float)0.;          //in mol%
  (*tcModelData).teproc_.xst[10] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[11] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[12] = (float).9999;      //in mol%
  (*tcModelData).teproc_.xst[13] = (float)1e-4;       //in mol%
  (*tcModelData).teproc_.xst[14] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[15] = (float)0.;         //in mol%
  (*tcModelData).teproc_.tst[1] = (float)45.;         //in °C

  /*Stream 1*/
  (*tcModelData).teproc_.xst[16] = (float).9999;      //in mol%
  (*tcModelData).teproc_.xst[17] = (float)1e-4;       //in mol%
  (*tcModelData).teproc_.xst[18] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[19] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[20] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[21] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[22] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[23] = (float)0.;         //in mol%
  (*tcModelData).teproc_.tst[2] = (float)45.;         //in °C

  /*Stream 4*/
  (*tcModelData).teproc_.xst[24] = (float).485;       //in mol%
  (*tcModelData).teproc_.xst[25] = (float).005;       //in mol%
  (*tcModelData).teproc_.xst[26] = (float).51;        //in mol%
  (*tcModelData).teproc_.xst[27] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[28] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[29] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[30] = (float)0.;         //in mol%
  (*tcModelData).teproc_.xst[31] = (float)0.;         //in mol%
  (*tcModelData).teproc_.tst[3] = (float)45.;         //in °C
  
  (*tcModelData).teproc_.cpflmx = (float)280275.;     //in ?
  (*tcModelData).teproc_.cpprmx = (float)1.3;         //in ?
  
  /*Time Constants of Valves*/
  (*tcModelData).teproc_.vtau[0] = (float)8.;         //in seconds
  (*tcModelData).teproc_.vtau[1] = (float)8.;         //in seconds
  (*tcModelData).teproc_.vtau[2] = (float)6.;         //in seconds
  (*tcModelData).teproc_.vtau[3] = (float)9.;         //in seconds
  (*tcModelData).teproc_.vtau[4] = (float)7.;         //in seconds
  (*tcModelData).teproc_.vtau[5] = (float)5.;         //in seconds
  (*tcModelData).teproc_.vtau[6] = (float)5.;         //in seconds
  (*tcModelData).teproc_.vtau[7] = (float)5.;         //in seconds
  (*tcModelData).teproc_.vtau[8] = (float)120.;       //in seconds
  (*tcModelData).teproc_.vtau[9] = (float)5.;         //in seconds
  (*tcModelData).teproc_.vtau[10] = (float)5.;        //in seconds
  (*tcModelData).teproc_.vtau[11] = (float)5.;        //in seconds 
  for (i__ = 1; i__ <= 12; ++i__){
    (*tcModelData).teproc_.vtau[i__ - 1] /= (float)3600.;
/* L300: */
  } //for (i__ = 1; i__ <= 12; ++i__){
  
  /*Seed of Random Generator*/
  if (rseed == NULL){
    (*tcModelData).randsd_.g = 1431655765.;
    (*tcModelData).randsd_.measnoise = 1431655765.;
    (*tcModelData).randsd_.procdist = 1431655765.;
  }else{
    (*tcModelData).randsd_.g = *rseed;
    (*tcModelData).randsd_.measnoise = *rseed;
    (*tcModelData).randsd_.procdist = *rseed;
  } //if (rseed == NULL){
    
  /*Amplitudes of Measurement Noise*/
  if (((*tcModelData).MSFlag & 0x10) > 0){
    for (i__ = 1; i__ <= 41; ++i__){
      (*tcModelData).teproc_.xns[i__ - 1] = 0.;       
    } //for (i__ = 1; i__ <= 41; ++i__){
    
    for (i__ = 1; i__ <= 34; ++i__){
      (*tcModelData).teproc_.xnsadd[i__ - 1] = 0.;    
    } //for (i__ = 1; i__ <= 13; ++i__){
  }else{
    (*tcModelData).teproc_.xns[0] = .0012;            //in kscmh
    (*tcModelData).teproc_.xns[1] = 18.;              //in kg/h
    (*tcModelData).teproc_.xns[2] = 22.;              //in kg/h
    (*tcModelData).teproc_.xns[3] = .05;              //in kscmh
    (*tcModelData).teproc_.xns[4] = .2;               //in kscmh
    (*tcModelData).teproc_.xns[5] = .21;              //in kscmh
    (*tcModelData).teproc_.xns[6] = .3;               //in kPa gauge
    (*tcModelData).teproc_.xns[7] = .5;               //in %
    (*tcModelData).teproc_.xns[8] = .01;              //in °C
    (*tcModelData).teproc_.xns[9] = .0017;            //in kscmh
    (*tcModelData).teproc_.xns[10] = .01;             //in °C
    (*tcModelData).teproc_.xns[11] = 1.;              //in %
    (*tcModelData).teproc_.xns[12] = .3;              //in kPa gauge
    (*tcModelData).teproc_.xns[13] = .125;            //in m³/h
    (*tcModelData).teproc_.xns[14] = 1.;              //in %
    (*tcModelData).teproc_.xns[15] = .3;              //in kPa gauge
    (*tcModelData).teproc_.xns[16] = .115;            //in m³/h
    (*tcModelData).teproc_.xns[17] = .01;             //in °C
    (*tcModelData).teproc_.xns[18] = 1.15;            //in kg/h
    (*tcModelData).teproc_.xns[19] = .2;              //in kW
    (*tcModelData).teproc_.xns[20] = .01;             //in °C
    (*tcModelData).teproc_.xns[21] = .01;             //in °C
    (*tcModelData).teproc_.xns[22] = .25;             //in mol %
    (*tcModelData).teproc_.xns[23] = .1;              //in mol %
    (*tcModelData).teproc_.xns[24] = .25;             //in mol %
    (*tcModelData).teproc_.xns[25] = .1;              //in mol %
    (*tcModelData).teproc_.xns[26] = .25;             //in mol %
    (*tcModelData).teproc_.xns[27] = .025;            //in mol %
    (*tcModelData).teproc_.xns[28] = .25;             //in mol %
    (*tcModelData).teproc_.xns[29] = .1;              //in mol %
    (*tcModelData).teproc_.xns[30] = .25;             //in mol %
    (*tcModelData).teproc_.xns[31] = .1;              //in mol %
    (*tcModelData).teproc_.xns[32] = .25;             //in mol %
    (*tcModelData).teproc_.xns[33] = .025;            //in mol %
    (*tcModelData).teproc_.xns[34] = .05;             //in mol %
    (*tcModelData).teproc_.xns[35] = .05;             //in mol %
    (*tcModelData).teproc_.xns[36] = .01;             //in mol %
    (*tcModelData).teproc_.xns[37] = .01;             //in mol %
    (*tcModelData).teproc_.xns[38] = .01;             //in mol %
    (*tcModelData).teproc_.xns[39] = .5;              //in mol %
    (*tcModelData).teproc_.xns[40] = .5;              //in mol %

    (*tcModelData).teproc_.xnsadd[0] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[1] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[2] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[3] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[4] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[5] = .125;          //in m³/h
    (*tcModelData).teproc_.xnsadd[6] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[7] = .125;          //in m³/h
    (*tcModelData).teproc_.xnsadd[8] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[9] = .01;           //in °C
    (*tcModelData).teproc_.xnsadd[10] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[11] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[12] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[13] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[14] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[15] = .025;         //in mol %
    (*tcModelData).teproc_.xnsadd[16] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[17] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[18] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[19] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[20] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[21] = .025;         //in mol %
    (*tcModelData).teproc_.xnsadd[22] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[23] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[24] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[25] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[26] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[27] = .025;         //in mol %
    (*tcModelData).teproc_.xnsadd[28] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[29] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[30] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[31] = .1;           //in mol %
    (*tcModelData).teproc_.xnsadd[32] = .25;          //in mol %
    (*tcModelData).teproc_.xnsadd[33] = .025;         //in mol %
  } //if (((*tcModelData).MSFlag & 0x10) > 0){
  
  /*Initilization of Disturbance Flags*/
  for (i__ = 1; i__ <= 28; ++i__){
    (*tcModelData).dvec_.idv[i__ - 1] = (float)0.;    //in 1
/* L500: */
  } //for (i__ = 1; i__ <= 28; ++i__){
  
  /*Data of Disturbance Processes*/
  (*tcModelData).wlk_.hspan[0] = .2;                  //in h
  (*tcModelData).wlk_.hzero[0] = .5;                  //in h
  (*tcModelData).wlk_.sspan[0] = .03;                 //in mole-ratio
  (*tcModelData).wlk_.szero[0] = .485;                //in mole-ratio
  (*tcModelData).wlk_.spspan[0] = 0.;                 //in mole-ratio/h

  (*tcModelData).wlk_.hspan[1] = .7;                  //in h
  (*tcModelData).wlk_.hzero[1] = 1.;                  //in h
  (*tcModelData).wlk_.sspan[1] = .003;                //in mole-ratio
  (*tcModelData).wlk_.szero[1] = .005;                //in mole-ratio
  (*tcModelData).wlk_.spspan[1] = 0.;                 //in mole-ratio/h
  
  (*tcModelData).wlk_.hspan[2] = .25;                 //in h
  (*tcModelData).wlk_.hzero[2] = .5;                  //in h
  (*tcModelData).wlk_.sspan[2] = 10.;                 //in °C
  (*tcModelData).wlk_.szero[2] = 45.;                 //in °C
  (*tcModelData).wlk_.spspan[2] = 0.;                 //in °C/h
  
  (*tcModelData).wlk_.hspan[3] = .7;                  //in h
  (*tcModelData).wlk_.hzero[3] = 1.;                  //in h
  (*tcModelData).wlk_.sspan[3] = 10.;                 //in °C
  (*tcModelData).wlk_.szero[3] = 45.;                 //in °C
  (*tcModelData).wlk_.spspan[3] = 0.;                 //in °C/h
  
  (*tcModelData).wlk_.hspan[4] = .15;                 //in h
  (*tcModelData).wlk_.hzero[4] = .25;                 //in h
  (*tcModelData).wlk_.sspan[4] = 10.;                 //in °C
  (*tcModelData).wlk_.szero[4] = 35.;                 //in °C
  (*tcModelData).wlk_.spspan[4] = 0.;                 //in °C/h
  
  (*tcModelData).wlk_.hspan[5] = .15;                 //in h
  (*tcModelData).wlk_.hzero[5] = .25;                 //in h
  (*tcModelData).wlk_.sspan[5] = 10.;                 //in °C
  (*tcModelData).wlk_.szero[5] = 40.;                 //in °C
  (*tcModelData).wlk_.spspan[5] = 0.;                 //in °C/h
  
  (*tcModelData).wlk_.hspan[6] = 1.;                  //in h
  (*tcModelData).wlk_.hzero[6] = 2.;                  //in h
  (*tcModelData).wlk_.sspan[6] = .25;                 //in 1
  (*tcModelData).wlk_.szero[6] = 1.;                  //in 1
  (*tcModelData).wlk_.spspan[6] = 0.;                 //in 1/h
  
  (*tcModelData).wlk_.hspan[7] = 1.;                  //in h
  (*tcModelData).wlk_.hzero[7] = 2.;                  //in h
  (*tcModelData).wlk_.sspan[7] = .25;                 //in 1
  (*tcModelData).wlk_.szero[7] = 1.;                  //in 1
  (*tcModelData).wlk_.spspan[7] = 0.;                 //in 1/h
  
  (*tcModelData).wlk_.hspan[8] = .4;                  //in h
  (*tcModelData).wlk_.hzero[8] = .5;                  //in h
  (*tcModelData).wlk_.sspan[8] = .25;                 //in ?
  (*tcModelData).wlk_.szero[8] = 0.;                  //in ?
  (*tcModelData).wlk_.spspan[8] = 0.;                 //in ?/h
  
  (*tcModelData).wlk_.hspan[9] = 1.5;                 //in h
  (*tcModelData).wlk_.hzero[9] = 2.;                  //in h
  (*tcModelData).wlk_.sspan[9] = 0.;                  //in ?
  (*tcModelData).wlk_.szero[9] = 0.;                  //in ?
  (*tcModelData).wlk_.spspan[9] = 0.;                 //in ?/h
  
  (*tcModelData).wlk_.hspan[10] = 2.;                 //in h
  (*tcModelData).wlk_.hzero[10] = 3.;                 //in h
  (*tcModelData).wlk_.sspan[10] = 0.;                 //in ?
  (*tcModelData).wlk_.szero[10] = 0.;                 //in ?
  (*tcModelData).wlk_.spspan[10] = 0.;                //in ?/h
  
  (*tcModelData).wlk_.hspan[11] = 1.5;                //in h
  (*tcModelData).wlk_.hzero[11] = 2.;                 //in h
  (*tcModelData).wlk_.sspan[11] = 0.;                 //in ?
  (*tcModelData).wlk_.szero[11] = 0.;                 //in ?
  (*tcModelData).wlk_.spspan[11] = 0.;                //in ?/h
  
  (*tcModelData).wlk_.hspan[12] = .15;                //in h
  (*tcModelData).wlk_.hzero[12] = .25;                //in h
  (*tcModelData).wlk_.sspan[12] = 10.;                //in °C
  (*tcModelData).wlk_.szero[12] = 45.;                //in °C
  (*tcModelData).wlk_.spspan[12] = 0.;                //in °C/h

  (*tcModelData).wlk_.hspan[13] = .25;                //in h
  (*tcModelData).wlk_.hzero[13] = .5;                 //in h
  (*tcModelData).wlk_.sspan[13] = 10.;                //in °C
  (*tcModelData).wlk_.szero[13] = 45.;                //in °C
  (*tcModelData).wlk_.spspan[13] = 0.;                //in °C/h

  (*tcModelData).wlk_.hspan[14] = .15;                //in h
  (*tcModelData).wlk_.hzero[14] = .25;                //in h
  (*tcModelData).wlk_.sspan[14] = 5.;                 //in lb-mol/h
  (*tcModelData).wlk_.szero[14] = 100.;               //in lb-mol/h
  (*tcModelData).wlk_.spspan[14] = 0.;                //in lb-mol/h²

  (*tcModelData).wlk_.hspan[15] = .25;                //in h
  (*tcModelData).wlk_.hzero[15] = .5;                 //in h
  (*tcModelData).wlk_.sspan[15] = 20.;                //in lb-mol/h
  (*tcModelData).wlk_.szero[15] = 400.;               //in lb-mol/h
  (*tcModelData).wlk_.spspan[15] = 0.;                //in lb-mol/h²

  (*tcModelData).wlk_.hspan[16] = .25;                //in h
  (*tcModelData).wlk_.hzero[16] = .5;                 //in h
  (*tcModelData).wlk_.sspan[16] = 20.;                //in lb-mol/h
  (*tcModelData).wlk_.szero[16] = 400.;               //in lb-mol/h
  (*tcModelData).wlk_.spspan[16] = 0.;                //in lb-mol/h²

  (*tcModelData).wlk_.hspan[17] = .7;                 //in h
  (*tcModelData).wlk_.hzero[17] = 1.;                 //in h
  (*tcModelData).wlk_.sspan[17] = 75.;                //in lb-mol/h
  (*tcModelData).wlk_.szero[17] = 1500.;              //in lb-mol/h
  (*tcModelData).wlk_.spspan[17] = 0.;                //in lb-mol/h²

  (*tcModelData).wlk_.hspan[18] = .1;                 //in h
  (*tcModelData).wlk_.hzero[18] = .2;                 //in h
  (*tcModelData).wlk_.sspan[18] = 50.;                //in gpm
  (*tcModelData).wlk_.szero[18] = (float)1e3;         //in gpm
  (*tcModelData).wlk_.spspan[18] = 0.;                //in gpm/h

  (*tcModelData).wlk_.hspan[19] = .1;                 //in h
  (*tcModelData).wlk_.hzero[19] = .2;                 //in h
  (*tcModelData).wlk_.sspan[19] = 60.;                //in gpm
  (*tcModelData).wlk_.szero[19] = 1200.;              //in gpm
  (*tcModelData).wlk_.spspan[19] = 0.;                //in gpm/h
  
  /*Initilization of Disturbance Processes Parameters*/
  for (i__ = 1; i__ <= 20; ++i__){
    (*tcModelData).wlk_.tlast[i__ - 1] = 0.;          //in h
	(*tcModelData).wlk_.tnext[i__ - 1] = .1;          //in h
	(*tcModelData).wlk_.adist[i__ - 1] =              //unit depends on 
                  (*tcModelData).wlk_.szero[i__ - 1]; //value
	(*tcModelData).wlk_.bdist[i__ - 1] = 0.;          //in x/h
	(*tcModelData).wlk_.cdist[i__ - 1] = 0.;          //in x/h²
	(*tcModelData).wlk_.ddist[i__ - 1] = 0.;          //in x/h³
/* L550: */
  } //for (i__ = 1; i__ <= 12; ++i__){
  
  (*tcModelData).tlastcomp = -1.;  
  *time = (float)0.;
  tefunc(ModelData, nn, time, &yy[1], &yp[1], 0);

  #undef isd
  
  return 0;
} /* teinit */


/*-------------------------------------------------------------------------
-                               t e f u n c                               -
-------------------------------------------------------------------------*/
static int tefunc(void *ModelData, 
                  const integer *nn, doublereal *time, doublereal *yy, 
                  doublereal *yp, shortint Callflag){
  /*----------------------------- Variables -----------------------------*/
  integer i__1;
  doublereal d__1;

  struct stModelData *tcModelData;
  int distende;
  int distindex[16];
  int distnum;
  int distindch;
  doublereal flms;
  doublereal xcmp[41];
  doublereal xcmpadd[24];
  doublereal hwlk;
  doublereal vpos[12];
  doublereal xmns;
  doublereal swlk;
  doublereal spwlk;
  doublereal vovrl;
  doublereal rg;
  doublereal flcoef;
  doublereal pr;
  doublereal tmpfac;
  doublereal uarlev;
  doublereal r1f;
  doublereal r2f;
  doublereal uac;
  doublereal fin[8];
  doublereal dlp;
  doublereal vpr;
  doublereal uas;
  doublereal prate;
  integer aux;
  integer i__;
  integer j__;
  #define isd ((doublereal *)&(*tcModelData).dvec_ + 28)
    
  /*Typcast of Dataset Pointer*/  
  tcModelData = ModelData;

  /*Parameter adjustments*/
  --yp;
  --yy;

  /*--------------------------- Function Body ---------------------------*/
  if((((*tcModelData).tlastcomp != *time) || (Callflag == 1)) &&
     (((*tcModelData).MSFlag & 0x8000) == 0)){
    /*Limiting of Disturbance Activations*/
    for (i__ = 1; i__ <= 28; ++i__){
      if ((*tcModelData).dvec_.idv[i__ - 1] < (float)0.){
  	    (*tcModelData).dvec_.idv[i__ - 1] = (float)0.;
	  } //if ((*tcModelData).dvec_.idv[i__ - 1] < 0){
      if ((*tcModelData).dvec_.idv[i__ - 1] > (float)1.){
	    (*tcModelData).dvec_.idv[i__ - 1] = (float)1.;
      } //if ((*tcModelData).dvec_.idv[i__ - 1] > 1){
      /* L500: */
    } //for (i__ = 1; i__ <= 20; ++i__){
    
    /*Assignment of Disturbance Activations*/
    (*tcModelData).wlk_.idvwlk[0]  = (*tcModelData).dvec_.idv[7];
    (*tcModelData).wlk_.idvwlk[1]  = (*tcModelData).dvec_.idv[7];
    (*tcModelData).wlk_.idvwlk[2]  = (*tcModelData).dvec_.idv[8];
    (*tcModelData).wlk_.idvwlk[3]  = (*tcModelData).dvec_.idv[9];
    (*tcModelData).wlk_.idvwlk[4]  = (*tcModelData).dvec_.idv[10];
    (*tcModelData).wlk_.idvwlk[5]  = (*tcModelData).dvec_.idv[11];
    (*tcModelData).wlk_.idvwlk[6]  = (*tcModelData).dvec_.idv[12];
    (*tcModelData).wlk_.idvwlk[7]  = (*tcModelData).dvec_.idv[12];
    (*tcModelData).wlk_.idvwlk[8]  = (*tcModelData).dvec_.idv[15];
    (*tcModelData).wlk_.idvwlk[9]  = (*tcModelData).dvec_.idv[16];
    (*tcModelData).wlk_.idvwlk[10] = (*tcModelData).dvec_.idv[17];
    (*tcModelData).wlk_.idvwlk[11] = (*tcModelData).dvec_.idv[19];
    (*tcModelData).wlk_.idvwlk[12] = (*tcModelData).dvec_.idv[20];
    (*tcModelData).wlk_.idvwlk[13] = (*tcModelData).dvec_.idv[21];
    (*tcModelData).wlk_.idvwlk[14] = (*tcModelData).dvec_.idv[22];
    (*tcModelData).wlk_.idvwlk[15] = (*tcModelData).dvec_.idv[23];
    (*tcModelData).wlk_.idvwlk[16] = (*tcModelData).dvec_.idv[24];
    (*tcModelData).wlk_.idvwlk[17] = (*tcModelData).dvec_.idv[25];
    (*tcModelData).wlk_.idvwlk[18] = (*tcModelData).dvec_.idv[26];
    (*tcModelData).wlk_.idvwlk[19] = (*tcModelData).dvec_.idv[27];
    
    if (((*tcModelData).MSFlag & 0x40) > 0){
      /*Recalculation of Disturbance Process Parameters - Determination of
        Processes to be Updated (1 - 9/13 - 20)*/
      distnum = 0;
      for (i__ = 1; i__ <= 20; ++i__){
        if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){
          distindex[distnum] = i__ - 1; 
          distnum++;
        } //if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){
        
        /*Step-over of 10 through 12*/
        if(i__ == 9){
          i__ = i__ + 3;
        }        
      } //for (i__ = 1; i__ <= 20; ++i__){ */
    
      /*Recalculation of Disturbance Process Parameters - Sorting (1 - 9/
        13 - 20)*/
      for(i__ = 1; i__ < distnum; ++i__){
        distindch = distindex[i__];
        j__ = i__;
        while((j__ > 0) && 
             ((*tcModelData).wlk_.tnext[j__ - 1] > 
                                    (*tcModelData).wlk_.tnext[distindch])){
          distindex[j__] = distindex[j__ - 1];
          j__--;
        } //while((j__ > 0) && ...
        distindex[j__] = distindch;
      } //for(i__ = 1; i__ < distnum; ++i__){
    
      /*Recalculation of Disturbance Process Parameters - Update (1 - 9/
        13 - 20)*/
      for(i__ = 0; i__ < distnum; ++i__){
  	    hwlk = (*tcModelData).wlk_.tnext[distindex[i__]] - 
                                 (*tcModelData).wlk_.tlast[distindex[i__]];
	    
        swlk = (*tcModelData).wlk_.adist[distindex[i__]] + 
               hwlk * ((*tcModelData).wlk_.bdist[distindex[i__]] + 
                   hwlk * ((*tcModelData).wlk_.cdist[distindex[i__]] + 
                       hwlk * (*tcModelData).wlk_.ddist[distindex[i__]]));
	    
        spwlk = 
           (*tcModelData).wlk_.bdist[distindex[i__]] + 
           hwlk * ((*tcModelData).wlk_.cdist[distindex[i__]] * 2. +
                    hwlk * 3. * (*tcModelData).wlk_.ddist[distindex[i__]]);
	    
        (*tcModelData).wlk_.tlast[distindex[i__]] = 
                                 (*tcModelData).wlk_.tnext[distindex[i__]];
	    
        tesub5_(ModelData, &swlk, &spwlk, 
                &(*tcModelData).wlk_.adist[distindex[i__]], 
                &(*tcModelData).wlk_.bdist[distindex[i__]], 
                &(*tcModelData).wlk_.cdist[distindex[i__]], 
                &(*tcModelData).wlk_.ddist[distindex[i__]], 
                &(*tcModelData).wlk_.tlast[distindex[i__]], 
   	            &(*tcModelData).wlk_.tnext[distindex[i__]], 
                &(*tcModelData).wlk_.hspan[distindex[i__]],
                &(*tcModelData).wlk_.hzero[distindex[i__]], 
                &(*tcModelData).wlk_.sspan[distindex[i__]], 
                &(*tcModelData).wlk_.szero[distindex[i__]], 
                &(*tcModelData).wlk_.spspan[distindex[i__]], 
                &(*tcModelData).wlk_.idvwlk[distindex[i__]]);
      } //for(i__ = 1; i__ <= distunm; ++i__){

      /*Recalculation of Disturbance Process Parameters - Determination of
        Processes to be Updated (10 - 12)*/
      distnum = 0;
      for (i__ = 10; i__ <= 12; ++i__){
        if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){
          distindex[distnum] = i__ - 1;
          distnum++;
        } //if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){
      } //for (i__ = 1; i__ <= 9; ++i__){ */
    
      /*Recalculation of Disturbance Process Parameters - Sorting (10 - 
        12)*/
      for(i__ = 1; i__ < distnum; ++i__){
        distindch = distindex[i__];
        j__ = i__;
        while((j__ > 0) && 
             ((*tcModelData).wlk_.tnext[j__ - 1] > 
                                    (*tcModelData).wlk_.tnext[distindch])){
          distindex[j__] = distindex[j__ - 1];
          j__--;
        } //while((j__ > 0) && ...
        distindex[j__] = distindch;
      } //for(i__ = 1; i__ < distnum; ++i__){
    
      /*Recalculation of Disturbance Process Parameters - Update (10 - 
        12)*/
      for(i__ = 0; i__ < distnum; ++i__){
        hwlk = (*tcModelData).wlk_.tnext[distindex[i__]] - 
                                 (*tcModelData).wlk_.tlast[distindex[i__]];
	    
        swlk = (*tcModelData).wlk_.adist[distindex[i__]] + 
               hwlk * ((*tcModelData).wlk_.bdist[distindex[i__]] + 
                   hwlk * ((*tcModelData).wlk_.cdist[distindex[i__]] + 
                       hwlk * (*tcModelData).wlk_.ddist[distindex[i__]]));
	    
        spwlk = 
           (*tcModelData).wlk_.bdist[distindex[i__]] + 
           hwlk * ((*tcModelData).wlk_.cdist[distindex[i__]] * 2. +
		  	        hwlk * 3. * (*tcModelData).wlk_.ddist[distindex[i__]]);
    
        (*tcModelData).wlk_.tlast[distindex[i__]] = 
                                 (*tcModelData).wlk_.tnext[distindex[i__]];   
        if (swlk > .1){
	      (*tcModelData).wlk_.adist[distindex[i__]] = swlk;
		  (*tcModelData).wlk_.bdist[distindex[i__]] = spwlk;
		  (*tcModelData).wlk_.cdist[distindex[i__]] = 
                                           -(swlk * 3. + spwlk * .2) / .01;
		  (*tcModelData).wlk_.ddist[distindex[i__]] = 
                                           (swlk * 2. + spwlk * .1) / .001;
		  (*tcModelData).wlk_.tnext[distindex[i__]] = 
                            (*tcModelData).wlk_.tlast[distindex[i__]] + .1;
	    }else{
          aux = -1;
		  hwlk = (*tcModelData).wlk_.hspan[distindex[i__]] * 
                           tesub7_(ModelData, &aux) + 
                           (*tcModelData).wlk_.hzero[distindex[i__]];
	      (*tcModelData).wlk_.adist[distindex[i__]] = swlk;
		  (*tcModelData).wlk_.bdist[distindex[i__]] = spwlk;

          /* Computing 2nd power */
		  d__1 = hwlk;
		  (*tcModelData).wlk_.cdist[distindex[i__]] = 
                ((*tcModelData).wlk_.idvwlk[distindex[i__]] - 
                                             2*spwlk*d__1) / (d__1 * d__1);
		  (*tcModelData).wlk_.ddist[distindex[i__]] = 
                                                     spwlk / (d__1 * d__1);
		  (*tcModelData).wlk_.tnext[distindex[i__]] = 
                          (*tcModelData).wlk_.tlast[distindex[i__]] + hwlk;
        } //if (swlk > .1){
      } //for(i__ = 0; i__ < distnum; ++i__){      
    }else{
      /* Original Code of J.J. Downs & E.F. Vogel and N.L. Ricker [2]*/
      /*Recalculation of Disturbance Process Parameters (1 - 9/13 - 20)*/
      if(((*tcModelData).MSFlag & 0x8000) > 0){
        distende = 9;
      }else{
        distende = 20;
      } //if(((*tcModelData).MSFlag & 0x8000) > 0){
      
      for (i__ = 1; i__ <= distende; ++i__){
        if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){
  	      hwlk = (*tcModelData).wlk_.tnext[i__ - 1] - 
                                        (*tcModelData).wlk_.tlast[i__ - 1];
	    
          swlk = (*tcModelData).wlk_.adist[i__ - 1] + 
                 hwlk * ((*tcModelData).wlk_.bdist[i__ - 1] + 
                         hwlk * ((*tcModelData).wlk_.cdist[i__ - 1] + 
                               hwlk * (*tcModelData).wlk_.ddist[i__ - 1]));
	    
          spwlk = (*tcModelData).wlk_.bdist[i__ - 1] + 
                  hwlk * ((*tcModelData).wlk_.cdist[i__ - 1] * 2. +
		                  hwlk * 3. * (*tcModelData).wlk_.ddist[i__ - 1]);
	    
          (*tcModelData).wlk_.tlast[i__ - 1] = 
                                        (*tcModelData).wlk_.tnext[i__ - 1];
	    
          tesub5_(ModelData, &swlk, &spwlk, 
                  &(*tcModelData).wlk_.adist[i__ - 1], 
                  &(*tcModelData).wlk_.bdist[i__ - 1], 
                  &(*tcModelData).wlk_.cdist[i__ - 1], 
                  &(*tcModelData).wlk_.ddist[i__ - 1], 
                  &(*tcModelData).wlk_.tlast[i__ - 1], 
  			      &(*tcModelData).wlk_.tnext[i__ - 1], 
                  &(*tcModelData).wlk_.hspan[i__ - 1],
                  &(*tcModelData).wlk_.hzero[i__ - 1], 
                  &(*tcModelData).wlk_.sspan[i__ - 1], 
                  &(*tcModelData).wlk_.szero[i__ - 1], 
                  &(*tcModelData).wlk_.spspan[i__ - 1], 
                  &(*tcModelData).wlk_.idvwlk[i__ - 1]);
        } //if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){

        /*Step-over of 10 through 12*/
        if(i__ == 9){
          i__ = i__ + 3;
        }        
      /* L900: */
      } //for (i__ = 1; i__ <= 20; ++i__){ */
       
      /*Recalculation of Disturbance Process Parameters (10 - 12)*/
      for (i__ = 10; i__ <= 12; ++i__){
        if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){
          hwlk = (*tcModelData).wlk_.tnext[i__ - 1] - 
                                        (*tcModelData).wlk_.tlast[i__ - 1];
	    
          swlk = (*tcModelData).wlk_.adist[i__ - 1] + 
                 hwlk * ((*tcModelData).wlk_.bdist[i__ - 1] + 
                        hwlk * ((*tcModelData).wlk_.cdist[i__ - 1] + 
                               hwlk * (*tcModelData).wlk_.ddist[i__ - 1]));
	    
          spwlk = (*tcModelData).wlk_.bdist[i__ - 1] + 
                  hwlk * ((*tcModelData).wlk_.cdist[i__ - 1] * 2. +
	     	  	          hwlk * 3. * (*tcModelData).wlk_.ddist[i__ - 1]);
	    
          (*tcModelData).wlk_.tlast[i__ - 1] = 
                                        (*tcModelData).wlk_.tnext[i__ - 1];   
          if (swlk > .1){
   	        (*tcModelData).wlk_.adist[i__ - 1] = swlk;
		    (*tcModelData).wlk_.bdist[i__ - 1] = spwlk;
		    (*tcModelData).wlk_.cdist[i__ - 1] = 
                                           -(swlk * 3. + spwlk * .2) / .01;
		    (*tcModelData).wlk_.ddist[i__ - 1] = 
                                           (swlk * 2. + spwlk * .1) / .001;
		    (*tcModelData).wlk_.tnext[i__ - 1] = 
                                   (*tcModelData).wlk_.tlast[i__ - 1] + .1;
	      }else{
            aux = -1;
		    hwlk = (*tcModelData).wlk_.hspan[i__ - 1] * 
                   tesub7_(ModelData, &aux) + 
                                        (*tcModelData).wlk_.hzero[i__ - 1];
   	        (*tcModelData).wlk_.adist[i__ - 1] = swlk;
		    (*tcModelData).wlk_.bdist[i__ - 1] = spwlk;

            /* Computing 2nd power */
		    d__1 = hwlk;
		    (*tcModelData).wlk_.cdist[i__ - 1] = 
                       ((*tcModelData).wlk_.idvwlk[i__ - 1] -
                                             2*spwlk*d__1) / (d__1 * d__1);
		    (*tcModelData).wlk_.ddist[i__ - 1] = spwlk / (d__1 * d__1);
		    (*tcModelData).wlk_.tnext[i__ - 1] = 
                                 (*tcModelData).wlk_.tlast[i__ - 1] + hwlk;
          } //if (swlk > .1){
	    } //if (*time >= (*tcModelData).wlk_.tnext[i__ - 1]){
      /* L910: */
      } //for (i__ = 10; i__ <= 12; ++i__){
    } //if (((*tcModelData).MSFlag & 0x40) > 0){

  /*Initilization of Disturbance Processes Parameters*/
    if (*time == 0.){
	  for (i__ = 1; i__ <= 20; ++i__){
	    (*tcModelData).wlk_.adist[i__ - 1] =  
                                        (*tcModelData).wlk_.szero[i__ - 1];
	    (*tcModelData).wlk_.bdist[i__ - 1] = 0.;
	    (*tcModelData).wlk_.cdist[i__ - 1] = 0.;
	    (*tcModelData).wlk_.ddist[i__ - 1] = 0.;
	    (*tcModelData).wlk_.tlast[i__ - 1] = 0.;
	    (*tcModelData).wlk_.tnext[i__ - 1] = .1;
      /* L950: */
      } //for (i__ = 1; i__ <= 20; ++i__){
    } //if (*time == 0.){
   
    /*Determination of Disturbed Values*/
    (*tcModelData).teproc_.xst[24] = tesub8_(ModelData, &c__1, time) - 
                                   (*tcModelData).dvec_.idv[0] * .03 - 
                                   (*tcModelData).dvec_.idv[1] * .00243719;
    (*tcModelData).teproc_.xst[25] = tesub8_(ModelData, &c__2, time) + 
                                   (*tcModelData).dvec_.idv[1] * .005;
    (*tcModelData).teproc_.xst[26] = 1. - (*tcModelData).teproc_.xst[24] - 
                                   (*tcModelData).teproc_.xst[25];
    (*tcModelData).teproc_.tst[0]  = tesub8_(ModelData, &c__3, time) + 
                                   (*tcModelData).dvec_.idv[2] * 5.;
    (*tcModelData).teproc_.tst[3]  = tesub8_(ModelData, &c__4, time);
    (*tcModelData).teproc_.tcwr    = tesub8_(ModelData, &c__5, time) + 
                                   (*tcModelData).dvec_.idv[3] * 5.;
    (*tcModelData).teproc_.tcws    = tesub8_(ModelData, &c__6, time) + 
                                   (*tcModelData).dvec_.idv[4] * 5.;
    r1f = tesub8_(ModelData, &c__7, time);   
    r2f = tesub8_(ModelData, &c__8, time);
    (*tcModelData).teproc_.tst[2]   = tesub8_(ModelData, &c__13, time);
    (*tcModelData).teproc_.tst[1]   = tesub8_(ModelData, &c__14, time);
    (*tcModelData).teproc_.vrng[2]  = tesub8_(ModelData, &c__15, time);
    (*tcModelData).teproc_.vrng[0]  = tesub8_(ModelData, &c__16, time);
    (*tcModelData).teproc_.vrng[1]  = tesub8_(ModelData, &c__17, time);
    (*tcModelData).teproc_.vrng[3]  = tesub8_(ModelData, &c__18, time);
    (*tcModelData).teproc_.vrng[9]  = tesub8_(ModelData, &c__19, time);
    (*tcModelData).teproc_.vrng[10] = tesub8_(ModelData, &c__20, time);

    /*Setting of Disturbance Outputs*/
    (*tcModelData).pv_.xmeasdist[0]  = (*tcModelData).teproc_.xst[24]*100;
    (*tcModelData).pv_.xmeasdist[1]  = (*tcModelData).teproc_.xst[25]*100;
    (*tcModelData).pv_.xmeasdist[2]  = (*tcModelData).teproc_.xst[26]*100;
    (*tcModelData).pv_.xmeasdist[3]  = (*tcModelData).teproc_.tst[0];
    (*tcModelData).pv_.xmeasdist[4]  = (*tcModelData).teproc_.tst[3];
    (*tcModelData).pv_.xmeasdist[5]  = (*tcModelData).teproc_.tcwr;
    (*tcModelData).pv_.xmeasdist[6]  = (*tcModelData).teproc_.tcws;   
    (*tcModelData).pv_.xmeasdist[7]  = r1f;
    (*tcModelData).pv_.xmeasdist[8]  = r2f;
    (*tcModelData).pv_.xmeasdist[9]  = tesub8_(ModelData, &c__9, time);
    (*tcModelData).pv_.xmeasdist[10] = tesub8_(ModelData, &c__10, time);
    (*tcModelData).pv_.xmeasdist[11] = tesub8_(ModelData, &c__11, time);
    (*tcModelData).pv_.xmeasdist[12] = tesub8_(ModelData, &c__12, time);
    (*tcModelData).pv_.xmeasdist[13] = (*tcModelData).teproc_.tst[2];
    (*tcModelData).pv_.xmeasdist[14] = (*tcModelData).teproc_.tst[1];
    (*tcModelData).pv_.xmeasdist[15] = (*tcModelData).teproc_.vrng[2]*
                                       (float).454;
    (*tcModelData).pv_.xmeasdist[16] = (*tcModelData).teproc_.vrng[0]*
                                       (float).454;
    (*tcModelData).pv_.xmeasdist[17] = (*tcModelData).teproc_.vrng[1]*
                                       (float).454;
    (*tcModelData).pv_.xmeasdist[18] = (*tcModelData).teproc_.vrng[3]*
                                       (float).454;
    (*tcModelData).pv_.xmeasdist[19] = (*tcModelData).teproc_.vrng[9]*
                                        (float)0.003785411784 * (float)60.;
    (*tcModelData).pv_.xmeasdist[20] = (*tcModelData).teproc_.vrng[10]*
                                        (float)0.003785411784 * (float)60.;
        
    /*Retrieving of Current States*/
    for (i__ = 1; i__ <= 3; ++i__){
      (*tcModelData).teproc_.ucvr[i__ - 1] = yy[i__];
  	  (*tcModelData).teproc_.ucvs[i__ - 1] = yy[i__ + 9];
  	  (*tcModelData).teproc_.uclr[i__ - 1] = (float)0.;
	  (*tcModelData).teproc_.ucls[i__ - 1] = (float)0.;
    /* L1010: */
    } //for (i__ = 1; i__ <= 3; ++i__){
    
    for (i__ = 4; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.uclr[i__ - 1] = yy[i__];
	  (*tcModelData).teproc_.ucls[i__ - 1] = yy[i__ + 9];
    /* L1020: */
    } //for (i__ = 4; i__ <= 8; ++i__){
    
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.uclc[i__ - 1] = yy[i__ + 18];
	  (*tcModelData).teproc_.ucvv[i__ - 1] = yy[i__ + 27];
    /* L1030: */
    } //for (i__ = 1; i__ <= 8; ++i__){
    (*tcModelData).teproc_.etr = yy[9];
    (*tcModelData).teproc_.ets = yy[18];
    (*tcModelData).teproc_.etc = yy[27];
    (*tcModelData).teproc_.etv = yy[36];
    (*tcModelData).teproc_.twr = yy[37];
    (*tcModelData).teproc_.tws = yy[38];
    for (i__ = 1; i__ <= 12; ++i__){
	  vpos[i__ - 1] = yy[i__ + 38];
    /* L1035: */
    } //for (i__ = 1; i__ <= 12; ++i__){
  
    /*Calculation of Collective Holdup*/
    (*tcModelData).teproc_.utlr = (float)0.;
    (*tcModelData).teproc_.utls = (float)0.;
    (*tcModelData).teproc_.utlc = (float)0.;
    (*tcModelData).teproc_.utvv = (float)0.;
    for (i__ = 1; i__ <= 8; ++i__){
      (*tcModelData).teproc_.utlr += (*tcModelData).teproc_.uclr[i__ - 1];
	  (*tcModelData).teproc_.utls += (*tcModelData).teproc_.ucls[i__ - 1];
	  (*tcModelData).teproc_.utlc += (*tcModelData).teproc_.uclc[i__ - 1];
	  (*tcModelData).teproc_.utvv += (*tcModelData).teproc_.ucvv[i__ - 1];
    /* L1040: */
    } //for (i__ = 1; i__ <= 8; ++i__){

    /*Calculation of Component Concentration*/
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.xlr[i__ - 1] = 
        (*tcModelData).teproc_.uclr[i__ - 1] / (*tcModelData).teproc_.utlr;
  	  (*tcModelData).teproc_.xls[i__ - 1] = 
        (*tcModelData).teproc_.ucls[i__ - 1] / (*tcModelData).teproc_.utls;
	  (*tcModelData).teproc_.xlc[i__ - 1] = 
        (*tcModelData).teproc_.uclc[i__ - 1] / (*tcModelData).teproc_.utlc;
	  (*tcModelData).teproc_.xvv[i__ - 1] = 
        (*tcModelData).teproc_.ucvv[i__ - 1] / (*tcModelData).teproc_.utvv;
    /* L1050: */
    } //for (i__ = 1; i__ <= 8; ++i__){

    /*Calculation of Specific Internal Energy*/
    (*tcModelData).teproc_.esr = 
                  (*tcModelData).teproc_.etr / (*tcModelData).teproc_.utlr;
    (*tcModelData).teproc_.ess = 
                  (*tcModelData).teproc_.ets / (*tcModelData).teproc_.utls;
    (*tcModelData).teproc_.esc = 
                  (*tcModelData).teproc_.etc / (*tcModelData).teproc_.utlc;
    (*tcModelData).teproc_.esv = 
                  (*tcModelData).teproc_.etv / (*tcModelData).teproc_.utvv; 
  
    /*Calculation of Temperatures*/
    tesub2_(ModelData, (*tcModelData).teproc_.xlr, 
            &(*tcModelData).teproc_.tcr, &(*tcModelData).teproc_.esr, 
            &c__0);
    (*tcModelData).teproc_.tkr = (*tcModelData).teproc_.tcr + 
                                 (float)273.15;
  
    tesub2_(ModelData, (*tcModelData).teproc_.xls, 
            &(*tcModelData).teproc_.tcs, &(*tcModelData).teproc_.ess, 
            &c__0);
    (*tcModelData).teproc_.tks = (*tcModelData).teproc_.tcs + 
                                 (float)273.15;
  
    tesub2_(ModelData, (*tcModelData).teproc_.xlc, 
            &(*tcModelData).teproc_.tcc, &(*tcModelData).teproc_.esc, 
            &c__0);
  
    tesub2_(ModelData, (*tcModelData).teproc_.xvv, 
            &(*tcModelData).teproc_.tcv, &(*tcModelData).teproc_.esv, 
            &c__2);
    (*tcModelData).teproc_.tkv = (*tcModelData).teproc_.tcv + 
                                 (float)273.15;

    /*Calculation of Densities*/
    tesub4_(ModelData, (*tcModelData).teproc_.xlr, 
            &(*tcModelData).teproc_.tcr, &(*tcModelData).teproc_.dlr);
    tesub4_(ModelData, (*tcModelData).teproc_.xls, 
            &(*tcModelData).teproc_.tcs, &(*tcModelData).teproc_.dls);
    tesub4_(ModelData, (*tcModelData).teproc_.xlc, 
            &(*tcModelData).teproc_.tcc, &(*tcModelData).teproc_.dlc);

    /*Calculation of Volume of Liquid and Vapor Phase*/
    (*tcModelData).teproc_.vlr =
                  (*tcModelData).teproc_.utlr / (*tcModelData).teproc_.dlr;
    (*tcModelData).teproc_.vls = 
                  (*tcModelData).teproc_.utls / (*tcModelData).teproc_.dls;
    (*tcModelData).teproc_.vlc = 
                  (*tcModelData).teproc_.utlc / (*tcModelData).teproc_.dlc;
    (*tcModelData).teproc_.vvr = 
                   (*tcModelData).teproc_.vtr - (*tcModelData).teproc_.vlr;
    (*tcModelData).teproc_.vvs = 
                   (*tcModelData).teproc_.vts - (*tcModelData).teproc_.vls;

    /*Calculation of Pressure*/
    (*tcModelData).teproc_.ptr = (float)0.;
    (*tcModelData).teproc_.pts = (float)0.;

    rg = (float)998.9;
    for (i__ = 1; i__ <= 3; ++i__){
	  (*tcModelData).teproc_.ppr[i__ - 1] = 
                  (*tcModelData).teproc_.ucvr[i__ - 1] * rg * 
                  (*tcModelData).teproc_.tkr / (*tcModelData).teproc_.vvr;
	  (*tcModelData).teproc_.ptr += (*tcModelData).teproc_.ppr[i__ - 1];

      (*tcModelData).teproc_.pps[i__ - 1] = 
                  (*tcModelData).teproc_.ucvs[i__ - 1] * rg * 
                  (*tcModelData).teproc_.tks / (*tcModelData).teproc_.vvs;
	  (*tcModelData).teproc_.pts += (*tcModelData).teproc_.pps[i__ - 1];
    /* L1110: */
    } //for (i__ = 1; i__ <= 3; ++i__){
    
    for (i__ = 4; i__ <= 8; ++i__){
	  vpr = exp((*tcModelData).const_.avp[i__ - 1] + 
                (*tcModelData).const_.bvp[i__ - 1] / 
                                     ((*tcModelData).teproc_.tcr + 
                                      (*tcModelData).const_.cvp[i__ - 1]));
	  (*tcModelData).teproc_.ppr[i__ - 1] = 
                                 vpr * (*tcModelData).teproc_.xlr[i__ - 1];
	  (*tcModelData).teproc_.ptr += (*tcModelData).teproc_.ppr[i__ - 1];

	  vpr = exp((*tcModelData).const_.avp[i__ - 1] + 
                (*tcModelData).const_.bvp[i__ - 1] / 
                                     ((*tcModelData).teproc_.tcs +
		                              (*tcModelData).const_.cvp[i__ - 1]));
	  (*tcModelData).teproc_.pps[i__ - 1] = 
                                 vpr * (*tcModelData).teproc_.xls[i__ - 1];
	  (*tcModelData).teproc_.pts += (*tcModelData).teproc_.pps[i__ - 1];
    /* L1120: */
    } //for (i__ = 4; i__ <= 8; ++i__){

    (*tcModelData).teproc_.ptv = (*tcModelData).teproc_.utvv * rg * 
                  (*tcModelData).teproc_.tkv / (*tcModelData).teproc_.vtv;
    
    /*Calculation of Component Concentration in Vapor Phase (Reactor and
      Separator)*/
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.xvr[i__ - 1] = 
          (*tcModelData).teproc_.ppr[i__ - 1] / (*tcModelData).teproc_.ptr;
	  (*tcModelData).teproc_.xvs[i__ - 1] = 
          (*tcModelData).teproc_.pps[i__ - 1] / (*tcModelData).teproc_.pts;
    /* L1130: */
    } //for (i__ = 1; i__ <= 8; ++i__){

    /*Calculation of Collective Holdup of Components in Vapor Phase (Reac-
      tor and Separator)*/
    (*tcModelData).teproc_.utvr = (*tcModelData).teproc_.ptr * 
              (*tcModelData).teproc_.vvr / rg / (*tcModelData).teproc_.tkr;
    (*tcModelData).teproc_.utvs = (*tcModelData).teproc_.pts * 
             (*tcModelData).teproc_.vvs / rg / (*tcModelData).teproc_.tks;
    
    /*Calculation of Single Holdup of Components in Vapor Phase (Reactor 
      and Separator)*/
    for (i__ = 4; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.ucvr[i__ - 1] = 
         (*tcModelData).teproc_.utvr * (*tcModelData).teproc_.xvr[i__ - 1];
  	  (*tcModelData).teproc_.ucvs[i__ - 1] = 
         (*tcModelData).teproc_.utvs * (*tcModelData).teproc_.xvs[i__ - 1];
    /* L1140: */
    } //for (i__ = 4; i__ <= 8; ++i__){

    
    /*Reaction kinetics*/
    (*tcModelData).teproc_.rr[0] = exp((float)31.5859536 - 
              (float)20130.85052843482 / (*tcModelData).teproc_.tkr) * r1f;
    (*tcModelData).teproc_.rr[1] = exp((float)3.00094014 - 
	          (float)10065.42526421741 / (*tcModelData).teproc_.tkr) * r2f;
    (*tcModelData).teproc_.rr[2] = exp((float)53.4060443 - 
	          (float)30196.27579265224 / (*tcModelData).teproc_.tkr);
    (*tcModelData).teproc_.rr[3] = (*tcModelData).teproc_.rr[2] * 
                                                                .767488334;
  
    if ((*tcModelData).teproc_.ppr[0] > (float)0. && 
                                (*tcModelData).teproc_.ppr[2] > (float)0.){
	  r1f = pow_dd((*tcModelData).teproc_.ppr, &c_b73);
	  r2f = pow_dd(&(*tcModelData).teproc_.ppr[2], &c_b74);

      (*tcModelData).teproc_.rr[0] = (*tcModelData).teproc_.rr[0] * 
                                 r1f * r2f * (*tcModelData).teproc_.ppr[3];
  	  (*tcModelData).teproc_.rr[1] = (*tcModelData).teproc_.rr[1] * 
                                 r1f * r2f * (*tcModelData).teproc_.ppr[4];
    }else{
	  (*tcModelData).teproc_.rr[0] = (float)0.;
	  (*tcModelData).teproc_.rr[1] = (float)0.;
    } //if ((*tcModelData).teproc_.ppr[0] > (float)0. && ... 
    (*tcModelData).teproc_.rr[2] = (*tcModelData).teproc_.rr[2] * 
             (*tcModelData).teproc_.ppr[0] * (*tcModelData).teproc_.ppr[4];
    (*tcModelData).teproc_.rr[3] = (*tcModelData).teproc_.rr[3] * 
             (*tcModelData).teproc_.ppr[0] * (*tcModelData).teproc_.ppr[3];
  
    for (i__ = 1; i__ <= 4; ++i__){
	  (*tcModelData).teproc_.rr[i__ - 1] *= (*tcModelData).teproc_.vvr;
    /* L1200: */
    } //for (i__ = 1; i__ <= 4; ++i__){
    
    /*Consumption and Creation of Components in Reactor*/
    (*tcModelData).teproc_.crxr[0] = -(*tcModelData).teproc_.rr[0] - 
               (*tcModelData).teproc_.rr[1] - (*tcModelData).teproc_.rr[2];
    (*tcModelData).teproc_.crxr[2] = -(*tcModelData).teproc_.rr[0] - 
               (*tcModelData).teproc_.rr[1];
    (*tcModelData).teproc_.crxr[3] = -(*tcModelData).teproc_.rr[0] - 
               (*tcModelData).teproc_.rr[3] * 1.5;
    (*tcModelData).teproc_.crxr[4] = -(*tcModelData).teproc_.rr[1] - 
               (*tcModelData).teproc_.rr[2];
    (*tcModelData).teproc_.crxr[5] = (*tcModelData).teproc_.rr[2] + 
               (*tcModelData).teproc_.rr[3];
    (*tcModelData).teproc_.crxr[6] = (*tcModelData).teproc_.rr[0];
    (*tcModelData).teproc_.crxr[7] = (*tcModelData).teproc_.rr[1];
    (*tcModelData).teproc_.rh = 
            (*tcModelData).teproc_.rr[0] * (*tcModelData).teproc_.htr[0] + 
            (*tcModelData).teproc_.rr[1] * (*tcModelData).teproc_.htr[1];


    (*tcModelData).teproc_.xmws[0] = (float)0.;
    (*tcModelData).teproc_.xmws[1] = (float)0.;
    (*tcModelData).teproc_.xmws[5] = (float)0.;
    (*tcModelData).teproc_.xmws[7] = (float)0.;
    (*tcModelData).teproc_.xmws[8] = (float)0.;
    (*tcModelData).teproc_.xmws[9] = (float)0.;
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.xst[i__ + 39] = 
                                       (*tcModelData).teproc_.xvv[i__ - 1];
	  (*tcModelData).teproc_.xst[i__ + 55] = 
                                       (*tcModelData).teproc_.xvr[i__ - 1];
	  (*tcModelData).teproc_.xst[i__ + 63] = 
                                       (*tcModelData).teproc_.xvs[i__ - 1];
	  (*tcModelData).teproc_.xst[i__ + 71] = 
                                       (*tcModelData).teproc_.xvs[i__ - 1];
	  (*tcModelData).teproc_.xst[i__ + 79] =
                                       (*tcModelData).teproc_.xls[i__ - 1];
	  (*tcModelData).teproc_.xst[i__ + 95] =
                                       (*tcModelData).teproc_.xlc[i__ - 1];
	
	  (*tcModelData).teproc_.xmws[0] += 
                                    (*tcModelData).teproc_.xst[i__ - 1] * 
                                    (*tcModelData).const_.xmw[i__ - 1];
	  (*tcModelData).teproc_.xmws[1] += 
                                    (*tcModelData).teproc_.xst[i__ + 7] * 
                                    (*tcModelData).const_.xmw[i__ - 1];
	  (*tcModelData).teproc_.xmws[5] += 
                                    (*tcModelData).teproc_.xst[i__ + 39] * 
                                    (*tcModelData).const_.xmw[i__ - 1];
	  (*tcModelData).teproc_.xmws[7] += 
                                    (*tcModelData).teproc_.xst[i__ + 55] * 
                                    (*tcModelData).const_.xmw[i__ - 1];
	  (*tcModelData).teproc_.xmws[8] += 
                                    (*tcModelData).teproc_.xst[i__ + 63] * 
                                    (*tcModelData).const_.xmw[i__ - 1];
	  (*tcModelData).teproc_.xmws[9] += 
                                    (*tcModelData).teproc_.xst[i__ + 71] * 
                                    (*tcModelData).const_.xmw[i__ - 1];
    /* L2010: */
    } //for (i__ = 1; i__ <= 8; ++i__){

    (*tcModelData).teproc_.tst[5] = (*tcModelData).teproc_.tcv;
    (*tcModelData).teproc_.tst[7] = (*tcModelData).teproc_.tcr;
    (*tcModelData).teproc_.tst[8] = (*tcModelData).teproc_.tcs;
    (*tcModelData).teproc_.tst[9] = (*tcModelData).teproc_.tcs;
    (*tcModelData).teproc_.tst[10] = (*tcModelData).teproc_.tcs;
    (*tcModelData).teproc_.tst[12] = (*tcModelData).teproc_.tcc;
    tesub1_(ModelData, (*tcModelData).teproc_.xst, 
            (*tcModelData).teproc_.tst, (*tcModelData).teproc_.hst, &c__1);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[8], 
            &(*tcModelData).teproc_.tst[1], &(*tcModelData).teproc_.hst[1], 
            &c__1);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[16], 
            &(*tcModelData).teproc_.tst[2], &(*tcModelData).teproc_.hst[2], 
            &c__1);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[24], 
            &(*tcModelData).teproc_.tst[3], &(*tcModelData).teproc_.hst[3],
            &c__1);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[40], 
            &(*tcModelData).teproc_.tst[5], &(*tcModelData).teproc_.hst[5],
            &c__1);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[56], 
            &(*tcModelData).teproc_.tst[7], &(*tcModelData).teproc_.hst[7], 
           &c__1);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[64], 
            &(*tcModelData).teproc_.tst[8], &(*tcModelData).teproc_.hst[8], 
            &c__1);
    (*tcModelData).teproc_.hst[9] = (*tcModelData).teproc_.hst[8];
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[80], 
            &(*tcModelData).teproc_.tst[10], &(*tcModelData).teproc_.hst[10], 
            &c__0);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[96], 
            &(*tcModelData).teproc_.tst[12], &(*tcModelData).teproc_.hst[12], 
            &c__0);
    (*tcModelData).teproc_.ftm[0] = vpos[0] * 
                            (*tcModelData).teproc_.vrng[0] / (float)100.;
    (*tcModelData).teproc_.ftm[1] = vpos[1] * 
                            (*tcModelData).teproc_.vrng[1] / (float)100.;
    (*tcModelData).teproc_.ftm[2] = vpos[2] *
                            (1. - (*tcModelData).dvec_.idv[5]) * 
                            (*tcModelData).teproc_.vrng[2] / (float)100.;
    (*tcModelData).teproc_.ftm[3] = vpos[3] * 
                            (1. - (*tcModelData).dvec_.idv[6] * .2) * 
                            (*tcModelData).teproc_.vrng[3] / (float)100. + 
                            1e-10;
    (*tcModelData).teproc_.ftm[10] = vpos[6] * 
                            (*tcModelData).teproc_.vrng[6] / (float)100.;
    (*tcModelData).teproc_.ftm[12] = vpos[7] * 
                            (*tcModelData).teproc_.vrng[7] / (float)100.;
  
    uac = vpos[8] * (*tcModelData).teproc_.vrng[8] * 
                    (tesub8_(ModelData, &c__9, time) + 1.) / (float)100.;
    (*tcModelData).teproc_.fwr = vpos[9] * 
                            (*tcModelData).teproc_.vrng[9] / (float)100.;
    (*tcModelData).teproc_.fws = vpos[10] *
                            (*tcModelData).teproc_.vrng[10] / (float)100.;
    (*tcModelData).teproc_.agsp = (vpos[11] + (float)150.) / (float)100.;
  
    dlp = (*tcModelData).teproc_.ptv - (*tcModelData).teproc_.ptr;
    if (dlp < (float)0.){
	  dlp = (float)0.;
    } //if (dlp < (float)0.){
    flms = sqrt(dlp) * 1937.6;
    (*tcModelData).teproc_.ftm[5] = flms / (*tcModelData).teproc_.xmws[5];

    dlp = (*tcModelData).teproc_.ptr - (*tcModelData).teproc_.pts;
    if (dlp < (float)0.){
	  dlp = (float)0.;
    } //if (dlp < (float)0.){   
    flms = sqrt(dlp) * 4574.21 * 
                            (1. - tesub8_(ModelData, &c__12, time) * .25);
    (*tcModelData).teproc_.ftm[7] = flms / (*tcModelData).teproc_.xmws[7];
  
    dlp = (*tcModelData).teproc_.pts - (float)760.;
    if (dlp < (float)0.){
	  dlp = (float)0.;
    } //if (dlp < (float)0.){
  
    flms = vpos[5] * .151169 * sqrt(dlp);
    (*tcModelData).teproc_.ftm[9] = flms / (*tcModelData).teproc_.xmws[9];
    pr = (*tcModelData).teproc_.ptv / (*tcModelData).teproc_.pts;
    if (pr < (float)1.){
  	  pr = (float)1.;
    } //if (pr < (float)1.){
    if (pr > (*tcModelData).teproc_.cpprmx){
	  pr = (*tcModelData).teproc_.cpprmx;
    } //if (pr > (*tcModelData).teproc_.cpprmx){
    flcoef = (*tcModelData).teproc_.cpflmx / 1.197;

    /* Computing 3rd power */
    d__1 = pr;
    flms = (*tcModelData).teproc_.cpflmx + 
         flcoef * ((float)1. - d__1 * (d__1 * d__1));
    (*tcModelData).teproc_.cpdh = 
         flms * ((*tcModelData).teproc_.tcs + 273.15) * 1.8e-6 * 1.9872 * 
	     ((*tcModelData).teproc_.ptv - (*tcModelData).teproc_.pts) / 
         ((*tcModelData).teproc_.xmws[8] * (*tcModelData).teproc_.pts);
    dlp = (*tcModelData).teproc_.ptv - (*tcModelData).teproc_.pts;
    if (dlp < (float)0.){
	  dlp = (float)0.;
    } //if (dlp < (float)0.){
    flms -= vpos[4] * 53.349 * sqrt(dlp);
    if (flms < .001){
	  flms = .001;
    } //if (flms < .001){
    (*tcModelData).teproc_.ftm[8] = flms / (*tcModelData).teproc_.xmws[8];
    (*tcModelData).teproc_.hst[8] += 
               (*tcModelData).teproc_.cpdh / (*tcModelData).teproc_.ftm[8];
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.fcm[i__ - 1] = 
                                    (*tcModelData).teproc_.xst[i__ - 1] * 
                                    (*tcModelData).teproc_.ftm[0];
  	  (*tcModelData).teproc_.fcm[i__ + 7] = 
                                    (*tcModelData).teproc_.xst[i__ + 7] * 
                                    (*tcModelData).teproc_.ftm[1];
   	  (*tcModelData).teproc_.fcm[i__ + 15] = 
                                    (*tcModelData).teproc_.xst[i__ + 15] * 
                                    (*tcModelData).teproc_.ftm[2];
	  (*tcModelData).teproc_.fcm[i__ + 23] = 
                                    (*tcModelData).teproc_.xst[i__ + 23] * 
                                    (*tcModelData).teproc_.ftm[3];
	  (*tcModelData).teproc_.fcm[i__ + 39] = 
                                    (*tcModelData).teproc_.xst[i__ + 39] *
                                    (*tcModelData).teproc_.ftm[5];
	  (*tcModelData).teproc_.fcm[i__ + 55] = 
                                    (*tcModelData).teproc_.xst[i__ + 55] * 
                                    (*tcModelData).teproc_.ftm[7];
	  (*tcModelData).teproc_.fcm[i__ + 63] = 
                                    (*tcModelData).teproc_.xst[i__ + 63] * 
                                    (*tcModelData).teproc_.ftm[8];
	  (*tcModelData).teproc_.fcm[i__ + 71] = 
                                    (*tcModelData).teproc_.xst[i__ + 71] * 
                                    (*tcModelData).teproc_.ftm[9];
	  (*tcModelData).teproc_.fcm[i__ + 79] = 
                                    (*tcModelData).teproc_.xst[i__ + 79] * 
                                    (*tcModelData).teproc_.ftm[10];
	  (*tcModelData).teproc_.fcm[i__ + 95] = 
                                    (*tcModelData).teproc_.xst[i__ + 95] * 
                                    (*tcModelData).teproc_.ftm[12];
    /* L5020: */
    } //for (i__ = 1; i__ <= 8; ++i__){
  
    if ((*tcModelData).teproc_.ftm[10] > (float).1){
	  if ((*tcModelData).teproc_.tcc > (float)170.){
	    tmpfac = (*tcModelData).teproc_.tcc - (float)120.262;
	  }else if ((*tcModelData).teproc_.tcc < (float)5.292){
	    tmpfac = (float).1;
	  }else{
	    tmpfac = (float)363.744 / ((float)177. - 
                 (*tcModelData).teproc_.tcc) - (float)2.22579488;
      } //if ((*tcModelData).teproc_.tcc > (float)170.){
    
	  vovrl = (*tcModelData).teproc_.ftm[3] / 
              (*tcModelData).teproc_.ftm[10] * tmpfac;
	  (*tcModelData).teproc_.sfr[3] = vovrl * (float) 8.501  / 
                                     (vovrl * (float)8.501 + (float)1.);
	  (*tcModelData).teproc_.sfr[4] = vovrl * (float)11.402  /  
                                     (vovrl * (float)11.402 + (float)1.);
	  (*tcModelData).teproc_.sfr[5] = vovrl * (float)11.795  / 
                                     (vovrl * (float)11.795 + (float)1.);
	  (*tcModelData).teproc_.sfr[6] = vovrl * (float)  .048  / 
                                     (vovrl * (float).048 + (float)1.);
	  (*tcModelData).teproc_.sfr[7] = vovrl * (float)  .0242 / 
                                     (vovrl * (float).0242 + (float)1.);
    }else{
	  (*tcModelData).teproc_.sfr[3] = (float).9999;
	  (*tcModelData).teproc_.sfr[4] = (float).999;
	  (*tcModelData).teproc_.sfr[5] = (float).999;
	  (*tcModelData).teproc_.sfr[6] = (float).99;
	  (*tcModelData).teproc_.sfr[7] = (float).98;
    } //if ((*tcModelData).teproc_.ftm[10] > (float).1){
  
    for (i__ = 1; i__ <= 8; ++i__){
	  fin[i__ - 1] = (float)0.;
	  fin[i__ - 1] += (*tcModelData).teproc_.fcm[i__ + 23];
	  fin[i__ - 1] += (*tcModelData).teproc_.fcm[i__ + 79];
    /* L6010: */
    } //for (i__ = 1; i__ <= 8; ++i__){
    (*tcModelData).teproc_.ftm[4] = (float)0.;
    (*tcModelData).teproc_.ftm[11] = (float)0.;
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.fcm[i__ + 31] = 
                       (*tcModelData).teproc_.sfr[i__ - 1] * fin[i__ - 1];
	  (*tcModelData).teproc_.fcm[i__ + 87] = 
                       fin[i__ - 1] - (*tcModelData).teproc_.fcm[i__ + 31];
    
	  (*tcModelData).teproc_.ftm[4]  += 
                                      (*tcModelData).teproc_.fcm[i__ + 31];
  	  (*tcModelData).teproc_.ftm[11] += 
                                      (*tcModelData).teproc_.fcm[i__ + 87];
    /* L6020: */
    } //for (i__ = 1; i__ <= 8; ++i__){
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.xst[i__ + 31] =
                                   (*tcModelData).teproc_.fcm[i__ + 31] / 
                                   (*tcModelData).teproc_.ftm[4];
	  (*tcModelData).teproc_.xst[i__ + 87] = 
                                   (*tcModelData).teproc_.fcm[i__ + 87] / 
                                   (*tcModelData).teproc_.ftm[11];
    /* L6030: */
    } //for (i__ = 1; i__ <= 8; ++i__){
    (*tcModelData).teproc_.tst[4] = (*tcModelData).teproc_.tcc;
    (*tcModelData).teproc_.tst[11] = (*tcModelData).teproc_.tcc;
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[32], 
            &(*tcModelData).teproc_.tst[4], &(*tcModelData).teproc_.hst[4], 
            &c__1);
    tesub1_(ModelData, &(*tcModelData).teproc_.xst[88], 
            &(*tcModelData).teproc_.tst[11],  
            &(*tcModelData).teproc_.hst[11],&c__0);
    (*tcModelData).teproc_.ftm[6] = (*tcModelData).teproc_.ftm[5];
    (*tcModelData).teproc_.hst[6] = (*tcModelData).teproc_.hst[5];
    (*tcModelData).teproc_.tst[6] = (*tcModelData).teproc_.tst[5];
    for (i__ = 1; i__ <= 8; ++i__){
	  (*tcModelData).teproc_.xst[i__ + 47] = 
                                      (*tcModelData).teproc_.xst[i__ + 39];
  	  (*tcModelData).teproc_.fcm[i__ + 47] =
                                      (*tcModelData).teproc_.fcm[i__ + 39];
    /* L6130: */
    } //for (i__ = 1; i__ <= 8; ++i__){
    
    /*Calculation of Heat Transfer in Reactor*/
    if ((*tcModelData).teproc_.vlr / (float)7.8 > (float)50.){
	  uarlev = (float)1.;
    }else if ((*tcModelData).teproc_.vlr / (float)7.8 < (float)10.){
	  uarlev = (float)0.;
    }else{
	  uarlev = (*tcModelData).teproc_.vlr * (float).025 / (float)7.8 - 
               (float).25;
    } //if ((*tcModelData).teproc_.vlr / (float)7.8 > (float)50.){

    /* Computing 2nd power */
    d__1 = (*tcModelData).teproc_.agsp;
    (*tcModelData).teproc_.uar = uarlev * 
          (d__1 * d__1 * (float)-.5 + 
          (*tcModelData).teproc_.agsp * (float)2.75 - (float)2.5) * .85549;
    (*tcModelData).teproc_.qur = (*tcModelData).teproc_.uar * 
          ((*tcModelData).teproc_.twr - (*tcModelData).teproc_.tcr) * 
          (1. - tesub8_(ModelData, &c__10, time) * .35);

    /*Calculation of Heat Transfer in Condenser (Separator)*/
    /* Computing 4th power */
    d__1  = (*tcModelData).teproc_.ftm[7] / (float)3528.73;
    d__1 *= d__1;
    uas   = ((float)1. - (float)1. / (d__1 * d__1 + (float)1.)) * 
	                                                        (float).404655;
    (*tcModelData).teproc_.qus = uas * 
            ((*tcModelData).teproc_.tws - (*tcModelData).teproc_.tst[7]) * 
	        (1. - tesub8_(ModelData, &c__11, time) * .25);
    
    /*Calculation of Heat Transfer in Stripper*/
    (*tcModelData).teproc_.quc = 0.;
    if ((*tcModelData).teproc_.tcc < (float)100.){
	  (*tcModelData).teproc_.quc = uac * 
                                 ((float)100. - (*tcModelData).teproc_.tcc);
    } //if ((*tcModelData).teproc_.tcc < (float)100.){
    
    (*tcModelData).tlastcomp = *time;
  }else{
    for (i__ = 1; i__ <= 12; ++i__){
	  vpos[i__ - 1] = yy[i__ + 38];
    } //for (i__ = 1; i__ <= 12; ++i__){
  } //if((((*tcModelData).tlastcomp < *time) || (Callflag == 1)) && ...
  
  /*Setting of Measured Values*/
  if((Callflag < 2) && (((*tcModelData).MSFlag & 0x8000) == 0)){
    (*tcModelData).pv_.xmeas[0] = (*tcModelData).teproc_.ftm[2] * 
                              (float).359 / (float)35.3145; 
    (*tcModelData).pv_.xmeas[1] = (*tcModelData).teproc_.ftm[0] * 
                              (*tcModelData).teproc_.xmws[0] * (float).454;
    (*tcModelData).pv_.xmeas[2] = (*tcModelData).teproc_.ftm[1] * 
                              (*tcModelData).teproc_.xmws[1] * (float).454;
    (*tcModelData).pv_.xmeas[3] = (*tcModelData).teproc_.ftm[3] * 
                              (float).359 / (float)35.3145;
    (*tcModelData).pv_.xmeas[4] = (*tcModelData).teproc_.ftm[8] * 
                              (float).359 / (float)35.3145;
    (*tcModelData).pv_.xmeas[5] = (*tcModelData).teproc_.ftm[5] * 
                              (float).359 / (float)35.3145;
    (*tcModelData).pv_.xmeas[6] = ((*tcModelData).teproc_.ptr - 
               (float)760.) / (float)760. * (float)101.325;
    (*tcModelData).pv_.xmeas[7] = ((*tcModelData).teproc_.vlr - 
               (float)84.6) / (float)666.7 * (float)100.;
    (*tcModelData).pv_.xmeas[8] = (*tcModelData).teproc_.tcr;
    (*tcModelData).pv_.xmeas[9] = (*tcModelData).teproc_.ftm[9] * 
                              (float).359 / (float)35.3145;
    (*tcModelData).pv_.xmeas[10] = (*tcModelData).teproc_.tcs;
    (*tcModelData).pv_.xmeas[11] = ((*tcModelData).teproc_.vls - 
               (float)27.5) / (float)290. * (float)100.;
    (*tcModelData).pv_.xmeas[12] = ((*tcModelData).teproc_.pts - 
               (float)760.) / (float)760. * (float)101.325;
    (*tcModelData).pv_.xmeas[13] = (*tcModelData).teproc_.ftm[10] / 
                              (*tcModelData).teproc_.dls / (float)35.3145;
    (*tcModelData).pv_.xmeas[14] = ((*tcModelData).teproc_.vlc - 
               (float)78.25) / (*tcModelData).teproc_.vtc * (float)100.;
    (*tcModelData).pv_.xmeas[15] = ((*tcModelData).teproc_.ptv - 
               (float)760.) / (float)760. * (float)101.325;
    (*tcModelData).pv_.xmeas[16] = (*tcModelData).teproc_.ftm[12] / 
                              (*tcModelData).teproc_.dlc / (float)35.3145;
    (*tcModelData).pv_.xmeas[17] = (*tcModelData).teproc_.tcc;
    (*tcModelData).pv_.xmeas[18] = (*tcModelData).teproc_.quc * 
                              1040. * (float).454; 
    (*tcModelData).pv_.xmeas[19] = (*tcModelData).teproc_.cpdh * 392.7;
    (*tcModelData).pv_.xmeas[19] = (*tcModelData).teproc_.cpdh * 293.07;
    (*tcModelData).pv_.xmeas[20] = (*tcModelData).teproc_.twr;
    (*tcModelData).pv_.xmeas[21] = (*tcModelData).teproc_.tws;
    
    /*Übergabe der zusätzlichen Ausgänge*/
    if(((*tcModelData).MSFlag & 0x1) == 1){
      (*tcModelData).pv_.xmeasadd[0] = (*tcModelData).teproc_.tst[2];
      (*tcModelData).pv_.xmeasadd[1] = (*tcModelData).teproc_.tst[0];
      (*tcModelData).pv_.xmeasadd[2] = (*tcModelData).teproc_.tst[1];
      (*tcModelData).pv_.xmeasadd[3] = (*tcModelData).teproc_.tst[3];
      (*tcModelData).pv_.xmeasadd[4] = (*tcModelData).teproc_.tcwr;
      (*tcModelData).pv_.xmeasadd[5] = (*tcModelData).teproc_.fwr * 
                 (float)0.003785411784 * (float)60.;
      (*tcModelData).pv_.xmeasadd[6] = (*tcModelData).teproc_.tcws;
      (*tcModelData).pv_.xmeasadd[7] = (*tcModelData).teproc_.fws * 
                 (float)0.003785411784 * (float)60.;
    } //if((*ModelData).MSFlag & 0x1) == 1){

    /*Checking of Shut-Down-Constraints*/
    *isd = (float)0.;
    if ((*tcModelData).pv_.xmeas[6] > (float)3e3){
      *isd = (float)1.;
      sprintf((*tcModelData).msg,
              "High Reactor Pressure!!  Shutting down.");
    } //if ((*tcModelData).pv_.xmeas[6] > (float)3e3){
  
    if ((*tcModelData).teproc_.vlr / (float)35.3145 > (float)24.){
      *isd = (float)2.;
      sprintf((*tcModelData).msg,
              "High Reactor Liquid Level!!  Shutting down.");
    } //if ((*tcModelData).teproc_.vlr / (float)35.3145 > (float)24.){
  
    if ((*tcModelData).teproc_.vlr / (float)35.3145 < (float)2.){
      *isd = (float)3.;
	  sprintf((*tcModelData).msg,
              "Low Reactor Liquid Level!!  Shutting down.");
    } //if ((*tcModelData).teproc_.vlr / (float)35.3145 < (float)2.){
  
    if ((*tcModelData).pv_.xmeas[8] > (float)175.){
     *isd = (float)4.;
      sprintf((*tcModelData).msg,
              "High Reactor Temperature!!  Shutting down.");
    } //if ((*tcModelData).pv_.xmeas[8] > (float)175.){
  
    if ((*tcModelData).teproc_.vls / (float)35.3145 > (float)12.){
      *isd = (float)5.;
      sprintf((*tcModelData).msg,
              "High Separator Liquid Level!!  Shutting down.");
    } //if ((*tcModelData).teproc_.vls / (float)35.3145 > (float)12.){
  
    if ((*tcModelData).teproc_.vls / (float)35.3145 < (float)1.){
      *isd = (float)6.;
      sprintf((*tcModelData).msg,
              "Low Separator Liquid Level!!  Shutting down.");
    } //if ((*tcModelData).teproc_.vls / (float)35.3145 < (float)1.){
  
    if ((*tcModelData).teproc_.vlc / (float)35.3145 > (float)8.){
	  *isd = (float)7.;
      sprintf((*tcModelData).msg,
              "High Stripper Liquid Level!!  Shutting down.");
    } //if ((*tcModelData).teproc_.vlc / (float)35.3145 > (float)8.){
  
    if ((*tcModelData).teproc_.vlc / (float)35.3145 < (float)1.){
      *isd = (float)8.;
      sprintf((*tcModelData).msg,
              "Low Stripper Liquid Level!!  Shutting down.");
    } //if ((*tcModelData).teproc_.vlc / (float)35.3145 < (float)1.){
    
    /*Adding of Measurement Noise*/
    if (*time > (float)0. && *isd == (float)0.){
      for (i__ = 1; i__ <= 22; ++i__){
	    tesub6_(ModelData, &(*tcModelData).teproc_.xns[i__ - 1], &xmns);
	    (*tcModelData).pv_.xmeas[i__ - 1] += xmns;
      /* L6500: */
      } //for (i__ = 1; i__ <= 22; ++i__){

      if(((*tcModelData).MSFlag & 0x1) == 1){
        for (i__ = 1; i__ <= 8; ++i__){
	      tesub6_(ModelData, &(*tcModelData).teproc_.xnsadd[i__ - 1], 
                  &xmns);
	      (*tcModelData).pv_.xmeasadd[i__ - 1] += xmns;
        /* L6500: */
        } //for (i__ = 1; i__ <= 22; ++i__){      
      }//if(((*tcModelData).MSFlag & 0x1) == 1){
    } //if (*time > (float)0. && *isd == 0){

    /*Analyzer Outputs*/
    xcmp[22] = (*tcModelData).teproc_.xst[48] * (float)100.;
    xcmp[23] = (*tcModelData).teproc_.xst[49] * (float)100.;
    xcmp[24] = (*tcModelData).teproc_.xst[50] * (float)100.;
    xcmp[25] = (*tcModelData).teproc_.xst[51] * (float)100.;
    xcmp[26] = (*tcModelData).teproc_.xst[52] * (float)100.;
    xcmp[27] = (*tcModelData).teproc_.xst[53] * (float)100.;
    xcmp[28] = (*tcModelData).teproc_.xst[72] * (float)100.;
    xcmp[29] = (*tcModelData).teproc_.xst[73] * (float)100.;
    xcmp[30] = (*tcModelData).teproc_.xst[74] * (float)100.;
    xcmp[31] = (*tcModelData).teproc_.xst[75] * (float)100.;
    xcmp[32] = (*tcModelData).teproc_.xst[76] * (float)100.;
    xcmp[33] = (*tcModelData).teproc_.xst[77] * (float)100.;
    xcmp[34] = (*tcModelData).teproc_.xst[78] * (float)100.;
    xcmp[35] = (*tcModelData).teproc_.xst[79] * (float)100.;
    xcmp[36] = (*tcModelData).teproc_.xst[99] * (float)100.;
    xcmp[37] = (*tcModelData).teproc_.xst[100] * (float)100.;
    xcmp[38] = (*tcModelData).teproc_.xst[101] * (float)100.;
    xcmp[39] = (*tcModelData).teproc_.xst[102] * (float)100.;
    xcmp[40] = (*tcModelData).teproc_.xst[103] * (float)100.;
  
    if(((*tcModelData).MSFlag & 0x1) == 1){
      xcmpadd[0]  = (*tcModelData).teproc_.xst[16] * (float)100.;
      xcmpadd[1]  = (*tcModelData).teproc_.xst[17] * (float)100.;
      xcmpadd[2]  = (*tcModelData).teproc_.xst[18] * (float)100.;
      xcmpadd[3]  = (*tcModelData).teproc_.xst[19] * (float)100.;
      xcmpadd[4]  = (*tcModelData).teproc_.xst[20] * (float)100.;
      xcmpadd[5]  = (*tcModelData).teproc_.xst[21] * (float)100.;

      xcmpadd[6]  = (*tcModelData).teproc_.xst[0] * (float)100.;
      xcmpadd[7]  = (*tcModelData).teproc_.xst[1] * (float)100.;
      xcmpadd[8]  = (*tcModelData).teproc_.xst[2] * (float)100.;
      xcmpadd[9]  = (*tcModelData).teproc_.xst[3] * (float)100.;
      xcmpadd[10] = (*tcModelData).teproc_.xst[4] * (float)100.;
      xcmpadd[11] = (*tcModelData).teproc_.xst[5] * (float)100.;

      xcmpadd[12] = (*tcModelData).teproc_.xst[8] * (float)100.;
      xcmpadd[13] = (*tcModelData).teproc_.xst[9] * (float)100.;
      xcmpadd[14] = (*tcModelData).teproc_.xst[10] * (float)100.;
      xcmpadd[15] = (*tcModelData).teproc_.xst[11] * (float)100.;
      xcmpadd[16] = (*tcModelData).teproc_.xst[12] * (float)100.;
      xcmpadd[17] = (*tcModelData).teproc_.xst[13] * (float)100.;
      
      xcmpadd[18] = (*tcModelData).teproc_.xst[24] * (float)100.;
      xcmpadd[19] = (*tcModelData).teproc_.xst[25] * (float)100.;
      xcmpadd[20] = (*tcModelData).teproc_.xst[26] * (float)100.;
      xcmpadd[21] = (*tcModelData).teproc_.xst[27] * (float)100.;
      xcmpadd[22] = (*tcModelData).teproc_.xst[28] * (float)100.;
      xcmpadd[23] = (*tcModelData).teproc_.xst[29] * (float)100.;
    } //if(((*tcModelData).MSFlag & 0x1) == 1){
    
    if (*time == 0.){
      for (i__ = 23; i__ <= 41; ++i__){
        (*tcModelData).teproc_.xdel[i__ - 1] = xcmp[i__ - 1];
	    (*tcModelData).pv_.xmeas[i__ - 1] = xcmp[i__ - 1];
      /* L7010: */
	  } //for (i__ = 23; i__ <= 41; ++i__){
      
      if(((*tcModelData).MSFlag & 0x1) == 1){
        for (i__ = 1; i__ <= 24; ++i__){
          (*tcModelData).teproc_.xdeladd[i__ - 1] = xcmpadd[i__ - 1];
	      (*tcModelData).pv_.xmeasadd[i__ + 7] = xcmpadd[i__ - 1];
	    } //for (i__ = 23; i__ <= 41; ++i__){
      } //if((*ModelData).MSFlag & 0x1) == 1){ 
      
      (*tcModelData).teproc_.tgas = (float).1;
	  (*tcModelData).teproc_.tprod = (float).25;
    } //if (*time == 0.){
    
    if (*time >= (*tcModelData).teproc_.tgas){
      for (i__ = 23; i__ <= 36; ++i__){
        (*tcModelData).pv_.xmeas[i__ - 1] = 
                                      (*tcModelData).teproc_.xdel[i__ - 1];
	    tesub6_(ModelData, &(*tcModelData).teproc_.xns[i__ - 1], &xmns);
	    (*tcModelData).pv_.xmeas[i__ - 1] += xmns;
        
	    (*tcModelData).teproc_.xdel[i__ - 1] = xcmp[i__ - 1];
      /* L7020: */
      } //for (i__ = 23; i__ <= 36; ++i__){
      
      if(((*tcModelData).MSFlag & 0x1) == 1){      
        for (i__ = 1; i__ <= 24; ++i__){
          (*tcModelData).pv_.xmeasadd[i__ + 7] = 
                                   (*tcModelData).teproc_.xdeladd[i__ - 1];
  	      tesub6_(ModelData, &(*tcModelData).teproc_.xnsadd[i__ - 1], 
                  &xmns);
	      (*tcModelData).pv_.xmeasadd[i__ + 7] += xmns;
        
	      (*tcModelData).teproc_.xdeladd[i__ - 1] = xcmpadd[i__ - 1];
        } //for (i__ = 23; i__ <= 36; ++i__){
      }//if(((*tcModelData).MSFlag & 0x1) == 1){
      (*tcModelData).teproc_.tgas += (float).1;
    } //if (*time >= (*tcModelData).teproc_.tgas){
    
    if (*time >= (*tcModelData).teproc_.tprod){
      for (i__ = 37; i__ <= 41; ++i__){
	    (*tcModelData).pv_.xmeas[i__ - 1] = 
                                      (*tcModelData).teproc_.xdel[i__ - 1];
	    tesub6_(ModelData, &(*tcModelData).teproc_.xns[i__ - 1], &xmns);
	    (*tcModelData).pv_.xmeas[i__ - 1] += xmns;
        
	    (*tcModelData).teproc_.xdel[i__ - 1] = xcmp[i__ - 1];
      /* L7030: */
	  } //for (i__ = 37; i__ <= 41; ++i__){
	  (*tcModelData).teproc_.tprod += (float).25;
    } //if (*time >= (*tcModelData).teproc_.tprod){
    
    /*Monitoring Outputs*/
    if(((*tcModelData).MSFlag & 0x4) > 1){
      (*tcModelData).pv_.xmeasmonitor[0]  = 
                             (*tcModelData).teproc_.crxr[0] * (float).454;
      (*tcModelData).pv_.xmeasmonitor[1]  = 
                             (*tcModelData).teproc_.crxr[2] * (float).454;
      (*tcModelData).pv_.xmeasmonitor[2]  = 
                             (*tcModelData).teproc_.crxr[3] * (float).454;
      (*tcModelData).pv_.xmeasmonitor[3]  = 
                             (*tcModelData).teproc_.crxr[4] * (float).454;
      (*tcModelData).pv_.xmeasmonitor[4]  = 
                             (*tcModelData).teproc_.crxr[5] * (float).454;
      (*tcModelData).pv_.xmeasmonitor[5]  = 
                             (*tcModelData).teproc_.crxr[6] * (float).454;
      (*tcModelData).pv_.xmeasmonitor[6]  = 
                             (*tcModelData).teproc_.crxr[7] * (float).454;
      (*tcModelData).pv_.xmeasmonitor[7]  = (*tcModelData).teproc_.ppr[0] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[8]  = (*tcModelData).teproc_.ppr[1] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[9]  = (*tcModelData).teproc_.ppr[2] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[10] = (*tcModelData).teproc_.ppr[3] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[11] = (*tcModelData).teproc_.ppr[4] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[12] = (*tcModelData).teproc_.ppr[5] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[13] = (*tcModelData).teproc_.ppr[6] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[14] = (*tcModelData).teproc_.ppr[7] / 
                                           (float)760. * (float)101.325;
      (*tcModelData).pv_.xmeasmonitor[15] = (*tcModelData).teproc_.xst[48]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[16] = (*tcModelData).teproc_.xst[49]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[17] = (*tcModelData).teproc_.xst[50]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[18] = (*tcModelData).teproc_.xst[51]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[19] = (*tcModelData).teproc_.xst[52]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[20] = (*tcModelData).teproc_.xst[53]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[21] = (*tcModelData).teproc_.xst[72]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[22] = (*tcModelData).teproc_.xst[73]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[23] = (*tcModelData).teproc_.xst[74]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[24] = (*tcModelData).teproc_.xst[75]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[25] = (*tcModelData).teproc_.xst[76]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[26] = (*tcModelData).teproc_.xst[77]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[27] = (*tcModelData).teproc_.xst[78]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[28] = (*tcModelData).teproc_.xst[79]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[29] = (*tcModelData).teproc_.xst[99]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[30] =(*tcModelData).teproc_.xst[100]*
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[31] =(*tcModelData).teproc_.xst[101]*
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[32] =(*tcModelData).teproc_.xst[102]*
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[33] =(*tcModelData).teproc_.xst[103]*
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[34] = (*tcModelData).teproc_.xst[16]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[35] = (*tcModelData).teproc_.xst[17]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[36] = (*tcModelData).teproc_.xst[18]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[37] = (*tcModelData).teproc_.xst[19]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[38] = (*tcModelData).teproc_.xst[20]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[39] = (*tcModelData).teproc_.xst[21]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[40] = (*tcModelData).teproc_.xst[0] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[41] = (*tcModelData).teproc_.xst[1] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[42] = (*tcModelData).teproc_.xst[2] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[43] = (*tcModelData).teproc_.xst[3] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[44] = (*tcModelData).teproc_.xst[4] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[45] = (*tcModelData).teproc_.xst[5] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[46] = (*tcModelData).teproc_.xst[8] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[47] = (*tcModelData).teproc_.xst[9] * 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[48] = (*tcModelData).teproc_.xst[10]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[49] = (*tcModelData).teproc_.xst[11]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[50] = (*tcModelData).teproc_.xst[12]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[51] = (*tcModelData).teproc_.xst[13]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[52] = (*tcModelData).teproc_.xst[24]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[53] = (*tcModelData).teproc_.xst[25]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[54] = (*tcModelData).teproc_.xst[26]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[55] = (*tcModelData).teproc_.xst[27]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[56] = (*tcModelData).teproc_.xst[28]* 
                                           (float)100.;
      (*tcModelData).pv_.xmeasmonitor[57] = (*tcModelData).teproc_.xst[29]* 
                                           (float)100.;
      
      prate = (float)211.3 * yy[46] / (float)46.534 + (float)1.0e-6;
      (*tcModelData).pv_.xmeasmonitor[58] = 
          (float)100 * ((float).0536 * (*tcModelData).pv_.xmeas[19] + 
                        (float).0318 * (*tcModelData).pv_.xmeas[18] +
                        (*tcModelData).pv_.xmeas[9] * (float).44791 * 
                           ((float)2.209 * (*tcModelData).pv_.xmeas[28] +
                            (float)6.177 * (*tcModelData).pv_.xmeas[30] +
                            (float)22.06 * (*tcModelData).pv_.xmeas[31] +
                            (float)14.56 * (*tcModelData).pv_.xmeas[32] +
                            (float)17.89 * (*tcModelData).pv_.xmeas[33] +
                            (float)30.44 * (*tcModelData).pv_.xmeas[34] +
                            (float)22.94 * (*tcModelData).pv_.xmeas[35]) +
                        prate * 
                           ((float).2206 * (*tcModelData).pv_.xmeas[36] +
                            (float).1456 * (*tcModelData).pv_.xmeas[37] + 
                            (float).1789 * (*tcModelData).pv_.xmeas[38])
                       ) / prate;
      (*tcModelData).pv_.xmeasmonitor[59] = 
        (float)100 * ((float).0536 * (*tcModelData).teproc_.cpdh * 293.07 + 
                      (float).0318 * (*tcModelData).teproc_.quc *  1040. * 
                      (float).454 +
                      (*tcModelData).teproc_.ftm[9] * 
                      (float).359 / (float)35.3145 * (float).44791 * 
                           ((float)2.209 * xcmp[28] +
                            (float)6.177 * xcmp[30] +
                            (float)22.06 * xcmp[31] +
                            (float)14.56 * xcmp[32] +
                            (float)17.89 * xcmp[33] +
                            (float)30.44 * xcmp[34] +
                            (float)22.94 * xcmp[35]) +
                      prate * 
                           ((float).2206 * xcmp[36] +
                            (float).1456 * xcmp[37] + 
                            (float).1789 * xcmp[38])
                     ) / prate;
      (*tcModelData).pv_.xmeasmonitor[60] = 
        ((float).0536 * (*tcModelData).pv_.xmeas[19] + 
         (float).0318 * (*tcModelData).pv_.xmeas[18] +
         (*tcModelData).pv_.xmeas[9] * (float).44791 * 
             ((float)2.209 * (*tcModelData).pv_.xmeas[28] +
              (float)6.177 * (*tcModelData).pv_.xmeas[30] +
              (float)22.06 * (*tcModelData).pv_.xmeas[31] +
              (float)14.56 * (*tcModelData).pv_.xmeas[32] +
              (float)17.89 * (*tcModelData).pv_.xmeas[33] +
              (float)30.44 * (*tcModelData).pv_.xmeas[34] +
              (float)22.94 * (*tcModelData).pv_.xmeas[35]) +
         prate * 
             ((float).2206 * (*tcModelData).pv_.xmeas[36] +
              (float).1456 * (*tcModelData).pv_.xmeas[37] + 
              (float).1789 * (*tcModelData).pv_.xmeas[38]));
      (*tcModelData).pv_.xmeasmonitor[61] = 
        ((float).0536 * (*tcModelData).teproc_.cpdh * 293.07 + 
         (float).0318 * (*tcModelData).teproc_.quc *  1040. * (float).454 +
         (*tcModelData).teproc_.ftm[9] * 
         (float).359 / (float)35.3145 * (float).44791 * 
             ((float)2.209 * xcmp[28] +
              (float)6.177 * xcmp[30] +
              (float)22.06 * xcmp[31] +
              (float)14.56 * xcmp[32] +
              (float)17.89 * xcmp[33] +
              (float)30.44 * xcmp[34] +
              (float)22.94 * xcmp[35]) +
         prate * 
             ((float).2206 * xcmp[36] +
              (float).1456 * xcmp[37] + 
              (float).1789 * xcmp[38]));
    } //if((*ModelData).MSFlag & 0x4) > 1){

    /*Output of Component Concentrations*/
    if(((*tcModelData).MSFlag & 0x8) > 1){
      for (i__ = 1; i__ <= 8; ++i__){
        (*tcModelData).pv_.xmeascomp[0  + i__ - 1] =
                                  (*tcModelData).teproc_.xst[0  + i__ - 1];
        (*tcModelData).pv_.xmeascomp[8  + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[8  + i__ - 1];
        (*tcModelData).pv_.xmeascomp[16 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[16 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[24 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[24 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[32 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[32 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[40 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[40 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[48 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[56 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[56 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[64 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[64 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[72 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[72 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[80 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[80 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[88 + i__ - 1];
        (*tcModelData).pv_.xmeascomp[88 + i__ - 1] = 
                                  (*tcModelData).teproc_.xst[96 + i__ - 1];
      } //for (i__ = 1; i__ <= 8; ++i__){
    } //if(((*tcModelData).MSFlag & 0x8) > 1){
  } //if((Callflag < 2) && (((*tcModelData).MSFlag & 0x8000) == 0)){
  
  /*Calculation of State Derivative*/
  if(((Callflag == 2) ||(Callflag == 0)) &&
     (((*tcModelData).MSFlag & 0x8000) == 0)){
    for (i__ = 1; i__ <= 8; ++i__){
  	  yp[i__]      = (*tcModelData).teproc_.fcm[i__ + 47] - 
	                 (*tcModelData).teproc_.fcm[i__ + 55] + 
                     (*tcModelData).teproc_.crxr[i__ - 1];
      yp[i__ + 9]  = (*tcModelData).teproc_.fcm[i__ + 55] - 
                     (*tcModelData).teproc_.fcm[i__ + 63] - 
		             (*tcModelData).teproc_.fcm[i__ + 71] - 
                     (*tcModelData).teproc_.fcm[i__ + 79];
      yp[i__ + 18] = (*tcModelData).teproc_.fcm[i__ + 87] - 
                     (*tcModelData).teproc_.fcm[i__ + 95];
	  yp[i__ + 27] = (*tcModelData).teproc_.fcm[i__ - 1]  + 
                     (*tcModelData).teproc_.fcm[i__ + 7]  + 
	      	         (*tcModelData).teproc_.fcm[i__ + 15] + 
                     (*tcModelData).teproc_.fcm[i__ + 31] + 
		             (*tcModelData).teproc_.fcm[i__ + 63] - 
                     (*tcModelData).teproc_.fcm[i__ + 39];
    /* L9010: */
    } //for (i__ = 1; i__ <= 8; ++i__){
    
    yp[9] = (*tcModelData).teproc_.hst[6] * (*tcModelData).teproc_.ftm[6] - 
            (*tcModelData).teproc_.hst[7] * (*tcModelData).teproc_.ftm[7] + 
            (*tcModelData).teproc_.rh + (*tcModelData).teproc_.qur;
/* 		Here is the "correct" version of the separator energy balance: */
/* 	YP(18)=HST(8)*FTM(8)- */
/*    .(HST(9)*FTM(9)-cpdh)- */
/*    .HST(10)*FTM(10)- */
/*    .HST(11)*FTM(11)+ */
/*    .QUS */
/* 		Here is the original version */
    yp[18] = 
           (*tcModelData).teproc_.hst[7]  * (*tcModelData).teproc_.ftm[7] - 
           (*tcModelData).teproc_.hst[8]  * (*tcModelData).teproc_.ftm[8] -
           (*tcModelData).teproc_.hst[9]  * (*tcModelData).teproc_.ftm[9] - 
	       (*tcModelData).teproc_.hst[10] * (*tcModelData).teproc_.ftm[10]+
           (*tcModelData).teproc_.qus;
    yp[27] = 
           (*tcModelData).teproc_.hst[3]  * (*tcModelData).teproc_.ftm[3] + 
           (*tcModelData).teproc_.hst[10] * (*tcModelData).teproc_.ftm[10]-
           (*tcModelData).teproc_.hst[4]  * (*tcModelData).teproc_.ftm[4] - 
	       (*tcModelData).teproc_.hst[12] * (*tcModelData).teproc_.ftm[12]+
           (*tcModelData).teproc_.quc;
    yp[36] = 
           (*tcModelData).teproc_.hst[0] * (*tcModelData).teproc_.ftm[0] + 
           (*tcModelData).teproc_.hst[1] * (*tcModelData).teproc_.ftm[1] + 
           (*tcModelData).teproc_.hst[2] * (*tcModelData).teproc_.ftm[2] + 
	       (*tcModelData).teproc_.hst[4] * (*tcModelData).teproc_.ftm[4] + 
           (*tcModelData).teproc_.hst[8] * (*tcModelData).teproc_.ftm[8] - 
           (*tcModelData).teproc_.hst[5] * (*tcModelData).teproc_.ftm[5];
    
    yp[37] = ((*tcModelData).teproc_.fwr * (float)500.53 * 
              ((*tcModelData).teproc_.tcwr - (*tcModelData).teproc_.twr) -
  	          (*tcModelData).teproc_.qur * 1e6 / (float)1.8) / 
             (*tcModelData).teproc_.hwr;
    yp[38] = ((*tcModelData).teproc_.fws * (float)500.53 * 
              ((*tcModelData).teproc_.tcws - (*tcModelData).teproc_.tws) - 
   	          (*tcModelData).teproc_.qus * 1e6 / (float)1.8) / 
             (*tcModelData).teproc_.hws;

    (*tcModelData).teproc_.ivst[9]  = (*tcModelData).dvec_.idv[13];
    (*tcModelData).teproc_.ivst[10] = (*tcModelData).dvec_.idv[14];
    (*tcModelData).teproc_.ivst[4]  = (*tcModelData).dvec_.idv[18];
    (*tcModelData).teproc_.ivst[6]  = (*tcModelData).dvec_.idv[18];
    (*tcModelData).teproc_.ivst[7]  = (*tcModelData).dvec_.idv[18];
    (*tcModelData).teproc_.ivst[8]  = (*tcModelData).dvec_.idv[18];
    for (i__ = 1; i__ <= 12; ++i__){
      if ((*time == 0.) || 
          (d__1 = (*tcModelData).teproc_.vcv[i__ - 1] - 
                  (*tcModelData).pv_.xmv[i__ - 1], 
  		   abs(d__1)) > (*tcModelData).teproc_.vst[i__ - 1] * 
                        (*tcModelData).teproc_.ivst[i__ - 1]){
	    (*tcModelData).teproc_.vcv[i__ - 1] = 
                                           (*tcModelData).pv_.xmv[i__ - 1];
	  } //if ((*time == 0.) || ...
    
      /*Constraints of Manipulated Variable*/
	  if ((*tcModelData).teproc_.vcv[i__ - 1] < (float)0.){
  	    (*tcModelData).teproc_.vcv[i__ - 1] = (float)0.;
	  } //if ((*tcModelData).teproc_.vcv[i__ - 1] < (float)0.){
	  if ((*tcModelData).teproc_.vcv[i__ - 1] > (float)100.){
	    (*tcModelData).teproc_.vcv[i__ - 1] = (float)100.;
	  } //if ((*tcModelData).teproc_.vcv[i__ - 1] > (float)100.){
    
	  yp[i__ + 38] = 
                   ((*tcModelData).teproc_.vcv[i__ - 1] - vpos[i__ - 1]) / 
		           (*tcModelData).teproc_.vtau[i__ - 1];
    /* L9020: */
    } //for (i__ = 1; i__ <= 12; ++i__){

    if (*time > (float)0. && *isd != (float)0.){
      i__1 = *nn;
	  for (i__ = 1; i__ <= i__1; ++i__){
        yp[i__] = (float)0.;
      /* L9030: */
	  } //for (i__ = 1; i__ <= i__1; ++i__){
    } //if (*time > (float)0. && *isd != 0){
  } //if(((Callflag == 3) ||(Callflag == 0)) && ...
  
  #undef isd
  
  return 0;
} /* tefunc_ */


/*-------------------------------------------------------------------------
-                              t e s u b 1 _                              -
-------------------------------------------------------------------------*/
static int tesub1_(void *ModelData, 
                   doublereal *z__, doublereal *t, doublereal *h__, 
                   const integer *ity){
  /*----------------------------- Variables -----------------------------*/
  doublereal d__1;
  struct stModelData *tcModelData;
  integer i__;
  doublereal r__, hi;

  /*Typcast of Dataset Pointer*/  
  tcModelData = ModelData;

  /*Parameter adjustments*/
  --z__;

  /*--------------------------- Function Body ---------------------------*/
  if (*ity == 0){
    *h__ = 0.;
    for (i__ = 1; i__ <= 8; ++i__){
      /* Computing 2nd power */
	  d__1 = *t;
	  /*Integration von Enthalpie-Gleichung (temperaturabhängigkeit) 
        in tesub3_*/
	  hi = *t * ((*tcModelData).const_.ah[i__ - 1] + 
                 (*tcModelData).const_.bh[i__ - 1] * *t / 2. + 
                 (*tcModelData).const_.ch[i__ - 1] * (d__1 * d__1) / 3.);
      hi *= 1.8;
	  *h__ += z__[i__] * (*tcModelData).const_.xmw[i__ - 1] * hi;
/* L100: */
    } //for (i__ = 1; i__ <= 8; ++i__){
  }else{
    *h__ = 0.;
    for (i__ = 1; i__ <= 8; ++i__){
      /* Computing 2nd power */
	  d__1 = *t;
	  hi = *t * ((*tcModelData).const_.ag[i__ - 1] + 
                 (*tcModelData).const_.bg[i__ - 1] * *t / 2. + 
	   	         (*tcModelData).const_.cg[i__ - 1] * (d__1 * d__1) / 3.);
      hi *= 1.8;
      hi += (*tcModelData).const_.av[i__ - 1];
      *h__ += z__[i__] * (*tcModelData).const_.xmw[i__ - 1] * hi;
/* L200: */
    } //for (i__ = 1; i__ <= 8; ++i__){
  } //if (*ity == 0){
    
  if (*ity == 2){
    r__ = 3.57696e-6;
    *h__ -= r__ * (*t + (float)273.15);
  } //if (*ity == 2){
  
  return 0;
} /* tesub1_ */


/*-------------------------------------------------------------------------
-                              t e s u b 2 _                              -
-------------------------------------------------------------------------*/
static int tesub2_(void *ModelData, 
                   doublereal *z__, doublereal *t, doublereal *h__, 
                   const integer *ity){
  /*----------------------------- Variables -----------------------------*/
  integer j;
  doublereal htest;
  doublereal dh;
  doublereal dt, err, tin;

  /*Parameter adjustments*/
  --z__;

  /*--------------------------- Function Body ---------------------------*/
  tin = *t;
  for (j = 1; j <= 100; ++j){
	tesub1_(ModelData, &z__[1], t, &htest, ity);
	err = htest - *h__;
	tesub3_(ModelData, &z__[1], t, &dh, ity);
	dt = -err / dh;
	*t += dt;
/* L250: */
    if (abs(dt) < 1e-12){
	  goto L300;
    } //if (abs(dt) < 1e-12){
  } //for (j = 1; j <= 100; ++j){
  *t = tin;
  
  /*------------------------ B R A N C H M A R K ------------------------*/
  L300:
  /*------------------------ B R A N C H M A R K ------------------------*/
  return 0;
} /* tesub2_ */


/*-------------------------------------------------------------------------
-                              t e s u b 3 _                              -
-------------------------------------------------------------------------*/
static int tesub3_(void *ModelData, 
                   doublereal *z__, doublereal *t, doublereal *dh, 
   		           const integer *ity){
  /*----------------------------- Variables -----------------------------*/
  doublereal d__1;
  struct stModelData *tcModelData;
  integer i__;
  doublereal r__, dhi;

  /*Typcast of Dataset Pointer*/
  tcModelData = ModelData;

  /*Parameter adjustments*/
  --z__;

  /*--------------------------- Function Body ---------------------------*/
  if (*ity == 0){
    *dh = 0.;
	for (i__ = 1; i__ <= 8; ++i__){
/* Computing 2nd power */
	  d__1 = *t;
	  dhi = (*tcModelData).const_.ah[i__ - 1] +
            (*tcModelData).const_.bh[i__ - 1] * *t + 
		    (*tcModelData).const_.ch[i__ - 1] * (d__1 * d__1);
      dhi *= 1.8;
      *dh += z__[i__] * (*tcModelData).const_.xmw[i__ - 1] * dhi;
/* L100: */
	} //for (i__ = 1; i__ <= 8; ++i__){
  }else{
	*dh = 0.;
	for (i__ = 1; i__ <= 8; ++i__){
/* Computing 2nd power */
	  d__1 = *t;
	  dhi = (*tcModelData).const_.ag[i__ - 1] + 
            (*tcModelData).const_.bg[i__ - 1] * *t +
		    (*tcModelData).const_.cg[i__ - 1] * (d__1 * d__1);
      dhi *= 1.8;
      *dh += z__[i__] * (*tcModelData).const_.xmw[i__ - 1] * dhi;
/* L200: */
	} //for (i__ = 1; i__ <= 8; ++i__){
  } //if (*ity == 0){
  
  if (*ity == 2){
	r__ = 3.57696e-6;
	*dh -= r__;
  } //if (*ity == 2){
  
  return 0;
} /* tesub3_ */


/*-------------------------------------------------------------------------
-                              t e s u b 4 _                              -
-------------------------------------------------------------------------*/
static int tesub4_(void *ModelData, 
                   doublereal *x, doublereal *t, doublereal *r__){
  /*----------------------------- Variables -----------------------------*/
  struct stModelData *tcModelData;
  integer i__;
  doublereal v;
  
  /*Typcast of Dataset Pointer*/
  tcModelData = ModelData;  

  /*Parameter adjustments*/
  --x;

  /*--------------------------- Function Body ---------------------------*/
  v = (float)0.;
  for (i__ = 1; i__ <= 8; ++i__){
	v += x[i__] * (*tcModelData).const_.xmw[i__ - 1] / 
         ((*tcModelData).const_.ad[i__ - 1] + 
          ((*tcModelData).const_.bd[i__ - 1] + 
           (*tcModelData).const_.cd[i__ - 1] * *t) * *t);
/* L10: */
  } //for (i__ = 1; i__ <= 8; ++i__){
  *r__ = (float)1. / v;
  return 0;
} /* tesub4_ */


/*-------------------------------------------------------------------------
-                              t e s u b 5 _                              -
-------------------------------------------------------------------------*/
static int tesub5_(void *ModelData, 
                   doublereal *s, doublereal *sp, doublereal *adist, 
                   doublereal *bdist, doublereal *cdist, doublereal *ddist,
                   doublereal *tlast, doublereal *tnext, doublereal *hspan,
   			       doublereal *hzero, doublereal *sspan, doublereal *szero,
			       doublereal *spspan, doublereal *idvflag){
  /*----------------------------- Variables -----------------------------*/
  doublereal h__;
  integer i__;
  doublereal s1;
  doublereal s1p;
  doublereal d__1;

  /*--------------------------- Function Body ---------------------------*/
  i__    = -1;
  h__    = *hspan * tesub7_(ModelData, &i__) + *hzero;
  s1     = *sspan * tesub7_(ModelData, &i__) * *idvflag + *szero;
  s1p    = *spspan * tesub7_(ModelData, &i__) * *idvflag;
  
  /* Computing 0th power */
  *adist = *s;
  /* Computing 1rd power */
  *bdist = *sp;   
  /* Computing 2nd power */
  d__1   = h__;
  *cdist = ((s1 - *s) * 3. - h__ * (s1p + *sp * 2.)) / (d__1 * d__1);
  /* Computing 3rd power */
  d__1   = h__;
  *ddist = ((*s - s1) * 2. + h__ * (s1p + *sp)) / (d__1 * (d__1 * d__1));

  *tnext = *tlast + h__;
  
  return 0;
} /* tesub5_ */


/*-------------------------------------------------------------------------
-                              t e s u b 6 _                              -
-------------------------------------------------------------------------*/
static int tesub6_(void *ModelData, doublereal *std, doublereal *x){
  /*----------------------------- Variables -----------------------------*/
  integer i__;
  
  /*--------------------------- Function Body ---------------------------*/
  *x = 0.;
  for (i__ = 1; i__ <= 12; ++i__){
    *x += tesub7_(ModelData, &i__);
  } //for (i__ = 1; i__ <= 12; ++i__){
    
  *x = (*x - 6.) * *std;
  
  return 0;
} /* tesub6_ */


/*-------------------------------------------------------------------------
-                              t e s u b 7 _                              -
-------------------------------------------------------------------------*/
static doublereal tesub7_(void *ModelData, integer *i__){
  /*----------------------------- Variables -----------------------------*/
  struct stModelData *tcModelData;
  doublereal ret_val, *d__1, c_b78;
  
  /*Typcast of Dataset Pointer*/
  tcModelData = ModelData;
  
  
  /*--------------------------- Function Body ---------------------------*/
  c_b78 = 4294967296.;
  
  /*Generation of Random Numbers for Measurment Noise*/
  if (*i__ >= 0){
    if(((*tcModelData).MSFlag & 0x20) > 0){
      d__1 = &(*tcModelData).randsd_.measnoise;
    }else{
      d__1 = &(*tcModelData).randsd_.g;
    }

    *d__1 = *d__1 * 9228907.;
    *d__1 = d_mod(d__1, &c_b78);    
    
    ret_val = *d__1 / 4294967296.;
  } //if (*i__ >= 0){
  
  /*Generation of Random Numbers for Process Disturbances*/
  if (*i__ < 0){
    if(((*tcModelData).MSFlag & 0x20) > 0){
      d__1 = &(*tcModelData).randsd_.procdist;
    }else{
      d__1 = &(*tcModelData).randsd_.g;
    }
    
    *d__1 = *d__1 * 9228907.;
    *d__1 = d_mod(d__1, &c_b78);
    
    ret_val = *d__1 * 2.0 / 4294967296. - 1.;
  } //if (*i__ < 0){
  
  return ret_val;
} /* tesub7_ */


/*-------------------------------------------------------------------------
-                              t e s u b 8 _                              -
-------------------------------------------------------------------------*/
static doublereal tesub8_(void *ModelData, 
                          const integer *i__, doublereal *t){
  /*----------------------------- Variables -----------------------------*/
  doublereal ret_val;
  struct stModelData *tcModelData;
  doublereal h__;

  /*Typcast of Dataset Pointer*/
  tcModelData = ModelData;

  /*--------------------------- Function Body ---------------------------*/
  h__ = *t - (*tcModelData).wlk_.tlast[*i__ - 1];
  ret_val = (*tcModelData).wlk_.adist[*i__ - 1] + 
            h__ * ((*tcModelData).wlk_.bdist[*i__ - 1] + 
                   h__ * ((*tcModelData).wlk_.cdist[*i__ - 1] + 
                          h__ * (*tcModelData).wlk_.ddist[*i__ - 1]));
  return ret_val;
} /* tesub8_ */


/*-------------------------------------------------------------------------
-                               ? ? ? ? ? ?                               -
-------------------------------------------------------------------------*/
#ifdef KR_headers
  #ifdef IEEE_drem
    double drem();
  #else
    double floor();
  #endif
  double d_mod(x,y) doublereal *x, *y;
#else
  #ifdef IEEE_drem
    double drem(double, double);
  #else
    #undef abs
  #endif
  double d_mod(doublereal *x, doublereal *y)
#endif
{
#ifdef IEEE_drem
  double xa, ya, z;
  
  if ((ya = *y) < 0.){
    ya = -ya;
  } //if ((ya = *y) < 0.){
  
  z = drem(xa = *x, ya);
  if (xa > 0){
	if (z < 0){
      z += ya;
    } //if (z < 0){
  }else{
    if (z > 0){
      z -= ya;
    } //if (z > 0){
  } //if (xa > 0){
  return z;
#else
	double quotient;
	if( (quotient = *x / *y) >= 0)
		quotient = floor(quotient);
	else
		quotient = -floor(-quotient);
	return(*x - (*y) * quotient );
#endif
} //?? 


/*-------------------------------------------------------------------------
-                               ? ? ? ? ? ?                               -
-------------------------------------------------------------------------*/
#ifdef KR_headers
  double pow();
  double pow_dd(ap, bp) doublereal *ap, *bp;
#else
  #undef abs
  double pow_dd(doublereal *ap, const doublereal *bp)
#endif
{
  return(pow(*ap, *bp) );
} //?? 



/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
