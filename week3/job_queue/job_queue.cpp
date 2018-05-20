#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Thread {
	long long finish_time;
	int worker;

	Thread(int worker):
		finish_time(0),
		worker(worker)
	{}

	bool operator<(const Thread & x) const {
		if (finish_time != x.finish_time)
			return finish_time > x.finish_time;
		return worker > x.worker;
	}
};

int main() {
	int no_of_workers, no_of_threads;
	cin >> no_of_workers >> no_of_threads;
	vector<long long> process_time(no_of_threads);
	vector<Thread> pq;

	for (int i = 0; i < no_of_threads; i++) {
		cin >> process_time[i];
	}
	
	for (int i = 0; i < no_of_workers; i++) {
		pq.push_back(Thread(i));
		push_heap(pq.begin(), pq.end());
	}

	for (int i = 0; i < process_time.size(); i++) {
		Thread k = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();
		cout << k.worker << " " << k.finish_time << endl;
		k.finish_time += process_time[i];
		pq.push_back(k);
		push_heap(pq.begin(), pq.end());
	}

}