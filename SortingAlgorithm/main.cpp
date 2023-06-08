#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;

int Partition(vector<int> &v, int start, int end){
    int pivot = end;
    int j = start;
    for(int i = start; i < end; ++i){
        if(v[i] < v[pivot]){
            swap(v[i], v[j]);
            ++j;
        }
    }
    swap(v[j], v[pivot]);
    return j;
    
}

void Quicksort(vector<int> &v, int start, int end){
    if(start < end){
        int p = Partition(v, start, end);
        
        Quicksort(v, start, p - 1);
        Quicksort(v, p + 1, end);
    }
}


vector<vector<int>> organizeInIntervals(vector<int> v, int start, int end, vector<int>* intervalLimits, int* amp) {
    int range             = v[end] - v[start];
    int numberOfIntervals = 2 + int(3.322 * log10(v.size()));
    int amplitude         = 1 + int(range / numberOfIntervals);
    
    vector<int> limits;
    
    for(int i = 0; i < numberOfIntervals; i++) {
        if(limits.empty()) {
            limits.push_back(v[i] + amplitude);
        }
        else {
            limits.push_back(limits[(i - 1)] + amplitude);
        }
    }
    
    vector<vector<int>> vOfIntervals;
    vector<int>::iterator ptr = v.begin();
    
    int limitCounter = 0;
    int counter = 0;
    for(int i = 0; i < numberOfIntervals; i++) {
        vOfIntervals.push_back(vector<int>());
        
        for(int j = 0; ptr != v.end(); j++) {
            ptr++;
            vOfIntervals[i].push_back(v[counter]);
            
            if(v[counter + 1] >= limits[i]) {
                limitCounter++;
                counter++;
                break;
            }
            counter++;
        }
    }
    
    *intervalLimits = limits;
    *amp            = amplitude;
    return vOfIntervals;
}


void PrintVector(vector<int> v){
    for(int i = 0; i < v.size(); ++i)
        cout<<v[i]<<" ";
    cout<<"\n\n";
    
    cout << "The biggest number was: " << v[int(v.size()) - 1] << endl;
    cout << "The smallest number was: " << v[0] << endl;
    
    cout << "\n";
}

int main() {
    system("clear");
    
    int amplitude;

    int n = 0;
    cout << "Enter the number of elements you array will have: ";
    cin >> n;

    cout << "\n";

    vector<int> v;

    cout << "Enter the elements of the array (separated by a space): " << endl;

    int x;
    for(int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }
    
    cout << "\n";
    
    Quicksort(v, 0, int(v.size()) - 1);
    
    cout << "Sorted Array: " << endl;
    PrintVector(v);
    
    vector<int> limits;
    vector<vector<int>> intervals = organizeInIntervals(v, 0, int(v.size() - 1), &limits, &amplitude);
    
    float classMarks[intervals.size()];
    unsigned long int absoluteFrequency[intervals.size()];
    double relativeFrequency[intervals.size()];
    unsigned long int accumulatedAbsoluteFrequency[intervals.size()];
    float accumulatedRelativeFrquency[intervals.size()];
    
    for(int i = 0; i < intervals.size(); i++) {
        classMarks[i] = (intervals[i][0] + limits[i]) / 2;
        absoluteFrequency[i] = intervals[i].size();
        relativeFrequency[i] = (double(absoluteFrequency[i]) / n) * 100;
        
        if(i == 0) {
            accumulatedAbsoluteFrequency[i] = intervals[i].size();
        }
        else {
            accumulatedAbsoluteFrequency[i] = absoluteFrequency[i] + accumulatedAbsoluteFrequency[i - 1];
        }
        
        accumulatedRelativeFrquency[i] = (double(accumulatedAbsoluteFrequency[i]) / n) * 100.0;
    }
    
    cout << left << setw(15) << "Intervals" << left << setw(10) << "ni" << left << setw(10)<< "fr%" << left << setw(10) << "Ni" << left << setw(10) << "Fr%" << endl;
    
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    
    for(int i = 0; i < intervals.size(); i++) {
        cout << "[" << limits[i] - amplitude << "; " << limits[i] << left << setw(6) << ")" << left << setw(10) << absoluteFrequency[i] << relativeFrequency[i] << left << setw(6) << "%" << left << setw(10) << accumulatedAbsoluteFrequency[i] << accumulatedRelativeFrquency[i] << "%" << endl;
    }
}
