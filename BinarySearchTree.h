//ï¿½ Created by Frank M. Carrano and Timothy M. Henry.
//ï¿½ Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 16-4. Altered

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
 
#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include <memory>
#include <vector>
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
// use this->rootPtr to access the BinaryNodeTree rootPtr
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   // Recursively finds where the given node should be placed and
   // inserts it in a leaf at that point.
  shared_ptr<BinaryNode<ItemType>> placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,shared_ptr<BinaryNode<ItemType>> newNode);
   
   // Removes the given target value from the tree while maintaining a
   // binary search tree.
  shared_ptr<BinaryNode<ItemType>> removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                     const ItemType target,
                                     bool& success) override;
   
   // Removes a given node from a tree while maintaining a
   // binary search tree.
   shared_ptr<BinaryNode<ItemType>> removeNode(shared_ptr<BinaryNode<ItemType>> nodePtr);
   
   // Removes the leftmost node in the left subtree of the node
   // pointed to by nodePtr.
   // Sets inorderSuccessor to the value in this node.
   // Returns a pointer to the revised subtree.
   shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                            ItemType& inorderSuccessor);
   
   // Returns a pointer to the node containing the given value,
   // or nullptr if not found.
   std::shared_ptr<BinaryNode<ItemType>> findNode(shared_ptr<BinaryNode<ItemType>> treePtr,
                                  const ItemType& target) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   // inherits from BinaryNodeTree
   
   //------------------------------------------------------------
   // Public Methods Section.
   //------------------------------------------------------------
   void setRootData(const ItemType& newData) override   ;
   bool add(const ItemType& newEntry) override;
   bool remove(const ItemType& anEntry) override;
   ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException) override;
   bool contains(const ItemType& anEntry) const override;
   
}; // end BinarySearchTree

// add function implementations below


#endif
template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData)
{
    this->rootPtr->setItem(newData);
}
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
    shared_ptr<BinaryNode<ItemType>> newNodePtr = make_shared<BinaryNode<ItemType>>(newEntry);
    this->rootPtr = placeNode(this->rootPtr,newNodePtr);
    return true;
}
template<class ItemType>
shared_ptr<BinaryNode<ItemType>>BinarySearchTree<ItemType>::placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,shared_ptr<BinaryNode<ItemType>> newNode)
{
    if(subTreePtr == nullptr)
        subTreePtr = newNode;
    else
    {
        if(subTreePtr->getItem() < newNode->getItem())
        {
            subTreePtr->getRightChildPtr() = placeNode(subTreePtr->getRightChildPtr(),newNode);
            subTreePtr->setRightChildPtr(subTreePtr->getRightChildPtr());
        }
        else if ( subTreePtr->getItem() > newNode->getItem())
        {
            subTreePtr->getLeftChildPtr() = placeNode(subTreePtr->getLeftChildPtr(),newNode);
            subTreePtr->setLeftChildPtr(subTreePtr->getLeftChildPtr());
        }
        else
        {
            subTreePtr = newNode;
        }
    }
    return subTreePtr;
}
