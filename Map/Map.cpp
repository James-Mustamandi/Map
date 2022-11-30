// Map.cpp 
#include <iostream>
#include <cassert>
#include "Map.h"
#include <string>
using namespace std;



bool Map::empty() const
{
    // The map will only be empty if the head of the list points to nothing (nullptr).
    if (head == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Map::size() const
{
    int count = 0;
   // Make a node p to traverse the list and count each time a node is passed and stop when p is nullptr
    Node* p = head;
    for (p = head; p != nullptr; p = p->next)
    {
        count++;
    }

    return count;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    // To Create a new Node, one must be dynamically created.
    Node* newNode = new Node(key, value);

    // When the list is empty - Make head point to the new Node
    if (head == nullptr)
    {
        head = newNode;
        return true;
    }

    // In the other case where there already exists other nodes, traverse the list until the p gets to the last Node
    Node* p = head;
    while (p->next != nullptr)
    {
        if (p->key == key) // In the case where p points to a Node whose key is the same as the user-defined key, make the function return false as maps cannot have duplicates.
        {
            return false;
        }
        p = p->next;
    }
    p->next = newNode; // By this point, p should be at the last Node, so now the next P value should be the Node that was created. In this case the function returns true
    return true;
}


bool Map::update(const KeyType& key, const ValueType& value)
{
    // To update an already existing key, traverse the list until the end and return false if the user-defined key was not found.
    Node* p = head;
    while (p->next != nullptr)
    {
        if (p->key == key)
        {
            p->value = value;
            return true; // The function returns true if p's key was found in the list and is then updated by the function call. 
        }
        p = p->next;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    // Same method as insert
    //===================================
    Node* newNode = new Node(key, value);
    Node* p = head;
    while (p->next != nullptr)
    {
        if (p->key == key)
        {
            p->value = value;
            return true;
        }
        p = p->next;
    }

    // same method as update
    //====================================
    p = head; // Reassign p to head to restart traversal if needed
    while (p->next != nullptr)
    {
        p = p->next;
    }
    p->next = newNode;
    return true;


}

bool Map::erase(const KeyType& key)
{
    // If the list is empty, then there's nothing to erase so the function will return false.
    if (head == nullptr)
        return false;

    Node* p = head;
    Node* previous = nullptr; // This Node is used to point to Node p while traversing
    while (p->next != nullptr) {
        if (p->key == key) { 
            if (previous != nullptr) { // When p reaches a Node with the desired key to erase, Node previous's next Node will be assigned to whatever p's next Node is.
                delete p; // When p is deleted, Node previous will then keep the list linked by taking p's next Node node prior to deletion.
                return true;
            }
            else { // In the case that the Node to be deleted is the first in the list make head point to the Node that the first Noide pointed to, then delete p and return true.
                head = p->next; 
                delete p;
                return true;
            }
        }
        previous = p; // If p does not point to the end of the list make Node previous point to p and continue list traversal.
        p = p->next;
    }
    return true;
}

bool Map::contains(const KeyType& key) const
{
    // Traverse the list and see if the Node that p points to contains the desired key and return true. Returns false otherwise
    Node* p = head;
    while (p != nullptr)
    {
        if (p->key == key)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    // Traverse the list until p's key is the desired key otherwise return false.
    Node* p = head;
    while (p != nullptr)
    {
        if (p->key == key) 
        {
            value = p->value;  // set's the user's value to p's value and return true.
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    // Function will return false if i > size or i < 0
    if (i < 0 || i > size())
        return false;

    Node* p = head;
    if (i >= 0 && i < size()) // Function will only return true if 0 <= i < size()
    {
        for (int j = 0; j != i; j++)
        {
            p = p->next;             // Node p will traverse as many times as the value of i 
        }
    }
    key = p->key;                   // The key and value will be assigned to p's key and p's value. This will allow simple iterations through the list when needed
    value = p->value;
    return true;
}


void Map::swap(Map& other)
{
    std::swap(head, other.head);    // To swap two seperate Maps, swap the heads of each Map and they will be swapped.
}



bool combine(const Map& m1, const Map& m2, Map& result)
{
    KeyType k;
    ValueType v_m1;
    ValueType v_m2;

    // Case 1: The size of m1 is greater than m2 (or equal)
    if (m1.size() >= m2.size()) 
    {
        Map* tempResult = new Map; // Create a dummy Map and copy all elements from m1 onto it.
        *tempResult = m1;

        for (int i = 0; i < m2.size(); i++)   // This will loop the same amount of times as the size of m2.
        {
            m2.get(i, k, v_m2);                     // Iterate through m2 and check to see if a key exists in m1 that also exists in m2 
            if (tempResult->get(k, v_m1) == false)  // If a does key exist in m1 that exists in m2, insert that key into the the dummy Map
            {
                tempResult->insert(k, v_m2);
            }
            else if (v_m1 != v_m2)  // In the case that the two lists share a key that has a different, then erase that key and return false. 
            {
                // Note that this else if will not execute if the key and value pair is the same, and will only keep a single pair in the final combined map.
                tempResult->erase(k);
                return false;
            }
        }
        result.swap(*tempResult); // After the Dummy Node has been finished, Make result the new combined Map.
        return true;
    }

    // Case 2: m2 is greater than m1 (Same method as Case 1 except this iterates through m1 and not m2)
    if (m1.size() < m2.size())  
    {
        Map* tempResult = new Map;
        *tempResult = m2; // Copies m2 instead of m1 like case 1.
        for (int i = 0; i < m1.size(); i++)
        {
            m1.get(i, k, v_m1);
            if (tempResult->get(k, v_m2) == false)
            {
                tempResult->insert(k, v_m1);
            }
            else if (v_m2 != v_m1)
            {
                tempResult->erase(k);
                return false;
            }
        }
        result.swap(*tempResult);
        return true;
    }

    return false;
}





void subtract(const Map& m1, const Map& m2, Map& result)
{
    KeyType k;
    ValueType v;
    Map tempResult; // Create Dummy Map

    if (m1.size() <= m2.size()) // In the case where m2 is the larger Map (or they are the same size)
    {
        for (int i = 0; i < m1.size(); i++)
        {
            m1.get(i, k, v);                 // Iterate through m1 and if m2 does not have the key, then insert that Node into the dummy Map
            if (m2.contains(k) == false)
            {
                tempResult.insert(k, v);
            }
        }
        result.swap(tempResult); // Make result contain all the Nodes the dummy Map has and empty the dummy Map
    }
    else // In the case where m1 is the larger map...
    {
        Map tempResult(m1); // copy all Nodes from m1 into the dummy Node
        for (int i = 0; i < m2.size(); i++)
        {
            m2.get(i, k, v);    // Iterate through m2 and erase all common Nodes that m1 and m2 share.
            tempResult.erase(k);
        }
        result.swap(tempResult); // Transfer the tempResult map onto result
    }
}

int main()
{
    Map m1;
    Map m2;
    Map* m3 = new Map;
   // Will Swap work when  one of the Maps are empty and the other is not

    m1.insert("a", 11);
    m1.insert("b", 5);
    assert(m1.size() == 2); // m1's size should be 2
    assert(m2.size() == 0); // m2 is empty

    m1.swap(m2);

    assert(m1.size() == 0); // m1 should now be empty
    assert(m2.size() == 2); // m2 should now have 2 Nodes


}


