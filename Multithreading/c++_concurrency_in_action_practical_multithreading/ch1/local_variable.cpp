#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct func{
	int& i;
	func(int& i_):i(i_){}
	
	//the background work of the operator-()
	void operator() (){
		FILE* file = fopen("/home/developer/ProjectExamples/parallel/Multithreading/c++_concurrency_in_action_practical_multithreading/log.txt", "w");
		if(file){
			cout << "File Created OK" << endl;
		}
		for (unsigned j=0; j<1000000;++j){
			do_something(i, file);//potential access to dangling reference(here may cause problem if the program terminate and the thread not terminate, so we should detach the thread for the local variable - i)
		}
		fclose(file);
	}
	
	void do_something(int i, FILE* f){
		fprintf(f, "The Value of var: %d", i);
	}
};

int main(int argc, char* argv[]){
	cout << "The Main program Begin" << endl;
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();//don't wait for thread to finish
	cout << "The Main Program Finished" << endl;
}//new Thread might still be running, and may these cause many problem depending on the work, type of the thread
//here we have background work so the program may finish and the thread not finishing yet.
//this happen to any other function(for example we can set the code on another function: void foo(){...Code Here...})
