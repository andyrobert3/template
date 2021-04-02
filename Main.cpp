/*
	Name: Matthew Alexander
	Describe your algorithm and explain your time complexity here:

	Algorithm time complexity: O(n^2)
	- Combines input array a & b to create array of (a_i, b_i) pairs
	- Sorts array of pairs by a_i (increasing) -> stores in ab_sorted_a
	- For each prefix of the items, calculate the min/max number of elements i < j to maintain property of S
	- Sort array of pairs by b_i (decreasing) -> stores in ab_reverse_sorted_b
	- For each element b_i in ab_reverse_sorted_b (starting from 0 index)
		- For each prefix, check if adding b_i to set S will violate property of S
			- if adding b_i violates, then skip b_i to b_(i+1)
			- else	add b_i to set S
	- Sum all elements in set S
*/

#include <iostream>
#include <vector> 
#include <algorithm>
#include <unordered_map>

#include <math.h> 

using namespace std;

// Sorting comparator that sorts array of pairs based on first element
bool sort_pair_via_a(pair<long, long> p1, pair<long, long> p2) {
	return p1.first < p2.first ? true : p1.first == p2.first ? p1.second < p2.second : false;
}

// Sorting comparator that sorts array of pairs in reverse based on second element
bool reverse_sort_pair_via_b(pair<long, long> p1, pair<long, long> p2) {
	return p1.second > p2.second ? true : p1.second == p2.second ? p1.first > p2.first : false;
}

// Prints array of pairs in cleanly, used for debugging purposes
void print_array_pairs(vector<pair<int, int> > arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << "(" << arr[i].first << ", " << arr[i].second << ")";
		if (i < arr.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

// Prints array of integers in cleanly, used for debugging purposes
void print_array(vector<int> arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	
	vector<int> a(n), b(n);
	vector<pair<long,long> > ab_sorted_a(n), ab_reverse_sorted_b(n);
	vector<pair<int, int> > bounds(n);
	vector<bool> chosen(n);
	unordered_map<long, int> a_index_mapper;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	for (int i = 0; i < n; i++) {
		ab_sorted_a[i] = make_pair(a[i], b[i]);
	}

	copy(ab_sorted_a.begin(), ab_sorted_a.begin() + n, ab_reverse_sorted_b.begin());

	long long answer = 0;

	// Sort array pairs with first element (increasing) 
	// O(N log N)
	sort(ab_sorted_a.begin(), ab_sorted_a.end(), sort_pair_via_a);

	// Discover lower & upper bounds for number of items in each prefix i from (0 to n)
	for (int i = 0; i < n; i++) {
		long upper_bound = min(i + 1, n / 2);
		long lower_bound = min(ceil( ( (float) (i + 1.0) / 2.0 ) ),  n / 2.0 );
		bounds[i] = make_pair(lower_bound, upper_bound);

		// a_i is distinct so can be used to map to ab_sorted_a index 
		a_index_mapper[ab_sorted_a[i].first] = i;
	}

	// Sort via b in decreasing order (Greedy) 
	// O(N log N)
	sort(ab_reverse_sorted_b.begin(), ab_reverse_sorted_b.end(), reverse_sort_pair_via_b);

	// Tackle greedy constraints when sorting by greatest b 
	// O(N ^ 2)
	for (int j = 0; j < n; j++) {
		int a_j = ab_reverse_sorted_b[j].first;
		int b_j = ab_reverse_sorted_b[j].second;

		int curr_pair_idx_in_sorted_a = a_index_mapper[a_j];
		pair<int, int> bound_j = bounds[j];

		int sum = 0;
		bool to_add_b_j = true;

		// Check whether property of S is maintained when we want to add b_j to S
		for (int k = 0; k < n; k++) {
			pair<int, int> curr_bound = bounds[k];

			if (k == curr_pair_idx_in_sorted_a || chosen[k] || sum < curr_bound.first) {
				sum++;
			} 

			// Adding b_j violates property of S
			if (sum > curr_bound.second) {
				to_add_b_j = false;
				break;
			}
		}

		if (to_add_b_j) {
			chosen[curr_pair_idx_in_sorted_a] = true;
			answer += b_j;
		}
	}

	cout << answer << endl;
	return 0;
}
