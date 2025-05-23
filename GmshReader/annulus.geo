// gmsh script which generates 2D finite element trianglar mesh for an annulus; reprents earths mantle
// how to run this script and create mesh file:
// gmsh -2 annulus.geo -format msh2 -o annulus.msh

// annulus.geo — 2D mesh for an annulus with physical boundary tags

// Parameters
r1 = 1;   // inner radius
r2 = 2;   // outer radius
lc = 0.1; // mesh element size

// Center point
Point(1) = {0, 0, 0, lc};

// Outer circle points
Point(2) = {r2, 0, 0, lc};
Point(3) = {0, r2, 0, lc};
Point(4) = {-r2, 0, 0, lc};
Point(5) = {0, -r2, 0, lc};

// Inner circle points
Point(6) = {r1, 0, 0, lc};
Point(7) = {0, r1, 0, lc};
Point(8) = {-r1, 0, 0, lc};
Point(9) = {0, -r1, 0, lc};

// Outer circle arcs (clockwise)
Circle(1) = {2, 1, 3};
Circle(2) = {3, 1, 4};
Circle(3) = {4, 1, 5};
Circle(4) = {5, 1, 2};

// Inner circle arcs (counter-clockwise)
Circle(5) = {6, 1, 9};
Circle(6) = {9, 1, 8};
Circle(7) = {8, 1, 7};
Circle(8) = {7, 1, 6};

// Line loops
Line Loop(1) = {1, 2, 3, 4};      // outer boundary
Line Loop(2) = {5, 6, 7, 8};      // inner hole

// Define annulus surface
Plane Surface(1) = {1, 2};

// Physical groups for boundary condition tagging
Physical Curve("OuterBoundary") = {1, 2, 3, 4};  // e.g., Dirichlet condition u = 0
Physical Curve("InnerBoundary") = {5, 6, 7, 8};  // e.g., Dirichlet condition u = 1

// Optional: tag the domain surface
Physical Surface("AnnulusDomain") = {1};

// Generate the mesh
Mesh 2;