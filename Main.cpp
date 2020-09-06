#include "mytreap.h"
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

#include "treaps.cpp"
int is_bst(tnode* r)
{
static int a=1;
if((r!=NULL) & (a!=0))
{


if((r->left!=NULL) && (r->left->key>r->key))
	a=0;
if((r->right!=NULL) && (r->right->key<r->key))
	a=0;
if(a!=0){
is_bst(r->left);
is_bst(r->right);
	}
}
return a;

}


int is_heap(tnode* r)
{
static int a=1;
if((r!=NULL) & (a!=0))
{


if((r->left!=NULL) && (r->left->priority<r->priority))
{
a=0;
cout<<"\nheap fail at left child "<<r->left->key<<endl;
}
if((r->right!=NULL )&& (r->right->priority<r->priority))
{
a=0;
cout<<"\nheap fail at right child "<<r->right->key<<endl;
}
if(a!=0){
is_heap(r->left);
is_heap(r->right);
}
}
return a;

}


int size_check(tnode *r)
{
static int t=1;
if(r!=NULL)
{

if((r->left==NULL )&& (r->right==NULL) &&(r->size!=1))
t=0;
else if((r->left!=NULL) && (r->right!=NULL)&&(r->size!=r->left->size+r->right->size+1))
t=0;
else if((r->left!=NULL) && (r->right==NULL) &&(r->size!=1+r->left->size))
t=0;
else if((r->left==NULL) &&(r->right!=NULL) &&(r->size!=1+r->right->size))
t=0;
size_check(r->right);
size_check(r->left);
}
return t;
}


int main()
{


		int p=0;
		for(p=0;p<5;p++){
			cout<<" time:\t"<<p<<endl;
        tnode *root=NULL;
        //root->key=-11;
        //root->parent=NULL;
        //root->priority=100;
        //root->size=1;
        tnode *temp;
        for(int i=0;i<15;i++){
                int key=rand()%100;
                cout<<"Key "<<i<<" is "<<key<<" \n ";
                temp=insert_key(root,key);
                if(temp) cout<<"Newly inserted key is "<<temp->key<< " and root node is "<<root->key<<endl;
        }
        cout<<"After insertion our preorder and inorder "<<endl;
        inOrder(root);
        cout<<endl;
        preOrder(root);



        cout<<"\nTesing BST\n";
        if(is_bst(root)==0) cout<<"Your treap is not holding BST\n";
        else cout<<"Treap holds BST property\n";


        cout<<"Testing min heap\n";
        if(is_heap(root)==0) cout<<" No, it is not heap\n";
        else cout<<"It is heap\n";
        cout<<"\nSize test\n";
        if(size_check(root)==0) cout<<"No not valid sizes\n";
        else cout<<"Valid sizes\n";

        //exit(0);
        float k=93;
        cout<<"This is find_next() function with key "<<k<<endl;
        tnode *find=find_next(root,k);
        if(find) cout<<" This is the node which is greater thn "<<k<<"  here is  "<<find->key<<endl;
        else cout<<k<<" is greater number "<<endl;
        k=83.1;
        cout<<num_less_than(root,k)<<" are num_less_than than "<<k<<endl;

        inorder_print(root);

        cout<<endl;

    /*    cout<<" Successor "<<endl;
        find=successor(root);
        if(find) cout<<" Successor of the node "<<root->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->key<<" \n";


        find=successor(root->right);
        if(find) cout<<" Successor of the node "<<root->right->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->key<<endl;

        find=successor(root->right->right);
        if(find) cout<<" Successor of the node "<<root->right->right->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->right->key<<endl;

        find=successor(root->right->left);
        if(find) cout<<" Successor of the node "<<root->right->left->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->left->key<<endl;

        find=successor(root->right->left->left);
        if(find) cout<<" Successor of the node "<<root->right->left->left->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->left->left->key<<endl;
        find=successor(root->right->right->right);
        if(find) cout<<" Successor of the node "<<root->right->right->key<<" is "<<endl;
        else cout<<" No successor for this node "<<root->right->right->key<<endl;
        cout<<endl;



        cout<<" predecessor "<<endl;
        find=predecessor(root);
        if(find) cout<<" Successor of the node "<<root->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->key<<" \n";


        find=predecessor(root->right);
        if(find) cout<<" Successor of the node "<<root->right->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->key<<endl;

        find=predecessor(root->right->right);
        if(find) cout<<" Successor of the node "<<root->right->right->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->right->key<<endl;

        find=predecessor(root->right->left);
        if(find) cout<<" Successor of the node "<<root->right->left->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->left->key<<endl;

        find=predecessor(root->right->left->left);
        if(find) cout<<" Successor of the node "<<root->right->left->left->key<<" is "<<find->key<<endl;
        else cout<<" No successor for this node "<<root->right->left->left->key<<endl;
        find=predecessor(root->right->right->right);
        if(find) cout<<" Successor of the node "<<root->right->right->key<<" is "<<endl;
        else cout<<" No successor for this node "<<root->right->right->key<<endl;
        cout<<endl;*/

        cout<<"***********************************************************\n";
        find=search_key(root,83);
        if(find) cout<<"Key is found and key is "<<find->key<<"\n";
        else cout<<"Key is not found\n";
          cout<<"***********************************************************\n";




        cout<<"*****SPLIT*****\n";
        find=split_treap(root,49.3); //Left Subtreap
        if(find){cout<<"T1\n";preOrder(find);}
        cout<<"\nT2\n";
        if(root) preOrder(root);


         cout<<"\nTesing BST\n";
        if(is_bst(root)==0) cout<<"Your treap is not holding BST\n";
        else cout<<"Treap holds BST property\n";


        cout<<"Testing min heap\n";
        if(is_heap(root)==0) cout<<" No, it is not heap\n";
        else cout<<"It is heap\n";
        cout<<"\nSize test\n";
        if(size_check(root)==0) cout<<"No not valid sizes\n";
        else cout<<"Valid sizes\n";



         cout<<"\nFind variable\nTesing BST\n";
        if(is_bst(find)==0) cout<<"Your treap is not holding BST\n";
        else cout<<"Treap holds BST property\n";


        cout<<"Testing min heap\n";
        if(is_heap(find)==0) cout<<" No, it is not heap\n";
        else cout<<"It is heap\n";
        cout<<"\nSize test\n";
        if(size_check(find)==0) cout<<"No not valid sizes\n";
        else cout<<"Valid sizes\n";
       // exit(0);

        cout<<"\n\nAfter joine\n";
        //cout<<"\nT2\n";
       // makeParent(find);
       // if(find){cout<<"T1\n";preOrder(find);}
       cout<<"This is join treaps\n";
        root=join_treaps(find,root);


         cout<<"\nTesing BST\n";
        if(is_bst(root)==0) cout<<"Your treap is not holding BST\n";
        else cout<<"Treap holds BST property\n";


        cout<<"Testing min heap\n";
        if(is_heap(root)==0) cout<<" No, it is not heap\n";
        else cout<<"It is heap\n";
        cout<<"\nSize test\n";
        if(size_check(root)==0) cout<<"No not valid sizes\n";
        else cout<<"Valid sizes\n";
       // exit(0);
        cout<<"\n After joining two treaps\n";
        preOrder(root);
        cout<<"\n\n";
        inOrder(root);
        cout<<"\n\n";

        cout<<" delete_node\n";

        root=delete_node(root,root->right);
        cout<<"\nAfter delete node test\n";
          cout<<"\nTesing BST\n";
        if(is_bst(root)==0) cout<<"Your treap is not holding BST\n";
        else cout<<"Treap holds BST property\n";


        cout<<"Testing min heap\n";
        if(is_heap(root)==0) cout<<" No, it is not heap\n";
        else cout<<"It is heap\n";
        cout<<"\nSize test\n";
        if(size_check(root)==0) cout<<"No not valid sizes\n";
        else cout<<"Valid sizes\n";
        inOrder(root);
        cout<<endl;
        preOrder(root);
    }

}


