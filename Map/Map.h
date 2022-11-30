#pragma once
#include <iostream>
#include <string>
#include <sstream>

using KeyType = std::string;
using ValueType = double;
using namespace std;



class Map
{
private:

    struct Node
    {
        KeyType key;
        ValueType value;
        Node* next;

        Node(KeyType keyEntered, ValueType valueEntered)
        {
            key = keyEntered;
            value = valueEntered;
            next = nullptr;
        }
    };

    Node* head;

public:
    //Constructors
    Map()
    {
        head = nullptr;
    }
    // Copy Constructor
    Map(const Map& rhs, KeyType key, ValueType value)
    {
        head = nullptr;
        Node* p_m1 = nullptr;
        Node* p_m2 = rhs.head;
        while (p_m2 != nullptr)
        {
            Node* newNode = new Node(key, value);
            newNode->next = nullptr;
            newNode->value = p_m2->value;
            if (p_m1 != nullptr)
            {
                p_m2->next = newNode;
            }
            if (head == nullptr)
            {
                head = newNode;
            }
            p_m1 = newNode;
            p_m2 = p_m2->next;
        }
    }

    // Assignment Operator
    Map& operator=(const Map& rhs)
    {
        if (this != &rhs)
        {
            Map temp = rhs;
            swap(temp);
        }
        return *this;
    }

    // Destructor
    ~Map()
    {
        Node* p = head;
        Node* previous = nullptr;
        while (p != nullptr) {
            previous = p;
            p = p->next;
            delete previous;
        }
    }


    // User Defined Methods
    bool empty() const;   
     int size() const;
    bool insert(const KeyType& key, const ValueType& value); 
    bool update(const KeyType& key, const ValueType& value); 
    bool insertOrUpdate(const KeyType& key, const ValueType& value); 
    bool erase(const KeyType& key);  
    bool contains(const KeyType& key) const; 
    bool get(const KeyType& key, ValueType& value) const; 
    bool get(int i, KeyType& key, ValueType& value) const; 
    void swap(Map& other); 
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);





