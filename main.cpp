#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Make a set unique by removing values from it.
 */
vector<int> *uniq(vector<int> *set) {
    sort(set->begin(), set->end());
    set->erase(unique(set->begin(), set->end()), set->end());

    return set;
}

/**
 * Allows simple debugging because it lets us read the vector.
 * @param message  Name to display in the logs<
 * @param myVector The vector to display.
 */
void vectorToString(string message, vector<int> *myVector) {
    cout << "Reading vector named '" << message << "'." << endl;
    cout << "\tPointer: " << myVector << endl;
    cout << "\tNull: " << (myVector == NULL ? "true" : "false") << endl;
    for(int i = 0, j = myVector->size(); i < j; i++) {
        cout << "\t" << myVector->at(i) << endl;
    }
    cout << "End of vector '" << message << "'." << endl;
}

/**
 * Gives the factors of a number.
 * @param number The given number where all returned numbers are factors of.
 * @param result List of results.
 */
void findAllFactorsOf(int number, vector<int> *result) {
    int i = 0, j = number*number;
    // Begins by 2 because 1 is always a diviser and is not included in
    // the solution set
    for(i = 2; i < j; i++) {
        if(number % i == 0) {
            result->push_back(i);
        }
    }
}

/**
 * This function finds the common numbers between two sets.
 * Returns the new result list.
 */
vector<int>* commonNumberMatcher(vector<int> *set1, vector<int> *set2) {
    vector<int> *result = new vector<int>();
    vector<int> *smallSet = NULL;
    vector<int> *bigSet = NULL;

    // Getting the minimum set to optimise parsing?
    if(set1->size() < set2->size()) {
        smallSet = set1;
        bigSet = set2;
    } else {
        smallSet = set2;
        bigSet = set1;
    }

    // Trying to find each elements in both sets and store the right one
    for(int i = 0, j = smallSet->size(); i < j; i++) {
        int currentAnalysedElement = smallSet->at(i);

        for(int m = 0, n = bigSet->size(); m < n; m++) {
            if(currentAnalysedElement == bigSet->at(m)) {
                result->push_back(currentAnalysedElement);
                continue;
            }
        }
    }

    return result;
}

/**
 * Find the common factors in the set of numbers given.
 * 1) find factors of each numbers
 * 2) find common factors between all
 * return common factors.
 */
vector<int> *commonFactorsIn(vector<int> *setOfIntegers) {
    vector<int> *result = new vector<int>();
    vector<int> *result_storage = new vector<int>();
    vector<int> *temp = new vector<int>();

    // First iteration: we find all factor numbers
    findAllFactorsOf(setOfIntegers->at(0), result);

    // If there is only one integer, return the factors of the first integer.
    if(setOfIntegers->size() == 1)
        return result;

    // All next iterations:
    // - do the same thing as step 1
    // - and keep common factors
    // - also free memory
    for(int i = 1, j = setOfIntegers->size(); i < j; i++) {
        findAllFactorsOf(setOfIntegers->at(i), temp);
        result_storage = commonNumberMatcher(result, temp);
        delete result;
        delete temp;
        temp = new vector<int>();
        result = result_storage;
    }

    delete temp;

    return result;
}

vector<int> *firstSetAreFactorsOfSecondSet(vector<int> *setA, vector<int> *setB) {
    vector<int> *result = new vector<int>();
    bool saveValue = true;

    // for each value in the set B, check that all values of setA are factors of it.
    for(int b_i = 0, b_j = setB->size(); b_i < b_j; b_i++) {
        for(int a_i = 0, a_j = setA->size(); a_i < a_j; a_i++) {
            if(setB->at(b_i) % setA->at(a_i) != 0) {
                saveValue = false;
            }
        }
        // add value if okay
        if(saveValue) {
            result->push_back(setB->at(b_i));
        }
        // reset conditions
        saveValue = true;
    }

    return result;
}

int main(int argc, char *argv[]) {
    int n, m;

    cin >> n >> m;

    vector<int> a(n);
    for(int a_i = 0; a_i < n; a_i++) {
        cin >> a[a_i];
    }
    vector<int> b(m);
    for(int b_i = 0; b_i < m; b_i++) {
        cin >> b[b_i];
    }

    cout << "n: " << n << endl;
    cout << "m: " << m << endl;


    vectorToString("a", &a);
    vectorToString("b", &b);

    // Find the common factors of all the numbers in b
    vector<int> *factors_b = uniq(commonFactorsIn(&b));

    vectorToString("factors_b", factors_b);

    vector<int> *between_x = firstSetAreFactorsOfSecondSet(&a, factors_b);

    vectorToString("between_x", between_x);

    cout << " >>> " << between_x->size() << endl;

    return 0;
}
