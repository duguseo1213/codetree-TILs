#define P printf
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {

	int id;
	int W;
	int bnum;
	Node* prev;
	Node* next;
};

Node Head[11];
Node Tail[11];

int broken[11];


unordered_map<int, Node*> um;

Node pool[100011];
int ncnt;
int q;
int N;
int M;

int arr[2][100011];

void init() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {

		scanf("%d", &arr[0][i]);
	}
	for (int i = 0; i < N; i++) {

		scanf("%d", &arr[1][i]);
	}

	for (int i = 0; i < M; i++) {

		for (int j = 0; j < N / M; j++) {

			Node* nd = &pool[ncnt];
			nd->id = arr[0][ncnt];
			nd->W = arr[1][ncnt];
			nd->bnum = i;
			if (Head[i].next == NULL && Tail[i].next == NULL) {

				nd->next = &Tail[i];
				nd->prev = &Head[i];

				Head[i].next = nd;
				Tail[i].prev = nd;


			}
			else {

				nd->next = &Tail[i];
				nd->prev = Tail[i].prev;

				Tail[i].prev->next = nd;

				Tail[i].prev = nd;

			}

			um[nd->id] = nd;
			ncnt++;
		}

	}

}

void drop() {
	int w_max;
	long long sum = 0;
	scanf("%d", &w_max);
	for (int i = 0; i < M; i++) {

		if (broken[i] == -1) continue;

		Node* temp = &Head[i];

		if (temp->next != &Tail[i]) {
			temp = temp->next;

			if (temp->W <= w_max) {

				sum += temp->W;

				if (temp->next != &Tail[i]) {
					Head[i].next = temp->next;
					temp->next->prev = &Head[i];
				}
				else {
					Head[i].next = &Tail[i];
					Tail[i].prev = &Head[i];
				}
				um.erase(temp->id);
			}
			else {
				
				if (temp->next == &Tail[i] && temp->prev == &Head[i]) continue;

				Head[i].next->prev = Tail[i].prev;
				Head[i].next->next->prev = &Head[i];

				Tail[i].prev = Head[i].next;

				Head[i].next = Tail[i].prev->next;

				Tail[i].prev->prev->next = Tail[i].prev;

				Tail[i].prev->next = &Tail[i];
				
			}

		}
	}

	printf("%lld\n", sum);

}

void remove() {
	int r_id;
	scanf("%d", &r_id);

	if (um.find(r_id) != um.end()) {

		Node* temp = um[r_id];

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;




		um.erase(r_id);

		printf("%d\n", r_id);
	}
	else {
		printf("-1\n");
	}


}

void check() {

	int f_id;
	scanf("%d", &f_id);


	if (um.find(f_id) != um.end()) {

		Node* temp = um[f_id];

		int num = temp->bnum;

		while (1) {

			if (broken[num] == 0) break;

			num++;
			num = num % M;
		}
		printf("%d\n", num + 1);


		if (temp->prev == &Head[num]) return;


		Head[num].next->prev = Tail[num].prev;
		Tail[num].prev->next = Head[num].next;

		temp->prev->next = &Tail[num];
		Tail[num].prev = temp->prev;


		Head[num].next = temp;
		temp->prev = &Head[num];

		
	}
	else {
		printf("-1\n");
	}

}

void broke() {
	int b_num;

	scanf("%d", &b_num);


	b_num--;
	if (broken[b_num] == -1) {
		printf("-1\n");
		return;
	}
	printf("%d\n", b_num + 1);
	broken[b_num] = -1;

	int num = b_num;

	while (1) {

		if (broken[num] == 0) break;

		num++;
		num = num % M;
	}

	Tail[num].prev->next = Head[b_num].next;
	Head[b_num].next->prev = Tail[num].prev;


	Tail[b_num].prev->next = &Tail[num];
	Tail[num].prev = Tail[b_num].prev;




}

int main() {
	scanf("%d", &q);

	for (int i = 0; i < q; i++) {
		int qnum;
		scanf("%d", &qnum);

		if (qnum == 100) {
			init();
		}
		else if (qnum == 200) {
			drop();
		}
		else if (qnum == 300) {
			remove();
		}
		else if (qnum == 400) {
			check();
		}
		else if (qnum == 500) {
			broke();
		}
		/*
		for (int j = 0; j < M; j++) {


			if (broken[j] == -1) continue;

			Node* temp = &Head[j];
			
			while (1) {
				if (temp == &Tail[j]) break;

				P("id: %d w: %d ", temp->id,temp->W);

				temp = temp->next;
			}
			P("\n");
		}
		P("\n");
		for (int j = 0; j < M; j++) {

			if (broken[j] == -1) continue;

			Node* temp = &Tail[j];

			while (1) {
				if (temp == &Head[j]) break;

				P("id: %d w: %d ", temp->id, temp->W);

				temp = temp->prev;
			}
			P("\n");
		}
		P("\n");*/
	}

}