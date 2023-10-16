#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;

class Node
{
public:
    int data;
    Node* next;
};

class HashTable 
{
private:
    Node* table[TABLE_SIZE];
    
public:
    HashTable() 
	{
        for (int i = 0; i < TABLE_SIZE; i++) 
            table[i] = NULL;
        
    }
    
    int hashFunction(int key) 
	{
        return key % TABLE_SIZE;
    }
    
    void insert(int key)
	{
        int index = hashFunction(key);
        Node* newNode = new Node();
        newNode->data = key;
        newNode->next = NULL;
        
        if (table[index] == NULL)
            table[index] = newNode;
        else 
		{
            Node* temp = table[index];
            while (temp->next != NULL) 
                temp = temp->next;
            
            temp->next = newNode;
        }
    }
    
    void search(int key) 
	{
        int index = hashFunction(key);
        Node* temp = table[index];
        bool found = false;
        
        while (temp != NULL) 
		{
            if (temp->data == key) 
			{
                found = true;
                break;
            }
            temp = temp->next;
        }
        
        if (found) 
            cout << "Key found in hash table\n";
        else 
            cout << "Key not found in hash table\n";
    }
    
    void remove(int key) 
	{
        int index = hashFunction(key);
        Node* temp1 = table[index];
        Node* temp2 = NULL;
        bool found = false;
        
        while (temp1 != NULL)
		{
            if (temp1->data == key) 
			{
                found = true;
                break;
            }
            temp2 = temp1;
            temp1 = temp1->next;
        }
        
        if (found) 
		{
            if (temp2 == NULL) 
                table[index] = temp1->next;
            else 
                temp2->next = temp1->next;
                
            delete temp1;
            cout << "Key deleted from hash table\n";
        }
      	else 
            cout << "Key not found in hash table\n";
        
    }
    
    void display()
	{
        for (int i = 0; i < TABLE_SIZE; i++) 
		{
            Node* temp = table[i];
            cout << "[" << i << "] -> ";
            while (temp != NULL) 
			{
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }
};

int main() 
{
    HashTable ht;
    
    ht.insert(10);
    ht.insert(20);
    ht.insert(15);
    ht.insert(7);
    ht.insert(25);
    cout<<"DISPLAYING : ";
    ht.display();
    
    ht.search(15);
    ht.search(30);
    
    ht.remove(20);
    cout<<"AFTER REMOVING 20 DISPLAYING : ";
    ht.display(); 
    
    return 0;
}

