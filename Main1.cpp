/*
	Name: Matthew Alexander
	Describe your algorithm and explain your time complexity here:

  Algorithm time complexity: O(N log N) 
  - Combines input array a & b to create array of (a_i, b_i) pairs [O(N)]
	- Sorts array of pairs by a_i (increasing) -> stores in ab_sorted_a [O(N log N)]
  - For each prefix of the items, calculate the min & max number (bound) of elements i < j to maintain property of S [O(N)]
  
	- For each bound at index i: [O(N log N)]
    - Push b_i to the maximum priority queue [O(log N)]
    - Check if size of set S is smaller than lower bound size for that prefix
      - If yes: Extract the biggest b_i in the priority queue to the set S [O(log N)]
  - Sum all elements in set S to get answer
*/

#include <iostream>
#include <vector> 
#include <algorithm>
#include <queue>

#include <math.h> 

using namespace std;

// Sorting comparator that sorts array of pairs based on first element
bool sort_pair_via_a(pair<long, long> p1, pair<long, long> p2) {
	return p1.first < p2.first ? true : p1.first == p2.first ? p1.second < p2.second : false;
}


int main() {
	int n;
	cin >> n;
	
	vector<int> a(n), b(n);
	vector<pair<long,long> > ab_sorted_a(n);
	vector<pair<int, int> > bounds(n);
  vector<int> S;
  priority_queue<int> pq;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	for (int i = 0; i < n; i++) {
		ab_sorted_a[i] = make_pair(a[i], b[i]);
	}

	long long answer = 0;

	// Sort array pairs with first element (increasing) 
	// O(N log N)
	sort(ab_sorted_a.begin(), ab_sorted_a.end(), sort_pair_via_a);

	// Discover lower & upper bounds for number of items in each prefix i from (0 to n)
	for (int i = 0; i < n; i++) {
		long upper_bound = min(i + 1, n / 2);
		long lower_bound = min( ceil( ( (float) (i + 1.0) / 2.0 ) ),  n / 2.0 );
		bounds[i] = make_pair(lower_bound, upper_bound);
	}

	// O(N * log N)
  for (int i = 0; i < n; i++) {
    // Priority queue used to get greatest value of b when deciding which b_i to push to set S
		// O(log N)
    pq.push(ab_sorted_a[i].second);
    int lower_bound = bounds[i].first;

    // Decide to push to S only to maintain property of S 
		// O(log N)
    if (S.size() < lower_bound) {
      S.push_back(pq.top());
      answer += pq.top();
      pq.pop();
    }
  }

	cout << answer << endl;
	return 0;
}
