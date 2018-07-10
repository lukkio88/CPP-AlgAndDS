#pragma once
#ifndef __HEAPSORT_H
#define __HEAPSORT_H
#include "commons.h"

int left(const int & idx);
int right(const int & idx);
void heapify(int * a, const int & size);
void heapFix(int * a, const int & size, const int & init_idx);
void heapSort(int * v, const int & size);

#endif