## GmshReader
### Introduction
* This is a small piece of software which allows us to read the generated `annulus.msh` mesh file into the application.
* Once `GmshReader` has read the `annulus.msh` file, we are left with essentially,`.dat` files which specifiy the problem domain.

#### 1. Reading .msh Files
* The files contains:
    * `Nodes` (points in space with coordinates).
    * `Elements` (triangles or quadrilaterals connecting nodes).
    * `Physical tags` (to identify boundaries or regions).
 
#### 2. Parsing Mesh Data into C++ Objects
* It stores:
    * A list of `nodes` as coordinate vectors (e.g., (x, y) points).
    * A list of `elements` as node indices (e.g., triangle with nodes 1, 2, 3).
    * Optional: boundary markers or physical regions.

#### 3. Output
* Three files are produced after running the software:
    * `nodes.dat` — List of node coordinates.
    * `elements.dat` — List of elements with node indices.
    * `boundary.dat` — Optional, depends on your mesh and tags
### Note:
* There is no need to create your own `annulus.msh` mesh file; I've provided this.

