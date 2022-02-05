#include<iostream>
#include<fstream>  // library for read and write file
#include<string>   // library to use string data type in cpp
#include <cstring>  // special string operation by converting it into char
#include<sstream>
//#include <cstdlib>

using namespace std;

//****  Global Variables  ***//

char M[100][4];  // declared memory to store program and data cards
int m=0;         // used to traverse defined memory
char IR[4];      // Instruction register to store 4 byte instruction from program card
int IC=0;           // Instruction counter points to next instruction going to execute
char R[4];         // General purpose register 'R' used for LR ,SR , CR instructions
int c;              // toggle Register used as a flag
int SI=0;           // Service Interrupt
char buffer[41];            // intermediate buffer for data transmission.
//char long_buf[120];
string s;

// Function...............
void show_memory()              // to display content of defined memory 'M'
{
    cout<<"\n\n";
    for(int i =0;i<100;i++)
    {                                   //  representation of memory.
        if (i<10)
        {
            cout<<"M["<<" "<<i<<"]: ";
        }
        else
        {
            cout<<"M["<<i<<"]: ";
        }
        for(int j =0;j<4; j++)
            cout<<M[i][j]<<"   ";
        cout<<"\n";
        if((i%10)==9)
            cout<<"\n";
    }
    cout<<"\n";
}

void clear_buf()        // to clear buffer for using it repetitively
{
    for(int i =0;i<40;i++)
    {
        buffer[i]='\0';
    }
    return;
}



void load();  // Declaring load function...
void init()
{                                   // function to initialize global variables and arrays
    for(int i =0;i<100;i++)
    {
        for(int j=0;j<4;j++)
        {
            M[i][j]='\0';
        }
        if(i<4)
        {
            IR[i]='\0';
            R[i]='\0';
            buffer[i]='\0';
        }
        else if(i<40)
        {
            buffer[i]='\0';
        }
    }

    IC=0;
    c;
    m=0;
}
ifstream inf("input.txt");      //opening input file in read mode
ofstream outf("output.txt");    //opening output file in write mode



void Read()         // function to read the data card from input file and store that data card in the memory using intermediate buffer
{
    inf.getline(buffer,40);
    int h=0;
    int i=0;
    int f=0;
    string a1,b1;
    a1=IR[2];
    b1=IR[3];

    int a= stoi(a1);
    int b = stoi(b1);
    while(buffer[(4*h)+i])
            {
                for(i =0;i<4; i++)
                {
                    if (buffer[(4*h)+i]=='\0')
                    {
                        f=1;
                        break;
                    }

                    M[(a*10)+h][i]=buffer[(4*h)+i];

                }
                h++;
                i=0;
                if (f==1)
                    return;

            }

}

void Write()
{                       //function to write output of job into output file using buffer
    int h=0;
    int i=0;
    int f=0;
    int k=0;
    int holder;
    int y;
    string a1,b1;
    a1=IR[2];
    b1=IR[3];

    int a = stoi(a1);
    int b = stoi(b1);
    h=(a*10);
    holder = h;
    clear_buf();
    while(h<(holder+10))
            {
                for(i =0;i<4; i++)
                {
                    if (M[h][i]=='\0')
                    {
                        y=h+1;
                        if (M[y][0]=='\0')
                        {
                            f=1;
                            break;
                        }
                        else
                        {
                            M[h][i]=' ';
                        }                                                         //writing memory content into a buffer
                    }

                    buffer[k++]=M[h][i];

                }

                h++;
                //i=0;
                if (f==1)
                    break;

            }
    cout<<buffer<<endl;           // writing complete buffer content into output file
    outf<<buffer<<"\n";


}

void Terminate()
{
   outf<<"\n\n";
   cout<<"";
   show_memory();
   init();    // initialize value for next job
   load();     //calling same function to execute consecutive job's

}

void MOS()
{
    switch(SI)
    {
        case 1:
            Read();
            break;
        case 2:
            Write();
            break;
        case 3:
            Terminate();
        default :
            break;
    }
    return;

}

void exe_user_pro()
{

    while(M[IC][0]!='\0')
    {
        for(int j =0;j<4; j++)
        {
            IR[j]=M[IC][j];             //loading IR with Program Card instruction.
        }
        IC++;                   // incrementing IC after each instruction get stored in IR
        if (IR[0]=='L')
        {
            string a1,b1;           // LR instruction implementation
            a1=IR[2];
            b1=IR[3];
            int a= stoi(a1);            // loading general purpose register R according to instruction.
            int b = stoi(b1);
            for(int j =0;j<4; j++)
            {
                R[j]=M[a*10+b][j];
            }
            for(int j =0;j<4; j++)
                cout<<R[j]<<endl;
        }
        else if(IR[0]=='S')
        {
            string a1,b1;           // SR instruction implementation
            a1=IR[2];
            b1=IR[3];
            int a= stoi(a1);
            int b = stoi(b1);
            for(int j =0;j<4; j++)
            {
                M[a*10+b][j]=R[j];
            }
            for(int j =0;j<4; j++)
                cout<<M[a*10+b][j]<<endl;
        }
        else if(IR[0]=='C')
        {
            string a1,b1;           // CR instruction implementation
            a1=IR[2];
            b1=IR[3];
            int a= stoi(a1);
            int b = stoi(b1);
            for(int j =0;j<4; j++)
            {
                if (M[a*10+b][j]!=R[j])
                {
                    c=0;
                    break;
                }
                else
                    c=1;
            }
        }
        else if(IR[0]=='B')
        {
            if (c==1)               // BT instruction implementation
            {
                string a1,b1;
                a1=IR[2];
                b1=IR[3];
                int a= stoi(a1);
                int b = stoi(b1);
                IC=a*10+b;
            }
        }
        else if (IR[0]=='G')
        {
           SI=1;
           MOS();
        }
        else if (IR[0]=='P')
        {
           SI=2;
           MOS();
        }
        else if (IR[0]=='H')
        {
           SI=3;
           MOS();
        }
        else if (IR[0]=='A')
        {
            int count=0;
            string a,num,na;
            na="NPos";
            a=(string)R;
            int b = stoi(a); //num from r

            string a1,b1,c1;
            a1=IR[2];
            b1=IR[3];
            int aa= stoi(a1);
            int bb = stoi(b1);
            c1=(string)M[aa*10+bb];
            int cc = stoi(c1);;
            int c = b+cc;
            stringstream ss;

            if(c<10000)
            {
                ss << c;
                ss >> num;
                strcpy(R, num.c_str());
            }
            else
            {
                cout<< "ADD NOT POSSIBLE"<<endl;
                strcpy(R, na.c_str());
            }



        }
    }

}

void start_exe()
{
    cout<<"Execution Started"<<endl;
    exe_user_pro();

}

void load()
{
    while(inf.eof() == 0)
    {
        inf.getline(buffer,41);
        if(buffer[0]=='$' && buffer[1]=='A' && buffer[2]=='M' && buffer[3]=='J')
        {
            //init();
        }
        else if(buffer[0]=='$' && buffer[1]=='D' && buffer[2]=='T' && buffer[3]=='A')
        {
            start_exe();
        }
        else if(buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D')
        {
            continue;
        }
        else
        {
            int i=0;
            int h=0;
            int f=0;
            while(buffer[(4*h)+i]!='\0')
            {
                for(i =0;i<4; i++)
                {
                    if (buffer[(4*h)+i]=='\0')
                    {
                        f=1;
                        break;
                    }

                    M[m][i]=buffer[(4*h)+i];
                    if (i>2)
                    {

                        m++;
                        h++;
                    }

                }
                if (f==1)
                    break;
                i=0;


            }

        }

    }
}



int main()
{

    load();
    inf.close();
    outf.close();

    cout<<"\nAll tasks executed successfully\n";
    return 0;
}
