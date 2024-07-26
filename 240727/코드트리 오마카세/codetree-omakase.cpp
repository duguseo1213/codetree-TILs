#define P printf
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <deque>

using namespace std;

struct chobab {
	int in;
	int location;
	string name;
	int out;
	
};

struct person_info {
	int in;
	int location;
	string name;
	int n;

};

struct cmp {

	bool operator()(chobab a, chobab b) {

		if (a.in == b.in) {

			return a.name > b.name;
		}


		return a.in > b.in;

	}



};

struct cmp2 {

	bool operator()(chobab a, chobab b) {

		if (a.out == b.out) {

			return a.name > b.name;
		}
		return a.out > b.out;

	}

};

vector<chobab> vec;

unordered_map<string, pair<int,int>> intime; //들어온 시간, 위치
unordered_map < string, int> cnt;


priority_queue<chobab, vector<chobab>, cmp> wait_queue;
priority_queue<chobab, vector<chobab>, cmp2> pq;

deque<person_info> persons;

vector<int> picture;

int L,Q;

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> L >> Q;

	for (int i = 0; i < Q; i++) {
		int qnum;
		int t, x,n;
		string str;
		cin >> qnum;

		if (qnum == 100) {
			cin >> t >> x >> str;

			vec.push_back({ t,x,str,0 });

		}
		else if (qnum == 200) {
			cin >> t >> x >> str>>n;

			persons.push_back({ t,x,str,n });
			intime[str] = { t,x };

		}
		else {
			cin >> t;
			picture.push_back(t);
		}


	}

	for (int i = 0; i < vec.size(); i++) {

		if (intime[vec[i].name].first > vec[i].in) {

			int x=((intime[vec[i].name].first - vec[i].in) + vec[i].location)%L;

			if (x > intime[vec[i].name].second) {
				vec[i].out = L - (x - intime[vec[i].name].second) + (intime[vec[i].name].first - vec[i].in);
			}
			else {
				vec[i].out = intime[vec[i].name].second - x+ (intime[vec[i].name].first - vec[i].in);
			}

		}
		else {

			int x = vec[i].location ;

			if (x > intime[vec[i].name].second) {
				vec[i].out = L - (x - intime[vec[i].name].second);
			}
			else {
				vec[i].out = intime[vec[i].name].second - x;
			}

		}

		vec[i].out += vec[i].in;

		//cout << vec[i].in << " " << vec[i].out <<" " << vec[i].name << "\n";

		wait_queue.push(vec[i]);

	}
	
	for (int i = 0; i < picture.size(); i++) {

		int t = picture[i];
		//cout << t;
		while (!persons.empty()) {

			if (t < persons.front().in) {

				break;
			}
			cnt[persons.front().name] = persons.front().n;
			persons.pop_front();
		}

		while (!wait_queue.empty()) {

			if (t < wait_queue.top().in) {
				break;
			}

			pq.push(wait_queue.top());
			wait_queue.pop();

		}

		while (!pq.empty()) {

			if (t < pq.top().out) {
				break;
			}

			if (cnt.find(pq.top().name) != cnt.end()) {
				cnt[pq.top().name]--;

				if (cnt[pq.top().name] == 0) {
					cnt.erase(pq.top().name);
				}
			}

			//cout << pq.top().in <<" " << pq.top().out<<" "<<pq.top().name<<" ";

			pq.pop();

		}

		cout << cnt.size() << " " << pq.size() << "\n";

	}
	


}