#include<iostream>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<deque>
#include<mutex>
#include<chrono>
#include<random>

std::deque <unsigned int> dq;

std::mutex dq_mutex;

void mimick_sensor_data()
{
    int val;
    srand((int)time(0));

	while(1)
    {
		val = (rand() % 360) + 1;
        //std::cout<<val<<"   ";
        dq.push_front(val);
        //std::cout<<"size : "<<dq.size()<<"  ";
    }
}

void averager()
{
    std::cout<<"averager running\n";
    std::chrono::seconds dura(5);
    std::this_thread::sleep_for(dura);
    std::cout<<"done waiting 5 sec\n";

    time_t start, end;
    double elapsed;  // seconds
    int num, terminate=1;
    double avg=0, sum=0, count=0;

    int i = 10;
    int val;

    while(1)
    {
        start = time(NULL);
        std::cout<<"main loop\n";
        //avg = 0;
        //sum = 0;
        //count = 0;
        //terminate = 1;

        while (terminate)
        {
            //std::cout<<"termination loop\n";
            end = time(NULL);
            elapsed = difftime(end, start);
            //std::cout<<"elapsed : "<<elapsed<<"     ";

            if (elapsed >= 2)//seconds
            {
                terminate = 0;
                avg = 0;
                sum = 0;
                count = 0;
            }
            if(dq.size()!=0)
            {
                sum += dq.front();
                dq.pop_front();
                count ++;
                //std::cout<<"sum : "<<sum<<"     ";
            }
            //std::cout<<"size : "<<dq.size()<<"      ";
        }


        avg = sum/count;
        std::cout<<"AVERAGE : "<<avg<<"\n";
    }

}

int main()
{
    std::thread thread2(averager);
    std::thread thread1(mimick_sensor_data);
    thread1.join();

    thread2.join();


}
