// Ex2 - RBtree.cpp
#include <iostream>
#include <cstdlib>
using namespace std;

class TreeNode         				   // define TreeNode class
{
  private:
  	int key;
  	bool color;        			   // black=0 ; red=1
  	TreeNode *parent,*lchild,*rchild;
  	
  public:
  	TreeNode(int k):key(k)   		   // constructor
	{
	  color=1;
	  parent=NULL;
	  lchild=NULL;
	  rchild=NULL;
	}
	void printColor()        		   // function for showing the color of the nodes
	{
	  if(this->color)
	    cout << "red";
	  else
	    cout << "black";
	}
	
  friend class RBTree;
  friend TreeNode* Min(TreeNode*);
  friend void Inorder(TreeNode*);
  friend void DeleteTree(TreeNode*);
};

class RBTree           				   // define RBTree class
{
  private:
  	TreeNode *root;
  	
  public:
  	RBTree(){root=NULL;}     		   // constructor
  	
	void Transplant(TreeNode* u,TreeNode* v)   // Transplant function
	{
      if(!u->parent) root=v;
  	  else if(u==u->parent->lchild) u->parent->lchild=v;
  	  else u->parent->rchild=v;
  	  if(v) v->parent=u->parent;
	}
	
	void LeftRotate(TreeNode* x)               // LeftRotate function
	{
  	  TreeNode *y=x->rchild;
  	  x->rchild=y->lchild;
  	  if(y->lchild) y->lchild->parent=x;
  
  	  Transplant(x,y);
  
  	  y->lchild=x;
  	  x->parent=y;
	}

	void RightRotate(TreeNode* x)             // RightRotate function
	{
  	  TreeNode *y=x->lchild;
  	  x->lchild=y->rchild;
  	  if(y->rchild) y->rchild->parent=x;
  
  	  Transplant(x,y);
 
 	  y->rchild=x;
 	  x->parent=y;
	}
	
	TreeNode* Search(int k)                  // search the TreeNode whose key==k
	{
  	  TreeNode* current=root;
  	  while(current)
  	  {
  	  	if (current->key==k) return current;
  	  	else if(current->key>k) current=current->lchild;
  	  	else current=current->rchild;
  	  }
	}
    
    void Insert(TreeNode*);
	void InsertFixup(TreeNode*);
	void Delete(TreeNode*);	
	void DeleteFixup(TreeNode*);
	
  friend void Inorder(RBTree*);
  friend void DeleteTree(RBTree*);
};

void RBTree::Insert(TreeNode* z)                 // Insert Function
{
  TreeNode *x=root,*y=NULL;
  while(x)
  {
  	y=x;
  	if(z->key==x->key) return;
  	else if(z->key<x->key) x=x->lchild;
  	else x=x->rchild;
  }
  z->parent=y; 
  if(!y) root=z;
  else if(z->key<y->key) y->lchild=z;
  else y->rchild=z;
  InsertFixup(z);
}

void RBTree::InsertFixup(TreeNode *z)            // InsertFixup function
{
  while(z!=root && z->parent!=root && z->parent->color)
  {
    if(z->parent==z->parent->parent->lchild)
    {
      TreeNode *y=z->parent->parent->rchild;
      if(y && y->color)
      {
      	z->parent->color=0;
      	y->color=0;
      	z->parent->parent->color=1;
      	z=z->parent->parent;
	  }
	  else if(z==z->parent->rchild)
	  {
	  	z=z->parent;
	  	LeftRotate(z);
	  	z->parent->color=0;
	  	z->parent->parent->color=1;
	  	RightRotate(z->parent->parent);  	
	  }
	  else
	  {
	  	z->parent->color=0;
	  	z->parent->parent->color=1;
	  	RightRotate(z->parent->parent); 
	  }
	}
	else
	{
      TreeNode *y=z->parent->parent->lchild;
      if(y && y->color)
      {
      	z->parent->color=0;
      	y->color=0;
      	z->parent->parent->color=1;
      	z=z->parent->parent;
	  }
	  else if(z==z->parent->lchild)
	  {
	  	z=z->parent;
	  	RightRotate(z);
	  	z->parent->color=0;
	  	z->parent->parent->color=1;
	  	LeftRotate(z->parent->parent);  	
	  }
	  else
	  {
	  	z->parent->color=0;
	  	z->parent->parent->color=1;
	  	LeftRotate(z->parent->parent); 
	  }
	}	
  }
  root->color=0;
}

void RBTree::Delete(TreeNode* z)                 // Delete function
{
  if(!z)
  {
  	cout << "error: no data to delete" << endl;
  	return;
  }
  
  TreeNode *x,*y=z;
  bool y_orig_color=y->color;
  if(!z->lchild)
  {
  	x=z->rchild;
  	Transplant(z,z->rchild);
  }
  else if(!z->rchild)
  {
  	x=z->lchild;
  	Transplant(z,z->lchild);
  }
  else
  {
  	y=Min(z->rchild);
  	y_orig_color=y->color;
    x=y->rchild;
    if(y->parent==z) 
	{
	  if(x) x->parent=y;
	}
    else
    {
      Transplant(y,y->rchild);
  	  y->rchild=z->rchild;
  	  y->rchild->parent=y;
    }
    Transplant(z,y);
    y->lchild=z->lchild;
    y->lchild->parent=y;
    y->color=z->color;
  }
  if(!y_orig_color && x) DeleteFixup(x);
  delete z;
}

void RBTree::DeleteFixup(TreeNode* x)            // DeleteFixup function
{
  while(x!=root && !x->color)
  {
  	if(x==x->parent->lchild)
  	{
  	  TreeNode* w=x->parent->rchild;
  	  if(w)
	  {
  	  	if(w->color)
  	  	{
  	  	  w->color=0;
  	  	  x->parent->color=1;
  	  	  LeftRotate(x->parent);
	  	}
	  	else if((w->lchild && !w->lchild->color) && (w->rchild && !w->rchild->color))
	  	{
	  	  w->color=1;
	  	  x=x->parent;
	  	}
	  	else if(w->rchild && !w->rchild->color)
	  	{
	  	  if(w->lchild) w->lchild->color=0;
	  	  w->color=1;
	  	  RightRotate(w);
	  	  w=x->parent->rchild;
	  	}
	    else
	  	{
	  	  w->color=x->parent->color;
	  	  x->parent->color=0;
	  	  if(w->rchild) w->rchild->color=0;
	  	  LeftRotate(x->parent);
	  	  x=root;
	  	}
	  }
	} 
	else
	{
  	  TreeNode* w=x->parent->lchild;
  	  if(w)
	  {
  	  	if(w->color)
  	  	{
  	  	  w->color=0;
  	  	  x->parent->color=1;
  	  	  RightRotate(x->parent);
	  	}
	  	else if((w->lchild && !w->lchild->color) && (w->rchild && !w->rchild->color))
	  	{
	  	  w->color=1;
	  	  x=x->parent;
	  	}
	  	else if(w->lchild && !w->lchild->color)
	  	{
	  	  if(w->rchild) w->rchild->color=0;
	  	  w->color=1;
	  	  LeftRotate(w);
	  	  w=x->parent->lchild;
	  	}
	    else
	  	{
	  	  w->color=x->parent->color;
	  	  x->parent->color=0;
	  	  if(w->lchild) w->lchild->color=0;
	  	  RightRotate(x->parent);
	  	  x=root;
	  	}
	  }
	} 
  }
  x->color=0;
}

TreeNode* Min(TreeNode* n)                     	   // look for the minimal key rooted at n
{
  while(n->lchild) n=n->lchild;
  return n;
}

void Inorder(RBTree* t) {Inorder(t->root);}    	   // Inorder driver

void Inorder(TreeNode* current)                    // Inorder workhorse
{
  if(current)
  { 
	if(current->lchild) Inorder(current->lchild);
	
	cout << "key: " << current->key << " parent: ";
	if(!current->parent) cout << " ";
	else cout << current->parent->key;
	cout << " color: ";
	current->printColor();
	cout << endl;
	
	if(current->rchild) Inorder(current->rchild);
  }
}

void DeleteTree(RBTree* t) {DeleteTree(t->root);}   // DeleteTree driver

void DeleteTree(TreeNode* current)                  // DeleteTree workhorse
{
  if(current)
  { 
	if(current->lchild) DeleteTree(current->lchild);
	if(current->rchild) DeleteTree(current->rchild);
	delete current;
  }
}

int main(void)
{
  RBTree tree;
  int t,op,n,tmp;
  cin >> t;
  if(t<=0 || t>15)
  {
  	cout << "error: t should range from 1~15" << endl;
  	return 0;
  }
  
  for(int i=1;i<=t;i++)
  {
  	cin >> op >> n;
  	if(n<=0 || n>20)
  	{
  	  cout << "error: n should range from 1~20" << endl;
  	  return 0;
  	}
  	
  	if(op==1)
  	{
  	  cout << "Insert: ";
  	  for(int j=1;j<=n;j++)
  	  {
  	  	cin >> tmp;
  	  	cout << tmp;
  	  	if(j!=n) cout << ", ";
  	  	TreeNode* z=new TreeNode(tmp);
  	  	tree.Insert(z);
	  }
	}
	else
	{
	  cout << "Delete: ";
	  for(int j=1;j<=n;j++)
  	  {
  	  	cin >> tmp;
  	  	cout << tmp;
  	  	if(j!=n) cout << ", ";
  	  	tree.Delete(tree.Search(tmp));
	  }
	}
	cout << endl;
	Inorder(&tree);
  }
  
  DeleteTree(&tree);
  return 0;
}
