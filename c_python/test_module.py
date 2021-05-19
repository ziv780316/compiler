import c_performance as c
import numpy as np

val = c.norm( order=2, vector=[1, 2, 3], debug=1 );
print( 'c.norm2 =', val );

print( 'np.norm2=', np.linalg.norm([1, 2, 3], 2) );

