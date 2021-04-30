#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct node                         //node to contain line numbers and occurence of a word
{
  int lno;
  int occur;
  struct node* next;
};
int search(struct node* head,int lno)     //update occurence if line number found ,else return 0
{
  struct node* ptr;
  ptr=head;int k=0;
  while(ptr!=NULL)
  {
   if(ptr->lno==lno)
   {
    ptr->occur=ptr->occur+1;
    k=1;
    break;
   }
   ptr=ptr->next;
  }
return k;
}
struct node* insert(int lno,struct node* head,int occur=1)      //inserts the line number and occurence 
{
 if(!search(head,lno))
 {
  node* new_mod=new node;                 //new node to store line number and occurence if not present
  new_mod->lno=lno;
  new_mod->occur=occur;
  new_mod->next=NULL;
  if(head==NULL)
  {
   head=new_mod;
   return head;	
  }	
  struct node *ptr;
  ptr=head;
  while(ptr->next!=NULL)
   ptr=ptr->next;
  ptr->next=new_mod;
  return head;
 }
 else
 return head;
}
void traverse(struct node* head)                //prints info of the word that user searches
{
  struct node *ptr;
  ptr=head;
  int sum=0;
  cout<<"Lines :";
  while(ptr!=NULL)
  {
   cout<<ptr->lno<<" ";
   sum=sum+ptr->occur;
   ptr=ptr->next;
  }
  cout<<"Occurence :"<<sum<<endl;
}
void traversal(struct node* head)             //prints when traversal order executes
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



class BST
{
  string data;                               //store word
  struct node* head;                         //head pointer to linked list containing info of a word 
  BST *left,*right;                          //left,right pointer
public:
BST()                                     //default constructor
{
 data =" ";
 head=NULL;
 left=right=NULL;
}
BST(string value,int lno)                 //parametised constructor to insert word,line number and occurence
{
 data=value;
 head=NULL;
 left=right=NULL;
 head=insert(lno,head);
}
BST* make(BST* root,string s,int lno)        //constructing BST
{
 if(!root)
 {  root = new BST(s,lno);
    return root;
 }
 if((root->data.compare(s))>0)
 {
  root->left= make(root->left,s,lno);
 }
 else if((root->data.compare(s))<0)
 {
  root->right= make(root->right,s,lno);
 }
 else if((root->data.compare(s))==0)            //if word is already present,update its line number and occurence
 {
  root->head=insert(lno,root->head);
 }
return root;
}
BST* search(BST* root,string key)             //searches the word asked by user
{
  if(root==NULL)
  {
   cout<<"Not found!"<<endl;
   return root;
  }
  if((root->data.compare(key))==0)
  {
   cout<<"Present!"<<endl;
   cout<<root->data<<endl;
   traverse(root->head);
   return root;
  }
  if((root->data.compare(key))<0)
   return search(root->right,key);
  else
  return search(root->left,key);
}
void inorder(BST *root)                  //prints inorder traversal of bst
{
  if(!root)
   return;
  inorder(root->left);
  cout<<"\n"<<root->data<<" ";
  traversal(root->head);
  inorder(root->right);
}
void write_file(BST *x)                   //write BST in a text file
{
  ofstream outFile;
  outFile.open("bst.txt", ios::out | ios::app);
  outFile<<x->data<<"-";                    //write word
  struct node *ptr;
  ptr=x->head;
  while(ptr->next!=NULL)
  {
    outFile<<ptr->lno<<":";                  //write line numbers
    ptr=ptr->next;
  }
  outFile<<ptr->lno<<">";
  ptr=x->head;
  while(ptr->next!=NULL)
  {
   outFile<<ptr->occur<<":";               //write occurences
   ptr=ptr->next;
  }
  outFile<<ptr->occur;
  outFile<<"\n";
  outFile.close();
}
void preorder(BST *root)              //preorder traversal of BST
{
 if(!root)
  return;
 write_file(root);                    //writing the traversal
 preorder(root->left);
 preorder(root->right);
}
};

int main()
{
 fstream fin;
 fin.open("file.txt",ios::in);       //file containing words is opened 
 if(fin)
 {
  int count=0;
  string line;
  BST ob,*root=NULL;
  char del[] =" ";
  while(getline(fin,line))           //reading the file
  {
    count++;
    char * cstr;
    cstr =&line[0];
    char *token=strtok(cstr,del);
    while(token!=NULL)
    { string s(token);
    root=ob.make(root,s,count);
    token=strtok(NULL,del);
    }
   }
   fin.close();
   int choice;
   do             //menu for different functions
   {
    cout<<"\nEnter 1 to search a word , 2 to print inorder traversal , 3 to store BST preorder traversal and 4 to exit:";
    cin>>choice;
    switch(choice)
    {
     case 1:{
      string word;
      cout<<"Enter the word :";
      cin>>word;
      root=ob.search(root,word);
      break;}
     case 2:{ ob.inorder(root);
      break;}
     case 3: { ob.preorder(root);
      break;}
     case 4:break;
     default:cout<<"Invalid choice!"<<endl;
    }
   }while(choice!=4);
 }
 else
  cout<<"file doesn't exist";
return 0;
}

