import c_performance as c
import numpy as np

print( c.__dir__() )
print( 'c.name=', c.__name__ )
print( 'c.file=', c.__file__ )
print( 'c.loader=', c.__loader__ )
print( 'c.package=', c.__package__ )
print( 'c.doc=', c.__doc__ )
print( 'c.spec=', c.__spec__ )

val = c.norm( order=2, vector=[1, 2, 3], debug=1 );
print( 'c.norm2 =', val );

print( 'np.norm2=', np.linalg.norm([1, 2, 3], 2) );

