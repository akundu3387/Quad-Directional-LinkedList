#include "graph.h"
Graph::Graph(){
  m_head = nullptr;
  m_dataFile = "";
  buildGraph(m_dataFile);
}

Graph::Graph(string dataFile){// read data from a file and initialize the object                                                                                                                          
  m_dataFile = dataFile;
  m_head = nullptr;
  buildGraph(m_dataFile);
}

Graph::~Graph(){// destructor                                                                                                                                                                             
  Node* curr = m_head;
  Node* next;
  clearResult();
  clearVisited();
  while(curr != nullptr){
    next = curr->m_next;
    delete curr;
    curr = next;
  }
}

void Graph::loadData(){//read data from file and initialize all member variables                                                                                                                          
    int numNodes;
    int node, n, e, s, w;
    ifstream dataFile;
    dataFile.open(m_dataFile);
    if (dataFile.is_open()) {
        dataFile >> numNodes;
        m_numNodes = numNodes;
        for (int i = 0; i < numNodes; i++) {
            dataFile >> node >> n >> e >> s >> w;
            insert(node, n, e, s, w);
        }
    }
    else
        //the following statement provides the reason if a file doesn't open 
        cerr << "Error: " << strerror(errno) << endl;
}

void Graph::insert(int node, int n, int e, int s, int w){
  Node* curr;
  if(findNode(node) == nullptr){//If node is not in the LL yet                                                                                                                                            
    curr = new Node(node);//allocate space and call insertAtHead                                                                                                                                          
    insertAtHead(curr);
  }
  else//If node is already in LL, assign it to curr and update m_varriables                                                                                                                               
    curr = findNode(node);

  //NORTH-----------------------                                                                                                                                                                          
  if(n < 0)//if no value for north(is nullptr)                                                                                                                                                            
    curr->m_north = nullptr;
  else if(n >= 0){//If north has a value                                                                                                                                                                  
    Node* north;
    if(findNode(n) == nullptr){//if Node is not in LL yet                                                                                                                                                 
      north = new Node(n);//allocate new space and add it to LL                                                                                                                                           
      insertAtHead(north);
    }
    else
      north = findNode(n);
    curr->m_north = north;//Assign curr-> north to north pointer                                                                                                                                          
  }

  //EAST---------------------------                                                                                                                                                                       
  if(e < 0)
    curr->m_east = nullptr;//no value                                                                                                                                                                     
  else if(e >= 0){//has value                                                                                                                                                                             
    Node* east;
    if(findNode(e) == nullptr){//not yet in LL                                                                                                                                                            
      east = new Node(e);//Allocate and insert in LL                                                                                                                                                      
      insertAtHead(east);
  }
    else
      east = findNode(e);
    curr->m_east = east;
  }

  //SOUTH------------------------------                                                                                                                                                                   
  if(s < 0)
    curr->m_south = nullptr;
  else if(s >= 0){
    Node* south;
    if(findNode(s) == nullptr){
      south = new Node(s);
      insertAtHead(south);
    }
    else
      south = findNode(s);
    curr->m_south = south;
  }

    //WEST----------------------------------                                                                                                                                                                
  if(w < 0)
    curr->m_west = nullptr;
  else if(w >= 0){
    Node* west;
    if(findNode(w) == nullptr){
      west = new Node(w);
      insertAtHead(west);
    }
    else
      west = findNode(w);
    curr->m_west = west;
  }
}

void Graph::insertAtHead(Node * aNode){//insert a node at the head od list                                                                                                                                
  aNode->m_next = m_head;
  m_head = aNode;
}

Node * Graph::findNode(int nodeValue){//traverses the list and finds a node                                                                                                                               
  Node* curr;
  curr = m_head;
  while(curr != nullptr){
    if(curr->m_value == nodeValue)
      return curr;
    curr = curr->m_next;
  }
  return nullptr;
}

bool Graph::findPath(int start, int end){// find a path from start to end nodes                                                                                                                           
  //cout<<"Find Path public "<<endl;                                                                                                                                                                      
  if(!m_path.empty())
    clearResult();
  clearVisited();
  Node* curr = findNode(start);
  bool TF;
  if(curr != nullptr)
    TF = findPath(curr,end);
  if(TF == false || curr == nullptr){
    //cout<<"TF is false clear result"<<endl;                                                                                                                                                             
    clearResult();
  }
}

bool Graph::findPath(Node* aNode, int end){
  if(aNode->m_value == end){//base case                                                                                                                                                                   
    m_path.push(aNode->m_value);
    return true;
  }
  if(aNode->m_north != nullptr && aNode->m_north->m_visited == false){//if north has value & isnt visited                                                                                                 
    aNode->m_north->m_visited = true;//tag node as visited                                                                                                                                                
    m_path.push(aNode->m_value);//push it on the stack                                                                                                                                                    
    if(findPath(aNode->m_north,end) == true)
      return true;
  }
  if(aNode->m_east != nullptr && aNode->m_east->m_visited == false){
    aNode->m_east->m_visited = true;
    m_path.push(aNode->m_value);
    if(findPath(aNode->m_east,end) == true)
      return true;
  }
  if(aNode->m_south != nullptr && aNode->m_south->m_visited == false){
    aNode->m_south->m_visited = true;
    m_path.push(aNode->m_value);
    if(findPath(aNode->m_south,end) == true)
      return true;
  }
  if(aNode->m_west != nullptr && aNode->m_west->m_visited == false){
    aNode->m_west->m_visited = true;
    m_path.push(aNode->m_value);
    if(findPath(aNode->m_west,end) == true)
      return true;
  }
  else{//if dead end                                                                                                                                                                                      
    if(!m_path.empty()){
      m_path.pop();
      return false;
    }
  }
}
/* 
//Function is giving multiple SEG FAULTs
bool Graph::findPath(Node* aNode, int end){//helper function for recursive calls                                                                                                                          
  if(aNode->m_visited == false){//if newly visited node                                                                                                                                                   
    aNode->m_visited = true;//tag node as visited                                                                                                                                                         
    m_path.push(aNode->m_value);//push nodes value in the stack                                                                                                                                           
    if(aNode->m_value == end)//if node is at destination                                                                                                                                                  
      return true;                                                                                                                                                                                        
    if(aNode->m_north != nullptr && m_north->visited == false)                                                                                                                                            
      findPath(aNode->m_north,end); 
    else if(aNode->m_east != nullptr)//cehck if prev rec is true                                                                                                                                          
      findPath(aNode->m_east,end);                                    //SEG FAULT HERE **FIXED**                                                                                                                                    
    else if(aNode->m_south != nullptr)                                                                                                                                                                    
      findPath(aNode->m_south,end);                                                                                                                                                                       
    else if(aNode->m_west != nullptr)                                                                                                                                                                     
      findPath(aNode->m_west,end);                                                                                                                                                                        
    else{//if no connecting nodes(dead end)                                                                                                                                                               
      //backtrack return false and pop last value                                                                                                                                                         
    }                                                                                                                                                                                                     
  }                                                                                                                                                                                                       
  else{
    //backtrack, make sure to return                                                                                                                                                                      
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}                                                                                                                                                                                                         
*/

void Graph::dump(){// print the path found from start to end nodes                                                                                                                                        
  //cout<<"Dump "<<endl;                                                                                                                                                                                  
  stack<int> temp;
  if(!m_path.empty()){
    while(!m_path.empty()){//getting seg fault here for 4->0                                                                                                                                              
      temp.push(m_path.top());
      m_path.pop();
    }
    while(temp.empty() == false){
      int t = temp.top();
      cout << t << " => ";
      temp.pop();
      m_path.push(t);
    }
  }
  cout<<"END "<<endl;
}


void Graph::clearResult(){//clear the stack storing the result, i.e. path                                                                                                                                 
  //cout<<"Clear resuilt"<<endl;                                                                                                                                                                          
  if(!m_path.empty()){
    while(!m_path.empty())
      m_path.pop();
  }
}

void Graph::clearVisited(){//reset visited flag of all nodes                                                                           
  //cout<<"Clear visited"<<endl;                                                                                                       
  Node *curr = m_head;
  while(curr != nullptr){
    if(curr->m_visited == true)
      curr->m_visited = false;
    curr = curr->m_next;
  }
}

/*                                                                                                                                     
void Graph::clearVisited(){//reset visited flag of all nodes                                                                           
  cout<<"Clear visited"<<endl;                                                                                                         
  Node *curr = m_head;                                                                                                                 
  while(curr != nullptr){                                                                                                              
    if(curr->m_visited == true)                                                                                                        
      curr->m_visited = false;                                                                                                         
    if(curr->m_north->m_visited == true)                                                                                               
      curr->m_north->m_visited = false;                                                                                                
    if(curr->m_east->m_visited == true)                                                                                                
      curr->m_east->m_visited = false;                                                                                                 
    if(curr->m_south->m_visited == true)                                                                                               
      curr->m_south->m_visited = false;                                                                                                
    if(curr->m_west->m_visited == true)                                                                                                
      curr->m_west->m_visited = false;                                                                                                 
    curr = curr->m_next;                                                                                                               
  }                                                                                                                                    
}                                                                                                                                      
*/

void Graph::buildGraph(string file){// construct a new graph from the file                                                             
  clearGraph();
  if(m_dataFile != ""){
    loadData();
  }
  //loadData();                                                                                                                        
}

void Graph::clearGraph(){//delete all memory and reset all member variables                                                            
  clearResult();
  clearVisited();
  Node *curr = m_head;
  Node *next;
  while(curr != nullptr){
    curr->m_north = nullptr;
    curr->m_east = nullptr;
    curr->m_south = nullptr;
    curr->m_west = nullptr;
    next = curr->m_next;
    curr = nullptr;
    curr = next;
  }
  m_head = nullptr;
}

const Graph & Graph::operator=(const Graph & rhs){// overloaded assignment operator                                                    
  if(&rhs != this){
    Node* curr = m_head;//deallocation of memory                                                                                       
    Node* next;
    clearResult();
    clearVisited();
    while(curr != nullptr){
      next = curr->m_next;
      delete curr;
      curr = next;
    }
    curr = nullptr;
    if(rhs.m_head == nullptr)
      m_head = nullptr;
    else{
      m_head = rhs.m_head;
      Node* temp = rhs.m_head;
    }
  }
  return *this;
}

bool Graph::empty() const               // is the list empty?                                                                          
    { return m_head == nullptr; }
