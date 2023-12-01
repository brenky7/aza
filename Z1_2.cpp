#include <iostream>
#include <string>
#include "disjoint_sets.cpp"
using namespace std;
const int n = 7;


// struktura jobu
struct job{
    int id;
    int deadline;
    int profit;
};


// insert sort, zoradi pole jobov podla profitu
void sort(job* arr){
    int i, key, key2, key3, j;
    for (i = 1; i < n; i++) {
        key = arr[i].profit;
        key2 = arr[i].deadline;
        key3 = arr[i].id;
        j = i - 1;
        while (arr[j].profit <= key && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1].profit = key;
        arr[j + 1].deadline = key2;
        arr[j + 1].id = key3;
    }
}


// vypise optimalne naplanovanie jobov
void schedule(job* jobs){
    // najdem maximalny deadline - treba na vytvorenie mnoziny U
    int max_deadline = jobs[0].deadline;
    for (int i = 1; i < n; i++){
        if (jobs[i].deadline > max_deadline){
            max_deadline = jobs[i].deadline;
        }
    }
    // pomocna funkcia na vytvorenie universe
    string U = make_universe(max_deadline);
    // sets predstavuje moj universe, v ktorom su jednoprvkove mnoziny
    string* sets = new string[U.length()];
    for (int i = 0; i < U.length(); i++) {
        sets[i] = make_set(U[i]);
    }
    // mnozina jobov, ktore budu vysledne naplanovane
    job* scheduled_jobs = new job[max_deadline];

    // planovaci algoritmus podla zadania 2
    for (int i = 0; i < n; i++){
        int min_deadline = min(jobs[i].deadline, max_deadline);
        string* p1 = find(to_string(min_deadline), sets);
        int smallest = small(p1);
        if (smallest != 0){
            string* p2 = find(to_string(min_deadline - 1), sets);
            sets = merge(p2, p1, sets);
            scheduled_jobs[min_deadline] = jobs[i];
        }
    }
    // vypis naplanovanych jobov
    cout << "Scheduled jobs: " << endl;
    for (int i = 1; i <= max_deadline; i++){
        cout << "Job id: " << scheduled_jobs[i].id << ", Deadline: " << scheduled_jobs[i].deadline << ", Profit: " << scheduled_jobs[i].profit << endl;
    }
}


int main(){

    // vytvorenie pola jobov
    job arr[] = {
            {1,2, 40},
            {2,4, 15},
            {3,3, 60},
            {4,2, 20},
            {5,3, 10},
            {6,1, 45},
            {7,1,55}
    };

    // zoradenie pola podla profitu
    sort(arr);

    // vypis celeho pola jobov, zoradeneho podla profitu
    cout << "Array of jobs sorted by profit: " << endl;
    for(auto & i : arr){
        cout << "Job id: " << i.id << ", Deadline: " << i.deadline << ", Profit: " << i.profit << endl;
    }
    cout << endl;

    // naplanovanie jobov
    schedule(arr);
    return 0;
}