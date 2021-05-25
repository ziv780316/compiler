C FORTRAN MODULE CALL BY C
C-----------------------------------------------------------------------
C COMPUTE VECTOR NORM
C-----------------------------------------------------------------------
C
      DOUBLE PRECISION FUNCTION NORM (X, N, ORDER, DEBUG)
C
C     Declare syntax = type [ [,attr]... :: ] symbol, if there is attr then :: is necessary to append
C     * flollow describe eachattr:
C      + value -> change call by reference to call by value, use in exchaning data with C function
C      + save -> static variable declaration (value will stay when function return))
C
      INTEGER, VALUE :: N;
      INTEGER, VALUE :: ORDER
      INTEGER, VALUE :: DEBUG
      INTEGER RET 
      DOUBLE PRECISION X
      INTEGER, SAVE:: CALL_COUNT = 0
      DIMENSION X(*)
      CALL_COUNT = CALL_COUNT + 1

      SUM = 0.0D0
      IF (ORDER .EQ. 1) THEN
        DO I = 1,N
          SUM = SUM + ABS(X(I))
        END DO 
        NORM = SUM
        IF (DEBUG .EQ. 1) THEN
          RET = C_PRINTF( '%d: norm1=%.15le\n', %VAL(CALL_COUNT), %VAL(NORM) )
        ENDIF
      ELSE
        DO I = 1,N
          SUM = SUM + X(I)**2
        END DO
        NORM = SQRT(SUM)
        IF (DEBUG .EQ. 1) THEN
          RET = C_PRINTF( '%d: norm2=%.15le\n', %VAL(CALL_COUNT), %VAL(NORM) )
        ENDIF
      ENDIF

      RETURN
C
C----------------------- END OF SUBROUTINE NORM ----------------------
      END
