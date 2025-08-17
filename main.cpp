#include "header.h"

class BankAccount{
    private:
    
    int accountNumber;
    
    double balance;
    
    public:
    BankAccount(const std::string & Name, double initialBalance,const int accountNum): username(Name), balance(initialBalance), accountNumber(accountNum) {}
    BankAccount() : username(""),balance(0.0),accountNumber(0){}
    std::string username;
    void deposit(double amount){
        balance+=amount;
        std::cout<< "You are depositing $"<< amount << "\nYou now have $" << balance <<" in your account.\n";
    }
     void withdraw(double amount){
        if (amount <= balance){
            balance-=amount;
            std::cout<< "You are withdrawing $"<< amount <<"." << "\nYou now have $" << balance <<" in your account.\n";
        }else{
            std::cout << "You do not have the funds in your account to make the withdrawal.\n";
        }
    }
    
};

int randNum() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(100000, 999999); // 6-digit number
        return dist(gen);
    }

int openingAcc(std::unordered_map<int,BankAccount>& accounts, double openingAmt){
    
    int accountNum;
    while(1){
        accountNum=randNum();
        if (accounts.find(accountNum)==accounts.end()){
            break;
        }
    }
    
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your initial deposit balance: ";
    std::cin >> openingAmt;
    accounts.emplace(accountNum,BankAccount(name,openingAmt,accountNum));
    return accountNum;
}
int main(){
    std::unordered_map<int,BankAccount> accounts;
    
    bool check{true};
    int selection{0};
    double openingAmount{0}, withdrawAmount, depositAmount;
    int newAcc;
    int accountNum;
    std::cout<<"Would you like to log in or create a new account?(1/2)\n";
    std::cin>>newAcc;
    if (newAcc==1){
        accountNum=openingAcc(accounts, openingAmount);
    }
    while(check){
        std::cout << "What would you like to do today?\n1. Deposit\n2. Withdraw\n3. Leave\n:";
        std::cin >> selection;
        if (selection<1 || selection>4){
            std::cout << "Please choose a valid option.\n";
            continue;
        }else if(selection == 1){
            std::cout << "Enter Deposit Amount: ";
            std::cin >> depositAmount;
            if(accounts.find(accountNum)!=accounts.end()){
                accounts[accountNum].deposit(depositAmount);
            }
            else{
                std::cout<<"Account not found\n";
            }
        }else if(selection == 2){
            std::cout << "Enter Withdraw Amount: ";
            std::cin >> withdrawAmount;
            if(accounts.find(accountNum)!=accounts.end()){
                accounts[accountNum].withdraw(withdrawAmount);
            }
            else{
                std::cout<<"Account not found\n";
            }
            
        } else if(selection == 3){
            std::cout << "Leaving";
            break;
        }
    }

    return 0;
}