#include <vEB.h>

bool isMember(vEBNode * V, const int & x) {
	if (V->u == 2) {
		if (x == V->min || x == V->max)
			return true;
		else return false;
	}
	else
		return isMember(V->cluster[high(x, V->u)], low(x, V->u));
}

int successor(vEBNode * V, const int & x) {
	if (V->u == 2) {
		if (x == 0 && V->max == 1)
			return 1;
		else
			return -1;
	}
	else if (V->min != -1 && x < V->min) {
		return V->min;
	}
	else {
		int max_low = V->cluster[high(x, V->u)]->max;
		if (max_low != -1 && x < max_low) {
			int offset = successor(V->cluster[high(x, V->u)], low(x, V->u));
			return index(high(x, V->u), offset,V->u);
		}
		else {
			int succ_cluster = successor(V->summary, high(x, V->u));
			if (succ_cluster == -1)
				return -1;
			else {
				int offset = V->cluster[succ_cluster]->min;
				return index(succ_cluster, offset, V->u);
			}
		}
	}
}


int predecessor(vEBNode * V, const int & x) {
	if (V->u == 2) {
		if (x == 1 && V->min == 0)
			return 0;
		else
			return -1;
	}
	else if (V->max != -1 && x > V->max) {
		return V->max;
	}
	else {
		int min_low = V->cluster[high(x,V->u)]->min;
		if (min_low != -1 && x > min_low) {
			int offset = predecessor(V->cluster[high(x, V->u)], low(x, V->u));
			return index(high(x, V->u), offset,V->u);
		}
		else {
			int pred_cluster = predecessor(V->summary, high(x, V->u));
			if (pred_cluster == -1)
				if (V->min != -1 && x > V->min)
					return V->min;
				else
					return -1;
			else {
				int offset = V->cluster[pred_cluster]->max;
				return index(pred_cluster, offset, V->u);
			}
		}
	}
}