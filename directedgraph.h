#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <vector>

class BadGraphException {

private:

    std::string message;

public:

    BadGraphException(std::string message) {
        this->message = message;
    }

    std::string getMessage() {
        return message;
    }

};

template <class V>
class DirectedGraph
{
public:

    DirectedGraph() {

    }

    ~DirectedGraph() {
        std::for_each(firstNodes.begin(), firstNodes.end(), [](Node* node) {
           delete node;
        });
    }

    class Node {

        friend class DirectedGraph;

    public:

        Node(DirectedGraph* graph, const V& value) {
            this->value = value;
            this->graph = graph;
        }

        ~Node() {
            std::for_each(outgoingNodes.begin(), outgoingNodes.end(), [](Node* node) {
               delete node;
            });
        }

        V getValue() {
            return this->value;
        }

        DirectedGraph* getGraph() {
            return graph;
        }

        std::vector<Node*> getOutgoingNodes() {
            return this->outgoingNodes;
        }

    private:

        bool hasPredecessors = false;

        DirectedGraph* graph;

        V value;

        std::vector<Node*> outgoingNodes;

        void addOutgoingNode(Node* node) {
            node->hasPredecessors = true;
            outgoingNodes.push_back(node);
        }

        void addOutgoingNodes(std::vector<Node*> nodes) {
            std::for_each(nodes.begin(), nodes.end(), [](Node* node) {
                node->hasPredecessors = true;
            });
            outgoingNodes.insert(outgoingNodes.end(), nodes.begin(), nodes.end());
        }

    };

    void addNode(Node* from, const V& value) throw(BadGraphException) {
        if (from->getGraph() != this) {
            throw BadGraphException("Node 'from' doesn't belong to this graph");
        }

        Node* n = new Node(this, value);
        from->addOutgoingNode(n);
    }

    void linkNodes(Node* nodeFrom, Node* nodeTo) {
        if (nodeFrom->getGraph() != this) {
            throw BadGraphException("Node 'from' doesn't belong to this graph");
        }
        if (nodeTo->getGraph() != this) {
            throw BadGraphException("Node 'to' doesn't belong to this graph");
        }

        if (!nodeFrom->hasPredecessors) {
            firstNodes.erase(std::remove(firstNodes.begin(), firstNodes.end(), nodeFrom), firstNodes.end());
        }

        nodeFrom->addOutgoingNode(nodeTo);
    }

    void addNode(const V& value) {
        Node* n = new Node(this, value);
        this->firstNodes.push_back(n);
    }

    std::vector<Node*> getFirstNodes() {
        return firstNodes;
    }

private:

    std::vector<Node*> firstNodes;

};

#endif // DIRECTEDGRAPH_H
