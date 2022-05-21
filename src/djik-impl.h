#pragma once

#include <vector>
#include <string>
#include <map>

extern "C" {
	class __declspec(dllexport) Node;
	
	class __declspec(dllexport) Connection {
		friend class Node;
		friend class Graph;
	private:
		int index;
		unsigned __int32 cost;

		Connection() = delete;

		Connection(const int, const unsigned __int32);
	};

	class __declspec(dllexport) Node {
		friend class Graph;
		friend class Connection;
	private:		
		std::string name;
		std::vector< Connection > connections;
		bool isLocked;
		__int32 associatedCost;
		int priorNode;

		Node() = delete; // forbid default constructor

		Node(const std::string&);

		bool CreateConnection(const int&, unsigned __int32);
	};

	class __declspec(dllexport) Graph {
	private:
		std::string name;
		std::vector<Node> nodes;

		Graph() = delete; // forbid default constructor
	public:
		enum class ErrState { success, attemptToCreateExistingNode, unkCNErr, nodeNotFound, noPossiblePath };
		std::string optimalRoute;
		unsigned __int32 optimalRouteCost;

		// Create new graph with specified name
		Graph(const std::string& n);

		// Connect the specified nodes asymmetrically. If a specified node doesn't exist, it will be created
		ErrState ConnectNodes(const std::string& node1, const std::string& node2, const unsigned __int32 forwardCost, const unsigned __int32 backwardCost);

		// Connect the specified nodes symmetrically. If a specified node doesn't exist, it will be created
		ErrState ConnectNodes(const std::string& node1, const std::string& node2, const unsigned __int32 edgeCost);

		// Create Node for this graph
		ErrState CreateNode(const std::string& name);

		// Output detailed information to the console
		ErrState CoutListNodes();

		// Perform run through of Djikstra's Algorithm to find the optimal route between 2 nodes
		ErrState RunDjikstrasAlgorithm(const std::string& start, const std::string& end);
	};
}
