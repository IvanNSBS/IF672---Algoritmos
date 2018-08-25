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

    friend std::ostream& operator<<(ostream& os, const P_Data& pd)  
    {  
        os << "Mag: " << pd.mag_id << " ProcTime:" << pd.proc_time << " Empresa num: " << pd.e_Num << " E_P_QuePos: " << pd.e_QueuePos << endl;  
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

    //cria os processos para as empresas
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
            newList->Stack_push(neo);    
        }
        e_list[i] = *newList; 
        //cout<< "Process "<< i << " list: " << endl; e_list[i].PrintTree();
    }


    int M;
    std::cin >> M;
    //lista com as os magisterios e seus dados
    M_Data* m_list = new M_Data[M];

    //cria os magisterios
    for(int i = 0; i < M; i++)
    {
        int hours;
        cin >> hours;
        M_Data mag_data(hours);
        m_list[i] = mag_data;
    }


    //passa os processos das empresas para os magisterios
    int nullCount = 0;
    while (nullCount <= E)
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

        for(int i = 0; i < M; i++)
    {
        cout << "Mag " << i << " Processes:"<< endl; m_list[i].proccesses->PrintTree();
    }

    //re-ordena os processos baseados nas prioridades
    //Getting segmentation fault(core dumped) here after rearranging stacks
    for(int y = 0; y < M; y++)
    {
        for(int x = 0; x < M; x++)
        {
            if(x != y)
            {
                Node<P_Data>* temp = m_list[x].proccesses->last;
                List<P_Data>* SY = new List<P_Data>();
                List<P_Data>* S0 = new List<P_Data>();
                while(temp != nullptr)
                {
                    //cout << m_list[j].proccesses->last->key;
                    if(y == temp->key.mag_id)
                    {
                        SY->Stack_push(m_list[x].proccesses->last->key);
                        m_list[x].proccesses->Stack_pop();
                    }
                    else
                    {
                        S0->Stack_push(m_list[x].proccesses->last->key);
                        m_list[x].proccesses->Stack_pop();
                    }
                    temp = temp->prev;
                }
                m_list[x].proccesses = S0;
                
                if(SY->head != nullptr)
                {
                    SY->head->prev = m_list[y].proccesses->last;
                    m_list[y].proccesses->last->next = SY->head;
                    m_list[y].proccesses->last = SY->last;
                }
            }
        }
    }

    for(int i = 0; i < M; i++)
    {
        cout << "Mag " << i << " Processes:"<< endl; m_list[i].proccesses->PrintTree();
    }

    //resolve os processos
    nullCount = 0;
    while(nullCount < M)
    {
        for(int i = 0; i < M; i++)
        {
            int fullTime = m_list[i].work_time;
            if(m_list[i].work_time > 0 && m_list[i].proccesses->head != nullptr)
            {
                while(m_list[i].work_time > 0 && m_list[i].proccesses->head != nullptr)
                {
                    int proctime = m_list[i].proccesses->last->key.proc_time;
                    m_list[i].proccesses->last->key.proc_time -= m_list[i].work_time;
                    m_list[i].work_time -= proctime;
                    if(m_list[i].proccesses->last->key.proc_time <= 0)
                    {
                        P_Data ref = m_list[i].proccesses->last->key;
                        cout << i << " " << ref.e_Num << " " << ref.e_QueuePos << endl;
                        m_list[i].proccesses->Stack_pop();
                        if(m_list[i].proccesses->head == nullptr)
                            nullCount++;
                    }
                }
            }
            m_list[i].work_time = fullTime;
        }
    }
    return 0;
}