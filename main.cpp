#include "header.hpp"
#include "json.hpp"

using json = nlohmann::json;

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
    double getBalance() const {
        return balance;
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
    std::cout<<"Your account number is "<<accountNum<<'\n';
    return accountNum;
}

void bankOps(std::unordered_map<int,BankAccount>& accounts, int accountNumber){
    double withdrawAmount, depositAmount;
    int selection{0};
    while(true){
        std::cout << "What would you like to do today?\n1. Deposit\n2. Withdraw\n3. Log Out\n:";
        std::cin >> selection;
        if (selection<1 || selection>4){
            std::cout << "Please choose a valid option.\n";
            continue;
        }else if(selection == 1){
            std::cout << "Enter Deposit Amount: ";
            std::cin >> depositAmount;
            if(accounts.find(accountNumber)!=accounts.end()){
                accounts[accountNumber].deposit(depositAmount);
            }
            else{
                std::cout<<"Account not found\n";
            }
        }else if(selection == 2){
            std::cout << "Enter Withdraw Amount: ";
            std::cin >> withdrawAmount;
            if(accounts.find(accountNumber)!=accounts.end()){
                accounts[accountNumber].withdraw(withdrawAmount);
            }
            else{
                std::cout<<"Account not found\n";
            }
            
        } else if(selection == 3){
            std::cout << "Leaving\n";
            break;
        }
    }
}
void startup(std::unordered_map<int, BankAccount> &accounts, const std::string& filename){
    std::ifstream i(filename);
    if (!i.is_open()){
        std::cout<<"Could not open file.\n";
        return;
    }
    json j;
    i >> j;
    
    for (auto& [key,items] : j.items()){
        int accountNum = std::stoi(key);
        std::string name = items["name"];
        double openingAmt = items["balance"];
        accounts.emplace(accountNum,BankAccount(name,openingAmt,accountNum));
    }
    

}
void saveMap(std::unordered_map<int,BankAccount> &accounts, const std::string& filename){
    json j;
    for (const auto& [accNum, acc] : accounts) {
        j[std::to_string(accNum)] = {
            {"name", acc.username},
            {"balance", acc.getBalance()}
        };
    }
     std::ofstream o("accounts.json");
    o << std::setw(4) << j << std::endl;

}

int main(){
    std::unordered_map<int,BankAccount> accounts;
    startup(accounts,"accounts.json");
    double openingAmount{0};
    int newAcc;
    int accountNum;
    while(true){
        std::cout<<"Would you like to log in or create a new account?(1/2)\n";
        std::cin>>newAcc;
        if (newAcc==2){
            accountNum=openingAcc(accounts, openingAmount);
        }
        if (newAcc==1){
            while(true){
                std::cout<< "Please enter your account number: ";
                std::cin>>accountNum;
                if (accounts.find(accountNum)!=accounts.end()&&accountNum!=0){
                    break;
                }
                std::cout<<"Number not valid\n";
                }
        }
        if (newAcc==3){
            break;
        }

        bankOps(accounts,accountNum);
    
    }
    saveMap(accounts, "accounts.json");
    return 0;
}