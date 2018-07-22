#pragma once
#ifndef __ALG_AND_DS_H
#define __ALG_AND_DS_H
#include <list.h>
#include <bstree.h>
#include <iostream>
#include <sstream>
#include <fstream>

enum COMMAND {
	INSERT,
	DELETE,
	SEARCH,
	NUM_COMMAND
};

int test_list(char *filename);
int test_binary_search_tree(char *filename);
int test_red_black_tree(char *filename);

#endif