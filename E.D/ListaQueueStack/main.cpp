#include "List.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

//Process Data
struct P_Data
{
    int mag_id;
    int proc_time;
    int e_Num;
    int e_QueuePos;

    P_Data()
    {
        mag_id = -1;
        proc_time = 0;
    }

    P_Data(int mag_id, int proc_time)
    {
        this->mag_id = mag_id;
        this->proc_time = proc_time;
    }

    P_Data(int mag_id, int proc_time, int eNum, int eQuePos)
    {
        this->mag_id = mag_id;
        this->proc_time = proc_time;
        e_Num = eNum;
        e_QueuePos = eQuePos;
    }

    void Print()
    {
        cout << "mag_id = " << mag_id << endl;
        cout << "proc_time = " << proc_time << endl;
    }

    friend std::ostream& operator<<(ostream& os, const P_Data& pd)  
    {  
        os << "Mag: " << pd.mag_id << " ProcTime:" << pd.proc_time << endl;  
        return os;  
    } 
};

struct M_Data
{
    int work_time;
    List<P_Data>* proccesses = new List<P_Data>();

    M_Data()
    {
        work_time = 24;
    }

    M_Data(int hours)
    {
        work_time = hours;
    }
};

int main()
{
    int E;
    std::cin >> E;
    //lista com as empresas e seus processos
    List<P_Data>* e_list = new List<P_Data>[E];
    //List<List<P_Data>>* test = new List<List<P_Data>>;

    for(int i = 0; i < E; i++)
    {
        int num_proc;
        cin >> num_proc;
        List<P_Data>* newList = new List<P_Data>();

        for(int j = 0; j < num_proc; j++)
        {
            int mag;
            cin >> mag;
            int times; 
            cin >> times; 
            P_Data neo(mag, times, i, j);
            newList->Enqueue(neo);    
        }
        e_list[i] = *newList; 
    }

    int M;
    std::cin >> M;
    //lista com as os magisterios e seus dados
    M_Data* m_list = new M_Data[M];

    for(int i = 0; i < M; i++)
    {
        int hours;
        cin >> hours;
        M_Data mag_data(hours);
        m_list[0] = mag_data;
    }


    int nullCount = 0;
    while (nullCount <= E-1)
    {
        for(int i = 0, j = 0; i < E; i++, j++)
        {
            if(j >= M)
                j = 0;
            if(e_list[i].head == nullptr)
                nullCount++;
            else
            {
                m_list[j].proccesses->Stack_push(e_list[i].head->key);
                e_list[i].Queue_pop();
            }
        }
    }

    //Getting segmentation fault(core dumped here after rearranging stacks)
    /*for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < M; j++)
        {
            Node<P_Data>* temp = m_list[j].proccesses->head;
            List<P_Data>* SY = new List<P_Data>();
            List<P_Data>* S0 = new List<P_Data>();
            while(temp != nullptr)
            {
                cout << m_list[j].proccesses->last->key;
                if(i == temp->key.mag_id)
                {
                    SY->Stack_push(m_list[j].proccesses->last->key);
                    m_list[j].proccesses->Stack_pop();
                }
                else
                {
                    S0->Stack_push(m_list[j].proccesses->last->key);
                    m_list[j].proccesses->Stack_pop();
                }

                temp = temp->next;
            }
            m_list[j].proccesses = S0;
            m_list[i].proccesses->last->next = SY->head;
            m_list[i].proccesses->last = SY->last;
        }
    }*/

    //no finishing loop correctly, both inner and out loop
    nullCount = 0;
    while(nullCount < M)
    {
        for(int i = 0; i < M; i++)
        {
            int fullTime = m_list[i].work_time;
            while(m_list[i].work_time > 0)
            {
                int proctime = m_list[i].proccesses->last->key.proc_time;
                m_list[i].proccesses->last->key.proc_time = proctime - m_list[i].work_time;
                cout << "work Time is:" << m_list[i].work_time << endl;
                m_list[i].work_time = m_list[i].work_time - abs(proctime);
                if(m_list[i].proccesses->last->key.proc_time <= 0)
                {
                    P_Data ref = m_list[i].proccesses->last->key;
                    cout << i << " " << ref.e_Num << " " << ref.e_QueuePos << endl;
                    m_list[i].proccesses->Stack_pop();
                    if(m_list[i].proccesses->head == nullptr)
                        nullCount++;
                }
                cout << "New Worktime is: " << m_list[i].work_time << endl;
            }
            m_list[i].work_time = fullTime;
        }
    }

    return 0;
}