from distutils import setup

setup (name='example',
       version='0.1',
       author='Nobody',
       description='Pippo',
       py_modules=["example"],
       packages=[''],
       package_data={'': ['example.cpython-38-x86_64-linux-gnu.so']})