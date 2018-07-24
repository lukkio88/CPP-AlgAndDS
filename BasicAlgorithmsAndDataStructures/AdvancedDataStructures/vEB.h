#pragma once
#ifndef __VEB_H
#define __VEB_H

int upperSqrt(const int & u);
int lowerSqrt(const int & u);
int high(const int & x, const int & u);
int low(const int & x, const int & u);
int index(const int & x, const int & y, const int & u);

struct vEBNode {

	vEBNode(const int & u) {
		this->u = u;
		min = max = -1;
		int curr_u = u;
		if (u != 2) {
			summary  = new vEBNode(lowerSqrt(u));
			cluster = new vEBNode*[upperSqrt(u)];
			for (auto i = 0; i < upperSqrt(u); ++i)
				cluster[i] = new vEBNode(lowerSqrt(u));
		}
	}

	int u;
	int min, max;
	vEBNode *summary;
	vEBNode **cluster;
};

bool isMember(vEBNode * V, const int & x);
int successor(vEBNode * V, const int & x);
int predecessor(vEBNode * V, const int & x);

#endif