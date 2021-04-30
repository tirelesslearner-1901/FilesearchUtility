#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
struct node                 //node to contain line numbers and occurence of a word
{
  int lno;
  int occur;
  struct node* next;
};
int n;
struct node* insert(struct node* head,int *p,int *q)        //creating linked list of information of a word
{ int i=0;
  while(i<n)
  {
   node* new_mod=new node;
   new_mod->lno=p[i];
   new_mod->occur=q[i];
   new_mod->next=NULL;
   if(head==NULL)
   {
    head=new_mod;	
   }
   else
   {	
    struct node *ptr;
    ptr=head;
    while(ptr->next!=NULL)
    ptr=ptr->next;
    ptr->next=new_mod;
   }
    i++;
   }
return head;
}
void traversal(struct node* head)            //traversing linked list
{
  struct node *ptr;
  ptr=head;
  while(ptr!=NULL)
  {
    cout<<"Line:"<<ptr->lno<<" ";
    cout<<"Occurence:"<<ptr->occur<<" ";
    ptr=ptr->next;
  }
} 
int* bifur(string key,int size)            //converts string form of numbers into int type array
{
  int* arr = new int[size];
  int i=0;
  char  del[] =":";
  char *cstr;
  cstr = &key[0];
  char *token=strtok(cstr,del);
  while(token!=NULL)
  {
    arr[i++]=atoi(token);                    //atoi converts char string to integer
    token=strtok(NULL,del);
  }
return arr;
}

class BST                               //BST class
{
  string data;                            //store word
  struct node* head;                      //head pointer to linked list containing info of a word 
  BST *left,*right;                       //left,right pointer 
  public:
  BST()                                   //default constructor
  {
    data =" ";
    head=NULL;
    left=right=NULL;
  }
  BST(string value)                      //parameterised constructor
  {
    data=value;
    head=NULL;
    left=right=NULL;
    head=NULL;
  }
  BST* createnode(BST* root,string s,string l,string o )      //reconstructing BST 
  {
   if(!root)
   {
    root= new BST(s);
    root->head=insert(root->head,bifur(l,n),bifur(o,n));
    return root;
   }
    if((root->data.compare(s))>0)
    root->left=createnode(root->left,s,l,o);
    if((root->data.compare(s))<0)
    root->right=createnode(root->right,s,l,o);
    return root;
   }
   void inorder(BST *root)                               //inorder traversal
   {
    if(!root)
    return;
    inorder(root->left);
    cout<<"\n"<<root->data<<" ";
    traversal(root->head);
    inorder(root->right);
    }
};

int main()
{
  fstream fin;
  fin.open("bst.txt",ios::in);              //file with preorder traversal is opened in read mode
  BST ob,*root=NULL;
  string line;
  while(getline(fin,line))                 //reading the file
  {
   int posd = line.find("-");
   int posa = line.find(">");
   string word=line.substr(0,posd);
   string lno=line.substr(posd+1,posa-posd-1);
   n=(lno.length()/2 )+1;
   line=line.substr(posa+1);
   root=ob.createnode(root,word,lno,line);   //bst reconstruction
  }
  fin.close();
  ob.inorder(root);                         //print the inorder traversal of bst;
return 0;
}
