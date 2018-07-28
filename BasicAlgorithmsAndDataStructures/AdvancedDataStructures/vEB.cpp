#include <vEB.h>

int upperSqrt(const int & u) {
	return ceil(log(sqrt(u)));
}

int lowerSqrt(const int & u) {
	return floor(log(sqrt(u)));
}

int high(const int & x, const int & u) {
	return x / lowerSqrt(u);
}

int low(const int & x, const int & u) {
	return x % lowerSqrt(u);
}
int index(const int & x, const int & y, const int & u) {
	return x * lowerSqrt(u) + y;
}

void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

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
	int & min = V->min;
	int & max = V->max;
	int & u = V->u;
	if (u == 2) {
		if (x == 0 && V->max != -1)
			return 1;
		else
			return -1;
	}
	else {
		if (min != -1 && x < min)
			return min;
		else {
			int max_low = V->cluster[high(x,u)]->max;
			if (max != -1 && x < max_low) {
				int offset = successor(V->cluster[high(x, u)], low(x,u));
				return index(high(x,u), offset,u);
			}
			else {
				int cluster_idx = successor(V->summary, high(x,u));
				if (cluster_idx != -1) {
					int offset = V->cluster[cluster_idx]->min;
					return index(cluster_idx, offset, u);
				}
				else {
					return -1;
				}
			}
		}
	}
}


int predecessor(vEBNode * V, const int & x) {
	int & min = V->min;
	int & max = V->max;
	int & u = V->u;
	if (u == 2) {
		if (x == 1 && V->min != -1)
			return 0;
		else {
			return -1;
		}
	}
	else {
		if (max != -1 && x > max) {
			return max;
		}
		else {
			int min_high = V->cluster[high(x, u)]->min;
			if (min_high != -1) {
				int offset = predecessor(V->cluster[high(x, u)], low(x,u));
				return index(high(x, u), offset,u);
			}
			else {
				int cluster_idx = predecessor(V->summary, high(x, u));
				if (cluster_idx != -1) {
					if (min != -1)
						return min;
					else return -1;
				}
				else {
					int offset = V->cluster[cluster_idx]->max;
					return index(cluster_idx, offset, u);
				}
			}
		}
	}
}

void insertEmpty(vEBNode * v, const int & x) {
	v->min = v->max = x;
}

void insert(vEBNode * V, const int & x) {
	int & min = V->min;
	int & max = V->max;
	int & u = V->u;
	int _x = x;
	if (min == -1) {
		insertEmpty(V, x);
	}
	else {
		if (_x < min) {
			swap(_x, min);
		}
		if (u > 2) {
			if (V->cluster[high(_x,u)]->min == -1) {
				insert(V->summary, high(_x, u));
				insertEmpty(V->cluster[high(_x, u)], low(_x,u));
			}
			else {
				insert(V->cluster[high(_x, u)], low(_x, u));
			}
		}
		if (_x > max) {
			max = _x;
		}
	}
}

void remove(vEBNode * V, const int & x) {
	int & min = V->min;
	int & max = V->max;
	int & u = V->u;
	if (min == max) {
		min = max = -1;
	}
	else if (u == 2) {
		if (x == 0)
			min = 1;
		else
			min = 0;
		max = min;
	}
	else {
		int _x = x;
		if (_x == min) {
			int cluster_idx = V->summary->min;
			_x = index(cluster_idx, V->cluster[cluster_idx]->min,u);
		}
		min = _x;
		remove(V->cluster[high(_x, u)], low(_x, u));
		if (V->cluster[high(_x, u)]->min == -1) {
			remove(V->summary, high(_x, u));
			if (_x == max) {
				int cluster_idx = V->summary->max;
				if (cluster_idx != -1) {
					max = index(cluster_idx, V->cluster[cluster_idx]->max, u);
				}
				else
					max = min;
			}
		}
		else if (_x == max) {
			max = index(high(_x, u), V->cluster[high(_x, u)]->max,u);
		}
	}
}