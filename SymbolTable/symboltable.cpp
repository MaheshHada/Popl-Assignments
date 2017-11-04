//POPL Assignment 1: Symbol Table
//Mahesh Hada
//2014B3A70963G

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//Node is a particular entry in the symbol table <identifier,type,kind>
struct Node {
	string identifier;
	string type;
	string kind;
	Node(string identifier,string kind,string type) {
		this->identifier = identifier;
		this->type = type;
		this->kind = kind;
	}
};

struct SymbolTable {
	vector<Node*> entry; //declarations in current scope
	SymbolTable *parent; //parent of the scope
	vector<SymbolTable*> children; //nested scopes from this scope
	SymbolTable() {
		this->parent = NULL;
	}
};

//given the scope it creates and returns the new nested scope from this scope
SymbolTable* enter_scope(SymbolTable *sym) {
	if(sym == NULL) {
		return NULL;
	}
	SymbolTable *newSym = new SymbolTable();
	newSym->parent = sym;
	sym->children.push_back(newSym);
	return newSym;
}

//creates a new scope in the current scope and inserts a particulr node in that scope
SymbolTable* insertSymbolTable(SymbolTable *currsym,string name,string kind,string type) {
	Node* newNode = new Node(name,kind,type);
	if(currsym == NULL) {
		currsym = new SymbolTable();
		currsym->entry.push_back(newNode);
		return currsym;
	}
	SymbolTable *newSymbolTable = new SymbolTable();
	newSymbolTable->entry.push_back(newNode);
	newSymbolTable->parent = currsym;
	currsym->children.push_back(newSymbolTable);
	return newSymbolTable;
}


//inserts a node in a symbolTable only if no confilict is there
SymbolTable* insertNode(SymbolTable *currsym,string name,string kind,string type) {
	if(currsym == NULL)
		return NULL;
	for(auto p : currsym->entry) {
		if(kind == "fun") {
			if(p->identifier == name && p->type == type) {
				cout<<"ERROR:Redeclaration of function <"<<name<<"|"<<kind<<"|"<<type<<">."<<endl;
				return currsym;
			}
		}
		else if(kind == "var") {
			if(p->identifier == name) {
				cout<<"ERROR:Redeclaration of variable <"<<name<<"|"<<kind<<"|"<<type<<">."<<endl;	
				return currsym;			
			}
		}
	}
	Node* newNode = new Node(name,kind,type);
	currsym->entry.push_back(newNode);
	return currsym;
}

void printNode(Node *node) {
	cout<<"<"<<node->identifier<<"|"<<node->kind<<"|"<<node->type<<">"<<endl;
}

Node* lookup(SymbolTable *sym,string name) {
	if(sym == NULL)
		return NULL;
	SymbolTable *curr_sym = sym;
	while(curr_sym != NULL) {
		vector<Node*> temp = curr_sym->entry;
		for(int i=0;i<temp.size();i++) {
			Node *curr_node = temp[i];
			if(curr_node->identifier == name) {
				cout<<"Found declaration: ";
				printNode(curr_node); 
				return curr_node;
			}
		}
		curr_sym = curr_sym->parent;
	}
	cout<<"ERROR: Declaration of'"<<name<<"' not found in hierarchy"<<endl;
	return NULL;
}

//returns the scope of the parent scope
SymbolTable* exit_scope(SymbolTable* currsym) {
	if(currsym == NULL) {
		cout<<"ERROR:NULL POINTER EXCEPTION."<<endl;
		return NULL;
	}
	if(currsym->parent == NULL) {
		cout<<"In Global Scope."<<endl;
		return currsym;
	}
	else {
		return currsym->parent;
	}
}

//returns the globalscope
SymbolTable* getGlobalScope(SymbolTable* curr_scope) {
	if(curr_scope == NULL) {
		cout<<"ERROR:NULL POINTER EXCEPTION."<<endl;
		return NULL;
	}
	SymbolTable *curr = curr_scope;
	while(curr->parent != NULL) {
		curr = curr->parent;
	}
	return curr;
}


//prints the level order traversal of the Symbol Table
void printSymbolTable(SymbolTable *sym) {
	if(sym == NULL)
		return;
	queue<SymbolTable*> q;
	q.push(sym);
	while(!q.empty()) {
		SymbolTable *curr_sym = q.front();
		q.pop();
		auto p = curr_sym->entry;
		for(int i=0;i<p.size();i++) {
			printNode(p[i]);
		}
		cout<<endl;
		auto r = curr_sym->children; 
		for(int i=0;i<r.size();i++) {
			q.push(r[i]);
		}
		cout<<endl;
	}
}


int main() {
	SymbolTable *globalSymTable = new SymbolTable();
	SymbolTable *curr_scope = globalSymTable;
	Node *curr_node = NULL;
	//if want to add a node in curr_scope call insertNode for current scope i.e curr_scope = insert(curr_scope,name,kind,type);
	//if you want to add a new scope call insertSymbolTable with a Node entry i.e curr_scope = insert(curr_scope,name,kind,type);
	//if want to add a new scope in the current scope just call enter_scope i.e curr_scope 
	// Part1:
	curr_scope = insertNode(curr_scope,"f","fun","int->void");
	curr_scope = enter_scope(curr_scope);
	curr_scope = insertNode(curr_scope,"a","par","int");
	curr_scope = insertNode(curr_scope,"b","par","int");
	curr_scope = insertNode(curr_scope,"x","var","double");
	curr_scope = insertNode(curr_scope,"i","var","int");
	curr_scope = insertSymbolTable(curr_scope,"while","scope","block");
	curr_scope = insertNode(curr_scope,"i","par","int");
	curr_scope = insertNode(curr_scope,"y","var","int");
	curr_scope = exit_scope(curr_scope);
	curr_scope = exit_scope(curr_scope);
	curr_scope = insertNode(curr_scope,"g","fun","int");
	curr_scope = insertSymbolTable(curr_scope,"x","var","int");
	curr_scope = insertNode(curr_scope,"f","fun","void");
	// printSymbolTable(globalSymTable);
	// curr_node = lookup(curr_scope,"f");
	// curr_node = lookup(curr_scope,"adcd");
	
	// Part2:
	curr_scope = getGlobalScope(curr_scope);
	curr_scope = insertNode(curr_scope,"f","fun","void");
	curr_scope = insertSymbolTable(curr_scope,"x","var","double");
	curr_scope = getGlobalScope(curr_scope);
	curr_scope = insertNode(curr_scope,"g","fun","int");
	// curr_scope = exit_scope(curr_scope);
	// curr_scope = exit_scope(NULL);
	printSymbolTable(globalSymTable);
	return 0;
}