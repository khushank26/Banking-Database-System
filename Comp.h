#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>
using namespace std;

class Comp : public BaseClass
{
public:
    Comp();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

private:
    int size;
    vector<int> v1;
    void mergeSort(vector<int> &arr, int left, int right);
    void merge(vector<int> &arr, int left, int mid, int right);
    long long pow(int b, int p, int s);
    int ord(char a);
};

#endif // COMP_H
