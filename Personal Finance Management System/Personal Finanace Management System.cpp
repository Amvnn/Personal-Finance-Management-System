#include<iostream>
#include<algorithm>
#include<string>
#include<map> //  map container provides a convenient way to access elements using keys, similar to how you might access elements in an array using indices.
#include<sstream>
#include<fstream>
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
transaction transactions[max_transaction];// in my datatype i made a array- transactions[max_transactions]
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
                transactions[j]=transactions[j+1]; // filling the gap of deleted transaction
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
        cout<<"Category : "<<transactions[i].category<<endl;
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
            totalincome=totalincome + transactions[i].amount; // in this loop it will go through all the transactions and add up the amount in total income
        }
        else if (transactions[i].type=="expense")
        {
            totalexpences=totalexpences+transactions[i].amount; // in this loops it will go through all the transactions and add ( type - "expense" ) adn add to the total expense.
        }
        
        
    }

    balance = totalincome - totalexpences;
   cout<<"Total Income : "<<totalincome<<endl;
   cout<<"Total Expense : "<<totalexpences<<endl;
   cout<<"Total Balance : "<<balance<<endl;

}

void categorysummary(){

    map<string,double>categorytotals;

    for (int i = 0; i < transactioncount; i++)
    {
        categorytotals[transactions[i].category]+= transactions[i].amount; // it will go through all the transactions add the all the similar catehory amount to the amount.
    }

   cout << "Category-wise Summary : \n";

   for (const auto& category : categorytotals) // "Category" - is iterator for "categorytotal" map
   {
    cout<<"Category : "<< category.first <<" , Total amount : "<<category.second << '\n';
   }
   
}

 void monthlyreport(int month, int year){
    double totalincome=0,totalexpense=0,balance=0;

    for (int i = 0; i < transactioncount; i++)
    {
        int transmonth,transyear;
        stringstream sso(transactions[i].date);
        char mark; // mark is like " - " between the dates we use usually.
        sso>>transyear>>mark>>transmonth; 

        if(transmonth == month && transyear==year){
            if(transactions[i].type=="income"){
                totalincome+=transactions[i].amount;
            }
            else if(transactions[i].type=="expense"){
                totalexpense+=transactions[i].amount;
            }
            
        }
    }

    balance=totalincome-totalexpense;
    cout<<"Monthly report for " <<month<<"/"<<year<<"\n";
    cout<<"Total income : "<<totalincome<<endl;
    cout<<"Total expense : "<<totalexpense<<endl;
    cout<<"Total Balance : "<< balance<<endl;
    
 }

 //Setting categorgy wise Budget

 map<string,double>categorybudgets;

 void setbudget(string category,double budget){
    categorybudgets[category]=budget;
    cout<<"Budget set for given Category"<<category<<" : "<<budget<<endl;
 }

 void trackbudget(){
    map<string,double>categoryspending;

    for (int i = 0; i < transactioncount; i++)
    {
    if(transactions[i].type=="expense"){
        categoryspending[transactions[i].category]+=transactions[i].amount;
        }
    }

    cout<<"Budget tracking : "<<endl;
    for (const auto& budget : categorybudgets)
    {
        string category=budget.first;
        double budgetamount=budget.second;
        double spentamount=categoryspending[category];
        cout<<"Category : "<<category<<endl;
        cout<<"Budget : "<<budgetamount<<endl;
        cout<<"Spent : "<<spentamount;

        if(spentamount>budgetamount){
            cout<<"OVER-BUDGET !";
        }
        cout<<endl;
    }
    
    
 }

 void exportdata(){
    ofstream file("transactions.csv");

    file<<"ID,Date,Amount,Category,Type \n";
    for (int i = 0; i < transactioncount; i++)
    {
    file<<transactions[i].id<<','<<transactions[i].date<<','<<transactions[i].amount<<','<<transactions[i].category<<','<<transactions[i].type<<endl;
    }
    file.close();
    cout<<"Data exported to transactions.csv \n";
 }


int main(){

    int choice;

    do
    {
    
    cout<<"1. Add Transaction \n 2. Delete Transaction \n 3. View Transaction \n 4. Update transaction \n 5. Generate Summary \n 6. Category-wise summary \n 7. Monthly Report \n 8. Set Budget \n 9. Track Budget \n 10. Export Data \n 11. Exit \n \n  Choose an option : ";
    cin>>choice;

    if(choice==1){
        string date,category,type;
        double amount;

        cout<<"Enter date (YYYY-MM-DD): ";
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
        cout<<"Enter transaction ID to delete : ";
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

        cout<<"Enter transaction ID to update : ";
        cin>>id;

        cout<<"Enter new Date : ";
        cin>>newdate;

        cout<<"Enter new amount : ";
        cin>>newamount;

        cout<<"Enter new category : ";
        cin>>newcategory;

        cout<<"Enter new type : ";
        cin>>newtype;

        update(id,newdate,newamount,newcategory,newtype);

    }
    else if(choice==5){
        summary();
    }

    else if(choice==6){
        categorysummary();
    }
    else if(choice == 7){
        int month ,year;
        cout<<"enter month (1-12) : ";
        cin>>month;

        cout<<"Enter year (20__ format) : ";
        cin>>year;

        monthlyreport(month,year);
    }
    else if(choice==8){
        string category;
        double budget;
        cout<<"Enter category : ";
        cin>>category;

        cout<<"Enter budget : ";
        cin>>budget;

        setbudget(category,budget);
    }
    else if(choice==9){
        trackbudget();
    }
    else if(choice==10){
        exportdata();
    }

    else if(choice==11){
        cout<<"Exiting... \n";
    }

    else{
        cout<<"Invalid choice ! please try again later \n";
    }
    
    }
    while(choice!=11); // This means the loop should keep executing as long as the user's choice is not 6.

    return 0;
} 