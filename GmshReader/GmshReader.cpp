
#include <iostream>     
#include <fstream>      
#include <sstream>      
#include "GmshReader.hpp"

// Reads the .msh file and populates node coordinates, elements, and boundary nodes
bool GmshReader::read(const std::string& fileName) {

	clear();  // Clear any existing data

	// Open the mesh file
	std::ifstream file(fileName); 

	// can't open mesh file
	if (!file) {

		std::cerr << "ERROR: Can't Open Mesh File: " << fileName << "\n";

		return false;
	}

	std::string line;

	// Skip lines until we find the $Nodes section
	while (std::getline(file, line)) {

		if (line == "$Nodes") { break; }
	}

	// total number of nodes used
	int numNodes;

	// Total number of nodes in the mesh
	file >> numNodes; 

	// Allocate space (2 rows for x, y; N cols)
	nodeCoordinates.resize(2, numNodes);

	// Read all node coordinates
	for (int i{0}; i < numNodes; ++i) {

		int id;

		// coordinates
		double x{0.0}, y{0.0}, z{0.0};

		// Read ID and coordinates
		file >> id >> x >> y >> z;

		// Store x coordinate (0-based index)               
		nodeCoordinates(0, id - 1) = x;

		// store y coordinate          
		nodeCoordinates(1, id - 1) = y;          
	}

	// Skip to the $Elements section
	while (std::getline(file, line)) {

		if (line == "$Elements") { break; }
	}

	// total number of elements
	int numElements;

	// read total number of elements
	file >> numElements; 

	// Read all elements
	for (int i{0}; i < numElements; ++i) {

		int id, type, numTags;

		// Element ID, type, and number of tags
		file >> id >> type >> numTags;  

		// list of tags
		std::vector<int> tags(numTags);

		for (int j{0}; j < numTags; ++j) {
			file >> tags[j];  // Read physical and other tags
		}

		// Handle line elements (used for boundary conditions)
		if (type == 1) {

			int n1, n2;
			file >> n1 >> n2;

			int physTAG = (numTags > 0) ? tags[0] : -1;

			boundaryNodes[physTAG].insert(n1 - 1);  // Store 0-based node index
			boundaryNodes[physTAG].insert(n2 - 1);
		}

		// Handle triangle elements (used for mesh geometry)
		else if (type == 2) {

			Element elem;
			elem.ID = id;

			elem.physicalTAG = (numTags > 0) ? tags[0] : -1;

			int n1, n2, n3;
			file >> n1 >> n2 >> n3;

			elem.nodeIDS = {n1 - 1, n2 - 1, n3 - 1};  // Store 0-based indices
			elements.push_back(elem);  // Save element
		}

		// Skip unsupported types
		else {
			std::getline(file, line);
		}
	}

	return true;  // Parsing successful
}

// Getter: node coordinates
const Eigen::MatrixXd& GmshReader::getNodeCoordinates() const { return nodeCoordinates; }

// Getter: triangle elements
const std::vector<Element>& GmshReader::getElements() const { return elements; }

// Getter: list of all physical tags
std::vector<int> GmshReader::getElementTags() const {

	// list of tags
	std::vector<int> tags;

	// Reserve space for performance
	tags.reserve(elements.size());  

	for (const auto& elem : elements) {

		tags.push_back(elem.physicalTAG);
	}

	return tags;
}

// Getter: boundary node map
const std::unordered_map<int, std::set<int>>& GmshReader::getBoundaryNodes() const {

	return boundaryNodes;
}

// Clear internal storage
void GmshReader::clear() {
	
	nodeCoordinates.resize(0, 0);  // Clear matrix
	elements.clear();             // Clear element list
	boundaryNodes.clear();        // Clear map
}