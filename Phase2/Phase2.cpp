#include<iostream>
#include<fstream>  // library for read and write file
#include<string>   // library to use string data type in cpp
#include <cstring>  // special string operation by converting it into char
#include<sstream>
#include <vector>
#include <algorithm>
//#include <cstdlib>

using namespace std;

class PCB
{
    public:
        int job_id;
        int TTL;
        int TLL;
        int TTC;
        int TLC;

        PCB()
        {
            job_id = 0;
            this->TTL = 0;
            this->TLL = 0;
            this->TTC = 0;
            this->TLC = 0;
        }

        void init(int jI,int TTL, int TLL)
        {
            job_id = jI;
            this->TTL = TTL;
            this->TLL = TLL;
            this->TTC = 0;
            this->TLC = 0;
        }
        void show()
        {
            cout<<"ID : "<<job_id<<" TTL : "<<TTL<<" TLL : "<<TLL<<endl;
        }

};

//****  Global Variables  ***//

char M[300][4];  // declared memory to store program and data cards
int m;         // used to traverse defined memory
char IR[4];      // Instruction register to store 4 byte instruction from program card
int IC;           // Instruction counter points to next instruction going to execute
char R[4];         // General purpose register 'R' used for LR ,SR , CR instructions
int c;              // toggle Register used as a flag
int SI;           // Service Interrupt
int PI;
int TI;           // Time Interrupt
char PTR[4];        // page table register

int VA;            // Virtual Address
int RA;           // Real Address
//int TTC;            // total time counter
//int LLC;            // Line Limit Counter
//int TTL;            // Total Time Limit
//int TLL;            // Total Line Limit
int EM;             // Error MSG
vector<int> frames;
PCB P;

char buffer[41];            // intermediate buffer for data transmission.
//char long_buf[120];
string s;

///////////////////////////////////////////////////////////////////////////////
// Function...............

void init()
{                                   // function to initialize global variables and arrays
    for(int i =0;i<300;i++)
    {
        for(int j=0;j<4;j++)
        {
            M[i][j]='\0';
        }
        if(i<4)
        {
            IR[i]='\0';
            R[i]='\0';
            //buffer[i]='\0';
            PTR[i]='\0';
        }
        else if(i<40)
        {
            //buffer[i]='\0';
        }
    }

    IC=0;
    c;
    m=0;
    SI=0;
    PI=0;
    TI=0;
    frames = {1,10,29,13,4,25,16,7,24,9,0,11,28,3,14,26,6,17,18,19,20,21,12,23,8,5,15,27,21,2};
}


void show_memory()              // to display content of defined memory 'M'
{
    cout<<"\n\n";
    for(int i =0;i<300;i++)
    {                                   //  representation of memory.
        if (i<10)
        {
            cout<<"M["<<" "<<i<<"] |  ";
        }
        else
        {
            cout<<"M["<<i<<"] |  ";
        }
        for(int j =0;j<4; j++)
            cout<<M[i][j]<<"  |  ";
        cout<<"\n_______________________________\n";
        if((i%10)==9)
            cout<<"\n________________________________\n";
    }
    cout<<"\n";
}

int Random_Gen(vector<int> &v)
{
    int i=0;
	random_shuffle(v.begin(), v.end());
	int r = v.front();
	v.erase(v.begin());
	cout<<r<<endl;
	random_shuffle(v.begin(), v.end());
	return r;
}



void init_PT(int ptr )
{
    for(int j=ptr;j<ptr+10;j++)
    {
        for (int z=0;z<4;z++)
        {
            M[j][z]='#';
        }
    }
}

int AddM(int VA)
{
     for(int x =0;x<4; x++)
    {
        cout<<"ptr "<<x<< "  "<<PTR[x]<<endl;
    }

    int pte = (((int)PTR[2] - 48) *10 + ((int)PTR[3] - 48))*10 + VA/10;
    cout<<"pte :"<<pte<<"  "<<VA<<endl;
    RA = ((((int)M[pte][2] - 48)*10 + (int)M[pte][3] - 48 )*10)+ VA%10;
    cout<<"RA : "<<RA<<endl;
    return RA;
}

void clear_buf()        // to clear buffer for using it repetitively
{
    for(int i =0;i<40;i++)
    {
        buffer[i]='\0';
    }
    return;
}

void Allocate( int SA)
{

}



void load();
void MOS(char c);  // Declaring load function...


ifstream inf("job.txt");      //opening input file in read mode
ofstream outf("output.txt");    //opening output file in write mode



void Read()
{
    cout<<"R";              // function to read the data card from input file and store that data card in the memory using intermediate buffer
    //inf>>buffer;
    inf.getline(buffer,40);
    //str_char(s);
    cout<<"*****"<<buffer;

    int h=0;
    int i=0;
    int f=0;
    int z =1;
    string a1,b1;
    a1=IR[2];
    b1=IR[3];
    if (buffer[0]=='$' && buffer[1]=='E')
    {
        z=0;
        MOS('o');
    }
    try
    {
        int a= stoi(a1);
        int b = stoi(b1);
    }
    catch (const std::invalid_argument& ia)
    {
        cout<<"*c";
        z=0;
        PI = 2;
        MOS('p');
    }

    if (z)
    {
        int sa = Random_Gen(frames);
        cout<<"sa "<<sa << endl;
        int q=0;
        int ptr = ((int)PTR[2] - 48)*10 + (int)PTR[3] - 48;

        while(M[ptr*10+q][0]!='#')
        {
            q++;
        }
                //cout<<"\nQ:"<<ptr*10+q<<endl;
        M[ptr*10+q][0]='0';
        M[ptr*10+q][1]='0';
        M[ptr*10+q][2]= (char)((sa/10)+48);
        M[ptr*10+q][3]= (char)((sa%10)+48);
        //cout<<a<<b<<endl;
        while(buffer[(4*h)+i])
                {
                    for(i =0;i<4; i++)
                    {
                       // cout<<m<< i<<" ";
                        if (buffer[(4*h)+i]=='\0')
                        {
                            f=1;
                            break;
                        }

                        M[(sa*10)+h][i]=buffer[(4*h)+i];
                        cout<<M[(sa*10)+h][i]<<buffer[(4*h)+i]<<" ";
                       // cout<<m<< i<<" ";

                    }
                    h++;
                    i=0;
                    if (f==1)
                        return;

                }
    }


}

void Write()
{                       //function to write output of job into output file using buffer
    cout<<"W";
    int h=0;
    int i=0;
    int f=0;
    int k=0;
    int z = 1;
    int holder;
    int y,a,b;
    string a1,b1;
    a1=IR[2];
    b1=IR[3];
    try
    {
        a= stoi(a1);
        b = stoi(b1);
    }
    catch (const std::invalid_argument& ia)
    {
        cout<<"*c";
        z=0;
        PI = 2;
        MOS('p');
    }
    if (z)
    {
        cout<<a<<b<<endl;
        VA=a*10;
        h = AddM(VA);
        if (h<0 || h>299)
        {
            z=0;
            PI = 3;
            MOS('p');

        }
        else
        {
            holder = h;
            clear_buf();
            while(h<(holder+10))
                    {
                        for(i =0;i<4; i++)
                        {
                           // cout<<m<< i<<" ";
                            if (M[h][i]=='\0')
                            {
                                //cout<<h;
                                y=h+1;
                                if (M[y][0]=='\0')
                                {
                                    //cout<<"***********"<<M[y][0]<<"**************"<<y<<" ";
                                    f=1;
                                    break;
                                }
                                else
                                {
                                    M[h][i]=' ';
                                }                                                         //writing memory content into a buffer
                            }

                            buffer[k++]=M[h][i];
                           // cout<<M[(a*10)+b+h][i]<<buffer[(4*h)+i]<<" ";
                           // cout<<m<< i<<" ";

                        }

                        h++;
                        i=0;
                        if (f==1)
                            break;

                }
        }

        cout<<buffer;           // writing complete buffer content into output file
        outf<<buffer<<"\n";
    }



}

void Terminate()
{
   outf<<"\n\n";
   //cout<<"t";
   show_memory();
   init();
   clear_buf();   // initialize value for next job
   load();     //calling same function to execute consecutive job's

}

void MOS( char c)
{
    if (c == 's')
    {
        switch(SI)
        {
            case 1:
                Read();
                //cout<<"@@@@";
                break;
            case 2:
                Write();
                break;
            case 3:
                Terminate();
            default :
                break;
        }
    }
    else if (c == 'p')
    {
        switch(PI)
        {
            case 1:
                cout<<"PE>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
                outf<<"ERROR  : Operation Error"<<"\n";
                outf<<"STATUS : Program( job id ="<<P.job_id<<" ) "<<" Terminated Abnormally.........................";
                cout<<"opp\n";
                //cout<<buffer;
                //while(inf.eof() == 0)
                while (buffer[1]!='E')
                {
                    inf.getline(buffer,40);
                    cout<<buffer;
                    //if (buffer[1]=='E')
                        //break;
                }

                SI=3;
                MOS('s');

                break;
            case 2:
                cout<<"0PDE>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
                outf<<"ERROR  : Operand Error"<<"\n";
                outf<<"STATUS : Program( job id ="<<P.job_id<<" ) "<<" Terminated Abnormaly.........................";
                cout<<"opD\n";
                //cout<<buffer;
                //while(inf.eof() == 0)
                while (buffer[1]!='E')
                {
                    inf.getline(buffer,40);
                    cout<<buffer;
                    //if (buffer[1]=='E')
                        //break;
                }

                SI=3;
                MOS('s');
                break;
            case 3:
                cout<<"pf>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
                outf<<"ERROR  : Invalid Page Fault"<<"\n";
                outf<<"STATUS : Program( job id ="<<P.job_id<<" ) "<<" Terminated Abnormally.........................";
                cout<<"pF\n";
                //cout<<buffer;
                //while(inf.eof() == 0)
                while (buffer[1]!='E')
                {
                    inf.getline(buffer,40);
                    cout<<buffer;
                    //if (buffer[1]=='E')
                        //break;
                }

                SI=3;
                MOS('s');
                break;
            default :
                break;
        }
    }
    else if (c == 't')
    {
        cout<<"TTE>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        outf<<"ERROR  : Time Limit Exceeded"<<"\n";
        outf<<"STATUS : Program( job id ="<<P.job_id<<" ) "<<" Terminated Abnormally.........................";
        cout<<"ott\n";
        cout<<buffer;
        //while(inf.eof() == 0)
        while (buffer[1]!='E')
        {
            inf.getline(buffer,40);
            cout<<buffer;
            //if (buffer[1]=='E')
                //break;
        }

        SI=3;
        MOS('s');
    }
    else if (c == 'o')
    {
        cout<<"DOE>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
                outf<<"ERROR  : Out of Data Error"<<"\n";
                outf<<"STATUS : Program( job id ="<<P.job_id<<" ) "<<" Terminated Abnormally.........................";
                cout<<"oDE\n";
                //cout<<buffer;
                //while(inf.eof() == 0)
                while (buffer[1]!='E')
                {
                    inf.getline(buffer,40);
                    cout<<buffer;
                    //if (buffer[1]=='E')
                        //break;
                }

                SI=3;
                MOS('s');
    }
    else if (c == 'l')
    {
        cout<<"TLE>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
        outf<<"ERROR  : Line Limit Exceeded"<<"\n";
        outf<<"STATUS : Program( job id ="<<P.job_id<<" ) "<<" Terminated Abnormally.........................";
        cout<<"oll\n";
        //cout<<buffer;
        //while(inf.eof() == 0)
        while (buffer[1]!='E')
        {
            inf.getline(buffer,40);
            cout<<buffer;
            //if (buffer[1]=='E')
                //break;
        }

        SI=3;
        MOS('s');
    }

    return;

}

void exe_user_pro()
{
    VA = IC;
    int z = 1;

    int m1 = AddM(VA);
    /*for(int x =0;x<4; x++)
    {
        cout<<"ptr "<<x<< "  "<<PTR[x]<<endl;
    }*/
     int ia= m1;

    while(M[m1][0]!='\0')
    {

        //cout<<IC<<"  "<<M[IC][0];
        for(int j =0;j<4; j++)
        {
            IR[j]=M[m1][j];             //loading IR with Program Card instruction.
            //if (M[IC][j]=='H')
                //break;
        }
        for(int j =0;j<4; j++)
            cout<<"\nIR:"<<IR[j]<<"    ";
        //cout<<"->";
        IC++;

        m1++;
                       // incrementing IC after each instruction get stored in IR


        if (IR[0]=='L' && IR[1]=='R')
        {
            P.TTC++;
            if (P.TTC > P.TTL)
            {
                MOS('t');
                break;
            }
            string a1,b1;           // LR instruction implementation
            a1=IR[2];
            b1=IR[3];
            int a,b;
            try
            {
                a= stoi(a1);
                b = stoi(b1);
            }
            catch (const std::invalid_argument& ia)
            {
                //cout<<"*c";
                z=0;
                PI = 2;
                MOS('p');
            }
            if (z)            // loading general purpose register R according to instruction.
            {
                VA=a*10+b;
                int l= AddM(VA);
                //cout<<"|"<<a<<b<<"|";
                for(int j =0;j<4; j++)
                {
                    R[j]=M[l][j];
                }
                for(int j =0;j<4; j++)
                    cout<<R[j];

            }



        }
        else if(IR[0]=='S' && IR[1]=='R')
        {
            P.TTC+=2;
            if (P.TTC > P.TTL)
            {
                MOS('t');
                break;
            }
            string a1,b1;           // SR instruction implementation
            a1=IR[2];
            b1=IR[3];
            int a,b;
            try
            {
                a= stoi(a1);
                b = stoi(b1);
            }
            catch (const std::invalid_argument& ia)
            {
                cout<<"*c";
                z=0;
                PI = 2;
                MOS('p');
            }
            if (z)
            {
                VA=a*10+b;
                int l= AddM(VA);
                //cout<<"|"<<a<<b<<"|";
                for(int j =0;j<4; j++)
                {
                    M[l][j]=R[j];
                }
                for(int j =0;j<4; j++)
                    cout<<M[l][j];
            }



        }
        else if(IR[0]=='C' && IR[1]=='R')
        {
            P.TTC++;
            if (P.TTC > P.TTL)
            {
                MOS('t');
                break;
            }
            string a1,b1;           // CR instruction implementation
            a1=IR[2];
            b1=IR[3];
            int a,b;
            try
            {
                a= stoi(a1);
                b = stoi(b1);
            }
            catch (const std::invalid_argument& ia)
            {
                cout<<"*c";
                z=0;
                PI = 2;
                MOS('p');
            }
            if (z)
            {
                VA=a*10+b;
                int l= AddM(VA);
                //cout<<"|"<<a<<b<<"|";
                for(int j =0;j<4; j++)
                {
                    if (M[l+b][j]!=R[j])
                    {
                        c=0;
                        break;
                    }
                    else
                        c=1;
            }
            }

            //cout<<"*"<<c;
        }
        else if(IR[0]=='B' && IR[1]=='T')
        {
            P.TTC++;
            if (P.TTC > P.TTL)
            {
                MOS('t');
                break;
            }
            int a,b;
            if (c==1)               // BT instruction implementation
            {
                string a1,b1;
                a1=IR[2];
                b1=IR[3];
                try
                {
                    a= stoi(a1);
                    b = stoi(b1);
                }
                catch (const std::invalid_argument& ia)
                {
                    cout<<"*c";
                    z=0;
                    PI = 2;
                    MOS('p');
                }
                if (z)
                {
                    IC=a*10+b;
                    exe_user_pro();
                    break;
                }

            }
        }
        else if (IR[0]=='G' && IR[1]=='D')
        {
           P.TTC+=2;
            if (P.TTC > P.TTL)
            {
                MOS('t');
                break;
            }
           SI=1;
           MOS('s');
           //cout<<"####";
           //break;
        }
        else if (IR[0]=='P' && IR[1]=='D')
        {
           P.TTC++;
           P.TLC++;
            if (P.TTC > P.TTL)
            {
                MOS('t');
                break;
            }
            else if (P.TLC > P.TLL)
            {
                MOS('l');
                break;
            }
           SI=2;
           MOS('s');
           //break;
        }
        else if (IR[0]=='H' && IR[1]=='\0')
        {
           P.TTC++;
            if (P.TTC > P.TTL + 1)
            {
                MOS('t');
                break;
            }
           cout<<"in t";
           SI=3;
           MOS('s');
           //break;
        }
        else
        {
            cout<<"*e";
            PI = 1;
            MOS('p');
        }

        if (m1 == ia+10 && M[m1-1][3]!='\0' && M[m1-1][0]!='H')
        {
            cout<<"IC :"<<IC;
            exe_user_pro();

            break;


        }

    }

}

void start_exe()
{
    cout<<"\nExecution Started..........\n";
    exe_user_pro();

}

void load()
{
    //string s;
    while(inf.eof() == 0)
    {
        //inf>>buffer;
        //string s;
        inf.getline(buffer,41);
        //str_char(s);

        //cout<<buffer;
        /*cout<<"buffer line:";
        for(int i =0;buffer[i]!='\0';i++)
        cout<<buffer[i];
        cout<<'\n';*/
        if(buffer[0]=='$' && buffer[1]=='A' && buffer[2]=='M' && buffer[3]=='J')
        {

            int j = ((int)buffer[6] -48)*10 +(int)buffer[7] -48;
            if (j==1)
                init();
            int t = ((int)buffer[10] -48)*10 +(int)buffer[11] -48;
            int l = ((int)buffer[14] -48)*10 +(int)buffer[15] -48;

            P.init(j,t,l);
            P.TTL = t;
            P.TLL = l;
            P.show();
            PTR[0]='0';
            PTR[1]='0';
            int ptr= Random_Gen(frames);
            PTR[2]=(char)((ptr/10)+48);
            PTR[3]= (char)((ptr%10)+48);

            init_PT(ptr*10);

            for(int x =0;x<4; x++)
            {

                 cout<<"ptr "<<x<< "  "<<PTR[x]<<endl;
            }
            cout<<"i";

        }
        else if(buffer[0]=='$' && buffer[1]=='D' && buffer[2]=='T' && buffer[3]=='A')
        {
            start_exe();
        }
        else if(buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D')
        {
            cout<<"Terminate program";
            continue;
        }
        else
        {
            int sa = Random_Gen(frames);
            cout<<"*sa "<<sa << endl;
            int q=0;
            int ptr = ((int)PTR[2] - 48)*10 + (int)PTR[3] - 48;

            while(M[ptr*10+q][0]!='#')
            {
                q++;
            }
            //cout<<"\nQ:"<<ptr*10+q<<endl;
            M[ptr*10+q][0]='0';
            M[ptr*10+q][1]='0';
            M[ptr*10+q][2]= (char)((sa/10)+48);
            M[ptr*10+q][3]= (char)((sa%10)+48);

            m=sa*10;
            int i=0;
            int h=0;
            int f=0;
            int g = 0;
            while(buffer[(4*h)+i-g]!='\0')
            {
                //cout<<m<< i<<" ";
                for(i =0;i<4; i++)
                {
                   // cout<<m<< i<<" ";
                    if (buffer[(4*h)+i-g]=='\0')
                    {
                        //cout<<"a";
                        f=1;
                        break;
                    }

                    M[m][i]=buffer[(4*h)+i-g];
                    if (buffer[(4*h)+i-g]=='H' && buffer[(4*h)+i+1-g]!='\0')
                    {
                        m++;
                        h++;
                        g=3;
                        break;
                    }
                   // cout<<m<< i<<" ";
                    if (i>2)
                    {

                        m++;
                        h++;
                        //i=0;
                    }

                }
                if (f==1)
                    break;
                //if (i==4)
                i=0;


            }


        }

    }
}



int main()
{

    load();
    //show_memory();
    inf.close();
    outf.close();
    //show_memory();

    cout<<"\n\n done \n";
    return 0;
}
