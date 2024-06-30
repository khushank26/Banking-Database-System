#include "Comp.h"
#include <iostream>
using namespace std;
Comp::Comp()
{
    size = 0;
    for (int i = 0; i < 100003; i++)
    {
        bankStorage2d.push_back({});
    }
}
void Comp::createAccount(std::string id, int count)
{
    Account a;
    a.balance = count;
    a.id = id;
    int k = hash(id);
    bankStorage2d[k].push_back(a);
    size++;
    v1.push_back(count);
}
int Comp::ord(char a)
{
    int x = a;
    return x - 55;
}
long long Comp::pow(int b, int p, int s)
{

    int temp;
    if (p == 0)
        return 1;
    temp = pow(b, p / 2, s);
    if (p % 2 == 0)
        return (temp * temp) % s;
    else
    {

        return (static_cast<long long>(b) * temp * temp) % s;
    }
}
std::vector<int> Comp::getTopK(int k)
{
    vector<int> v2;
    mergeSort(v1, 0, v1.size() - 1);

    int i = v1.size() - 1;
    while (v2.size() != k)
    {
        v2.push_back(v1[i]);
        i--;
    }
    return v2;
}

int Comp::getBalance(std::string id)
{
    int k = hash(id);
    auto it = bankStorage2d[k].begin();

    while (it != bankStorage2d[k].end())
    {
        if (it->id == id)
        {
            return it->balance;
        }
        it++;
    }

    return -1;
}
void Comp::merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void Comp::mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void Comp::addTransaction(std::string id, int count)
{
    if (!doesExist(id))
    {
        createAccount(id, count);
    }
    else
    {
        int a = getBalance(id);
        int k = hash(id);

        for (int i = 0; i < v1.size(); i++)
        {
            if (v1[i] == a)
            {
                v1.erase(v1.begin() + i);
                break;
            }
        }

        auto it = bankStorage2d[k].begin();
        while (it != bankStorage2d[k].end())
        {
            if (it->id == id)
            {
                it->balance = it->balance + count;

                v1.push_back(it->balance);

                break;
            }
            it++;
        }
    }
}

bool Comp::doesExist(std::string id)
{
    int k = hash(id);
    auto it = bankStorage2d[k].begin();
    while (it != bankStorage2d[k].end())
    {
        if (it->id == id)
        {
            return true;
        }
        it++;
    }
    return false;
}

bool Comp::deleteAccount(std::string id)
{
    if (!doesExist(id))
    {
        return false;
    }
    else
    {
        int k = hash(id);
        int a = getBalance(id);
        auto it = bankStorage2d[k].begin();
        for (int i = 0; i < v1.size(); i++)
        {
            if (v1[i] == a)
            {
                v1.erase(v1.begin() + i);
                break;
            }
        }
        while (it != bankStorage2d[k].end())
        {
            if (it->id == id)
            {
                bankStorage2d[k].erase(it);
                size--;
                return true;
            }
            it++;
        }
        return false;
    }
}
int Comp::databaseSize()
{
    return size;
}

int Comp::hash(string id)
{
    int m = 100003;
    int nm = 0;
    for (int i = 0; i < 4; i++)
    {
        nm = nm + (ord(id[i]) * (pow(37, 20 - i, 100003))) % 100003;
    }
    for (int i = 0; i < 7; i++)
    {
        nm = nm + ((id[i + 4]) * (pow(37, 16 - i, 100003))) % 100003;
    }
    for (int i = 0; i < 10; i++)
    {
        nm = nm + ((id[i + 12]) * (pow(37, 9 - i, 100003))) % 100003;
    }
    return nm % 100003;
}
// int main()
// {
//     Comp l;
//     l.createAccount("CDAD7786825_7990768648", 648);
//     l.createAccount("DCDA7547234_9919615552", 552);
//     l.createAccount("AACB1850545_7974534788", 788);
//     cout << l.databaseSize() << endl;
//     l.createAccount("CDBD5250777_1124276711", 711);
//     l.createAccount("ABCB8377155_0656808575", 575);
//     for (auto i : l.getTopK(1))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.createAccount("CDDC3792028_3313680038", 38);
//     l.createAccount("CBBA9574444_7470182321", 321);
//     l.createAccount("DBCC4334636_8057544188", 188);
//     for (auto i : l.getTopK(3))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.createAccount("BABD5741078_5109455304", 304);
//     l.createAccount("BCBA7529510_0817878868", 868);
//     cout << l.databaseSize() << endl;
//     for (auto i : l.getTopK(1))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.addTransaction("BCBA7529510_0817878868", -860);
//     cout << l.getBalance("BCBA7529510_0817878868") << endl;
//     for (auto i : l.getTopK(1))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.addTransaction("DCDA7547234_9919615552", 592);
//     for (auto i : l.getTopK(5))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.deleteAccount("DCDA7547234_9919615552");
//     for (auto i : l.getTopK(4))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     cout << l.databaseSize() << endl;
// }

// int main()
// {
//     Comp l;
//     l.createAccount("CDAD7786825_7990768648", 648);
//     l.createAccount("DCDA7547234_9919615552", 552);
//     l.createAccount("AACB1850545_7974534788", 788);
//     cout << l.databaseSize() << endl;
//     l.createAccount("CDBD5250777_1124276711", 711);
//     l.createAccount("ABCB8377155_0656808575", 575);
//     for (auto i : l.getTopK(1))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.createAccount("CDDC3792028_3313680038", 38);
//     l.createAccount("CBBA9574444_7470182321", 321);
//     l.createAccount("DBCC4334636_8057544188", 188);
//     for (auto i : l.getTopK(3))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.createAccount("BABD5741078_5109455304", 304);
//     l.createAccount("BCBA7529510_0817878868", 868);
//     cout << l.databaseSize() << endl;
//     for (auto i : l.getTopK(1))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.addTransaction("BCBA7529510_0817878868", -860);
//     cout << l.getBalance("BCBA7529510_0817878868") << endl;
//     for (auto i : l.getTopK(1))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.addTransaction("DCDA7547234_9919615552", 592);
//     for (auto i : l.getTopK(5))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     l.deleteAccount("DCDA7547234_9919615552");
//     for (auto i : l.getTopK(4))
//     {
//         cout << i << " ";
//     }
//     cout << endl;
//     cout << l.databaseSize() << endl;
// }
