
#include <iostream>            
#include <fstream>             
#include <unordered_map>      
#include "GmshReader.hpp"      

// Converts a physical tag to a string label
std::string boundaryLabel(int tag) {

	switch (tag) {

	case 1: return "Outer";
	case 2: return "Inner";
	default: return "Unknown";

	}
}

// -- functions for writing data to dat files -- //

// Save node coordinates to a dat file
void saveNodes(const std::string& fileName, const Eigen::MatrixXd& coords) {

	std::ofstream out(fileName);
	out << "id, x, y\n";

	for (int i{0}; i < coords.cols(); ++i) {

		out << i << "," << coords(0, i) << "," << coords(1, i) << "\n";
	}
}

// Save triangle connectivity and tags to a dat file
void saveTriangles(const std::string& fileName, const std::vector<Element>& elements) {

	std::ofstream out(fileName);

	out << "id, node0, node1, node2, tag\n";

	for (size_t i{0}; i < elements.size(); ++i) {

		const auto& e { elements[i] };

		out << i << "," << e.nodeIDS[0] << "," << e.nodeIDS[1] << "," << e.nodeIDS[2] << "," << e.physicalTAG << "\n";
	}
}

// Save boundary nodes (coordinates + tag info) to a dat file
void saveBoundaryNodes(const std::string& fileName, const Eigen::MatrixXd& coords, const std::unordered_map<int, std::set<int>>& boundaryNodes) {

	std::ofstream out(fileName);

	out << "x, y, tag, label\n";

	for (const auto& [tag, nodes] : boundaryNodes) {

		// labels
		std::string label { boundaryLabel(tag) };

		for (int nid : nodes) {

			out << coords(0, nid) << "," << coords(1, nid) << "," << tag << "," << label << "\n";
		}
	}
}


int main() {

	// Gmsh object
	GmshReader reader;

	// Load the mesh file
	if (!reader.read("../annulus.msh")) {

		// problem with msh file; abort
		std::cerr << "ERROR: Can't Load Mesh\n";

		return 1;
	}

	// Retrieve parsed mesh data
	const auto& coords { reader.getNodeCoordinates() };
	const auto& elems { reader.getElements() };
	const auto& boundary { reader.getBoundaryNodes() };

	// Print summary
	std::cout << "Nodes: " << coords.cols() << "\n"
	          << "Triangles: " << elems.size() << "\n";

	// Export to dat files
	saveNodes("nodes.dat", coords);
	saveTriangles("triangles.dat", elems);
	saveBoundaryNodes("boundary_nodes.dat", coords, boundary);

	std::cout << "Exported: nodes.dat, triangles.dat, boundary_nodes.dat\n";
}