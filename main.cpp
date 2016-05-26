#define WINDOWS
//#define LINUX

/** FAMILY TREE */

#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

struct node
{
    char name[50];
    short int age,x;    // x - height of node
    bool g;             // g- gender
    node* fc;           // Pointer to first child
    node* ns;           // Pointer to next sibiling

    node();
    void getData();
};

node::node()
{
    fc=ns=NULL;
    g=0;
    strcpy(name,"");
    age=x=0;
}

void node::getData()
{
    char ch;
    cout<<"\nName of the Person: ";
    cin>>name;
    cout<<"Age of "<<name<<": ";
    cin>>age;
    cout<<name<<" is (m/f): ";
    cin>>ch;
    if(ch=='m')
        g=1;
}

class familyTree
{

public:

    node* start;

    familyTree();

    node* traverseDown(node*,char[]);   // Search functions
    node* traverseRight(node*,char[]);
    node* search(char[]);

    void addSib(node*,node*);           // Functions for adding new members
    void addChild(node*,node*);
    void addNew();

    void find();                        // Function to find relations
    void show(node*);                   // Function to show details of particular person
    void display(node*);                // Function to display full tree
    void destroy(node*);                // Function to destroy full tree
    void updateX(node*,int);

};

familyTree::familyTree()
{
    start = NULL;
}

void familyTree::destroy(node* ptr)
{
    node* temp = ptr;

    if(ptr==NULL)
        return;

    while(ptr!=NULL)
    {
        destroy(ptr->fc);
        temp = ptr;
        ptr = ptr->ns;
        delete temp;
    }

    start = NULL;
}

void familyTree::show(node* ptr)
{
    char g[10];
    strcpy(g,"Female");
    if(ptr->g)
        strcpy(g,"Male");
    cout<<"\n\nName: "<< ptr->name <<endl;
    cout<<"Age: "<< ptr->age <<endl;
    cout<<"Gender: "<<g<<endl;
}

void familyTree::display(node* ptr)
{
    // Traverses the full n-array tree by recursion to display names of all people

    if(ptr==NULL)
        return;

    while(ptr!=NULL)
    {
        cout<< ptr->name <<endl;
        display(ptr->fc);
        ptr = ptr->ns;
    }
}

void familyTree::updateX(node* ptr,int x)
{
    // Traverses the full n-array tree by recursion and updates x value of all people

    if(ptr==NULL)
        return;

    while(ptr!=NULL)
    {
        updateX(ptr->fc,x++);
        if(ptr->ns!=NULL)
            ptr->ns->x = x;
        ptr = ptr->ns;
    }
}

void familyTree::find()
{

    /*
        Same hight: Sibiling if same parent, else cousin
        Difference of height = 1 - Parent if immediate, else uncule/aunt
        Difference oh height = 2 - Grand parents if same link, elss idk
    */

    char name1[50],name2[50];
    cout<<"Enter names of two persons:\n";
    cin>>name1>>name2;
    node* ptr1 = search(name1);
    node* ptr2 = search(name2);
    node* ptr;
    node* ptrk=ptr1;
    node* ptrk1=ptr2;

    switch(ptr1->x - ptr2->x)
    {

    case 0:
            char s[50];
            strcpy(s,"sister");
            if(ptr1->g)
                strcpy(s,"brother");

            ptr = ptr1;
            while(ptr!=NULL)
            {
                if(ptr==ptr2)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<s<<endl;
                    return;
                }
                ptr = ptr->ns;
            }
            ptr = ptr2;
            while(ptr!=NULL)
            {
                if(ptr==ptr1)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<s<<endl;
                    return;
                }
                ptr = ptr->ns;
            }
            cout<<endl<<name1<<" and "<<name2<<" are Cousins";
            break;

    case 1:
            char str3[50];
            strcpy(str3,"daughter");
            if(ptr1->g)
                strcpy(str3,"son");
            ptr2 = ptr2->fc;
            while(ptr2!=NULL)
            {
                if(ptr2==ptr1)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<str3;
                    return;
                }
                ptr2=ptr2->ns;
            }
            strcpy(str3,"niece");
            if(ptr1->g)
                strcpy(str3,"nephew");
            cout<<endl<<name1<<" is "<<name2<<"'s "<<str3;
            break;
    case -1:
            char str[10];
            strcpy(str,"mother");
            if(ptrk->g)
                strcpy(str,"father");

            ptr = ptrk->fc;
            while(ptr!=NULL)
            {
                if(ptr==ptrk1)
                {
                    cout<<endl<<name1<<" is "<<name2<<"'s "<<str;
                    return;
                }
                ptr=ptr->ns;
            }
            strcpy(str,"aunt");
            if(ptrk->g)
                strcpy(str,"uncule");
            cout<<endl<<name1<<" is "<<name2<<"'s "<<str;
            break;

    case 2:
            char str1[50];
            strcpy(str1,"daughter");
            if(ptr2->g)
                strcpy(str1,"son");
            ptr2 = ptr2->fc->fc;
            while(ptr2!=NULL)
            {
                if(ptr2==ptr1)
                {
                    cout<<endl<<name1<<" is grand "<<str1<<" of "<<name2;
                    return;
                }
                ptr2 = ptr2->ns;
            }
            break;
    case -2:
            char str2[50];
            strcpy(str2,"mother");

            if(ptr1->g)
                strcpy(str2,"father");

             ptr1 = ptr1->fc->fc;

            while(ptr1!=NULL)
            {
                if(ptr1==ptr2)
                {
                    cout<<endl<<name1<<" is grand "<<str2<<" of "<<name2;
                    return;
                }
                ptr1 = ptr1->ns;
            }

            break;
    default:
            cout<<"Too far relationship";
            break;
    }
}



node* familyTree::search(char s[50])
{
    /*
        Searches for the given name from start to it's sibilings and their children
        Returns the pointer of node where the name is present
    */

    node *ptr = start;

    if(strcmp(ptr->name,s)==0)
        return ptr;
    else if(traverseRight(start,s)!=NULL)
        return traverseRight(start,s);
    else if(traverseDown(start,s)!=NULL)
        return traverseDown(start,s);
    else
    {
        return NULL;
        cout<<"***Not found***8";
    }
}

node* familyTree::traverseDown(node* ptr, char s[50])
{
    // Searches all the children

    ptr = ptr->fc;

    while(ptr!=NULL)
    {
        if(  strcmp(ptr->name,s)==0 )
            return ptr;
        else if(traverseRight(ptr,s)!=NULL)
            return traverseRight(ptr,s);
        else
            ptr = ptr->fc;
    }
    return NULL;
}

node* familyTree::traverseRight(node* ptr, char s[50])
{

    //  Searches all the sibilings

    ptr = ptr->ns;

    while(ptr!=NULL)
    {
        if(strcmp(ptr->name,s)==0)
            return ptr;
        else if (traverseDown(ptr,s)!=NULL)
            return traverseDown(ptr,s);
        else
            ptr = ptr->ns;
    }
    return NULL;
}

void familyTree::addNew()
{
    node* temp = new node;
    temp->getData();

    if(start == NULL)
    {
        start = temp;
        temp->x=0;
    }

    else
    {
        cout<<"\nEnter any relation's name: ";
        char name[50];
        cin>>name;
        cout<<"\n1. Child\n2. Sibiling\n\n"<< temp->name <<" is ____ to "<<name<<" : ";
        int opt;
        cin>>opt;
        switch(opt)
        {
            case 1:
                    addChild(search(name),temp);
                    break;
            case 2:
                    addSib(search(name),temp);
                    break;

        }
    }
    cout<<"\nPerson sucessfully added.\n";
}

void familyTree::addSib(node* a,node* b)
{
    // b is added as sibling of a

    while(a->ns!=NULL)
        a=a->ns;
    a->ns = b;

    b->x = a->x;
}

void familyTree::addChild(node* a,node* b)
{

    // b is added as child as a (or) b is added as sibiling to last child of a

    if(a->fc==NULL)
        a->fc = b;
    else
        addSib(a->fc,b);

    b->x = a->x+1;
}

void connect(familyTree *T1, familyTree *T2)
{
    char name[50];
    int opt;
    int x;
    cout<<"Name of person in 1st tree to merge: ";
    cin>>name;
    cout<<T2->start->name<<" is __ to "<<name<<"\n1. Child 2. Sibling - ";;
    cin>>opt;
    node *ptr = T1->search(name);
    switch(opt)
    {
        case 1:
            T1->addChild(ptr,T2->start);
            x = ptr->x + 1;
            break;
        case 2:
            T1->addSib(ptr,T2->start);
            x = ptr->x;
            break;
     }
     T2->updateX(T2->start,x);
     T2->destroy(T2->start);
     cout<<"\nMerged\n";
}

int main()
{
    familyTree T[100];
    int opt,n,n1,n2;
    char c,name[50];
    cout<<"\nEnter the family tree number = ";
    cin>>n;
    while(1)
    {
#ifdef WINDOWS
        system("cls");
#endif // WINDOWS
#ifdef LINUX
        system("clear");
#endif // LINUX
        cout<<"\n\n\n\tFamily tree no = "<<n<<"\n\n\t1. Add new person\n\t2. Find relationship b/w two persons\n\t3. Search\n\t4. Destroy\n\t5. Display\n\t6. Change family tree\n\t7. Connect two family trees\n\t8. Exit\n\n\tEnter your choice = ";
        cin>>opt;
        cout<<endl;

        switch(opt)
        {

        default:
                cout<<"Invalid input";
                break;

        case 1:
                T[n].addNew();
                break;

        case 2:
                T[n].find();
                break;

        case 3:
                cout<<"Enter name of person to search: ";
                cin>>name;
                T[n].show(T[n].search(name));
                break;

        case 4:
                T[n].destroy(T[n].start);
                cout<<"Tree "<<n<<" has been destroyed sucessfully";
                break;

        case 5:
                T[n].display(T[n].start);
                break;

        case 6:
                cout<<"Enter family tree number: ";
                cin>>n;
                break;

        case 7:
               cout<<"Merge __ to __ \n";
               cin>>n2>>n1;
               connect(&T[n1],&T[n2]);
               break;

        case 8:
            return 0;

        }
        cout<<"\n\nPress any key to continue.....";
        cin>>c;
    }
}
