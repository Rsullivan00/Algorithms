//Program to find the most frequently occurring element
//in an array.
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

void vPrint(std::vector<int> &V){
    for(int i = 0; i < V.size(); i++)
        std::cout << V[i] << ' ';
    std::cout << std::endl;
}

void fillVector(std::vector<int> &V, int range, int num){
    for(int i = 0; i < num; i++){
        int n = rand()%range;
        V.push_back(n);
    }
}

//Outputs the element that occurs the most and the number of times.
//If more than one element occur the same number of times, the lower
//element is chosen.
int main(){
    srand(time(0));
    std::vector<int> A;
    fillVector(A, 20, 500);
    vPrint(A);
    std::stable_sort(A.begin(), A.end());   //nlgn time
    unsigned maxCount = 0;
    unsigned currentCount = 0;
    unsigned elementIndex = 0;
    unsigned maxIndex = 0;
    for(int i = 0; i < A.size(); i++){  //Linear time
        if(A[i] != A[elementIndex]){ //If we are looking at a new int
            currentCount = 0;
            elementIndex = i;
        }
        currentCount++;
        if(currentCount > maxCount){
            maxCount = currentCount;
            maxIndex = elementIndex;
        }
    }
    std::cout << A[maxIndex] << " occurs " << maxCount << " times." << std::endl;
    return 0;
}
