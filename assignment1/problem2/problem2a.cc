#include <iostream>
#include <string.h>

using namespace std;

char* quickSort(char charArray[], int left, int right){
    char pivot = charArray[(left + right) / 2];
    char temp;
    int i = left;
    int j = right;

    while(i <= j){
        while(charArray[i] < pivot)
            i++;
        while(charArray[j] > pivot)
            j--;
        if(i <= j){
            temp = charArray[i];
            charArray[i] = charArray[j];
            charArray[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j)
        quickSort(charArray, left, j);
    if(i < right)
        quickSort(charArray, i, right);

    return charArray;
}

int main(void){
    char nameArray[] = "dennishuebert";
    char* sortedArray = quickSort(nameArray, 0, strlen(nameArray) - 1);
    cout << sortedArray << endl;
    return 0;
}
