C  MEASUREMENT AND VALVE COMMON BLOCK
C
      DOUBLE PRECISION XMEAS, XMV
	integer isd
      COMMON/PV/ XMEAS(41), XMV(12), isd
C
C   DISTURBANCE VECTOR COMMON BLOCK
C
      INTEGER IDV
      COMMON/DVEC/ IDV(20)
	
c	NOTE: I have included isd in the /PV/ common.  This is set
c		non-zero when the process is shutting down.

