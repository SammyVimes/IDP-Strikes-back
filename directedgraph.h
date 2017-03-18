#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <vector>

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
    public:

        Node(const V& value) {
            this->value = value;
        }

        ~Node() {
            std::for_each(outgoingNodes.begin(), outgoingNodes.end(), [](Node* node) {
               delete node;
            });
        }

        void addOutgoingNode(Node* node) {
            node->hasPredecessors = true;
            outgoingNodes.push_back(node);
        }

        void addOutgoingNodes(DirectedGraph& graph, std::vector<Node*> nodes) {
            std::for_each(nodes.begin(), nodes.end(), [](Node* node) {
                node->hasPredecessors = true;
            });
            outgoingNodes.insert(outgoingNodes.end(), nodes.begin(), nodes.end());
        }

        V getValue() {
            return this->value;
        }

        std::vector<Node*> getOutgoingNodes() {
            return this->outgoingNodes;
        }

    private:

        bool hasPredecessors = false;

        V value;

        std::vector<Node*> outgoingNodes;

    };

    void addNode(Node* from, const V& value) {
        Node* n = new Node(value);
        from->addOutgoingNode(n);
    }

    void linkNodes(Node* nodeFrom, Node* nodeTo) {
        if (nodeFrom->hasPredecessors) {
            firstNodes.erase(std::remove(firstNodes.begin(), firstNodes.end(), nodeFrom), firstNodes.end());
        }
        nodeFrom->addOutgoingNode(nodeTo);
    }

    void addNode(const V& value) {
        Node* n = new Node(value);
        this->firstNodes.push_back(n);
    }

    std::vector<Node*> getFirstNodes() {
        return firstNodes;
    }

private:

    std::vector<Node*> firstNodes;

};

#endif // DIRECTEDGRAPH_H
