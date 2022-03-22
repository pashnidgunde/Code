#include <iostream>
#include <vector>
using namespace std;
 
// Function to print a given set
void printSet(int n , vector<int> const &input)
{
    cout << n << " : [";
    for (int i: input) {
        cout << i;
        if (--n) {
            cout << ", ";
        }
    }
    cout << "]\n";
}
 
// Function to generate power set of a given set `S`
void printPowerSet(vector<int> const &S, vector<int> &set, int n)
{
    printSet(S.size(),set);

    // if we have considered all elements
    if (n == S.size())
    {
        printSet(S.size(),set);
        return;
    }
 
    set.push_back(S[n]);
    printPowerSet(S, set, n + 1);
    printSet(S.size(),set);

    set.pop_back();                    // backtrack
 
    // or don't consider the n'th element
    printPowerSet(S, set, n + 1);
}
 
// Wrapper over `printPowerSet()` function
void findPowerSet(vector<int> const &S)        // no-ref, no-const
{
    // create an empty vector to store elements of a subset
    vector<int> set;
    printPowerSet(S, set, 0);
}
 
int main()
{
    vector<int> S = { 1, 2, 3 };
 
    findPowerSet(S);
 
    return 0;
}