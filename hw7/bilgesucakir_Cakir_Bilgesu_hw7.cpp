#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
#include <time.h>
#include <iomanip>
#include <ctime>
#include "bilgesucakir_Cakir_Bilgesu_hw7_HW7DynIntQueue.h"
using namespace std;

//Bilgesu Cakir 27889 CS204 Homework 7

//This program represents of a simulation of a producing a product, using 6 different threads (main thread, producer thread, 2 filling threads and
//2 packaging threads) by taking inputs like box number, min and max values for duration processes.

mutex coutMutex; //mutex for cout statements to not to be divided
mutex producingMutex, fillingMutex, packagingMutex; //mutexes for dequeueing and enqueueing processes.
bool stopFill = false, stopPackage = false; //global bool variables for controlling Fill and Package functions' while loops
int total_box_count; 
int filledCount = 0, packagedCount = 0; //keeps the number of boxes filled/packaged

/* Begin: code taken and from CS204_Homework7_Spring2021.pdf */
int random_range(const int & min, const int & max){
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}
/* End: code taken and from CS204_Homework7_Spring2021.pdf */

void Produce(HW7DynIntQueue & fillQ, int & min, int & max){
	int Qsize, timeRandom;

	for(int i=0; i<total_box_count; i++){
		int numberOfTheCurrentBox = i+1;
		timeRandom = random_range(min, max);

		this_thread::sleep_for(chrono::seconds(timeRandom));

		producingMutex.lock();
		fillQ.enqueue(i+1);
		producingMutex.unlock();

		Qsize = fillQ.getCurrentSize();

		coutMutex.lock();
		/* Begin: code taken from 7-multithreading.pdf */
		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
		struct tm *ptm = new struct tm;
		localtime_s(ptm, &tt);
		/* End: code taken from 7-multithreading.pdf */
		cout << "Producer has enqueued a new box " << numberOfTheCurrentBox << " to filling queue (filling queue size is " << Qsize << "): " << put_time(ptm,"%X") << endl;
		coutMutex.unlock();
		delete ptm;
	}
}

void Fill(HW7DynIntQueue & fillQ, HW7DynIntQueue & packQ, int & min, int & max, int tag){
	int fillSize, packSize, theBox, randomTime;

	while(! stopFill){ //loop continues until all the boxes are filled totally as a summation of 2 filler threads' filled boxes (a global int variable used for counting this).
		/* Begin: code taken and updated from ProducerConsumer.cpp */
		fillingMutex.lock();
		if(! fillQ.isEmpty()){
			fillQ.dequeue(theBox);
			fillingMutex.unlock();

			randomTime = random_range(min, max);
			fillSize = fillQ.getCurrentSize();

			coutMutex.lock();
			/* Begin: code taken from 7-multithreading.pdf */
			time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
			struct tm *ptm = new struct tm;
			localtime_s(ptm, &tt);
			/* End: code taken from 7-multithreading.pdf */
			cout << "Filler " << tag << " started filling the box "<< theBox << " (filling queue size is "<< fillSize << "): " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
			delete ptm;

			this_thread::sleep_for(chrono::seconds(randomTime));

			coutMutex.lock();
			/* Begin: code taken and updated from 7-multithreading.pdf */
			time_t tt2 = chrono::system_clock::to_time_t (chrono::system_clock::now());
			struct tm *ptm2 = new struct tm;
			localtime_s(ptm2, &tt2);
			/* End: code taken and updated from 7-multithreading.pdf */
			cout << "Filler " << tag << " finished filling the box " << theBox << ": " << put_time(ptm2,"%X") << endl;
			coutMutex.unlock();
			delete ptm2;

			fillingMutex.lock();
			packQ.enqueue(theBox);
			filledCount++;
			fillingMutex.unlock();

			packSize = packQ.getCurrentSize();

			coutMutex.lock();
			/* Begin: code taken and updated from 7-multithreading.pdf */
			time_t tt3 = chrono::system_clock::to_time_t (chrono::system_clock::now());
			struct tm *ptm3 = new struct tm;
			localtime_s(ptm3, &tt3);
			/* End: code taken and updated from 7-multithreading.pdf */
			cout << "Filler " << tag << " put box " << theBox << " into packaging queue (packaging queue size is " << packSize << "): " << put_time(ptm3,"%X") << endl;
			coutMutex.unlock();
			delete ptm3;

			if(filledCount == total_box_count){
				stopFill = true; //now the loop stops
			}
		}
		else{
			fillingMutex.unlock();
		}
		/* End: code taken and updated from ProducerConsumer.cpp */
	}
}

void Package(HW7DynIntQueue & packQ, int & min, int & max, int tag){
	int theBox, packSize, randomTime;

	while(! stopPackage){//loop continues until all the boxes are packaged totally as a summation of 2 packager threads' filled boxes (a global int variable used for counting this).
		/* Begin: code taken and updated from ProducerConsumer.cpp */
		packagingMutex.lock();
		if(! packQ.isEmpty()){
			packQ.dequeue(theBox);
			packagedCount++;
			packagingMutex.unlock();

			randomTime = random_range(min, max);
			packSize = packQ.getCurrentSize();

			coutMutex.lock();
			/* Begin: code taken from 7-multithreading.pdf */
			time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
			struct tm *ptm = new struct tm;
			localtime_s(ptm, &tt);
			/* Begin: code taken from 7-multithreading.pdf */
			cout << "Packager " << tag << " started packaging the box " << theBox << " (packaging queue size is " << packSize << "): " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
			delete ptm;

			this_thread::sleep_for(chrono::seconds(randomTime));

			coutMutex.lock();
			/* Begin: code taken and updated from 7-multithreading.pdf */
			time_t tt2 = chrono::system_clock::to_time_t (chrono::system_clock::now());
			struct tm *ptm2 = new struct tm;
			localtime_s(ptm2, &tt2);
			/* End: code taken and updated from 7-multithreading.pdf */
			cout << "Packager " << tag << " finished packaging the box "<< theBox << ": " << put_time(ptm2, "%X") <<  endl;
			coutMutex.unlock();
			delete ptm2;

			if(packagedCount == total_box_count){
				stopPackage = true; //now the loop stops
			}
		}
		else{
			packagingMutex.unlock();
		}
		/* End: code taken and updated from ProducerConsumer.cpp */
	}
}

int main(){
	int min_production, max_production, min_filling_time, max_filling_time, min_packaging_time, max_packaging_time;

	//getting inputs
	cout << "Please enter the total number of items:";
	cin >> total_box_count;
	cout << "Please enter the min-max waiting time range of producer:" << endl;
	cout << "Min: ";
	cin >> min_production;
	cout << "Max: ";
	cin >> max_production;
	cout << "Please enter the min-max waiting time range of filler workers:" << endl;
	cout << "Min: ";
	cin >> min_filling_time;
	cout << "Max: ";
	cin >> max_filling_time;
	cout << "Please enter the min-max waiting time range of packager workers:" << endl;
	cout << "Min: ";
	cin >> min_packaging_time;
	cout << "Max: ";
	cin >> max_packaging_time;

	HW7DynIntQueue fillingQ, packagingQ;

	thread producer;
	thread fillers[2];
	thread packagers[2];

	/* Begin: code taken and updated from 7-multithreading.pdf*/
	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
	struct tm *ptm = new struct tm;
	localtime_s(ptm, &tt);
	/* Begin: code taken and updated from 7-multithreading.pdf*/
	cout << "Simulation starts " << put_time(ptm,"%X") << endl;
	delete ptm;

	producer = thread(&Produce, ref(fillingQ), ref(min_production), ref(max_production));
	fillers[0] = thread(&Fill, ref(fillingQ), ref(packagingQ), ref(min_filling_time), ref(max_filling_time), 1);
	fillers[1] = thread(&Fill, ref(fillingQ), ref(packagingQ), ref(min_filling_time), ref(max_filling_time), 2);
	packagers[0] = thread(&Package, ref(packagingQ), ref(min_packaging_time), ref(max_packaging_time), 1);
	packagers[1] = thread(&Package, ref(packagingQ), ref(min_packaging_time), ref(max_packaging_time), 2);

	producer.join();
	fillers[0].join();
	fillers[1].join();
	packagers[0].join();
	packagers[1].join();

	/* Begin: code taken and updated from 7-multithreading.pdf*/
	time_t tt2 = chrono::system_clock::to_time_t (chrono::system_clock::now());
	struct tm *ptm2 = new struct tm;
	localtime_s(ptm2, &tt2);
	/* Begin: code taken and updated from 7-multithreading.pdf*/
	cout << "End of the simulation ends: " << put_time(ptm2,"%X") << endl;
	delete ptm2;

	return 0;
}