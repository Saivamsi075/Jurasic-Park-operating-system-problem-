#include<iostream>
#include<thread>
#include<vector>
#include<ctime>
#include<chrono>
#include<stdlib.h>

using namespace std;

class cars
{
public:

	bool loaded;
	int startTime;
	int endTime;

	cars()
	{
		loaded = false;
		startTime = -1;
		endTime = -1;
	}
};

int Random(int n)
{
	srand(time(0) * rand());
	return 1 + (rand() % n);
}

static bool Exit = true;

void Process(int n,int m)
{
	using namespace std::literals::chrono_literals;

	int semaphore_n, semaphore_m;
	semaphore_n = n;
	semaphore_m = m;

	vector<cars> car;
	car.resize(n);

	int pq = 0;
	int clk = 1;
	int cr = 0;//completed rides
	int r = 1;

	//process cars while time remains
	while (Exit)
	{
		if (r == clk)
		{
			while(semaphore_m > 0)
			{
					pq++;
					semaphore_m--;
			}
			r = clk + Random(10);
		}
		
		for (int i = 0; i < n; i++)
		{

			if (car[i].loaded && car[i].endTime == clk)
			{
				car[i] = cars();

				cr++;
				semaphore_n++;
				semaphore_m++;
			}

			if (pq > 0 && !car[i].loaded)
			{
				car[i].loaded = true;
				car[i].startTime = clk;
				car[i].endTime = clk + Random(10);


				pq--;
				semaphore_n--;
			}

		}

		cout << endl << endl <<"Passengers wandering : "<<semaphore_m<<"   Passengers in queue : "<<pq<<"   Passengers in ride : "<< m - semaphore_m - pq << endl;
		cout << "cars in ride : "<<n-semaphore_n <<"   cars waiting : "<<semaphore_n<<"   Rides completed : "<<cr<< endl;

		this_thread::sleep_for(1s);

		clk++;

	}

}

int main()
{
	int n;  //number of safari cars
	int m;  //number of passengers wandering in the museum

	re_enter_n:
	cout << "Enter number of single-passenger cars : ";
	cin >> n;
	if (n < 0)
	{
		cout << endl<<"Enter valid number of Single-passenger cars "<<endl;
		cout << endl;
		goto re_enter_n;
	}
	re_enter_m:
	cout << "Enter number of Passengers : ";
	cin >> m;
	if (m < 0)
	{
		cout << endl << "Enter valid number of Passengers " << endl;
		cout << endl;
		goto re_enter_m;
	}
	cin.ignore();

	thread exec(Process,n,m);

	cin.get();
	Exit = false;
	cout << "Process stopped!" << endl << "press enter to exit." << endl;

	exec.join();

	cin.get();
	return 0;
}
