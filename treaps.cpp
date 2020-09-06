#include "mytreap.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <bits/stdc++.h>
#include<cstdlib>
#include<ctime>

using namespace std;



/****************** *******************************************/
 /*These functions are used to display key, priority, parent and size of the nodes in the treaps */

void inOrder(tnode *root)
{
        if(root)
        {
                inOrder(root->left);
                if(root->parent==NULL) printf("%0.0f\t%d\t\t%0.0f\t%d\n",root->key,root->priority,root->key,root->size);
                else printf("%0.0f\t%d\t\t%0.0f\t%d\n",root->key,root->priority,root->parent->key,root->size);
                inOrder(root->right);
        }
}
void preOrder(tnode *root){
        if(root)
        {
                if(root->parent==NULL) printf("%0.0f\t%d\t\t%0.0f\t%d\n",root->key,root->priority,root->key,root->size);
                else printf("%0.0f\t%d\t\t%0.0f\t%d\n",root->key,root->priority,root->parent->key,root->size);
                preOrder(root->left);
                preOrder(root->right);
        }
}



/***********************************/














/*****************************************************************/

/*This makeParent function is used in split_treaps. This function takes one pointer as argument. In this function we traverse downwards from given node pointer
we recursively make call to this function to assign exact parent pointers of the nodes.

*/
void makeParent(tnode *root)
{
    if(root!=NULL){
        if(root->left!=NULL) root->left->parent=root;
        if(root->right!=NULL) root->right->parent=root;
        makeParent(root->left);
        makeParent(root->right);
    }
}




/*
	This countNodes function takes one pointer as argument. This function will recursively  count the number of nodes of the given node. 
	We count nodes from leaf nodes to root node recursively.
*/

int countNodes(tnode *root)
{
    if(root==NULL) return 0;
    else
    {

      root->size=1+countNodes(root->left)+countNodes(root->right);
      return root->size;
    }
}




/*
    rightRotation function takes tnode pointer (over which right rotations has to taken) as argument. This function performs right rotation on given pointer node. and It also responsible to change size attribute value of nodes that are involving in rotations. After right rotation this function will return pointer that points to the node which is free-from violation of treap property.
    We consider root node's left child is higher priority than the root. So we have to rotate over root node. We have done approriate changes in pointers that gets reflected while doing pointers and also make changes in size attribute of everynode that included in rotations.
*/

tnode *rightRotate(tnode *root)
{
    if(root==NULL) return root; /* If the root node is NULL then nothing to do with this rotation function*/
    tnode *x = root->left,  *y = x->right;
    tnode *p=root->parent;
    x->right = root;
    root->left = y;
    x->parent=p;
    root->parent=x;

    if(root->left!=NULL) root->left->parent=root;


    /*To get clear idea see the following diagram and relate it to above code.*/

    /*     parent                                       parent
             |                                             |
            root    After right rotation                   X
            /   \    on root                              / \
           X     q  =========================>           z  root
          / \                                                / \
         z   Y                                              Y   q

         So, After rotation size attribute of 'X' and 'root' nodes has to be changed.
    */


    /*Below code takes care of size attribute changes*/

    int nRoot=(root->size)-(x->size); /* The root pointer's node size  will be decreased by it's left child node's size i.e x pointer node.*/
    int xRight=0;
    if(y!=NULL) /* If x->right pointer is null we don't need to find size of that node */
    {
        xRight=y->size;
    }
    //int rootRight=0;
    int xLeft=0;
    if(x->left!=NULL) xLeft=x->left->size;/* Here we are finding x->left node size attribute */
    root->size=nRoot+xRight; /* Here we are updating root node's size attribute */
    x->size=1+xLeft+root->size; /* Here value of x node's size will be updated; */

    return x; /* x pointer points to node which is not violating the propery of treap. See above diagram  */
}





/*
    leftRotation function takes tnode pointer (over which left rotations has to taken) as argument. This function performs left rotation on given pointer node. and It also responsible to change size attribute value of nodes that are involving in rotations. After left rotation this function will return pointer that points to the node which is free-from violation of treap property.
    We consider root node's right child is higher priority than the root. So we have to rotate over root node. We have done approriate changes in pointers that gets reflected while doing pointers and also make changes in size attribute of everynode that included in rotations.
*/


tnode *leftRotate(tnode *root)
{
    if(root==NULL) return root; /* If the root node is NULL then nothing to do with this rotation function*/
    tnode *y = root->right, *x = y->left;
    tnode *p=root->parent;
    y->left = root;
    root->right = x;
    y->parent=p;
    root->parent=y;
    if(root->right!=NULL) root->right->parent=root;

    /*To get clear idea see the following diagram and relate it to above code.*/

    /*     parent                                        parent
             |                                              |
            root    After left rotation                     Y
            /  \    on root                               /   \
           z    Y  =========================>           root   q
               / \                                       / \
              X   q                                     z   X

         So, After rotation size attribute of 'X' and 'root' nodes has to be changed.
    */


    /*Below code takes care of size attribute changes*/

    int xOwn=(root->size)-(y->size); /*xOwn variable stores the number of nodes after decreasing it's right child's number of nodes */
    int yLeft=0;
    if(x!=NULL) /*It is Y's left child. It is appended as root's right child. So if x is not null we have to add x->size value with root node size attribute*/
    {
          yLeft=x->size;
    }
    root->size=xOwn+yLeft; /* Updating root size attribute with new child x and old child z*/
    int yRight=0;

    /* yRight variable stores number of nodes in q node. If q pointer is null yRight=0*/
    if(y->right!=NULL) yRight=y->right->size;
    y->size=root->size+yRight+1; /*Updating y->size value here*/

    return y; /* Returning the pointer to the node*/
}





/* This insert function is used as utility function in insert_key(tnode *&root, int key) function.
   This function takes two pointers as arguements. One is pointing to root and another one is pointing to the node which has to be inserted into the treap.
   This function will be returning the root node which is pointing to the newly updated root after left and right rotations (if occurs).
   This function will use two more utility functions called leftRotation() and rightRotation() which will help us to over come the violation of treap property


*/
tnode *insert(tnode *root,tnode *node)
{

        if(!root) return node; /* If root node is NULL we are returning the *node directly*/

        if(node->key<root->key) /* If the key (i.e node->key) to be inserted is less than root->key, then we move to the left side of the root node in the treap and try to insert the node into the appropriate location in the leaves.*/
                {


                        root->left=insert(root->left,node); /* Recursive call to find location of node to insert*/
                        root->left->parent=root; /* Making the parent node updation for node*/
                        root->size+=1;/* Increasing size attribute*/

                        /* This condition check for the priority violation of the node. If any violation, then it calls rightRotate function on root to overcome that violations*/
                        if(root->left->priority<root->priority)
                        {
                                root=rightRotate(root); /*Calling utility function to do right rotation over root*/

                        }

                }
        else
                {
                      /*    If the key to be isnerted is greater than or equal to, then we move right side of the root node in the treap.
                            We recursively make call to find currect location for node and insert it
                        */
                        root->right=insert(root->right,node); /* Recursive call to find exact location of the node to be inserted*/
                        root->right->parent=root; /* Parent updation here*/
                        root->size+=1; /*Size updation here*/

                        /*This condition check for the priority violation of the node. If any violation, then it calls leftRotation function on root to overcome that violations*/
                        if(root->right->priority<root->priority)
                        {
                                root=leftRotate(root); /*Calling utility function to do right rotation over root*/

                        }


                }

        return root;
}






/*  This is our defined insert_key function. This function takes tnode pointer and key as arguements.
    In this function we are creating a node called temp and assigning it's key value to given 'key', size to '1', and
    priority to some random priority. We are making it's left , right and parent pointers to NULL.


*/
tnode *insert_key(tnode *&root,float k){

        /* Creating new node to insert*/
        tnode *temp=new tnode();
        temp->left=NULL;
        temp->right=NULL;
        temp->parent=NULL;
        temp->size=1;
        temp->key=k;
        //srand(time(0));
        temp->priority=rand()%100111+rand()%100; /*This is random priority*/
      

        if(!root){ /* If the root node is null then first created node will be inserted and it will be root node*/

                root=temp;
                return temp;
        }
        else{
                /* If root node is not null i.e some nodes are inserted into treap. We just make use of insert utility function here.
                   insert function will make insertion and returns the node to root of the treap.

                */
                tnode *dup=root;

                root=insert(dup,temp); /* Calling insert() utility function and assigning new root node to the root pointer*/

        }
        return temp; /* Asked to return pointer points to newly inserted node */
}




/* This function deletes node x  from the treap that it is part of. Returns pointer to root of resulting treap.
   This function takes two pointers as arguements , one pointer points to root of the treap and other will point to the node to deleted
 */
tnode* delete_node(tnode *root, tnode *x)
{
        if(root==NULL||x==NULL) return root; /* The root or node x is NULL*/


        if(x->key<root->key) /* Checking the x node key with root node key , If x node's key is lessthan the root key then recursively call delete_node function by travelling towards left child of the root node*/
                root->left=delete_node(root->left,x);
                
                
        else if(x->key>root->key)/* Checking the x node key with root node key , If x node's key is greater than the root key then recursively call delete_node function by travelling towards right child of the root node*/
                root->right=delete_node(root->right,x);
                
                

        else /*If root node's key is equal to the x node's key then we have to check for all possible cases to delete that node*/
        {
                if(root->left==NULL&&root->right==NULL) /* If deleted node has no children then directly delete that node*/
                {
                        if(root->parent!=NULL)root->parent->size-=1; /* After deleting node we have to decrease size of it's parent node*/
                        delete(root);
                        root=NULL;
                }
                else if(root->left==NULL&&root->right!=NULL) /*If the node is having only right child and no left child. We add root's right child to it's parent by deleting root*/
                {
                                tnode *parent=root->parent;
                                root->right->parent=parent;
                                tnode *temp=root->right;
                                if(parent!=NULL) parent->size-=1; /*Decreasing the size of root's parent node by 1*/
                                delete(root);
                                root=temp;
                }
               else if(root->left!=NULL&&root->right==NULL)/*If the node is having only left child and no right child. We add root's left child to it's parent by deleting root*/
                {
                                tnode *parent=root->parent;
                                root->left->parent=parent;
                                tnode *temp=root->left;
                                if(parent!=NULL) parent->size-=1;/*Decreasing the size of root's parent node by 1*/
                                delete(root);
                                root=temp;
                }
                else/* If the node has both left and right children. We check priority of root's left adn right children to make replace with root node.
                    */
                {
                        if(root->left->priority > root->right->priority) /*If root's right child priority is lessthan the left child then we perform left rotation on root and then recursively call delete_node on root->left node
                                                                        */
                        {
                                if(root->parent!=NULL) root->parent->size-=1;/* Decreasing parent's node size by 1*/
                                root=leftRotate(root);
                                root->left=delete_node(root->left, x); /* Recursive call on root->left node*/
                        }
                        else /*If root's left child priority is lessthan the right child then we perform right rotation on root and then recursively call delete_node on root->right node*/
                        {
                                if(root->parent!=NULL) root->parent->size-=1; /* Decreasing parent's size by 1*/
                                root = rightRotate(root);
                                root->right = delete_node(root->right, x); /* Recursive call on root->right*/
                        }
                }
        }
        countNodes(root);/*This function will make count of nodes and updates size attribute of each node*/
        return root; /* Returning the new root node after deleting the given node*/
}





/* search for a key k in treap with given root. Returns pointer to node if found,  NULL if not found.
*/
tnode* search_key(tnode *root, float k){

        if(!root||root->key==k) return root; /*If the root node is NULL or root's key is equal to given key then we are returning root node*/
        if(k<root->key) return search_key(root->left,k);/* If the given key is less than the root node's key then we recursively call search key on left subtree of root node by calling search_key(root->left, k). */
        return search_key(root->right,k);/*If the given key is greater thar or equals to root then we recursively call on right subtree of the root by calling search_key(root->right,k).*/
}







/* This function is called in Split_treap() function. This function takes four arguements. THis function recursively split the treap into two treaps and stores left subtree in pointer l, which will have keys < given key. and other subtree pointer r will points to other subtree,
	This function logic will slit the treap in such a way that one treap will consists of keys that are less than the given key and other treap will consist of keys that are 
	greater or equal to the given key. So, We will be deleting the node that equals to the given key in SPLIT_TREAP() function.

	This function will take four arguments. one is pointer to the root node of the treap , second one is key,based on which we have to split the treap. 
	Other two arguments are references to the tnode pointer which will store splitted treaps.
*/
void split(tnode * root, float key, tnode *&l,tnode *&r ){
    if(!root)
        l =  r = NULL;
    else if(key < root->key) /* If the given key is lessthan root key*/
    {
        r = root;
        split(root->left,key,l,root->left);
    }
    else /* If the given key is greater than or equals to given key*/
    {
        l =root;
        split(root->right,key,root->right,r);
    }

    /*
        This function recursively checks keys of every node and make split accordingly
    */
}




/* Splits the treap with root r into two treaps, one with keys <key, other with keys >key
    This function returns the subtree root with keys < given key k.
    This function takes help from split().
*/
tnode* split_treap(tnode *&root, float k)
{
        if(root==NULL) return NULL; /*If the given root is NULL then we perform no action*/
        tnode *x=root;
        tnode *left=NULL,*right=NULL;
        split(x,k,left,right); /* This function makes treap split*/

        /*Above split function makes treap slit based on key. One subtree will have keys less than given key and other tree will have keys with greater than or equals to given key*/

        
       /* As mentioned above , right subtree may contain key which equals to given key. So we have to delete it using delete_node()*/
       if(right){
       
        right->parent=NULL;
        tnode *t=new tnode();
        t->key=k;
        right=delete_node(right,t); /* Deleting the node which equals to the given key */
        makeParent(right);/* This function will make sure the parent nodes of the nodes in the treap*/
       }

       /* There may be chance to the given key that present if left subtreap. So we delete that node using delete_node() function.*/
       if(left){
       
        left->parent=NULL;
        tnode *t=new tnode();
        t->key=k;
        left=delete_node(left,t); /* Deleting the node which equals to the given key */
        makeParent(left);/* This function will make sure the parent nodes of the nodes in the treap*/
       }


       /* Below two lines of code will calculate node's size and assigns the value to size attribute.*/
       if(right!=NULL) countNodes(right); /* Calculates size attribute of right subtreap*/
       if(left!=NULL) countNodes(left);/* Calculates size attribute of left subtreap*/

       root=right; /*Points to T2 i.e >key */

        return left;/* Points to T1 */
}





/* Joins two treaps with roots root1, root2 into a single one. We assumeds that every key in T_1 < every key in T_2 . This function returns pointer to new root.
    The basic idea is that we created a new node (called temp) and we have assigned random key=-100 and priority=-1. We append root1 pointer as left chilf of temp
    node and assigned root2 pointer as right child of temp node. After this we are deleting the temp node. So that the resulting trep will be joined treap.
 */
tnode* join_treaps(tnode *root1, tnode *root2)
{			
            	/* Below two lines of code is used to check whether given root1 and root2 are NULL or not. If one of then is NULL we return other.*/    
                if(root1==NULL) return root2;
                if(root2==NULL) return root1;


                /* Below few lines shows creation of new node. This node will be used to create new treap with root1 as left child and root2 as right child*/
                tnode *temp=new tnode();
                temp->left=root1; /*Making root1 as left child*/
                temp->right=root2;/* Making root2 as right child*/
                temp->parent=NULL;
                temp->size=0;
                temp->key=-100;
                temp->priority=-1;
                root1->parent=temp; /*Making root1 parent is temp*/
                root2->parent=temp; /*Making root2 parent is temp*/

                /* We have to assign size for temp node. We are calculating the root1 and root2 node's size and assigning to temp node.*/
                int tCount=0,tCount2=0;
                if(root1!=NULL) tCount=root1->size;
                if(root2!=NULL) tCount2=root2->size;
                temp->size=1+tCount2+tCount;


                temp=delete_node(temp,temp); /* We are deleting the node which we are created for our sake. After deleting the temp node the resulting treap will be our joined treap.*/

             

                return temp; /* Returning the node pointer which points to root node of joined treap*/

}






/* This function prints the inorder traversal of the treap given by root pointer.
    This function follows these recusive three steps.
    1. Traverse to the left of the treap.
    2. Print the node
    3. Travers to the right of the treap
*/

void inorder_print(tnode *root)
{
        if(root) /* If the root is not null then only we traverse through the treap*/
        {
                inorder_print(root->left); /* Traversing towards left of the treap*/
                cout<<root->key<<" "; /* Printing the node's key*/
                inorder_print(root->right);/* Traversing towards right of the treap*/
        }

}




/* This function is used to find minimum key in the subtreap given by root pointer. We go to left side of treap until we find minimum in the treap.

*/
tnode *findMinRightSubTreap(tnode *root)
{
        if(root==NULL) return root;
        while(root->left!=NULL) root=root->left;
        return root;
}

/* This function is used to find maximum key in the subtreap given by root pointer. We go to right side of treap until we find maximum in the treap given by the pointer root.

*/
tnode *findMaxLeftSubTreap(tnode *root)
{
        if(root==NULL) return root;
        while(root->right!=NULL) root=root->right;
        return root;
}




/* This function will take one pointer as argument and returns the pointer to the successor of node if exist or NULL if successor is not exist.
*/
tnode* successor(tnode *root){



        if(root==NULL) return NULL;

        /* Successor of a node is always resides in right subtreap of the node( If exists and if right link isnot NULL).Here , we are checking whether the right link is not NULL or not. If root's right link is not NULL we are
            finding the minimum element in the right subtreap. We are using a function called findMinRightSubTree() to find the minimum element in right subtreap.
            */
        if(root->right!=NULL) return findMinRightSubTreap(root->right); /*Finding the minimmum element in right subtreap and returning that pointer*/

        /*If right->right is null then we follow below steps.*/
        int key=root->key;
        tnode *temp;
        while(root->parent!=NULL) root=root->parent; /*Finding the root of the treap*/
        temp=root;
       tnode* successor = NULL;


       /*
			Here in below code, we iteratively try to move from root node to down to the leaf and try to find the successor fo the given node.
			From root we go down by using binary search and make appropriate pointers assignment to find the successor.
       */

	while (1)
	{

		if (key < temp->key) /* If given key is less than the temp pointer then we move towards left side of the treap and  we store that temp node as successor and we move on.*/
		{

			successor = temp;
			temp = temp->left;
		}


		else if (key > temp->key) /*If the given key is greater than the temp node then we simply move towards right side of the treap.*/
		{
			temp = temp->right;
		}


		else /*If the given key is equals to the temp key then we check for minimum element in the right subtreap of the temp node.*/
		{
			if (temp->right)
				successor = findMinRightSubTreap(temp->right); /* If minimum element is find in right subtreap of temp then seccessor variable will beassigned with that element's address otherwise it will be assigned with NULL*/
			break;
		}


		if (!temp) 
			return NULL;
	}

	return successor; /* Returning the pointer to the successor*/
}






/* This function will take one pointer as argument and returns the pointer to the predecessor of node if exist or NULL if predessor is not exist.
*/

tnode* predecessor(tnode *root){


        if(root==NULL) return NULL; /*If the root node is NULL we do nothing*/


         /* Predecessor of a node is always resides in Left subtreap of the node( If exists).Here , we are checking whether the left link is not NULL or not. If root's left link is not NULL we are
            finding the maximum element in the left subtreap. We are using a function called findMaxleftSubTree() to find the maximu element in left subtreap.
            */
        if(root->left!=NULL) return findMaxLeftSubTreap(root->left);/*Finding the maximum element in left subtreap and returning that pointer*/

        /*If the root->left is NULL*/

        int key=root->key;
        tnode *temp;
        while(root->parent!=NULL) root=root->parent; /* Finding the root node of the treap*/
        temp=root;


       tnode *predecessor = NULL;


       /*
			Here in below code, we iteratively try to move from root node to down to the leaf and try to find the predecessor fo the given node.
			From root we go down by using binary search and make appropriate pointers assignment to find the predecessor.
       */

  while (1)
	{

		if (key >temp->key) /* If given key is greater than the temp pointer then we move towards right side of the treap and  we store that temp node as predecessor and we move on.*/
		{

			predecessor = temp;
			temp = temp->right;
		}


		else if (key <temp->key)/*If the given key is less than the temp node then we simply move towards left side of the treap.*/
		{
			temp = temp->left;
		}


		else /*If the given key is equals to the temp key then we check for max element in the left subtreap of the temp node.*/
		{
			if (temp->left)
				predecessor = findMaxLeftSubTreap(temp->left); /*This fu ction will return maximum element the treap pointer with temp->left*/
			break;
		}


		if (!temp)
			return NULL;
	}

	return predecessor;/* Returning the pointer to the predecessor */



}






/* This function returns a pointer to a node in the treap, with the smallest key that is > k. NULL if no such node exists.
    In this function we are making  binary search kind of technique to get required node pointer.
 */

tnode* find_next(tnode *root,float k)
{
       
        if(root==NULL) return root;

        tnode *dup=root; /*Assigning root pointer to dup */
        tnode *parent=NULL; /*This pointer will be usefull at the end of the while loop.*/

        while(dup!=NULL)/* Loop condition fails when dup pointer equals to NULL*/
        {
                parent=dup; /*This parent pointer will be used after this while loop termination.*/

                if(k<dup->key) dup=dup->left; /*Checking the key and traversing towards left if given key is less than the dup node's key*/
                else if(k>dup->key) dup=dup->right; /* This shows traversing towards right side by checking given key with dup node's key*/
                else break; /* If given key is equals to the node key value we are forcefully terminating the loop*/
        }



        if(parent->key==k) /* If the parent pointer key is equals to the given key then we have to find the successor of parent pointer to reach requirement*/
        {
            return successor(parent); /* Returning the pointer which will be returned by the successor function*/
        }

        else if(parent->key<k) /* If the parent key is < given key we do following*/
        {

        		while(parent!=NULL)/*Here we are trying to find out the parent node which has greater key than the given key.This case occurs when we reach end of the node on which we don't move further in above while loop (mention above). In such case we have to trace back to the parent nodes and we will stop if such node exist or while loop breaks if no such parent node exist.*/
        		{
        			if(parent->key<k) 
        				parent=parent->parent; /*Tracing back parent pointer of the node*/
        			else break; /*If the node key is greater than the given key then we break the loop.It means that the node key value is smallest greater value than the given key.*/
        		}
        		if(parent==NULL) return NULL; /*If the traced parent pointer is NULL then it means that No such greater element exist  in the treap*/
        		if(parent->key > k ) return parent; /* If traced parent pointer has key is greater than the given key then we return that pointer */
        		else return NULL;
        }
        else if(parent->key>k) return parent; /*This is the case when we find the pointer that has key is greater than the given key (In the first while loop)*/

        else return NULL; /* If above conditions fails and all nodes in the treap are lessthan the given key*/
}





/*This function  returns the number of nodes in the treap rooted at root, with keys less than k
    We are recursively calculating the no.of node which are less than given key.

 */
int num_less_than(tnode *root, float k)
{
        int n=0;
        if(root==NULL) return 0; /* If the root is null then we can assume that no.of nodes is 0. So we return 0*/

        else if(root->key>=k) return num_less_than(root->left,k); /* If the given key is greater than of equals to the root's key then we move towards left side of the treap. Because the keys at right subtreap always greater than the given key*/
        else /*If the node's key is less than the given keyss*/
        {
          n=1;
          if(root->left!=NULL) n+=root->left->size; /*If the left subtreap at the root exist we need not to traverse ( i.e node in left subtreap always less than the given key) , So we are taking size attribute value here and adding them with n*/
          if(root->right!=NULL) n+=num_less_than(root->right,k); /*If the right subtreap exists then we travers towards right subtreap and recursively calculate no.of node that are lessthan given key*/
          return n;/* Returrning the no.of nodes that are lessthan given k*/
        }
}
