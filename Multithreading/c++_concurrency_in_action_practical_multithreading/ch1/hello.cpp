#include <iostream>
#include <thread>

void hello(){
	std::cout << "Salam Concurrent World" << std::endl;
}

//main function has its mai thread.
int main(){
	std::thread t(hello);
	//t.join();//for joining with the main thread.
	//also we can write
	if(t.joinable()){
		t.join();
	}
}
