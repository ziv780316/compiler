from distutils.core import setup, Extension

c_performance_module = Extension( 'c_performance', sources=['c_module.c'] );

setup(
  name='c_performance',
  description='A C package for speeding up performance',
  ext_modules=[c_performance_module],
);
