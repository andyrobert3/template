/*
	Name: Matthew Alexander
	Describe your algorithm and explain your time complexity here:

	Algorithm time complexity O(n^2)
*/

#include <iostream>
#include <vector> 
#include <algorithm>
#include <unordered_map>

#include <math.h> 

using namespace std;

bool sort_pair_via_a(pair<long, long> p1, pair<long, long> p2) {
	return p1.first < p2.first ? true : p1.first == p2.first ? p1.second < p2.second : false;
}

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
	vector<pair<long,long> > ab_sorted_a(n), ab_sorted_b(n);
	vector<pair<int, int> > bounds(n);
	vector<bool> chosen(n);

	unordered_map<long, int> a_index_mapper;

	// Debugging purposes
	vector<int> b_values_chosen;


	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	for (int i = 0; i < n; i++) {
		ab_sorted_a[i] = make_pair(a[i], b[i]);
	}

	copy(ab_sorted_a.begin(), ab_sorted_a.begin() + n, ab_sorted_b.begin());

	long long answer = 0;

	// Sort array pairs
	sort(ab_sorted_a.begin(), ab_sorted_a.end(), sort_pair_via_a);

	// Discover lower & upper bounds for set S
	for (int i = 0; i < n; i++) {
		long upper_bound = min(i + 1, n / 2);
		long lower_bound = min(ceil( ( (float) (i + 1.0) / 2.0 ) ),  n / 2.0 );
		bounds[i] = make_pair(lower_bound, upper_bound);
		// a_i is distinct can be used to map
		a_index_mapper[ab_sorted_a[i].first] = i;
	}

	// Sort by greatest b (Greedy)
	sort(ab_sorted_b.begin(), ab_sorted_b.end(), reverse_sort_pair_via_b);
	// print_array_pairs(bounds);

	// Tackle greedy constraints when sorting by greatest b
	for (int j = 0; j < n; j++) {
		int a_j = ab_sorted_b[j].first;
		int b_j = ab_sorted_b[j].second;

		int curr_pair_idx_in_sorted_a = a_index_mapper[a_j];
		pair<int, int> bound_j = bounds[j];

		int sum = 0;
		bool to_add = true;

		for (int k = 0; k < n; k++) {
			pair<int, int> curr_bound = bounds[k];

			if (k == curr_pair_idx_in_sorted_a || chosen[k] || sum < curr_bound.first) {
				sum++;
			} 

			if (sum > curr_bound.second) {
				to_add = false;
				break;
			}
		}

		if (to_add) {
			chosen[curr_pair_idx_in_sorted_a] = true;
			b_values_chosen.push_back(b_j);
			answer += b_j;
		}
	}

	// print_array(b_values_chosen);
	cout << answer << endl;

	return 0;
}
