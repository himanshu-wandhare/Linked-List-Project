#include <iostream>
#include <ctype.h>
using namespace std;

class linkedList
{
    struct node
    {
        int data;
        string name;
        node *link;
    }*headerList[10],*ptr,*newNode,*backTrace;
    public:
        int top,fileNo;
        linkedList();

        void menu();
        void listSelectionMenu();
        void createNewList();
        void copyList();
        void mergeList();
        node* searchList();
        void sortList();
        void display();

        void insertMenu();
        void insertAtFront(node*);
        void insertAtAny(node*);
        void insertAtEnd(node*);

        void deleteMenu();  
        void deleteAtFront(node*);
        void deleteAtAny(node*);
        void deleteAtEnd(node*);
};
linkedList::linkedList()
{
    top=0;
}
void linkedList::menu()
{
    int choice;
    node *loc;
    while(1){
        cout<<"\n1. Create a New List";
        cout<<"\n2. Insert a Element in List";
        cout<<"\n3. Delete a element in List";
        cout<<"\n4. Copy a List";
        cout<<"\n5. Merge a List";
        cout<<"\n6. Sort a List";
        cout<<"\n7. Search a element in a List";
        cout<<"\n8. Display a List";
        cout<<"\n9. Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice){
            case 1: createNewList();
                    break;
            case 2: insertMenu();
                    break;
            case 3: deleteMenu();
                    break;
            case 4: copyList();
                    break;
            case 5: mergeList();
                    break;
            case 6: sortList();
                    break;
            case 7: loc=searchList();
                    if(loc!=NULL)
                        cout<<"\nElement found at location: "<<loc;
                    break;
            case 8: display();
                    break;
            case 9: return;
            default:cout<<"\nPlease select proper choice";
                    break;
        }
    }    
}
void linkedList::listSelectionMenu()
{
    cout<<"\nList of files";
    for(int i=1;i<=top;i++){
        cout<<"\n"<<i<<". "<<headerList[i]->name;
    } 
    cout<<"\nSelect a file: ";
    cin>>fileNo;
}
void linkedList::createNewList()
{
    char choice='Y';
    while(toupper(choice)=='Y'){
        node *header=new node;
        if(header==NULL){
            cout<<"Memory Allocation failed";
            return;
        }
        else{
            header->link=NULL;
            cout<<"Enter the Name of List: ";
            cin>>header->name;

            top+=1;
            headerList[top]=header;         //pushing address of header node into array.

            while(toupper(choice)=='Y'){
                insertAtEnd(header);
                cout<<"\nDo you want to add more element(Y/N): ";
                cin>>choice;
            }
            cout<<"\nList created sucessfully!.";
        }
        cout<<"\nDo you want to create more lists(Y/N): ";
        cin>>choice;
    }
}
void linkedList::copyList()
{
    if(top==0){
        cout<<"\nThere is no list to copy.";
    }
    else{
        node *copyPtr;
        node *header=new node;
        header->link=NULL;

        listSelectionMenu();
        top+=1;
        headerList[top]=header;
        header->name=headerList[fileNo]->name+"(1)";
        
        ptr=headerList[fileNo]->link;
        copyPtr=header;
        while(ptr!=NULL){
            newNode=new node;
            newNode->data=ptr->data;
            newNode->link=NULL;
            copyPtr->link=newNode;
            copyPtr=newNode;
            ptr=ptr->link;
        }
        cout<<"\nList Copied Sucessfully !"; 
    }
}
void linkedList::mergeList()
{
    if(top==0)
        cout<<"\nThere is no list to Merge.";
    else if(top==1)
        cout<<"\nTo Merge a file you need alteast two files.";
    else{
        node *header=new node;
        if(header==NULL){
            cout<<"\nMemory allocation is failed.";
        }
        else{
            cout<<"\nSelect List 1\n";
            copyList();
            node *header=headerList[top];
            ptr=header;
            while(ptr->link!=NULL){
                ptr=ptr->link;
            }
            cout<<"\nSelect List 2\n";
            listSelectionMenu();
            ptr->link=headerList[fileNo]->link;
            cout<<"\nEnter a name for new Merged List: ";
            cin>>header->name;
            cout<<"\nList is sucessfully Merged.";
        }
    }
}
linkedList::node* linkedList::searchList()
{
    if(top==0)
        cout<<"\nThere is no list to search.";
    else{
        listSelectionMenu();
        node *loc=NULL;
        int flag=0,item;
        if(headerList[fileNo]->link==NULL){
            cout<<"List is empty.\n";
            cout<<"Please insert elements in list before searching.\n";
        }
        else{
            cout<<"Enter the element: ";
            cin>>item;
            ptr=headerList[fileNo]->link;
            while(ptr!=NULL && flag==0){
                if(ptr->data==item){
                    flag=1;
                    loc=ptr;
                    return loc;
                }
                else{
                    ptr=ptr->link;
                }
            }
            if(ptr==NULL){
                cout<<"element does not exist.\n";
            }
        }
        return loc;
    }
}
void linkedList::sortList()
{   
    listSelectionMenu();
    ptr=headerList[fileNo];
    if(ptr->link==NULL){
        cout<<"\nList is empty. Sorting not possible.";
        return;
    }
    int temp;
    node *ptr1;
    while(ptr->link!=NULL){
        ptr1=ptr->link;
        while(ptr1!=NULL){
            if(ptr->data>ptr1->data){
                temp=ptr->data;
                ptr->data=ptr1->data;
                ptr1->data=temp;
            }
            ptr1=ptr1->link;
        }
        ptr=ptr->link;
    }
    cout<<"\nSorting successful";
}
void linkedList::display()
{
    if(top==0){
        cout<<"\nThere is no list to display";
        return;
    }
    listSelectionMenu();
    ptr=headerList[fileNo]->link;
    while(ptr!=NULL){
        cout<<endl<<ptr->data;
        ptr=ptr->link;
    }
    cout<<"\n";
}
void linkedList::insertMenu()
{
    if(top==0){
        cout<<"\nThere is no list for Insertion Operation";
    }
    else{
        listSelectionMenu();
        int choice;
        while(1){
            cout<<"\n1. Insert element at front";
            cout<<"\n2. Insert element at particular position";
            cout<<"\n3. Insert element at end";
            cout<<"\n4. Exit";
            cout<<"\nEnter your choice: ";
            cin>>choice;
            switch(choice){
                case 1: insertAtFront(headerList[fileNo]);
                        break;
                case 2: insertAtAny(headerList[fileNo]);
                        break;
                case 3: insertAtEnd(headerList[fileNo]);
                        break;
                case 4: return;
                default: cout<<"\nPlease select proper choice";
                        break;
            }   
        }
    }
}
void linkedList::insertAtFront(node *header)
{  
    newNode=new node;
    if(newNode==NULL){
        cout<<"\nMemory allocation failed."<<endl;
    }
    else{
        cout<<"\nEnter the element: ";
        cin>>newNode->data;
        newNode->link=header->link;
        header->link=newNode;
        cout<<"\nInsertion Sucessful !";
    }
}
void linkedList::insertAtEnd(node *header)
{
    newNode=new node;
    if(newNode==NULL){
        cout<<"\nMemory allocation failed."<<endl;
    }
    else{
        ptr=header;
        while(ptr->link!=NULL){
            ptr=ptr->link;
        }
        cout<<"\nEnter the element: ";
        cin>>newNode->data;
        ptr->link=newNode;
        newNode->link=NULL;
        cout<<"\nInsertion Sucessful !";
    }
}
void linkedList::insertAtAny(node *header)
{
    int key;
    newNode=new node;
    if(newNode==NULL){
        cout<<"\nMemory allocation failed."<<endl;
    }
    else{
        cout<<"\nEnter the key: ";
        cin>>key;

        ptr=header;
        while(ptr->link!=NULL && ptr->data!=key){
            ptr=ptr->link;
        }
        if(ptr->link==NULL){
            cout<<"\nKey is not available"<<endl;
        }
        else{
            cout<<"\nEnter the element: ";
            cin>>newNode->data;
            newNode->link=ptr->link;
            ptr->link=newNode;
            cout<<"\nInsertion Sucessful !";
        }
    }
}
void linkedList::deleteMenu()
{
    if(top==0){
        cout<<"\nThere is no list for Deletion Operation";
    }
    else{
        listSelectionMenu();
        int choice;
        while(1){
            cout<<"\n1. Delete element from front";
            cout<<"\n2. Delete element from particular position";
            cout<<"\n3. Delete element from end";
            cout<<"\n4. Exit";
            cout<<"\nEnter your choice: ";
            cin>>choice;
            switch(choice){
                case 1: deleteAtFront(headerList[fileNo]);
                        break;
                case 2: deleteAtAny(headerList[fileNo]);
                        break;
                case 3: deleteAtEnd(headerList[fileNo]);
                        break;
                case 4: return;
                default: cout<<"\nPlease select proper choice";
                        break;
            }   
        }
    }
}
void linkedList::deleteAtFront(node *header)
{
    ptr=header->link;
    if(ptr==NULL){
        cout<<"\nThe list is empty, deletion is not possible."<<endl;
    }
    else{
        header->link=ptr->link;
        delete ptr;
        cout<<"\nDeletion Sucessful !";
    }
}
void linkedList::deleteAtEnd(node *header)
{
    ptr=header;
    if(ptr->link==NULL){
        cout<<"\nThe list is empty, deletion is not possible."<<endl;
    }
    else{
        while(ptr->link!=NULL){
            backTrace=ptr;
            ptr=ptr->link;
        }
        backTrace->link=NULL;
        delete ptr;
        cout<<"\nDeletion Sucessful !";
    }
}
void linkedList::deleteAtAny(node *header)
{
    int key;

    ptr=header->link;
    if(ptr==NULL){
        cout<<"List is empty, deletion is not possible.";
    }

    cout<<"\nEnter a key: ";
    cin>>key;

    while(ptr!=NULL){
        if(ptr->data!=key){
            backTrace=ptr;
            ptr=ptr->link;
        }
        else{
            backTrace->link=ptr->link;
            delete ptr;
            cout<<"\nDeletion Sucessful !";
            break;
        }
    }
    if(ptr==NULL){
        cout<<"\nKey not found\n";
    }
}
int main()
{
    linkedList list;
    list.menu();
    return 0;
}