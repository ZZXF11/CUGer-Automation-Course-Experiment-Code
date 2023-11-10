c	.MEX implementation of the Tennessee Eastman process model.

c	Copyright by N. L. Ricker, Professor
c	Department of Chemical Engineering, BF-10
c	University of Washington
c	Seattle, WA 98195

c	E-mail:  ricker@cheme.washington.edu

C	This is a standard Matlab system function in the format required by
c	SIMULINK and the associated analysis and integration routines.  It has
c	50 states, 12 inputs, and 41 outputs.  See the paper by Downs and Vogel
c	for an explanation of these variables.

c	In addition to the standard input arguments (time, states, inputs, flag),
c	you must supply 4 parameters, as follows:

c	p1	idv(20)  -- a vector of length 20 containing the desired values of
c		the disturbance flags (see paper by Downs and Vogel).

c		The following are all used by the TE routines to save data between
c		Matlab calls.  They are initialized by a call to this function with
c		time<0 and flag=0.  You must create Matlab variables of the 
c		appropriate size (a vector of zeros is convenient),
c		and pass them to te_mex as input arguments.

c	p2	Vector of length 153
c	p3	Vector of length 586
c	p4	Vector of length 139

c	Here are some example calls from Matlab:

c	t=-1;
c	x=[];
c	u=[];
c	flag=0;
c	idv=zeros(20,1);
c	p2=zeros(153,1);
c	p3=zeros(586,1);
c	p4=zeros(139,1);
c	x0=te_mex(t,x,u,flag,idv,p2,p3,p4);
	
c	u=[specify a vector, length 12];
c	flag=1;
c	t=0;
c	dxdt=te_mex(t,x0,u,flag,idv,p2,p3,p4);
c	flag=3;
c	y=te_mex(t,x0,u,flag,idv,p2,p3,p4);

c	The first call to te_mex initializes the storage vectors, p2 to p4, and
c	returns the initial state vector in x0. 

c	The second call to te_mex calculates the time-derivatives of the states
c	at the initial conditions (x0) and for a set of inputs that you must specify
c	(in the "u" vector).

c	The third call to te_mex returns the values of the outputs (all 41 of them -
c	see paper by Downs and Vogel) for the given x0 and u.

c	The following sequence of Matlab statements should reproduce the graphs
c	shown in Figure 3 of Downs and Vogel:

c	idv=zeros(20,1);
c	p2=zeros(153,1);
c	p3=zeros(586,1);
c	p4=zeros(139,1);
c	[sys,x0]=te_mex(-1,[],[],0,idv,p2,p3,p4);
c	u0=[63.53,  53.98, 24.644, 61.302, 22.21, ...
c	    40.064, 38.1,  46.534, 47.446, 41.106, ...
c	    18.114, 50];       % Base case inputs (XMV variables).
c	u0(10)=38;             % Specifies a step in XMV(10)
c	tvec=[0; 0.3];         % Starting and ending time.
c	ut=[tvec [u0;u0] ];    % Specifies constant inputs.
c	options=[.001, .00001, .001, 0, 0, 0, 0];
c	[tt,xt,yt]=rk45('te_mex',tvec,x0,options,ut,idv,p2,p3,p4);

c	clg
c	subplot(221)
c	plot(tt,yt(:,6)),title('Reactor Feed'),xlabel('Time (hours)')
c	subplot(222)
c	plot(tt,yt(:,7)),title('Reac Pressure'),xlabel('Time (hours)')
c	subplot(223)
c	plot(tt,yt(:,8)),title('Reac Level'),xlabel('Time (hours)')
c	subplot(224)
c	plot(tt,yt(:,9)),title('Reac Temp'),xlabel('Time (hours)')
c	pause

c	clg
c	subplot(221)
c	plot(tt,yt(:,11)),title('Prod Sep Temp'),xlabel('Time (hours)')
c	subplot(222)
c	plot(tt,yt(:,12)),title('Prod Sep Level'),xlabel('Time (hours)')
c	subplot(223)
c	plot(tt,yt(:,10)),title('Purge Rate'),xlabel('Time (hours)')
c	subplot(224)
c	plot(tt,yt(:,18)),title('Stripper Temp'),xlabel('Time (hours)')
c	pause

c	I found that a specification of a maximum step size of about 0.001
c	was necessary to get reliable accuracy from the Matlab integration
c	package (see use of "options" variable, above).  Other settings
c	may give better performance.  I didn't experiment with it too much.
c	Elapsed time for the integration was about 1 minute on a Mac IIfx.

c	The following additional commands show how the concentrations
c	from the analyzers vary with time.  You can observe the discrete
c	sampling behavior, e.g., the product concentrations vary every 0.25
c	hours, and the others vary every 0.1 hours.

c	clg
c	subplot(221)
c	plot(tt,yt(:,23)),title('A in Feed'),xlabel('Time (hours)')
c	subplot(222)
c	plot(tt,yt(:,30)),title('B in Purge'),xlabel('Time (hours)')
c	subplot(223)
c	plot(tt,yt(:,40)),title('G in Product'),xlabel('Time (hours)')
c	subplot(224)
c	plot(tt,yt(:,41)),title('H in Product'),xlabel('Time (hours)')

c	Many other uses of te_mex should be obvious to those familiar with
c	the analysis tools in SIMULINK and the various Matlab toolboxes.

C---------------------------------------------------------------------

      SUBROUTINE USRFCN(NLHS, PLHS, NRHS, PRHS)
      INTEGER PLHS(*), PRHS(*)
      INTEGER NLHS, NRHS
C
      INTEGER CRTMAT, REALP, IMAGP, GETGLO, ALREAL, ALINT, GETSTR
C
      DOUBLE PRECISION GETSCA
C
C THE ABOVE SUBROUTINE, ARGUMENT, AND FUNCTION DECLARATIONS ARE STANDARD
C IN ALL FORTRAN MEX FILES.
C---------------------------------------------------------------------
C

c	The following will hold pointers:

	integer t,x,u,flag,p1,p2,p3,p4

c		The following are local variables.  In this case we know
c		that there will be 50 continuous states, 12 inputs, and 41 outputs.
c		These values are specified by the parameters nx, nu, and ny,
c		respectively.  Also define corresponding character constants
c		lenx, lenu, to use in error messages, and double precision
c		constants for the SIZES vector.

	integer iflag,m,n,nx,nu,ny
	character*(*) lenu,lenx
	double precision dnx, dnu, dny
	parameter (nx=50, nu=12, ny=41, lenx='50', lenu='12', dnx=50.,
     +		dnu=12.,dny=41.)
	
	
	double precision 	rx(nx),rx0(nx),dxdt(nx),sizes(6),rt

c		The states, inputs, and outputs are arranged as explained in the
c		paper by Downs and Vogel.  The following is the standard 
c		common block definition used as a user interface to the TE
c		routines.

      DOUBLE PRECISION XMEAS, XMV
	integer isd
      COMMON/PV/ XMEAS(41), XMV(12), isd
C
C   DISTURBANCE VECTOR COMMON BLOCK
C
      INTEGER IDV
	double precision didv(20)  	! For temporary storage of IDV.
      COMMON/DVEC/ IDV(20)
	
c	NOTE: I have included isd in the PV column.  This is set
c		to -1 when the process is shutting down.

c	In addition, must include all the other common areas, so data can
c	be saved in Matlab between calls.

	DOUBLE PRECISION G_dum
      COMMON/RANDSD/G_dum
	double precision dp2
	common /const/ dp2(112)
	double precision dp3
	common /teproc/dp3(586)
	double precision dp4
	common /wlk/ dp4(139)
	double precision dp2tmp(153)

c	Note:  /wlk/ is one element longer than that in the TEPROB.F definition.
c	I am using the extra space to hold the value of the scalar in /RANDSD/.

	character*80 message	! For debug messages to screen
	
c		The following is the appropriate definition of the SIZES
c		vector for SIMULAB system functions when there are no
c		discrete-time states and no direct feed-through from input
c		to output.

	data sizes/dnx, 0., dny, dnu, 0., 0./
	

c		Check the number of input arguments

	if (nrhs .ne. 8) then
		call mexerr('TE_mex needs 8 input variables.')
	else

c			There are 8 input arguments.  Set pointers and copy the
c			inputs to local storage.

		call getsiz(prhs(1),m,n)		! Get size of "t" array.
		if (m.gt.0 .and. n.gt.0) then		! If it's non-empty...
			rt=getsca(prhs(1))		! gets time value (a scalar).
		else
			rt=0.0				! Otherwise set to zero.
		end if
		
		call getsiz(prhs(4),m,n)		! "flag"
		if (m.gt.0 .and. n.gt.0) then
			if (m.eq.1 .and. n.eq.1) then
				iflag=abs(nint(getsca(prhs(4))))
			else
				call mexerr('FLAG must be a scalar.')
			end if
		else
			iflag=0
		end if
			
		call getsiz(prhs(2),m,n)		! "x" vector.
		if (m.gt.0 .and. n.gt.0) then		
			if (min(m,n).ne.1 .or. max(m,n) .ne. nx) then	
				call mexerr('X must be a vector, length '//lenx)
			end if
			x=realp(prhs(2))
			call cpout(x,rx,nx)		! copy x into local storage
		else if (iflag.eq.1 .or. iflag.eq.3) then
			call mexerr('X must be supplied.')
		end if
	
			
		call getsiz(prhs(3),m,n)		! "u" vector.
		if (m.gt.0 .and. n.gt.0) then		
			if (min(m,n).ne.1 .or. max(m,n) .ne. nu) then	
				call mexerr('U must be a vector, length '//lenu)
			end if
			u=realp(prhs(3))
			call cpout(u,xmv,nu)		! copy u into local storage
		else if (iflag.eq.1 .or. iflag.eq.3) then
			call mexerr('U must be supplied.')
		end if
		
		call getsiz(prhs(5),m,n)		! IDV
		if (m.eq.1 .and. n.eq.20 .or. m.eq.20 .and. n.eq.1) then
			p1=realp(prhs(5))
			call cpout(p1,didv,20)		! copy IDV to local REAL*8 array 
			do i=1,20
				idv(i)=nint(didv(i))	! convert to integer
			end do
		else
			call mexerr('P1 must be a vector, length 20.')
		end if
	
				
		call getsiz(prhs(6),m,n)		! P2
		if (m.eq.1 .and. n.eq.153 .or. m.eq.153 .and. n.eq.1) then
			p2=realp(prhs(6))
			call cpout(p2,dp2tmp,153)		! copy P2 into temporary storage
			do i=1,112
				dp2(i)=dp2tmp(i)			! Load common /CONST/
			end do
			do i=1,41
				xmeas(i)=dp2tmp(i+112)		! Load old XMEAS(i) values 
			end do
		else
			call mexerr('P2 must be a vector, length 153.')
		end if

		call getsiz(prhs(7),m,n)		! P3
		if (m.eq.1 .and. n.eq.586 .or. m.eq.586 .and. n.eq.1) then
			p3=realp(prhs(7))
			call cpout(p3,dp3,586)		! copy P3 into common /TEPROC/ 
		else
			call mexerr('P3 must be a vector, length 586.')
		end if

		call getsiz(prhs(8),m,n)		! P4
		if (m.eq.1 .and. n.eq.139 .or. m.eq.139 .and. n.eq.1) then
			p4=realp(prhs(8))
			call cpout(p4,dp4,139)		! copy P4 into common /WLK/ 
			G_dum=dp4(139)			! also initialize /RANDSD/
		else
			call mexerr('P4 must be a vector, length 139.')
		end if

	end if
	
	if (rt.lt.0.0.and.iflag.eq.0) then
		call TEINIT(nx,rt,rx0,dxdt)	! Initialize common areas
	end if
	
	
c		Now return outputs according to the value of "flag"

	if (iflag.eq.0) then

c			Default state vector

		rx0(1)=10.40491389
		rx0(2)=4.363996017
		rx0(3)=7.570059737
		rx0(4)=0.4230042431
		rx0(5)=24.15513437
		rx0(6)=2.942597645
		rx0(7)=154.3770655
		rx0(8)=159.1865960
		rx0(9)=2.808522723
		rx0(10)=63.75581199
		rx0(11)=26.74026066
		rx0(12)=46.38532432
		rx0(13)=0.2464521543
		rx0(14)=15.20484404
		rx0(15)=1.852266172
	      rx0(16)=52.44639459
	      rx0(17)=41.20394008
	      rx0(18)=0.5699317760
	      rx0(19)=0.4306056376
	      rx0(20)=7.9906200783D-03
	      rx0(21)=0.9056036089
	      rx0(22)=1.6054258216D-02
	      rx0(23)=0.7509759687
	      rx0(24)=8.8582855955D-02
	      rx0(25)=48.27726193
	      rx0(26)=39.38459028
	      rx0(27)=0.3755297257
	      rx0(28)=107.7562698
	      rx0(29)=29.77250546
	      rx0(30)=88.32481135
	      rx0(31)=23.03929507
	      rx0(32)=62.85848794
	      rx0(33)=5.546318688
	      rx0(34)=11.92244772
	      rx0(35)=5.555448243
	      rx0(36)=0.9218489762
	      rx0(37)=94.59927549
	      rx0(38)=77.29698353
	      rx0(39)=63.05263039
	      rx0(40)=53.97970677
	      rx0(41)=24.64355755
	      rx0(42)=61.30192144
	      rx0(43)=22.21000000
	      rx0(44)=40.06374673
	      rx0(45)=38.10034370
	      rx0(46)=46.53415582
	      rx0(47)=47.44573456
	      rx0(48)=41.10581288
	      rx0(49)=18.11349055
	      rx0(50)=50.00000000

		plhs(1)=crtmat(6,1,0)				! "sizes"
		call cpin(sizes,realp(plhs(1)),6)
		if (nlhs.gt.1) then
			plhs(2)=crtmat(nx,1,0)			! "x0"
			call cpin(rx0,realp(plhs(2)),nx)
		end if
		if (nlhs.gt.2) then
			plhs(3)=crtmat(0,0,0)			! "xstr" (empty)
		end if
		
	else if (iflag.eq.1 .or. iflag.eq.3) then
	
		call TEFUNC(nx,rt,rx,dxdt)    	! Uses value of x from Matlab
     		if (isd.lt.0) then
			call mexerr('SHUTTING DOWN!')
		end if

		if (iflag.eq.1) then
			plhs(1)=crtmat(nx,1,0)
			call cpin(dxdt,realp(plhs(1)),nx)  		! returns dxdt to Matlab
		else
			plhs(1)=crtmat(ny,1,0)
			call cpin(xmeas,realp(plhs(1)),ny)  	! returns y to Matlab
		end if		
	else

c			For all other flags, return an empty matrix.	

		plhs(1)=crtmat(0,0,0)
	
	end if
	
c		Save TEPROB common areas in Matlab memory.

	do i=1,112
		dp2tmp(i)=dp2(i)
	end do
	do i=1,41
		dp2tmp(i+112)=xmeas(i)
	end do
	call cpin(dp2tmp,p2,153)
	call cpin(dp3,p3,586)
	dp4(139)=G_dum
	call cpin(dp4,p4,139)
	
	return
	end
