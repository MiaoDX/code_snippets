Porting [Mosegaards Cloth Simulation Coding Tutorial](https://viscomp.alexandra.dk/?p=147) into one CMAKE project.

Build [dcnieho/FreeGLUT](https://github.com/dcnieho/FreeGLUT) or [sourceforge](http://freeglut.sourceforge.net/) from source and install, as always, in Windows I install into `C:/tools/cmake_install_libs/freeglut`.

The only special operation is `freeglut` can only be used as dynamic lib instead of static one (or, some other tricks are needed), so we add `POST_BUILD` in the CMakelists.txt.