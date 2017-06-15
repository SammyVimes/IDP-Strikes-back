#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <vector>
#include "exception.h"
#include <iomanip>
#include <QtXml>
#include <signal.h>

using namespace std;

class IteratorNullElementException;

#define THROW_DG_ITERATOR_LAST_ELEMENT_EXCEPTION() throw IteratorNullElementException(__LINE__, __FUNCTION__, __TIMESTAMP__)

#define THROW_DG_ALLOCATOR_EXCEPTION() throw AllocatorException(__LINE__, __FUNCTION__, __TIMESTAMP__)

class IteratorNullElementException: public Exception
 {
 public:
   IteratorNullElementException(int line, std::string function, std::string timestamp):
     Exception(line, function, timestamp)
   {
   }
 };

class AllocatorException: public Exception
 {
 public:
   AllocatorException(int line, std::string function, std::string timestamp):
     Exception(line, function, timestamp)
   {
   }
 };


namespace MDP {

template <class V>
class NodesEqualException;
template <class V>
class NodeDoesntBelongException;

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

        inline void setId(int value) {
            this->nodeId = value;
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

public:
    Node* addNode(Node* from, const V& value) throw(NodeDoesntBelongException<V>);

    template <typename V2>
    friend std::ostream& operator<< (std::ostream& os, const DirectedGraph<V2>& dt);

    template <typename V2>
    friend std::istream& operator>> (std::istream& is, DirectedGraph<V2>& dt);

    bool isValid() {
        for (Node* node : nodes) {
            auto out = node->getOutgoingNodes();
            for (auto oNode : out) {
                if (oNode == node) {
                    return false;
                }
            }
        }
        return true;
    }

    void linkNodes(Node* nodeFrom, Node* nodeTo) throw(NodeDoesntBelongException<V>, NodesEqualException<V>);

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

template <class V>
class NodesEqualException {


private:

    typedef typename DirectedGraph<V>::Node* NodePtr;
    NodePtr node;

public:

    NodesEqualException(NodePtr node) {
        this->node = node;
    }


    NodePtr getNode() const
    {
        return node;
    }
};

template <class V>
class NodeDoesntBelongException {


private:

    typedef typename DirectedGraph<V>::Node* NodePtr;
    typedef DirectedGraph<V>* GraphPtr;
    NodePtr node;
    GraphPtr graph;
    GraphPtr actualGraph;


public:

    NodeDoesntBelongException(NodePtr node, GraphPtr graph, GraphPtr actualGraph) {
        this->node = node;
        this->graph = graph;
        this->actualGraph = actualGraph;
    }

    NodePtr getNode() const
    {
        return node;
    }

    GraphPtr getGraph() const
    {
        return graph;
    }

    GraphPtr getActualGraph() const
    {
        return actualGraph;
    }

};


template<class V>
void DirectedGraph<V>::linkNodes(DirectedGraph<V>::Node *nodeFrom, DirectedGraph<V>::Node *nodeTo)  throw(NodeDoesntBelongException<V>, NodesEqualException<V>)
{
    if (nodeFrom == nodeTo) {
        throw NodesEqualException<V>(nodeFrom);
    }
    if (nodeFrom->getGraph() != this) {
        throw NodeDoesntBelongException<V>(nodeFrom, this, nodeFrom->getGraph());
    }
    if (nodeTo->getGraph() != this) {
        throw NodeDoesntBelongException<V>(nodeTo, this, nodeTo->getGraph());
    }

    nodeFrom->addOutgoingNode(nodeTo);
}


template<class V>
typename DirectedGraph<V>::Node *DirectedGraph<V>::addNode(DirectedGraph<V>::Node *from, const V &value) throw(NodeDoesntBelongException<V>)
{
    if (from->getGraph() != this) {
        throw NodeDoesntBelongException<V>(from);
    }

    Node* n = new Node(this, value, ++lastId);
    from->addOutgoingNode(n);

    this->nodes.push_back(n);
    return n;
}


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
//      THROW_DG_ITERATOR_LAST_ELEMENT_EXCEPTION("Null pointer exception, icrement > MultiGraph-vertexes-size!");
      THROW_DG_ITERATOR_LAST_ELEMENT_EXCEPTION();
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
//      THROW_DG_ITERATOR_LAST_ELEMENT_EXCEPTION("Null pointer exception, icrement > MultiGraph-vertexes-size!");
      THROW_DG_ITERATOR_LAST_ELEMENT_EXCEPTION();
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
//      THROW_DG_ITERATOR_LAST_ELEMENT_EXCEPTION("Null pointer exception, Try access to last NULL element!");
      THROW_DG_ITERATOR_LAST_ELEMENT_EXCEPTION();
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
//    THROW_DG_ALLOCATOR_EXCEPTION("can't find returned value in nodes pool!");
    THROW_DG_ALLOCATOR_EXCEPTION();
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

    template<typename V2>
    std::ostream& operator<< (std::ostream& os, const NodeManipulator<V2>& dt)
    {
      typedef typename DirectedGraph<V2>::Node NODE;
      if(!dt.nodePointer) return os;

      auto outgoingNodes = dt.nodePointer->getOutgoingNodes();

      auto node = dt.nodePointer;
      os << QString("<node><id>").append(QString::number(node->getId())).append("</id><connections>").toStdString();

      std::for_each (outgoingNodes.begin(), outgoingNodes.end(), [&node, &os](NODE* i)
      {
          os << "<id>" << std::to_string(i->getId()) << "</id>"  << endl;
      });

      os << "</connections></node>" << endl;

      return os;
    }

    template <typename V2>
    std::ostream& operator<< (std::ostream& os, const DirectedGraph<V2>& dt) {
        typedef typename DirectedGraph<V2>::Node NODE;
        size_t edgesCounter = 0;

        os << "<graph>" << endl;

        os << "<nodes>" << endl;

        std::for_each (dt.nodes.begin(), dt.nodes.end(), [&os, &edgesCounter](NODE* i)
        {
            string x =  QString("<node><id>").append(QString::number(i->getId())).append("</id><value>").toStdString();
            os << x << endl ;
            os << i->getValue();
            os << "</value></node>";
        });

        os << "</nodes>" << endl;

        os << "<outgoing>" << endl;
        std::for_each (dt.nodes.begin(), dt.nodes.end(), [&os](NODE* i)
        {
            os << NodeManipulator<V2>(i);
        });
        os << "</outgoing>" << endl;

        os << "</graph>" << endl;

        return os;
    }



}

#endif // DIRECTEDGRAPH_H
