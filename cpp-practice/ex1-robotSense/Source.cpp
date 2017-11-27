#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

int grid_cells = 5;
vector <double> p(grid_cells, (1.0 / grid_cells));

string world[] = { "green", "red", "red", "green", "green" };
string measurements[] = { "red", "green" };
int motions[] = { 1,1 };

float pHit = 0.6;
float pMiss = 0.2;
float pExact = 0.8;
float pOverShoot = 0.1;
float pUnderShoot = 0.1;

vector<double> sense(vector<double> p, string Z) {
	vector<double> q;
	for (int i = 0; i < p.size(); i++) {
		bool hit = (Z == world[i]);
		q.push_back(p[i] * (hit*pHit + (1 - hit)*pMiss));
	}
	double sum = accumulate(q.begin(), q.end(), 0.0);
	
	// normalize probabilities
	for (int i = 0; i < q.size(); i++) {
		q[i] /= sum;
	}

	return q;
}

vector<double> move(vector<double> p, int U) {
	vector<double> q(p.size(),0.0);
	for (int i = 0; i < p.size(); i++) {
		
		//Method 1
		q[(i + U) % p.size()] += p[i] * pExact;
		q[(i + U - 1) % p.size()] += p[i] * pUnderShoot;
		q[(i + U + 1) % p.size()] += p[i] * pOverShoot;
		
		/*
		//Method 2
		int org_pos = (i < U) ? p.size() - U + i : i - U;
		int overShoot_pos = (i + 1 < U) ? p.size() - U + i + 1 : i - U + 1;
		int underShoot_pos = (i - 1 < U) ? p.size() - U + i - 1 : i - U - 1;
		q[i] = p[org_pos] * pExact + p[overShoot_pos] * pOverShoot + p[underShoot_pos] * pUnderShoot;
		*/
	}
	return q;
}

int main() {
	for (int i = 0; i < sizeof(measurements) / sizeof(string); i++) {
		p = sense(p, measurements[i]);
		p = move(p, motions[i]);

	}

	// print probability distribution
	for (int i = 0; i < p.size(); i++) {
		cout << p[i] << "\t";
	}

	system("pause");
	return 0;
}