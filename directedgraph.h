#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <vector>
#include "exception.h"

class NullPointerException;

#define THROW_DG_NULL_POINTER_EXCEPTION(s) throw NullPointerException(s, __LINE__, __FUNCTION__, __TIMESTAMP__)

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

class NullPointerException: public Exception
 {
 public:
   NullPointerException(std::string text, int line, std::string function, std::string timestamp):
     Exception(text, line, function, timestamp)
   {
   }
 };

template <class V>
class DirectedGraph
{
public:

    DirectedGraph() {

    }

    ~DirectedGraph() {
        std::for_each(nodes.begin(), nodes.end(), [](Node* node) {
           delete node;
        });
    }

    class Node;

    class NodeIterator
        {
        public:
          NodeIterator(const NodeIterator& iterator);
          NodeIterator(const size_t position, std::vector<Node*>* vertex);
          NodeIterator& operator ++ ();
          NodeIterator& operator += (const size_t k);
          bool operator == (const NodeIterator& iterator);
          bool operator != (const NodeIterator& iterator);
          Node* operator * ();
        private:
          size_t _position;
          std::vector<Node*>* _vertexP;
          typename std::vector<Node*>::iterator _vertexIterator;

    };

    NodeIterator begin() {
        return NodeIterator(0, &nodes);
    }

    NodeIterator end() {
        return NodeIterator(nodes.size(), &nodes);
    }

    class Node {

        friend class DirectedGraph;

    public:

        Node(DirectedGraph* graph, const V& value) {
            this->value = value;
            this->graph = graph;
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

        DirectedGraph* graph;

        V value;

        std::vector<Node*> outgoingNodes;

        void addOutgoingNode(Node* node) {
            outgoingNodes.push_back(node);
        }

        void addOutgoingNodes(std::vector<Node*> nodes) {
            outgoingNodes.insert(outgoingNodes.end(), nodes.begin(), nodes.end());
        }

    };

    Node* addNode(Node* from, const V& value) throw(BadGraphException) {
        if (from->getGraph() != this) {
            throw BadGraphException("Node 'from' doesn't belong to this graph");
        }

        Node* n = new Node(this, value);
        from->addOutgoingNode(n);

        this->nodes.push_back(n);
        return n;
    }

    void linkNodes(Node* nodeFrom, Node* nodeTo) {
        if (nodeFrom->getGraph() != this) {
            throw BadGraphException("Node 'from' doesn't belong to this graph");
        }
        if (nodeTo->getGraph() != this) {
            throw BadGraphException("Node 'to' doesn't belong to this graph");
        }

        nodeFrom->addOutgoingNode(nodeTo);
    }

    Node* addNode(const V& value) {
        Node* n = new Node(this, value);
        this->nodes.push_back(n);
        return n;
    }

    std::vector<Node*> getNodes() {
        return nodes;
    }

private:

    std::vector<Node*> nodes;

};

template<class V> inline
  DirectedGraph<V>::NodeIterator::NodeIterator(const DirectedGraph<V>::NodeIterator &iterator)
  {
    _vertexP = iterator._vertexP;
    _position = iterator._position;
    _vertexIterator = _vertexP->begin();
    for(size_t i = 0; i < _position; i++) _vertexIterator++;
  }

  template<class V> inline
  DirectedGraph<V>::NodeIterator::NodeIterator(const size_t position, std::vector<Node*> *vertex)
  {
    _position = position;
    _vertexP = vertex;
    _vertexIterator = _vertexP->begin();
    for(size_t i = 0; i < _position; i++) _vertexIterator++;
  }

  template<class V> inline
  typename DirectedGraph<V>::NodeIterator &DirectedGraph<V>::NodeIterator::operator ++()
  {
    if(_vertexP->size() < (_position + 1))
    {
      THROW_DG_NULL_POINTER_EXCEPTION("Null pointer exception, icrement > MultiGraph-vertexes-size!");
      return *this;
    }
    _position++;
    _vertexIterator++;
    return *this;
  }

  template<class V> inline
  typename DirectedGraph<V>::NodeIterator &DirectedGraph<V>::NodeIterator::operator += (const size_t k)
  {
    if(_vertexP->size() < (_position + k))
    {
      THROW_DG_NULL_POINTER_EXCEPTION("Null pointer exception, icrement > MultiGraph-vertexes-size!");
      return *this;
    }
    _position += k;
    for(size_t i = 0; i < k; i++) _vertexIterator++;
    return *this;
  }

  template<class V> inline
  bool DirectedGraph<V>::NodeIterator::operator ==(const DirectedGraph<V>::NodeIterator &iterator)
  {
    return (_vertexIterator == iterator._vertexIterator);
  }

  template<class V> inline
  bool DirectedGraph<V>::NodeIterator::operator !=(const DirectedGraph<V>::NodeIterator &iterator)
  {
    return (_vertexIterator != iterator._vertexIterator);
  }

  template<class V> inline
  typename DirectedGraph<V>::Node *DirectedGraph<V>::NodeIterator::operator *()
  {
    if(_position == _vertexP->size())
    {
      THROW_DG_NULL_POINTER_EXCEPTION("Null pointer exception, Try access to last NULL element!");
      return nullptr;
    }
    return *_vertexIterator;
  }

#endif // DIRECTEDGRAPH_H
