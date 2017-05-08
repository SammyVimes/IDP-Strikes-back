#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <vector>
#include "exception.h"
#include <iomanip>

class NullPointerException;

#define THROW_DG_NULL_POINTER_EXCEPTION(s) throw NullPointerException(s, __LINE__, __FUNCTION__, __TIMESTAMP__)

#define THROW_DG_ALLOCATOR_EXCEPTION(s) throw AllocatorException(s, __LINE__, __FUNCTION__, __TIMESTAMP__)

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

class AllocatorException: public Exception
 {
 public:
   AllocatorException(std::string text, int line, std::string function, std::string timestamp):
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

        Node(DirectedGraph* graph, const V& value, int id) {
            this->value = value;
            this->graph = graph;
            this->nodeId = id;
        }

        V getValue() {
            return this->value;
        }

        inline int getId() {
            return this->nodeId;
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

        int nodeId;

        std::vector<Node*> outgoingNodes;

        void addOutgoingNode(Node* node) {
            outgoingNodes.push_back(node);
        }

        void addOutgoingNodes(std::vector<Node*> nodes) {
            outgoingNodes.insert(outgoingNodes.end(), nodes.begin(), nodes.end());
        }

    };

    private:
        class Allocator
        {
        public:
          Allocator(){}
          virtual ~Allocator();

          Node* getNode(DirectedGraph* graph, const V& value, int id);

          void returnNode(Node* vertex);

          void returnAll();

        private:
          std::list<Node*> nodesPool;
        };

    Allocator alloc;

    Node* addNode(Node* from, const V& value) throw(BadGraphException) {
        if (from->getGraph() != this) {
            throw BadGraphException("Node 'from' doesn't belong to this graph");
        }

        Node* n = new Node(this, value, ++lastId);
        from->addOutgoingNode(n);

        this->nodes.push_back(n);
        return n;
    }

    template <typename V2>
    friend std::ostream& operator<< (std::ostream& os, const DirectedGraph<V2>& dt);

    template <typename V2>
    friend std::istream& operator>> (std::istream& is, DirectedGraph<V2>& dt);

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
        Node* n = new Node(this, value, ++lastId);
        this->nodes.push_back(n);
        return n;
    }

    std::vector<Node*> getNodes() {
        return nodes;
    }

private:

    std::vector<Node*> nodes;

    int lastId = 0;

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

template<typename V> inline
DirectedGraph<V>::Allocator::~Allocator()
{
  returnAll();
}

template<typename V> inline
typename DirectedGraph<V>::Node *DirectedGraph<V>::Allocator::getNode(DirectedGraph* graph, const V& value, int id)
{
  DirectedGraph<V>::Node* newNode = new DirectedGraph<V>::Node(graph, value, id);
  nodesPool.push_back(newNode);
  return newNode;
}

template<typename V> inline
void DirectedGraph<V>::Allocator::returnNode(DirectedGraph<V>::Node *node)
{
  auto pos = std::find(nodesPool.begin(), nodesPool.end(), node);

  if(pos == nodesPool.end())
  {
    THROW_DG_ALLOCATOR_EXCEPTION("can't find returned value in nodes pool!");
    return;
  }

  nodesPool.erase(pos);
  delete node;
}

template<typename V> inline
void DirectedGraph<V>::Allocator::returnAll()
{
  std::for_each(nodesPool.begin(), nodesPool.end(),
                [](DirectedGraph<V>::Node* i) {delete i;});

  nodesPool.clear();
}


template<typename V>
class NodeManipulator
  {

  typedef typename DirectedGraph<V>::Node* NodePtr;

  public:
    NodeManipulator(NodePtr val){
        nodePointer = val;
    }

    template <typename V2>
    friend std::ostream& operator<< (std::ostream& os, const NodeManipulator<V2>& dt);

  private:
    NodePtr nodePointer;
  };

template<typename V, typename E>
std::ostream& operator<< (std::ostream& os, const NodeManipulator<V>& dt)
{
  if(!dt.nodePointer) return os;

  dt.nodePointer->
  os << dt.nodePointer->getSource()->getData() << "\n"
     << dt.nodePointer->getDestenation()->getData() << "\n"
     << dt.nodePointer->getValue() << "\n";
  return os;
}


template <typename V2>
std::ostream& operator<< (std::ostream& os, const DirectedGraph<V2>& dt) {
    typedef typename DirectedGraph<V2>::Node NODE;
    os << dt.nodes.size() << "\n";
    size_t edgesCounter = 0;
    std::for_each (dt.nodes.begin(), dt.nodes.end(), [&os, &edgesCounter](NODE* i)
    {
             DirectedGraph<V2>::Node* n = i;
             os << i->getValue() << "\n";
             edgesCounter += i->getOutgoingNodes().size();
    });

    os << edgesCounter << "\n";

    std::for_each (dt.nodes.begin(), dt.nodes.end(), [&os](NODE* i)
    {
      auto outgoingNodes = i->getOutgoingNodes();

      std::for_each(outgoingNodes.begin(), outgoingNodes.end(), [&os](NODE* j)
      {
        os << NodeManipulator<V2>(j);
      });
    });

    return os;
}

template <typename V2>
friend std::istream& operator>> (std::istream& is, DirectedGraph<V2>& dt) {

}

#endif // DIRECTEDGRAPH_H
