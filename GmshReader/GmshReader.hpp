// GmshReader.hpp

#pragma once  

#include <string>                  
#include <vector>                 
#include <set>                     // For std::set (used for storing unique boundary node indices)
#include <unordered_map>          // For std::unordered_map (maps boundary tags to sets of nodes)
#include <Eigen/Dense>           // For Eigen::MatrixXd (used for storing node coordinates)

// properties of a triangular element
struct Element {

	// Element ID from msh file
	int ID;

	// Physical group/tag (e.g., domain marker)                        
	int physicalTAG;

	// Indices of nodes (0-based) that make up the triangle               
	std::vector<int> nodeIDS;      
};

// Class to read and store mesh data from annulus.msh
class GmshReader {

private:

	// Matrix of node coordinates (2 x N)
	Eigen::MatrixXd nodeCoordinates;

	// list of triangle elements                        
	std::vector<Element> elements;

	// Boundary tag -> set of node indices                         
	std::unordered_map<int, std::set<int>> boundaryNodes;    

	// Clears internal storage
	void clear();

public:

	// Read mesh file
	bool read(const std::string& fileName);

	// -- Getters for internal data

	// Returns node coordinates
	const Eigen::MatrixXd& getNodeCoordinates() const;

	// Returns element list       
	const std::vector<Element>& getElements() const;

	// Returns all physical tags (one per element)         
	std::vector<int> getElementTags() const;    

	// Boundary tag -> node indices             
	const std::unordered_map<int, std::set<int>>& getBoundaryNodes() const; 
};
