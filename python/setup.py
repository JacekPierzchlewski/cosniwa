#
# setup.py [version 1.0]
#
# Setup script for cCosniwa Python3 module.
#
# read more on: www.speedupcode.com
#
# (c) Jacek Pierzchlewski, 2017  jacek@pierzchlewski.com
# license: BSD-2-Clause.
#
from distutils.core import setup, Extension

cCosniwa = Extension('cCosniwa', sources=['cCosniwa_py.cpp', 'cosniwa.cpp'])
setup(name='cCosniwa',
      version='1.0',
      author='Jacek Pierzchlewski',
      author_email='jacek@pierzchlewski.com',
      url='https://www.speedupcode.com/cosniwa',
      packages=['cCosniwa'],
      ext_modules=[cCosniwa],
      license='BSD 2-clause',
      platforms='Linux, OS X',
      description="""(C)++-implemented (CO)de (SNI)ppet stop(WA)tch Dedicated
      for Profiling (cCoSniWa)""",
      long_description="""cCoSniWa allows to profile Python, C++, and Python+C++
      code. It uses timestamps to mark when chosen code snippets start and stop.
      The module is especially useful for profiling multi-object code."""
     )
