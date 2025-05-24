# PoissonDensity
## Introduction
* __2D C++17 Solver__ for solving __Poissons Equation__ in order to find the __Mass-Density Distribution__ within __Earth's Mantle__.
* __Poisson’s Equation__ relates the __Gravitational Potential Φ(r)__ to the __Mass-Density ρ(r)__.
* What the solver is trying to do, is solve the ___Inverse Problem___; I.e. find the __Mass-Density ρ(r)__ __Φ(r)__, given the calculated value(s) of __Gravitational Potential Φ(r)__.
* Calculated values of __Gravitational Potential Φ(r)__ and __Mass-Density ρ(r)__ will be compared to those from the [GRACE](https://www.csr.utexas.edu/missions/grace/) data set(s).
* A __2D Annulus Shaped Mesh__ has been created using [gmsh](https://Gmsh.info/); see the __GmshReader__ folder to find the software which reads in the mesh file, `annulus.msh`.
* This file represents a __2D Slice of Earth's Interior__.
* The reader generates 3 files: `nodes.dat`, `triangles.dat` and `boundary_nodes.dat`. These are then used by the application to solve the __2D Poisson Equation__.
* Note: `annulus.geo`, `annulus.msh` `nodes.dat`,`triangles.dat` and `boundary_nodes.dat` have been provided so you don't actually need to use `GmshReader`; its there if you want to alter the mesh file to configure a different geometry etc.

## Problem Specification
* The __Earth’s Mantle__ is __Non-Uniform__, and variations in __Density__ (due to __Temperature__, __Composition__, __Phase-Changes__) create __Gravitational Anomalies__.
* By solving __Poisson’s Equation__, you can:
    * __Forward Model__: Predict __Gravity__ from a known __Density Distribution__.
    * __Inverse Model__: Estimate __Density Anomalies__ from __Gravity Measurements__. This what we're doing in this project.
 
* Once __Poissons Equation__ has been discretize via the __Finite Element Method (FEM)__, the resulting system of __Algebraic Equations__ is solved via the ___Conjugate Gradient Method___.
* The resulting discretized system takes the form:
    * __Ax = b__.
    * __A__: __Sparse Stiffness Matrix__.
    * __u__: __Gravitational Potential Φ(r)__.
    * __b__: __Mass-Density ρ(r)__.
* The __Inverse Problem__ is __Ill-Posed__, so ___Tikhonov Regularization___ will be used to stabilize the problem.
* __Key Steps__ involved in solving this problem:
    1. Use __Poisson’s Equation__.
    2. __Discretize Earth’s Mantle Domain__ via __FEM__.
    3. Input __Gravitational Potential Φ(r)__ data from e.g. [GRACE](https://www.csr.utexas.edu/missions/grace/).
    4. Solve the __Inverse Problem__.
    5. __Interpretation__: Analyze __Density Variations__ to infer __Mantle Structure__.
* __Boundary Conditions__: __Dirichlet__.

### Conjugate Gradient Method
* TODO.

### Tikhonov Regularization
* TODO.

## Gmsh: Mesh File Generation
#### What is it
* [gmsh](https://Gmsh.info/) is an open source __3D Finite Element Mesh Generator__ with a built-in CAD engine and post-processor.
* For more information (e.g. tutorial), see the link above.
#### Installation
* `$ sudo apt install gmsh`
* Check installation:
* `$ gmsh --version`
* Should get something like:
* `4.4.1`.
#### Using Gmsh
* You need to create a `.geo` script (`annulus.geo`) which specifies the geometry of the problem domain; see the `gmsh` directory which contains a `C++ reader`.
* Once you've created the script, you need to create the ___mesh file___, `annulus.msh`; see below:
* `$ gmsh -2 annulus.geo -format msh2 -o annulus.msh
* Once you have `annulus.msh`, this can be loaded into `GmshReader` (see separate folder) to generate `nodes.dat`, `triangles.dat` and `boundary_nodes.dat`.
* These are then loaded into the main application.
`. 
## Requirements
* __Compiler__: `g++ 13.1.0`.
* __OS__: `Ubuntu 20.04`.
* `CMake`.
* `gmsh`: for creating the `mesh file`; see notes r.e. `gmsh`.
* __Eigen Template Library__: for the __Linear Algebra__.
* Knowledge of the __Finite Element Method__, __Numerical Linear Algebra__ and __Numerical Partial Differential Equations__.

## Getting/Running the Software
* `$ git clone git@github.com:MRLintern/PoissonDensity.git`.
* `$ cd PoissonDensity`.
* TBC.
