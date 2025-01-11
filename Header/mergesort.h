#ifndef MERGE_SORT_H
#define MERGE_SORT_H

void merge(char **v, int left, int mid, int right);
void mergeSort(char **v, int left, int right);
void mergeSortRadix(char **v, int left, int right, int exp);
void mergeRadix(char **v, int left, int mid, int right, int exp);
int menuMergeSort();

#endif