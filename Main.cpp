/*
	Name: Matthew Alexander
	Describe your algorithm and explain your time complexity here:

*/

#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

bool reverse_pair(pair<long, long> p1, pair<long, long> p2) {
	return p1.second < p2.second ? true : p1.second == p2.second ? p1.first < p2.first : false;
}

void print_array(vector<pair<int, int> > arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << "(" << arr[i].first << ", " << arr[i].second << ")";
		if (i < arr.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	vector<pair<long,long> > ab(n);
	vector<bool> chosen(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	for (int i = 0; i < n; i++) {
		ab[i] = make_pair(a[i], b[i]);
	}

	long long answer = 0;

	// O( N log N )
	sort(ab.begin(), ab.end(), reverse_pair);
	// print_array(ab);

	// Right pointer
	for (int i = n - 1; i >= 1; i--) {
		if (chosen[i]) {
			continue;
		}

		// Left pointer
		int j = 0;
		bool is_max_b_flag = false;

		pair<long, long> prev_elem = make_pair(0, 0);
		int prev_elem_idx = 0;

		// Find suitable pair to store current pair in S
		// If not found, then store suitable pair in S
		while (j < i) {
			if (chosen[j]) {
				j++;
				continue;
			}

			// Largest b value is taken
			if (ab[j].first > ab[i].first) {
				answer += ab[i].second;
				is_max_b_flag = true;
				break;
			}

			// Take into account "chosen" pairs
			prev_elem = ab[j];
			prev_elem_idx = j;

			j++;
		}	

		chosen[i] = true;
		if (!is_max_b_flag) {
			answer += prev_elem.second;
			chosen[prev_elem_idx] = true;
		} else {
			chosen[j] = true;
		}		
	}

	cout << answer << endl;

	return 0;
}
