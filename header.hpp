#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>


class BankAccount;

int randNum();
int openingAcc(std::unordered_map<int,BankAccount>& accounts, double openingAmt);
void bankOps(std::unordered_map<int,BankAccount>& accounts, int accountNumber);
void startup(std::unordered_map<int, BankAccount> &accounts, const std::string& filename);
void saveMap(std::unordered_map<int,BankAccount> &accounts, const std::string& filename);

int main();