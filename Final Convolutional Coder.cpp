#include<bits/stdc++.h>

#include <iostream>
#define ll long long
using namespace std;


int main(){
int i,j,k,ran,count=0,error[1000],channel;
double snr;
double p;
cout<<"Enter bit length\n";
cin>>k;

cout<<"Which Channel do you want:\n1.BSC\n2.BEC\n3.Gaussian\n";
cin>>channel;
if(channel ==1||channel==2)
{
    cout<<endl<<"Enter error probability\n"<<endl;
    cin>>p;
}
if(channel==3)
{
    cout<<endl<<"Enter SNR\n"<<endl;
    cin>>snr;
}
int code[k+4];
int a[2*k+4];
code[0]=0;
code[1]=0;
code[k+3]=0;
code[k+2]=0;


srand(time(0));
for(i=2;i<k+2;i++)
{
    ran=rand();
    code[i]=ran%2;
}
cout<<"\n Generated Code: ";
for(i=2;i<k+2;i++)
    cout<<code[i];
cout<<"\n Generated Code: ";
for(i=0;i<k+4;i++)
    cout<<code[i];

//Encoder

for(i=2,j=0;i<k+4;i++,j++)
{
    a[j*2]=(code[i]+code[i-1]+code[i-2])%2;
    a[j*2+1]=(code[i]+code[i-2])%2;
}
cout<<endl<<" Encoded Code:";
for(i=0;i<2*k+4;i++)
    cout<<a[i];
cout<<endl;

//Channel

if(channel==1)
{
    for(i=0;i<2*k+4;i++)
{
    ran=rand()%100;
    if(ran<=p*100)
    {
        error[count]=i;
        count++;
        if(a[i]==0)
            a[i]=1;
        if(a[i]==1)
            a[i]=0;
    }
}
}

if(channel==2)
{
   for(i=0;i<2*k+4;i++)
{
    ran=rand()%100;
    if(ran<=p*100)
    {
        error[count]=i;
        count++;
        a[i]=0;
    }
}
}

if(channel==3)
{
    double a1[2*k+4],a2[2*k+4];

    for(i=0;i<2*k+4;i++)
    {
        a1[i]=a[i];
        a2[i]=a1[i];
    }

    double snr_linear,variance_square,variance,f_term,value,x1,x2,sign_chk;

    snr=snr/10;
    snr_linear=pow(10,snr);
    variance_square=1/snr_linear;
    variance=sqrt(variance_square);
    for(i=0;i<2*k+4;i++)
    {
        a2[i]=2*a2[i]-1;
    }
    f_term=1/(sqrt(2*3.14)*variance);
    for(i=0;i<2*k+4;i++)
    {
        x1=(rand()%400)/1000.0;
        if(x1<0.130)
            x1=x1+0.130;
        x2=(rand()%400)/1000.0;
        if(x2<0.130)
            x2=x2+0.130;
        if(x1>x2)
        {
            value=sqrt(-2*variance*log(x1/f_term));
        }
        else
            value=sqrt(-2*variance*log(x2/f_term));
        sign_chk=rand()%2;
        if(sign_chk==0)
            value=-value;
        a2[i]=a2[i]+value;
    }

    for(i=0;i<2*k+4;i++)
    {
        if(a2[i]<0)
            a2[i]=0;
        else
            a2[i]=1;
    }
    for(i=0;i<2*k+4;i++)
    {
        if(a1[i]!=a2[i])
        {
            error[count]=i;
            count++;
        }



    }
    for(i=0;i<2*k+4;i++)
        a[i]=(int)a2[i];



}

cout<<"Encoded Code After passing through Channel:";
for(i=0;i<2*k+4;i++)
    cout<<a[i];
cout<<endl;



//Decoder
int st[8]={0,0,1,1,1,0,0,1};//states 00,11,10,01s
	int st1[8]={1,1,0,0,0,1,1,0};

	int n=k+2,x,y;
	int b[n][4];
	int bm[n][4];
	int decoded[n];
	int a1,b1;
	b[0][3]=1000;
	b[0][2]=1000;

	for(j=0;j<2;j++)
	{
	     b[0][j]=0;
	        if(st[j*2]!=a[0*2])
	            b[0][j]++;
	        if(st[j*2+1]!=a[0*2+1])
	            b[0][j]++;
	}
	for(i=0;i<4;i++)
        bm[0][i]=b[0][i];
	for(i=1;i<n;i++)
	{

	    for(j=0;j<4;j++)
	    {

	       if(j<2)
	       {
	           x=b[i-1][0];
	           if(st[j*2]!=a[i*2])
	            x++;
	            if(st[j*2+1]!=a[i*2+1])
	            x++;



	           y=b[i-1][2];
	            if(st1[j*2]!=a[i*2])
	            y++;
	            if(st1[j*2+1]!=a[i*2+1])
	            y++;



	           if(x<y)
               {
                    b[i][j]=x;
                    bm[i][j]=x-b[i-1][0];
               }

	            if(x>=y)
                {
                    b[i][j]=y;
                    bm[i][j]=y-b[i-1][2];
                }

	       }
	        else
	        {

	               x=b[i-1][1];
	                if(st[j*2]!=a[i*2])
	                x++;
	                if(st[j*2+1]!=a[i*2+1])
	                x++;



	           y=b[i-1][3];
	            if(st1[j*2]!=a[i*2])
	            y++;
	            if(st1[j*2+1]!=a[i*2+1])
	            y++;


                if(x<y)
               {
                    b[i][j]=x;
                    bm[i][j]=x-b[i-1][1];
               }

	            if(x>=y)
                {
                    b[i][j]=y;
                    bm[i][j]=y-b[i-1][3];
                }
	        }


	    }
	}
    cout<<endl<<"Branch Matrix:\n";
	for(i=0;i<n;i++)
	{
	    for(j=0;j<4;j++)
	        cout<<bm[i][j]<<"  ";
	    cout<<endl;
	}
	cout<<endl<<"Path Matrix:\n";
	for(i=0;i<n;i++)
	{
	    for(j=0;j<4;j++)
	        cout<<b[i][j]<<"  ";
	    cout<<endl;
	}



	x=0;
	y=x;
	//back-tracing starts
    for(i=0;i<n;i++)
    {
       if(x==0||x==2)
       {
           if(b[i][0]>b[i][1])
                x=1;
           if(b[i][0]<b[i][1])
                x=0;
           if(b[i][0]==b[i][1])//tie break
                {
                    if(b[i+1][0]>b[i+1][1])
                        a1=b[i+1][1];
                    else
                        a1=b[i+1][0];

                    if(b[i+1][2]>b[i+1][3])
                        b1=b[i+1][3];
                    else
                        b1=b[i+1][2];

                    if(a1>b1)
                        x=1;
                    else if(b1>=a1)
                        x=0;
                }
       }

        if(x==1||x==3)
       {
           if(b[i][2]>b[i][3])
                x=3;
           if(b[i][2]<b[i][3])
                x=2;
           if(b[i][2]==b[i][3])//tie break
                {
                    if(b[i+1][0]>b[i+1][1])
                        a1=b[i+1][1];
                    else
                        a1=b[i+1][0]; if(a[i]==0)
            a[i]=1;
        if(a[i]==1)
            a[i]=0;

                    if(b[i+1][2]>b[i+1][3])
                        b1=b[i+1][3];
                    else
                        b1=b[i+1][2];

                    if(a1>b1)
                        x=3;
                    else if(b1>=a1)
                        x=2;
                }
       }

       decoded[i]=x%2;

    }
    cout<<endl<<"Decoded Code:";
    for(i=0;i<n-2;i++)
        cout<<decoded[i];


int cnt=0;
for(i=0;i<k;i++)
{
    if(code[i+2]!=decoded[i])
        cnt++;

}
cout<<"\nNumber of error bits in decoded code:"<<cnt<<"\n Number of error bits in encoded code:"<<count;
cout<<"\n Positions of errors:\n";
for(i=0;i<count;i++)
    cout<<error[i]<<" ";

 return 0;
}
