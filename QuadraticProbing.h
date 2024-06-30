#ifndef QUADRATICPROBING_H
#define QUADRATICPROBING_H

#include "BaseClass.h"
#include <iostream>
using namespace std;

class QuadraticProbing : public BaseClass
{
public:
    QuadraticProbing();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

private:
    int m;
    int size;
    vector<int> v1;
    void mergeSort(vector<int> &arr, int left, int right);
    void merge(vector<int> &arr, int left, int mid, int right);
    int pow(int b, int p, int m);
    int ord(char a);
};

#endif // QUADRATICPROBING_H
