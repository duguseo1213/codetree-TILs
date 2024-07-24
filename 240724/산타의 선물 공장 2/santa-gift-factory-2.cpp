#define P printf
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {

	int id;
	Node* next;
	Node* prev;

};

unordered_map<int, Node*> um;

Node pool[100110];
Node Head[100110];
Node Tail[100110];
int lcnt[100110];
int ncnt;

int Q, N,M;

void init() {
	scanf("%d %d", &N, &M);
	

	for (int i = 1; i <= N; i++) {
		Head[i].next = &Tail[i];
		Tail[i].prev = &Head[i];
	}

	for (int i = 1; i <= M; i++) {
		int num;
		scanf("%d", &num);

		Node* nd = &pool[ncnt];

		nd->id = i;
		um[i] = nd;
		lcnt[num]++;
		if (Head[num].next == NULL) {
			Head[num].next = nd;
			Tail[num].prev = nd;

			nd->next = &Tail[num];
			nd->prev = &Head[num];
			

		}
		else {
			Tail[num].prev->next = nd;

			nd->prev = Tail[num].prev;

			Tail[num].prev = nd;
			nd->next = &Tail[num];


		}

		ncnt++;
		

	}

}

void move() {
	int src, dst;

	scanf("%d %d", &src, &dst);

	if (lcnt[src] == 0) {
		printf("%d\n", lcnt[dst]);
		return;

	}


	Tail[src].prev->next = Head[dst].next;
	Head[dst].next->prev = Tail[src].prev;

	Head[src].next->prev = &Head[dst];
	Head[dst].next = Head[src].next;

	
	Head[src].next = &Tail[src];
	Tail[src].prev = &Head[src];



	lcnt[dst] += lcnt[src];
	lcnt[src] = 0;
	printf("%d\n", lcnt[dst]);

}

void change() {
	int src, dst;

	scanf("%d %d", &src, &dst);

	if (lcnt[src] == 0 && lcnt[dst] == 0) {
		printf("0\n");
	}
	else if (lcnt[dst] == 0) {

		Node* temp = Head[src].next;

		Head[src].next->next->prev = &Head[src];
		Head[src].next = Head[src].next->next;

		temp->next = Head[dst].next;
		temp->prev = &Head[dst];

		Head[dst].next->prev = temp;
		Head[dst].next = temp;



		lcnt[src]--;
		lcnt[dst]++;
		printf("%d\n", lcnt[dst]);
	}
	else if (lcnt[src] == 0) {



		Node* temp = Head[dst].next;

		Head[dst].next->next->prev = &Head[dst];
		Head[dst].next = Head[dst].next->next;

		temp->next = Head[src].next;
		temp->prev = &Head[src];

		Head[src].next->prev = temp;
		Head[src].next = temp;

		lcnt[dst]--;
		lcnt[src]++;
		printf("%d\n", lcnt[dst]);
	}
	else {
		Node* temp1 = Head[src].next;

		Node* temp2 = Head[dst].next;

		Head[src].next->next->prev = &Head[src];
		Head[src].next = Head[src].next->next;

		Head[dst].next->next->prev = &Head[dst];
		Head[dst].next = Head[dst].next->next;


		temp2->next = Head[src].next;
		temp2->prev = &Head[src];

		Head[src].next->prev = temp2;
		Head[src].next = temp2;

		temp1->next = Head[dst].next;
		temp1->prev = &Head[dst];

		Head[dst].next->prev = temp1;
		Head[dst].next = temp1;

		printf("%d\n", lcnt[dst]);
	}


}

void divide() {
	int src, dst;

	scanf("%d %d", &src, &dst);

	int num = lcnt[src] / 2;
	lcnt[src] = lcnt[src] / 2+1;

	lcnt[dst] += num;
	printf("%d\n", lcnt[dst]);


	if (num == 0) {
		return;
	}


	Node* temp = &Head[src];

	for (int i = 0; i < num; i++) {

		temp = temp->next;

	}
	


	Node* ttemp = Head[dst].next;

	Head[dst].next = Head[src].next;

	Head[src].next->prev = &Head[dst];

	Head[src].next = temp->next;
	temp->next->prev= &Head[src];

	temp->next = ttemp;
	ttemp->prev = temp;


}

int main() {

	scanf("%d", &Q);

	


	for (int i = 0; i < Q; i++) {

		int qnum;

		scanf("%d", &qnum);

		if (qnum == 100) {
			init();
		}
		else if (qnum == 200) {
			move();
		}
		else if (qnum == 300) {
			change();
		}
		else if (qnum == 400) {
			divide();
		}
		else if (qnum == 500) {
			int pnum;

			scanf("%d", &pnum);

			Node* temp = um[pnum];

			int a, b;

			if (temp->prev->id == 0) {
				a = -1;
			}
			else {
				a = temp->prev->id;
			}

			if (temp->next->id == 0) {
				b = -1;
			}
			else {
				b = temp->next->id;
			}

			printf("%d\n", a + 2 * b);

		}
		else if (qnum == 600) {
			int pnum;

			scanf("%d", &pnum);
			if (lcnt[pnum] == 0) {
				printf("-3\n");
			}
			else {
				printf("%d\n", Head[pnum].next->id + (Tail[pnum].prev->id) * 2 + lcnt[pnum] * 3);
			}

		}
		/*
		for (int i = 1; i <= N; i++) {
			Node* temp = &Head[i];

			while (temp != &Tail[i]) {

				P("%d ", temp->id);
				temp = temp->next;

			}
			P("\n");
		}
		P("\n");
		
		for (int i = 1; i <= N; i++) {
			Node* temp = &Tail[i];

			while (temp != &Head[i]) {

				P("%d ", temp->id);
				temp = temp->prev;

			}
			P("\n");
		}
		P("\n");
		*/
		



	}


}