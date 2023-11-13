#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
const int n = 7;

struct job{
    int deadline;
    int profit;
};

int* sort(job* arr){                                                // insert sort, vracia pole deadlinov
    int i, key, key2, j;
    for (i = 1; i < n; i++) {
        key = arr[i].profit;
        key2 = arr[i].deadline;
        j = i - 1;
        while (arr[j].profit <= key && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1].profit = key;
        arr[j + 1].deadline = key2;
    }
    int* deadlines = new int[n];
    for (i = 0; i < n; i++){
        deadlines[i] = arr[i].deadline;
    }
    return deadlines;
}


string isFeasible(string sequence, string deadlines){               // prejde vsetky permutacie novej sekvencie
    string sequence2 = sequence;                                    // ak najde nejaku splnitelnu, vrati ju
    sequence2.erase(sequence2.length() -1);                    // ak nenajde, vrati povodnu sekvenciu
    do{
        string output;
        for(int i = 0; i < sequence.length(); i++){
            char s = sequence[i];
            int d = deadlines[((s - '0') - 1)] - '0';
            if(d >= (i + 1)){
                output += sequence[i];
            }
        }
        if(output.length() == sequence.length()){
            return output;
        }
    } while(next_permutation(sequence.begin(), sequence.end()));
    return sequence2;
}


void schedule(int* deadlines){                                        // vypise optimalnu sekvenciu
    string Deadlines;
    for (int i =0; i < n; i++){
        Deadlines += to_string(deadlines[i]);
    }
    string sequence_final = "1", sequence_temp;
    for (int i = 2; i <= n; i++){
        sequence_temp = sequence_final + to_string(i);
        sequence_final = isFeasible(sequence_temp, Deadlines);
    }
    cout << "Optimal sequence of jobs: " << endl;
    for(char i : sequence_final){
        cout << i << " ";
    }
}


int main(){
    job arr[] = {{2, 40}, {4, 15}, {3, 60}, {2, 20}, {3, 10}, {1, 45}, {1,55}};
    int* deadlines = sort(arr);
    cout << "Array of jobs sorted by profit: " << endl;
    for(int i = 0; i < n; i++){
        cout << "Job: " << i+1 << ", Deadline: " << arr[i].deadline << ", Profit: " << arr[i].profit << endl;
    }
    schedule(deadlines);
}