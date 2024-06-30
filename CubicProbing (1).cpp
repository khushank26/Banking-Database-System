#include "CubicProbing.h"

CubicProbing::CubicProbing()
{

    size = 0;
    Account a;
    a.balance = 0;
    a.id = "0";
    for (long long i = 0; i < 100019; i++)
    {
        bankStorage1d.push_back(a);
    }
}
long long CubicProbing::pow(int b, int p, int s)
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
void CubicProbing::createAccount(std::string id, int count)
{
    int m = 100019;
    int k = hash(id);
    int a = hash(id);
    Account a1;
    a1.balance = count;
    a1.id = id;
    long long i = 0;
    while (bankStorage1d[k].id != "0")
    {

                long long temp = i;
        temp = (temp*i)%m;
        temp = (temp*i)%m;
        k = (a+temp)%m;
        i++;
    }
    bankStorage1d[k] = a1;
    size++;
    v1.push_back(count);
}

std::vector<int> CubicProbing::getTopK(int k)
{

    vector<int> v2;
    if (v1.size() == 0)
        return vector<int>();
    mergeSort(v1, 0, v1.size() - 1);

    long long i = v1.size() - 1;
    while (v2.size() != k)
    {
        v2.push_back(v1[i]);
        i--;
    }
    return v2;
}

int CubicProbing::getBalance(std::string id)
{
    int m = 100019;
    int a = hash(id);
    int k = hash(id);
    long long i = 0;
    while (bankStorage1d[k].id != id)
    {

                long long temp = i;
        temp = (temp*i)%m;
        temp = (temp*i)%m;
        k = (a+temp)%m;
        i++;
        if (i == m)
        {
            return -1;
        }
    }

    return bankStorage1d[k].balance;
}

void CubicProbing::addTransaction(std::string id, int count)
{
    int a = hash(id);
    int k = hash(id);
    int m = 100019;
    long long i = 0;
    while (bankStorage1d[k].id != id)
    {
                long long temp = i;
        temp = (temp*i)%m;
        temp = (temp*i)%m;
        k = (a+temp)%m;
        i++;
        if (i == m)
        {
            createAccount(id, count);
            return;
        }
    }
    int b = bankStorage1d[k].balance;
    for (int j = 0; j < v1.size(); j++)
    {
        if (v1[j] == b)
        {
            v1.erase(v1.begin() + j);
            break;
        }
    }
    bankStorage1d[k].balance = bankStorage1d[k].balance + count;
    v1.push_back(bankStorage1d[k].balance);
}
void CubicProbing::merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (long long i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (long long i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    long long i = 0, j = 0, k = left;

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

void CubicProbing::mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

bool CubicProbing::doesExist(std::string id)
{
    int a = hash(id);
    int k = hash(id);
    int m = 100019;
    long long i = 0;
    while (bankStorage1d[k].id != id)
    {
                long long temp = i;
        temp = (temp*i)%m;
        temp = (temp*i)%m;
        k = (a+temp)%m;
        i++;
        if (i == m)
        {
            return false;
        }
    }
    if (bankStorage1d[k].id == id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CubicProbing::deleteAccount(std::string id)
{
    int k = hash(id);
    int a = k;
    int m = 100019;
    long long i = 0;
    while (bankStorage1d[k].id != id)
    {
                long long temp = i;
        temp = (temp*i)%m;
        temp = (temp*i)%m;
        k = (a+temp)%m;
        i++;
        if (i == m)
        {
            return false;
        }
    }
    for (int j = 0; j < v1.size(); j++)
    {
        if (v1[j] == bankStorage1d[k].balance)
        {
            v1.erase(v1.begin() + j);
            break;
        }
    }

    bankStorage1d[k].id = "0";
    bankStorage1d[k].balance = 0;
    size--;
    return true;
}
int CubicProbing::databaseSize()
{

    return size;
}

int CubicProbing::ord(char a)
{
    int x = a;
    return x - 55;
}

int CubicProbing::hash(string id)
{
    int m = 100003;
    int nm = 0;
    for (int j = 0; j < 4; j++)
    {
        nm = nm + (ord(id[j]) * (pow(37, 20 - j, 100003))) % 100003;
    }
    for (int j = 0; j < 7; j++)
    {
        nm = nm + ((id[j + 4]) * (pow(37, 16 - j, 100003))) % 100003;
    }
    for (int j = 0; j < 10; j++)
    {
        nm = nm + ((id[j + 12]) * (pow(37, 9 - j, 100003))) % 100003;
    }
    return nm % 100019;
}
// int main()
// {
//     CubicProbing l;
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
