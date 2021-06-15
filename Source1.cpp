#include<iostream>
#include<climits> 
#include<vector>
#include <fstream>
#include<string>
#include<cmath>
using namespace std;

                //  written by dalia etmaize //

struct Table {
	vector<vector<int>> t1;
	vector<int>parent;
};
  

// dijkstra algorthim
int minimumDist(vector<int> dist, vector<bool> Dset, int n)   //A method to find the vertex with minimum distance which is not yet included in Dset
{
	int min = INT_MAX, index;                 //initialize min with the maximum possible value as infinity does not exist
	for (int v = 0; v < n; v++)
	{
		if (Dset[v] == false && dist[v] <= min)
		{
			min = dist[v];
			index = v;
		}
	}
	return index;
}
void dijkstra(vector<vector<int>> v1, int src, int n, vector<vector<int>> &t,vector<int> &parent) /*Method to implement shortest path algorithm*/
{
	vector<int>dist;
	vector<bool>Dset;
	

	for (int i = 0; i < n; i++)                    /*Initialize distance of all the vertex to INFINITY and Dset as false*/
	{
		dist.push_back(INT_MAX);
		Dset.push_back(false);
		parent.push_back(-1);
	}
	dist[src] = 0;                                   //Initialize the distance of the source vertec to zero
	for (int c = 0; c < n; c++)
	{
		int u = minimumDist(dist, Dset, n);              //u is any vertex that is not yet included in Dset and has minimum distance
		Dset[u] = true;                              //If the vertex with minimum distance found include it to Dset
		for (int v = 0; v < n; v++)
			//Update dist[v] if not in Dset and their is a path from src to v through u that has distance minimum than current value of dist[v]
		{
			if (!Dset[v] && v1[u][v] && dist[u] != INT_MAX && dist[u] + v1[u][v] < dist[v]) {
				     parent[v] = u;
					dist[v] = dist[u] + v1[u][v];
			}
		}
	}

	
	
	for (int i = 0; i < n; i++)                       
	{
		vector<int>T;
		int c =  i;
		T.push_back(c);
		T.push_back(dist[i]);
		t.push_back(T);
	}

}

             //floyd algorthim
void printMatrix(vector<vector<int>>A,int n);

void floyd(vector<vector<int>>& A, int n)
{

	int  i, j, k;
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (A[i][k] + A[k][j] < A[i][j])
					A[i][j] = A[i][k] + A[k][j];
			}
		}
	}
}

void printMatrix(vector<vector<int>>A,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] == INT_MAX)
				cout << "INF"
				<< "  ";
			else
				cout << A[i][j] << "  ";
		}
		cout << endl;
	}
}

void printPath(vector<int>parent, int j)
{

	// Base Case If j is source 
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	cout<<"  the vertix "<< j;
}





int main()
{

	int n;// number of vertices
	int d;
	vector<vector<int>> FileArray;
	vector<vector<int>> v1;
	vector<vector<int>> Floydpath;
	Table array[10000];
	

	//cheak if the  file name is exsist
	ifstream infile;
	string fileName;
	do {
		cout << "Enter the File name (absolute path ) please : ((if you enter a wrong name you will enter again ))" << endl;
		
		getline(cin, fileName);
		infile.open(fileName);

	} while (infile.fail());
	
	//calculate the number of vertices using the file
	int read;
	int count=0;
	while (!infile.eof()) {
		infile >>read;
		count++;
	}
	n = sqrt(count);
	infile.close();


	// read the graph using file
	infile.open(fileName);
	while (!infile.eof()) {
		for (int i = 0; i < n; i++) {
			vector<int>arr;
			for (int j = 0; j < n; j++) {
				infile >> d;
				arr.push_back(d);
			}
			FileArray.push_back(arr);
		}
	}
	
	infile.close();

	//print the array that the file read

	cout << "the graf you read from the file :" << endl<<endl;
	printMatrix(FileArray, n);
	cout << endl << endl;


	//caling algorithms and print the tables
	v1 = FileArray;    
	Floydpath = FileArray;
	
	//calling Floyd algorthim and print floyd table
	cout << "floyd Table :" << endl;
	floyd(Floydpath, n);
	printMatrix(Floydpath, n);
	cout << endl << endl;

	// calling dijkstra n times and print it tables
		for (int i = 0; i < n; i++) {
			dijkstra(v1, i, n, array[i].t1, array[i].parent);
		}
	

	cout << "dijkstra tables :" << endl<<endl;
	for (int o = 0; o < n; o++) {
		cout << "table number :" << o+1 << endl;
		for (int v = 0; v < n; v++) {
			for (int num = 0; num < 2; num++)
				cout << array[o].t1[v][num] << "  ";
			cout << endl;
		}
		cout << endl << endl;

	}
	// calculate the path using both algorthim .
	cout << "note that the vertices Name is 0,1......to n-1( n : the number of vertices ) " << endl;
	cout << "if you want to calculate the shortest bath between two vertices :" << endl;
	cout << "enter the start vertix :"<<endl;
	int start; cin >> start;
	cout << "enter the end vertix :" << endl;
	int end; cin >> end;
	cout << " the shortest path Long using dijkstra :" << endl;
	cout << array[start].t1[end][1] << endl;
	cout << " the shortest path Long using Floyd :" << endl;
	cout << Floydpath[start][end] << endl;
	cout << "the exact path is : " << endl;
	cout << "from the source vertix " << start;
	printPath(array[start].parent, end);
	cout << endl << endl;
	system("pause");
	return 0;
}