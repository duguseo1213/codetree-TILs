#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#define P printf 
using namespace std;

struct NODE {
	int id;
	int weight;
	NODE* next;
	NODE* before;
};

NODE HEAD[10];
NODE DATAS[100010];

int rail[10];

unordered_map <int, pair<NODE*, int>> um;

int cnt;

int N, M;

vector<int> input_id;
vector<int> input_weight;

int find(int tar)
{
	if (tar == rail[tar])
	{
		return tar;
	}
	int root = find(rail[tar]);

	return root;



}

void setunion(int a, int b)
{
	int t1 = find(a);
	int t2 = find(b);
	if (t1 == t2) return;

	rail[t2] = t1;
}

void make(int h, int id, int weight)
{
	NODE* nd = &DATAS[cnt];

	nd->id = id;
	nd->weight = weight;


	if (!HEAD[h].next)
	{
		nd->next = &HEAD[h];
		nd->before = &HEAD[h];
		HEAD[h].next = nd;
		HEAD[h].before = nd;

	}
	else
	{
		nd->next = HEAD[h].next;
		nd->next->before = nd;
		HEAD[h].next = nd;
		nd->before = &HEAD[h];

	}
	um[input_id.back()] = { nd, h };
	cnt++;

	return;
}

void init()
{
	int n, m;
	scanf("%d %d", &n, &m);
	N = n;
	M = m;

	int id;
	int weight;
	/*
	for (int i = 0; i < 10; i++)
	{
		HEAD[i].next = &HEAD[i];
		HEAD[i].before = &HEAD[i];
	}*/

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n / m; j++)
		{
			scanf("%d", &id);
			input_id.push_back(id);
		}
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n / m; j++)
		{
			scanf("%d", &weight);
			input_weight.push_back(weight);
		}
	}

	for (int i = m - 1; i >= 0; i--)
	{
		for (int j = 0; j < n / m; j++)
		{

			make(i, input_id.back(), input_weight.back());

			input_id.pop_back();
			input_weight.pop_back();
		}
	}




	for (int i = 0; i < M; i++)
	{
		rail[i] = i;
	}


}

void down()
{
	int w_max;
	scanf("%d", &w_max);
	long long sum = 0;
	for (int i = 0; i < M; i++)
	{
		if (find(i) == i && HEAD[i].next->id != 0)
		{

			//P("%d ", HEAD[i].next->weight);
			if (HEAD[i].next->weight <= w_max) //하차시키기 //um에서 지우기
			{

				um.erase(HEAD[i].next->id);
				sum = sum + HEAD[i].next->weight;
				//P("%d ", HEAD[i].next->weight);
				HEAD[i].next->next->before = &HEAD[i];
				HEAD[i].next = HEAD[i].next->next;


			}
			else //맨뒤로 보내기
			{
				NODE* nd = HEAD[i].next;

				HEAD[i].next = nd->next;
				nd->next->before = &HEAD[i];

				nd->next = &HEAD[i];
				nd->before = HEAD[i].before;

				HEAD[i].before->next = nd;
				HEAD[i].before = nd;


			}
		}
	}
	printf("%lld\n", sum);


}

void remove()
{
	int r_id;
	scanf("%d", &r_id);
	if (um.find(r_id) != um.end())
	{
		NODE* nd = um[r_id].first;

		nd->before->next = nd->next;

		nd->next->before = nd->before;



		um.erase(r_id);
		printf("%d\n", r_id);
	}
	else
	{
		printf("-1\n");
	}
}

void check()
{
	int f_id;
	scanf("%d", &f_id);

	if (um.find(f_id) != um.end())
	{
		NODE* nd = um[f_id].first;
		int ral = find(um[f_id].second);

		HEAD[ral].before->next = HEAD[ral].next;
		HEAD[ral].next->before = HEAD[ral].before;

		nd->before->next = &HEAD[ral];
		HEAD[ral].before = nd->before;

		HEAD[ral].next = nd;
		nd->before = &HEAD[ral];




		printf("%d\n", find(um[f_id].second) + 1);
	}
	else
	{
		printf("-1\n");
	}



}

void destroy()
{
	int b_num;
	scanf("%d", &b_num);
	b_num--;
	if (find(b_num) != b_num)
	{
		printf("-1\n");
	}
	else
	{
		int cnt = b_num;
		while (1)
		{

			cnt = (cnt + 1) % M;

			if (rail[cnt] == cnt)
			{
				
					//HEAD[cnt].next->before = HEAD[b_num].before;

					HEAD[cnt].before->next = HEAD[b_num].next;
					HEAD[b_num].next->before = HEAD[cnt].before;

					HEAD[b_num].before->next = &HEAD[cnt];
					HEAD[cnt].before = HEAD[b_num].before;


					setunion(cnt, b_num);
				
				break;
			}

		}
		printf("%d\n", b_num + 1);
	}


}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	int q;
	scanf("%d", &q);

	for (int i = 0; i < q; i++)
	{
		int qnum;
		scanf("%d", &qnum);
		if (qnum == 100)
		{
			init();
		}
		else if (qnum == 200)
		{
			down();
		}
		else if (qnum == 300)
		{
			remove();
		}
		else if (qnum == 400)
		{
			check();
		}
		else
		{
			destroy();
		}
	}


}