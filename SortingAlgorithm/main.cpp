#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>

using namespace std;

int Partition(vector<float> &v, int start, int end){
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

void Quicksort(vector<float> &v, int start, int end){
    if(start < end){
        int p = Partition(v, start, end);
        
        Quicksort(v, start, p - 1);
        Quicksort(v, p + 1, end);
    }
}


vector<vector<float>> organizeInIntervals(vector<float> v, int start, int end, vector<float>* intervalLimits, float* amp) {
    float range             = v[end] - v[start];
    float numberOfIntervals = 2 + int(3.322 * log10(v.size()));
    float amplitude         = 1 + int(range / numberOfIntervals);
    
    vector<float> limits;
    
    for(int i = 0; i < numberOfIntervals; i++) {
        if(limits.empty()) {
            limits.push_back(v[i] + amplitude);
        }
        else {
            limits.push_back(limits[(i - 1)] + amplitude);
        }
    }
    
    vector<vector<float>> vOfIntervals;
    vector<float>::iterator ptr = v.begin();
    
    vector<string> _intervalLimits;
    
    int limitCounter = 0;
    int counter = 0;
    for(int i = 0; i < numberOfIntervals; i++) {
        vOfIntervals.push_back(vector<float>());
        
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


void PrintVector(vector<float> v){
    for(int i = 0; i < v.size(); ++i)
        cout<<v[i]<<" ";
    cout<<"\n\n";
    
    cout << "The biggest number was: " << v[int(v.size()) - 1] << endl;
    cout << "The smallest number was: " << v[0] << endl;
    
    cout << "\n";
}

int main() {
    system("clear");
    
    float amplitude;

    int n = 0;
    cout << "Enter the number of elements you array will have: ";
    cin >> n;

    cout << "\n";

    vector<float> v;

    cout << "Enter the elements of the array (separated by a space): " << endl;

    float x;
    for(int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }
    
    cout << "\n";
    
    Quicksort(v, 0, int(v.size()) - 1);
    
    cout << "Sorted Array: " << endl;
    PrintVector(v);
    
    vector<float> limits;
    vector<vector<float>> intervals = organizeInIntervals(v, 0, int(v.size() - 1), &limits, &amplitude);
    
    cout << "This is a test change" << endl;
    
    float classMarks[intervals.size()];
    unsigned long int absoluteFrequency[intervals.size()];
    float relativeFrequency[intervals.size()];
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
    
    int colwidth = 15;
    
    cout << setfill('-') << setw(7 * colwidth) << "-" << endl;
    cout << setfill(' ') << fixed;
    
    cout << "Intervals" << setw(colwidth) << "xi" << setw(colwidth)<< "ni" << setw(colwidth) << "fr%" << setw(colwidth) << "Ni" << setw(colwidth) << "Fr%" << endl;
    
    cout << setfill('-') << setw(7 * colwidth) << "-" << endl;
    cout << setfill(' ') << fixed;
    
    string stringInterval[intervals.size()];
    for(int i = 0; i < intervals.size(); i++) {
        stringInterval[i] = "[" + to_string(limits[i] - amplitude) + "; " + to_string(limits[i]) + ")";
    }
    
    for(int i = 0; i < intervals.size(); i++) {
        unsigned long int sizeDif = stringInterval[i].length() - stringInterval[0].size();
        
        cout << setprecision(2) << "[" << limits[i] - amplitude << "; " << limits[i] << ")" << setw((colwidth - 5) - int(sizeDif))
                                << ((limits[i] - amplitude) + limits[i]) / 2 << setw(colwidth - 1)
                                << absoluteFrequency[i] << setw(colwidth)
                                << relativeFrequency[i] << "%" << setw(colwidth)
                                << accumulatedAbsoluteFrequency[i] << setw(colwidth - 1)
                                << accumulatedRelativeFrquency[i] << "%" << endl;
    }
}
