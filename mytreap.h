/*
 * Header file for CS6013 Assignment-2 (Treaps)
 * Declares the node structure, insert, delete, search, split and join methods.
 * Supplied by RV.
 * Instructions to students: Do NOT modify this file. Implement the required functions in a separate file (roll-number-treap.cpp)
 * Please note changes made on 07/10: insert, search, split. 
 * Changes: insert_key now takes the root node passed by reference. So you may update this pointer within the function if you want to change the root of the treap.
 * Insert, Delete, search take float values to search for. The previous version used int, which may cause type conversion warnings.
 * 
 */


#ifndef MYTREAP_H
#define MYTREAP_H

/* treap node struct */


typedef struct tnode{
  tnode *left;
  tnode *right;
  tnode *parent;
  int priority, size;
  float key;
  /* priority : assigned priority of node. lower number implies higher priority, meaning it will be closer to the root in  min-heap property.
  size: number of nodes in subtree with this node as root Needs to be updated with every operation.that modifies the treap.
  key: actual key stored in this node */
} tnode;


/* Dummy function for testing/illustrative purposes.You need not implement this */
tnode* test_func(int k);


/***** IMPLEMENT THE FOLLOWING FUNCTIONS  IN YOUR C++ FILE ***/

/* inserts a node into the treap with root root. Returns pointer to node created
* Note: Change from previous header file: Now the root node is passed by reference. So you may change it in place.
*/
tnode* insert_key(tnode *&root, float k);

/* Deletes node x  from the treap that it is part of. Returns pointer to root of resulting treap */
tnode* delete_node(tnode *root, tnode *x);

/* search for a key k in treap with given root. Returns pointer to node if found,  NULL if not found.*/
tnode* search_key(tnode *root, float k);

/* splits the treap with root r into two treaps, one with keys <key, other with keys >key 
*/
tnode* split_treap(tnode *&root, float k);
/* NOTE: The above passes by REFERENCE the pointer to root. This should point to the root of one of the treaps after the split. The return value points to the other treap's root */


/* Joins two treaps with roots root1, root2 into a single one. Assumes that every key in T_1 < every key in T_2 . Returns pointer to new root. */
tnode* join_treaps(tnode *root1, tnode *root2); 


/* BST functions below */

/* Prints the treap keys in inorder ordering to standard output. Root of treap is root. The keys are printed on a single line separated by spaces, followed by a endline */
void inorder_print(tnode *root);

/* Finds the successor of a node x in the treap that contains x. NULL if no such node exists*/
tnode* successor(tnode *x);

/* Finds the predecessor of a node x in the treap that contains x. NULL if no such node exists*/
tnode* predecessor(tnode *x);

/* returns a pointer to a node in the treap root node root, with the smallest key that is > k. NULL if no such node exists. Note: k may not be in the tree. */
tnode* find_next(tnode* root, float k);

/* returns the number of nodes in the treap rooted at root, with keys less than k */
int num_less_than(tnode *root, float k);





#endif
