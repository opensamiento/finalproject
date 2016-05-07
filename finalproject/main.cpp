#include <iostream>
#include <fstream> //stream class to read/write to/from files
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

class Job
{
private:
    int id; //customer ID
    int transfer; //transfer amount
    int withdraw; //account # withdrawing from
    int deposit; //account # depositing to
    int wealth; //customer wealth
    int dtime; //time deposit must be made by

public:
    Job ();
    //getters (data obtained from int_vector when constructing jobs)
    int get_id ();
    int get_transfer ();
    int get_withdraw ();
    int get_deposit ();
    int get_wealth ();
    int get_dtime ();
    //setters
    void set_id (int idd);
    void set_transfer (int trans);
    void set_withdraw (int with);
    void set_deposit (int dep);
    void set_wealth (int we);
    void set_dtime (int dtim);
};

Job::Job() //empty constructor
{
    id=transfer=withdraw=deposit=wealth=dtime=0; //set up job's values as all 0s, change them later when inserted into job_vector
}

int Job::get_id()
{
    return id;
}

int Job::get_transfer()
{
    return transfer;
}

int Job::get_withdraw()
{
    return withdraw;
}

int Job::get_deposit()
{
    return deposit;
}

int Job::get_wealth()
{
    return wealth;
}

int Job::get_dtime()
{
    return dtime;
}

void Job::set_id(int idd)
{
    id = idd;
}

void Job::set_transfer(int trans)
{
    transfer=trans;
}

void Job::set_withdraw(int with)
{
    withdraw = with;
}

void Job::set_deposit(int dep)
{
    deposit = dep;
}

void Job::set_wealth(int we)
{
    wealth = we;
}

void Job::set_dtime(int dtim)
{
    dtime = dtim;
}


int read_file(vector <string> &v); //read in file, put into string
int str_conversion(string n_str); //conversion from string to int
int sorted_ints (vector <int> &vi, string int_str);
void endl_conversion(vector <int> &vi, string int_str);

void QuickSort (vector <int> &vt, int left, int right);
void swapp (int *x, int *y); //for use in quicksort, swapping values
int part (vector <int> &vt, int left, int right);

int main()
{
    vector <string> csv; //items first read in from CSV file are strings
    vector <int> int_vector; //conversions happen just for ints in CSV file, put here
    vector <Job> jobs_vector; //jobs w 6 related categories, inserted into vector w all jobs (unsorted in beginning)
    vector <int> job_times;
    vector <Job> sorted_jobs; //after quicksorting the times, jobs are resorted into new vector
    int time, success, fail; //time - increment by 5 after job completed; success keeps # of successful jobs postings; fail keeps track of failed jobs
    time=success=fail=0;
    read_file(csv); //begin reading from csv file
    string no_str = csv[5]; //use for special case at beg of csv file (string AND int are joined together)
    char * no_array = new char [3];
    int k=0, i=0; //indexing purposes
    for (k=0;k<no_str.size();k++) //UNIQUE CASE - get fifth position of string vector when numbers are combined with string of text
                                    //in this case it's the first line on the CSV file (423 is attached at end)
    {
        if (no_str[k] == '\n' ) //find the newline char
        {
            no_array[0] = no_str[no_str.size()-3]; //customer ID for first job is 423, 3 digits total
            no_array[1] = no_str [no_str.size()-2];
            no_array[2] = no_str [no_str.size()-1];
            int_vector.push_back(atoi(no_array)); //first item is put on int_vector, later to be used for first job's ID
            k = no_str.size(); //ends loop (k's value indicates loop should end)
        }
    }

    for (i=6;i<csv.size();i++) //sort thru string vector AFTER first 6 lines
    {
        if (i%5==0) //every line that has the two nos combined is in index divisible by 5 (i.e. every 5th position in vector csv)
            endl_conversion(int_vector, csv[i]);
        else
            int_vector.push_back(str_conversion(csv[i])); //if it's not at that position, just insert the number onto the vector (after conversion)
    }

    Job temp_job; //temp_job will represent the new job to be inserted into jobs_vector
    i = 0; //reset index indicator i to 0 to start new search
    while (i<int_vector.size()) { //begin searching in int_vector for data; data is grouped as 6 ints in int_vector for each job
        temp_job.set_id(int_vector[i]);
        temp_job.set_transfer(int_vector[i+1]);
        temp_job.set_withdraw(int_vector[i+2]);
        temp_job.set_deposit(int_vector[i+3]);
        temp_job.set_wealth(int_vector[i+4]);
        temp_job.set_dtime(int_vector[i+5]);
        jobs_vector.push_back(temp_job); //push newly created job onto jobs_vector
        i+=6; //increase index by 6 to get next set of information for next job
    }
    //cout << "size of jobs_vector: " << jobs_vector.size() << endl << endl; //debugging

    int t;
    for (i=0;i<jobs_vector.size();i++)
    {
        t = jobs_vector[i].get_dtime();
        job_times.push_back(t);
    }

    QuickSort(job_times, 0, job_times.size()-1);
    for (i=0;i<job_times.size();i++) //jobs now sorted thanks to results from quicksort
    {
        for (int j=0;j<jobs_vector.size();j++)
        {
            if (job_times[i]==jobs_vector[j].get_dtime())
            {
                temp_job.set_id(jobs_vector[j].get_id());
                temp_job.set_transfer(jobs_vector[j].get_transfer());
                temp_job.set_withdraw(jobs_vector[j].get_withdraw());
                temp_job.set_deposit(jobs_vector[j].get_deposit());
                temp_job.set_wealth(jobs_vector[j].get_wealth());
                temp_job.set_dtime(jobs_vector[j].get_dtime());
                sorted_jobs.push_back(temp_job);
            }
        }
    }

    int answer;
    cout << "Jobs will begin taking place! Press 1 to begin! \n";
    cin >> answer;
    if (answer!=1) //let user decide when to begin job postings
    {
        cout << "Error, please try again \n";
        cin >> answer;
    }

    int next_time, current_time, next_wealth, current_wealth; //info on time/wealth for current/next job
    for (i=0;i<sorted_jobs.size();i++) //jobs will begin to be posted here
    {
        next_time = sorted_jobs[i+1].get_dtime(); current_time = sorted_jobs[i].get_dtime();
        next_wealth = sorted_jobs[i+1].get_wealth(); current_wealth = sorted_jobs[i].get_wealth();
        cout << "******************CURRENT TIME: ***************************" << time << endl << endl << endl;
        double current_hash = ceil(current_time/5);
        double next_hash = ceil(next_time/5);
        if (current_hash==next_hash) //collision w time occurs here
        {
            cout << "ERROR, issue with job times! Will fix! \n";
            if (current_wealth>next_wealth) //compare wealth
            {
                cout << "*********Job " << i << " takes priority due to wealth! Details further below. \n";
                cout << "Data for Job " << i << ": " << endl;
                cout << "ID: " << sorted_jobs[i].get_id() << endl;
                cout << "Transfer:  " << sorted_jobs[i].get_transfer() << endl;
                cout << "Withdraw: " << sorted_jobs[i].get_withdraw() << endl;
                cout << "Deposit: " << sorted_jobs[i].get_deposit() << endl;
                cout << "Wealth: " << sorted_jobs[i].get_wealth() << endl;
                cout << "Time: " << sorted_jobs[i].get_dtime() << endl << endl << endl;
                time+=5;
                if (time > sorted_jobs[i].get_dtime())
                {
                    fail++;
                    cout <<"Unfortunately the job posted late. \n";
                }
                else
                {
                    success++;
                    cout <<"The job posted on time and clients are happy. \n";
                }
                  //counters increase

            }
            else
            {
                cout << "*********Job " << i+1 << " takes priority due to wealth! Details further below. \n";
                cout << "Data for Job " << i+1 << ": " << endl;
                cout << "ID: " << sorted_jobs[i+1].get_id() << endl;
                cout << "Transfer:  " << sorted_jobs[i+1].get_transfer() << endl;
                cout << "Withdraw: " << sorted_jobs[i+1].get_withdraw() << endl;
                cout << "Deposit: " << sorted_jobs[i+1].get_deposit() << endl;
                cout << "Wealth: " << sorted_jobs[i+1].get_wealth() << endl;
                cout << "Time: " << sorted_jobs[i+1].get_dtime() << endl << endl << endl;
                time+=5;
                if (time > sorted_jobs[i+1].get_dtime()) //remember time is the current time going. when this time is greater than the time we need to post a job by, we have failed our service
                {
                    fail++; //counter increases
                    cout <<"Unfortunately the job posted late. \n"; //insufficient time to post job
                }
                else
                {
                    success++; //counter increases
                    cout <<"The job posted on time and clients are happy. \n"; //no issues w time
                }
            }

        }
        else
        {
            cout << "SUCCESS! Job posting details below. \n"; //output job details
            cout << "Data for Job " << i << ": " << endl;
            cout << "ID: " << sorted_jobs[i].get_id() << endl;
            cout << "Transfer:  " << sorted_jobs[i].get_transfer() << endl;
            cout << "Withdraw: " << sorted_jobs[i].get_withdraw() << endl;
            cout << "Deposit: " << sorted_jobs[i].get_deposit() << endl;
            cout << "Wealth: " << sorted_jobs[i].get_wealth() << endl;
            cout << "Time: " << sorted_jobs[i].get_dtime() << endl << endl << endl;
            time+=5;
            if (time > sorted_jobs[i].get_dtime())
                {
                    fail++;
                    cout <<"Unfortunately the job posted late. \n";
                }
                else
                {
                    success++;
                    cout <<"The job posted on time and clients are happy. \n";
                }
        }
    }

    cout << "DONE! Results below! \n \n \n"; //give breakdown of counters and fails, successes, time elapsed
    cout << "Total number of jobs: " << sorted_jobs.size() << endl;
    cout << "Successful postings: " << success << endl;
    cout << "Failed postings: " << fail << endl;
    cout << "Time elapsed: " << time << endl;
    cout << "\n \n \n THANKS FOR YOUR BUSINESS! \n";

    return 0;
}

int read_file (vector <string> &v)
{
    ifstream in; //input filestream to read file
    char * filename = new char [15]; //user input to type name of file with .txt extension
    cout << "Please enter the name of the file: ";
    cin >> filename;
    in.open(filename); //read from file name
    if (!in.is_open()){ //when the file cannot be opened, show error msg and give user another chance until the right file is typed
        cout << "Error, please try another file. \n \n";
        return read_file(v); //give user another chance to type in filename
    }

    char * num = new char [100]; //char array to store the integers as they are read
    while(in.peek()!=EOF)
    {
        in.getline(num,100,',');//int will be put in char array with the delimiter being a comma and the instance of a new line
        v.push_back(num);
    }

    in.clear();
    in.close();
    return 1;
}

int str_conversion (string n_str) //l=size of string being inserted (size of nos depends in this case)
{
    int real_int, l;
    l = n_str.size();
    char * new_array = new char [l];
    for (int b=0;b<l;b++) //copy chars int new array
    {
        new_array [b] = n_str [b];
    }
    real_int = atoi(new_array); //convert new array
    return real_int; //return array as a int
}

void endl_conversion(vector <int> &vi, string int_str)
{
    int A, B, j, e; //length of digits for these two numbers (time and customer ID); e = pos where endl exists; j = indexing purposes
    int k=0; //for B_array position
    for (j=0;j<int_str.size();j++) //get no of units for first and second int (time and cust ID)
    {
        if (int_str[j] == '\n'){
            e=j; //record pos where endl char exists
        }
        else{
            A++;
        }
    }
    B = e+1;
    char * A_array = new char [A]; //set up char arrays (to be used for conversion later below)
    char * B_array = new char [B];
    for (j=0;j<int_str.size();j++)
    {
        if (j<e)
            A_array[j]=int_str[j];
    }

    for (j=e;j<int_str.size();j++)
    {
        B_array[k] = int_str[j];
        k++;
    }
    int tempA, tempB;
    tempA = atoi(A_array);
    tempB = atoi (B_array);
    if (tempA!=0) //if number is NOT 0, add it!
        vi.push_back(atoi(A_array)); //two numbers are pushed onto vector, first is A and then B (time, THEN cust ID)
    if (tempB!=0) //same as tempA, avoid having any 0s in vector
        vi.push_back(atoi(B_array));

}

void QuickSort (vector <int> &vt, int left, int right)
{
    if (left<right)
    {
		int p = part(vt, left, right);

		QuickSort(vt, left, right-1);
		QuickSort(vt, p+1, right);
	}
}

void swapp (int &x, int &y) //for use in quicksort, swapping values
{
    int temp = x;
    x = y;
    y = temp;
}

int part (vector <int> &vt, int left, int right) //for use in quicksort
{
    int pivot = vt [right]; //pivot created
	int i = left-1;
	for (int j=left; j<=right-1; j++)
	{
		if (vt[j]<=pivot)
		{
			i++;
			swapp (vt[i], vt[j]); //swap ints
		}
	}
	swapp (vt[i+1], vt[right]); //swap here as well
	return i+1;
}


