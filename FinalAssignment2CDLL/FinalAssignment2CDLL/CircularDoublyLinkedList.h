#pragma once
#include <assert.h>
template <class T> //The CDLL is templated so that it is able to accept values of any type
class CircularDoublyLinkedList   //A Circular Doubly Linked List
{
public:
	class Node {   
	public:
		Node(T val, Node * nx = nullptr, Node * prv = nullptr) : value(val), next(nx), prev(prv) { }
		T  value;
		Node * next;
		Node * prev;
	};

	//The class definition for node that exists in the CDLL. Creates Nodes of a linked list that point forward and backward to eachother

public:
	CircularDoublyLinkedList(); //Default constructor that creates an empty linked list
	CircularDoublyLinkedList(const CircularDoublyLinkedList &other); //Copy constructor for if a CDLL is initialized to be a copy of an existing one

	~CircularDoublyLinkedList();    //destructor for a CDLL
	unsigned int size() const;  //returns the value of m_size when it is called
	bool isEmpty() const;  // returns whether m_size is empty(m_size == 0)
	void addHead(T item);  //adds a Node to the front of a linked list. This is called a number of times when creating the linked list
	T removeHead();  //removes the head node from the linked list
					
	T retrieveHead() const;  //retrieves the value of the head node
							
	void addTail(T item); //adds a tail onto the CDLL
	T removeTail(); //removes a tail from the CDLL				
	T retrieveTail() const; //retrieves the value of the tail of the CDLL						
	void add(unsigned int n, T item); //Adds a node into the CDLL at a given spot and with a given value							 
	T replace(unsigned int n, T item); //replaces the value of a node, at a given position, with another given value					   
	T remove(unsigned int n); //removes a node from the CDLL
	T retrieve(unsigned int n) const; //retrieves the value of node at a given point in the CDLL
	void swap(unsigned int n, unsigned int i); //swaps two values in the linked list. I use this function for my spinner in the TopSpin game
	void shiftRight(unsigned int y); //Shifts right a given number of moves. I use this in my TopSpin game 
	void shiftLeft(unsigned int z); //Shifts left a given number of moves. I use this in my TopSpin game 
	bool isSolved(int size) const; //I used this to check if the pieces are in order for the TopSpin game
									
	inline Node* getHead() const { return m_head; } //gets the head node when called


public:
	Node * m_head; //pointer to the head node
	Node * m_tail; //pointer to the tail node
	Node * current; //pointer to a current node that is created in addHead
	unsigned int m_size;

public:
	class Iterator {
	private:
		Node* m_ptr;    
	public:
		Iterator(Node* ptr) { m_ptr = ptr; } //sets m_ptr to the ptr supplied
		void operator++ () { m_ptr = m_ptr->next; } //iterate through the list with ++
		bool operator != (const Iterator& b) { return m_ptr != b.m_ptr; }
		T operator *() { return m_ptr->value; } 
		T getValue() { return m_ptr->value; } //get value pointer is pointing too
		void setValue(T val) { m_ptr->value = val; } //sets value given to the node the m_ptr is currently pointing too
	};

	Iterator begin() { return Iterator(m_head); } //return the beginning node
	Iterator end() { return Iterator(nullptr); } 
};


template <class T>
CircularDoublyLinkedList<T> ::CircularDoublyLinkedList() //default constructor that creates a empty linked list
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{}

template <class T>
CircularDoublyLinkedList<T>::CircularDoublyLinkedList(const CircularDoublyLinkedList<T> &other) {

	if (other.m_size == 0) { //if size is 0
		m_head = nullptr;
		m_tail = nullptr;
		m_size = 0;
	}

	else {
		m_size = other.m_size;
		m_head = new Node(other.m_head->value, nullptr, nullptr);
		if (other.m_tail == nullptr) {
			m_tail = m_head;
		}
		else {
			Node * copyFrom = other.m_head->next;
			Node *nextNode = m_head;

			while (copyFrom != nullptr) {
				nextNode->next = new Node(copyFrom->value);
				copyFrom = copyFrom->next;
				nextNode = nextNode->next;
				copyFrom->prev = nextNode; //to make the list doubly linked
			}
			m_tail = nextNode;
			m_tail->next = m_head; //to make the new list circular again list circular again
			m_head->prev = copyFrom; //Makes the head node point backward to the very last node created, which is pointed at by the copyFrom pointer
		}

	}
}





template <class T>
CircularDoublyLinkedList<T> :: ~CircularDoublyLinkedList() //destructor for the circular doubly linked list which goes through and releases the nodes from memory
{
	Node * here = m_head, *nextNode;
	for (int i = 0; i < m_size; i++) //go through list releasing memory
	{
		nextNode = here->next;
		delete here;
		here = nextNode;
	}
	
}

template <class T>
unsigned int CircularDoublyLinkedList<T> ::size() const
{
	return m_size; //returns ths size of the CDLL
}

template <class T>
bool CircularDoublyLinkedList<T> ::isEmpty() const
{
	return (m_size == 0); //checks to see if the CDLL is empty than returns a bool
}

template <class T>
void CircularDoublyLinkedList<T> ::addHead(T item) //adds a head to the current CDLL, this is the function that builds the CDLL
{
	if (m_size == 0) //if there isn't an original node, it is created here
	{
		m_head = new Node(item, m_head, m_head);
		if (m_tail == nullptr) m_tail = m_head;
		m_size++;
	}


	else { //if there is an existing CDLL, it adds a node the the start of the CDLL

		current = new Node(item, m_head, m_tail);
		m_tail->next = current; //setting the tail nodes previous pointer to make the CDLL circular
		m_head->prev = current; //setting the heads previous node to the newly created current node
		m_head = current; //making the new node the head


		m_size++; //increment the size
	}
}

template <class T>
T CircularDoublyLinkedList<T> ::removeHead() //removes the head node from the CLLL
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "CircularDoublyLinkedList is Empty (in removeHead)"));
	Node * oldNode = m_head;
	m_tail = m_head->prev; //setting the tail to be the node previous to the head 
	T returnVal = m_head->value;
	m_head = m_head->next;
	m_head->prev = m_tail; //correcting the CDLL to be circular again
	if (m_head == nullptr) m_tail = nullptr;
	m_size--; //decrementing the size of the CDLL
	delete oldNode; //releasing the oldNode from memory
	return returnVal;
}

template <class T>
T CircularDoublyLinkedList<T>::retrieveHead() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "CircularDoublyLinkedList is Empty (in retrieveHead)"));
	return m_head->value; //retrieves value from head node
}

template <class T>
void CircularDoublyLinkedList<T> ::addTail(T item) //adds a node to the end of the CDLL
{
	Node * corrector = m_tail;
	if (isEmpty()) addHead(item);
	m_tail = m_head->prev;
	else
	{
		m_tail = m_tail->next = new Node(item);
		m_tail->prev = corrector; //fixing the CDLL to make the tail doubly linked
		m_tail->next = m_head; //seeting the tail nodes next to the head node to make it circular again
		m_size++;
	}
}

template <class T>
T CircularDoublyLinkedList<T> ::removeTail() //removes the tail node from the linked list, it then corrects it to be circular again
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "CircularDoublyLinkedList is Empty (in removeTail)"));
	m_tail = m_head->prev;
	if (m_head == m_tail) return removeHead();
	T returnVal = m_tail->value;
	Node * preTail = m_head;
	while (preTail->next != m_tail)
		preTail = preTail->next;
	preTail->next = nullptr;
	delete m_tail;
	m_tail = preTail;
	m_size--;
	return returnVal;
}

template <class T>
T CircularDoublyLinkedList<T> ::retrieveTail() const
{
	// PRECONDITION: list is not already empty
	assert((!isEmpty() && "CircularDoublyLinkedList is Empty (in retrieveTail)"));
	m_tail = m_head->prev;
	return m_tail->value;
}

template <class T>
void CircularDoublyLinkedList<T> ::add(unsigned int n, T item)
{
	// PRECONDITION: n should be a valid position in the list
	assert(((n >= 1) && (n <= size() + 1) && "CircularDoublyLinkedList index is out of bounds (in add)"));
	if (n == 1) addHead(item);
	else if (n == (size() + 1)) addTail(item);
	else
	{
		Node * here = m_head;
		for (unsigned int k = 1; k < n - 1; k++)
			here = here->next;
		here->next = new Node(item, here->next);
		m_size++;
	}
}

template <class T>
T CircularDoublyLinkedList<T> ::replace(unsigned int n, T item)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "CircularDoublyLinkedList index is out of bounds (in replace)"));
	T returnValue;
	Node * here = m_head;
	for (unsigned int k = 1; k < n; k++)
		here = here->next;
	returnValue = here->value;
	here->value = item;
	return returnValue;
}

template <class T>
T CircularDoublyLinkedList<T> ::remove(unsigned int n)
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "CircularDoublyLinkedList index is out of bounds (in remove)"));
	if (n == 1) return removeHead();
	if (n == size()) return removeTail();

	Node * here = m_head;
	Node * tracker; //tracker is used in this remove function to make sure that the node before and after removed node become linked together
	for (unsigned int k = 1; k < n - 1; k++)
		here = here->next;
	Node * kill = here->next;
	T returnVal = kill->value;
	here->next = kill->next;
	tracker = kill->next; //points to the node after the kill node so the next line of code works
	tracker->prev = here; //takes the tracker node and points it back to the prev node here so that the CDLL is back to being circular
	delete kill;
	m_size--; //decrement the size to account for the change in 
	return returnVal;
}

template <class T>
T CircularDoublyLinkedList<T> ::retrieve(unsigned int n) const //retrieves the value from a certain node in the list
{
	// PRECONDITION: n must be a valid current list position
	assert(((n >= 1) && (n <= size()) && "CircularDoublyLinkedList index is out of bounds (in retrieve)"));
	if (n == 1) return retrieveHead();  
	Node * here = m_head; //shuffle through list until add the desired node
	for (unsigned int k = 1; k < n; k++) here = here->next;
	return here->value;
}

template <class T>
void CircularDoublyLinkedList<T> ::swap(unsigned int n, unsigned int j) //swap function to switch the values of two desired nodes
{
	Node * firstCheck = m_head; //pointers used during the swapping process
	Node * secondCheck = m_head;
	T firstTemp; //variables for temporary value storage
	T secondTemp;
	if (n == 1) //condition for if one of the values passed in the head node
	{
		firstTemp = retrieveHead();
	}

	for (unsigned int i = 1; i < n; i++) //continue through list until node pointer points to the desired node
	{
		firstCheck = firstCheck->next; 
	}
	firstTemp = firstCheck->value; //store value from the node 
	
	for (unsigned int a = 1; a < j; a++)
	{
		secondCheck = secondCheck->next;
	}
	secondTemp = secondCheck->value;

	replace(n, secondTemp); //using the replace function in the CDLL to replace with the new value
	replace(j, firstTemp);
}

template <class T>
void CircularDoublyLinkedList<T> ::shiftLeft(unsigned int y) //used in the TopSpin game, this is how the CDLL is shifted to the Left
{
	Node * leftMover = m_head;
	for (unsigned int i = 0; i < y; i++)
	{
		leftMover = leftMover->next;
	}
	m_head = leftMover; //makes the head node point to the one created and shifted the desired amount of times
	m_tail = m_head->prev;
}

template <class T>
void CircularDoublyLinkedList<T> ::shiftRight(unsigned int z) //this is how the CDLL is shifted to the right 
{
	Node  * rightMover = m_head;
	for (unsigned int i = 0; i < z; i++)
	{
		rightMover = rightMover->prev;
	}
	m_head = rightMover; //makes the head node point to the one created and shifted the desired amount of times
	m_tail = m_head->prev; //since it is a circular doubly linked list, the tail is directly previous of the head
}


template<class T>
bool CircularDoublyLinkedList<T>::isSolved(int size) const //The function used in the CDLL the checks if the pieces in the game TopSpin are in ascending order
{ //it is a constant function to disable it from changing the CDLL

	Node * nodePtr = m_head;
	while (nodePtr->value != 1)
	{
		nodePtr = nodePtr->next;
	}

		for (int i = 1; i < size; i++) //runs through this for as many times as the size of the board
		{
			nodePtr = nodePtr->next;
			if (nodePtr->value != (nodePtr->prev->value + 1))
			{
				return 1; //if the value is not 1 greater than the previous value, return 1 meaning the board is not solved
			}
		}
		return 0; //if the for-loop runs to completion without entering the if statement, this means the board is solved and will return 0
	}


