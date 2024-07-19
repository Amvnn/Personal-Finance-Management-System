#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

struct transaction // created our datatype transaction
{
    int id;
    string date;
    double amount;
    string category;
    string type; //"income" or "expense"
};

const int max_transaction=1000;

transaction transactions[max_transaction];
int transactioncount=0; 
int nextID=1;

void addtransaction(string date,double amount,string category,string type){
    if (transactioncount>=max_transaction)
    {
        cout<<"Transaction limit reached ! \n";
        return;
    }

    transaction newtransaction={nextID++,date,amount,category,type};
    transactions[transactioncount++]=newtransaction;
    cout<<"Transaction added successfully ! \n";
    
}

void deletetransaction(int ID){
    bool found=false;

    for (int i = 0; i < transactioncount; i++)
    {
        if (transactions[i].id == ID)
        {
            for (int j = i; j < transactioncount-1; j++)
            {
                transactions[j]=transactions[j+1];
            }
            transactioncount--;
            found=true;
            cout<<"Transaction Deleted Successfully ! "<<endl;
            break;
        }
        
    }
    if(!found){
        cout<<"Transaction Not Found "<<endl;
    }
    
}

void view(){
    for (int i = 0; i < transactioncount; i++)
    {
        cout<<"ID : "<<transactions[i].id<<endl;
        cout<<"Date : "<<transactions[i].date<<endl;
        cout<<"Amount : "<<transactions[i].amount<<endl;
        cout<<"Ctegory : "<<transactions[i].category<<endl;
        cout<<"Type : "<<transactions[i].type<<endl;
    }
    
}

void update(int id, string newdate, double newamount, string newcategory, string newtype ){
  for (int i = 0; i < transactioncount; i++)
  {
    if (transactions[i].id==id)
    {
        transactions[i].date=newdate;
        transactions[i].amount=newamount;
        transactions[i].category=newcategory;
        transactions[i].type=newtype;
        cout<<"Transaction Updated ! "<<endl;
        return ;

    }
    
  }
  cout<<"transaction not found "<<endl;
  
}

void summary(){
    double totalincome=0;
    double totalexpences=0;
    double balance=0;

    for (int i = 0; i < transactioncount; i++)
    {
        if (transactions[i].type=="income")
        {
            totalincome=totalincome + transactions[i].amount;
        }
        else if (transactions[i].type=="expense")
        {
            totalexpences=totalexpences+transactions[i].amount;
        }
        
        
    }

    balance=totalincome- totalexpences;
   cout<<"Total Income : "<<totalincome<<endl;
   cout<<"Total Expense : "<<totalexpences<<endl;
   cout<<"Total Balance : "<<balance<<endl;

}

int main(){

    int choice;
do{
    cout<<"1. Add Transaction \n 2. Delete Transaction \n 3. View Transaction \n 4. Update transaction \n 5. Generate Summary \n 6. Exit \n Choose an option : ";
    cin>>choice;

    if(choice==1){
        string date,category,type;
        double amount;

        cout<<"Enter date : ";
        cin>>date;

        cout<<"Enter amount : ";
        cin>>amount;

          cout<<"Enter category : ";
        cin>>category;

          cout<<"Enter type (income/expense) : ";
        cin>>type;

          addtransaction(date,amount,category,type);
    }

    else if(choice==2){
        int id;
        cout<<"Enter transaction ID to delete : "<<endl;
        cin>>id;

        deletetransaction(id);
    }

    else if(choice==3){
        view();
    }

    else if(choice==4){
        int id;
        string newdate,newcategory,newtype;
        double newamount;

        cout<<"Enter transaction ID to update : "<<endl;
        cin>>id;

        cout<<"Enter new Date : "<<endl;
        cin>>newdate;

        cout<<"Enter new amount : "<<endl;
        cin>>newamount;

        cout<<"Enter new category : "<<endl;
        cin>>newcategory;

        cout<<"Enter new type : "<<endl;
        cin>>newtype;

        update(id,newdate,newamount,newcategory,newtype);

    }
    else if(choice==5){
        summary();
    }
}
    while(choice!=6); // This means the loop should keep executing as long as the user's choice is not 6.

    return 0;
}