#include <iostream>
using namespace std;
int *sort_list(int n[],int s)
{
    int c;
    for (int i=0 ; i<=s; i++)
    {
        for (int j=0; j<s; j++)
        {
            if (n[i]<n[j])
            {
                c=n[i];
                n[i]=n[j];
                n[j]=c;
            }
        }
    }
    return n;
}
int scan(int arr[],int initially,int s)
{
    int total=0,init=0;

    for(int i=0; i<=s; i++)
    {
        if(arr[i]==initially)
            init=i;
    }
    for(int i=init; i>=0; i--)
    {
        if(i>0)
            total+=(arr[i]-arr[i-1]);
        else
            total+=arr[i];
    }
    for(int i=init+1; i<=s; i++)
    {
        if(i==init+1)
            total+=arr[i];
        else
            total+=(arr[i]-arr[i-1]);
    }
    return total;
}
int main()
{
    int *arr,x,initially;
    cout<<"Enter series number : ";
    cin>>x;
    arr=new int[x+1];
    for(int i=0; i<x; i++)
    {
        cout<<"Enter the cylinder number "<<i+1<<" : ";
        cin>>arr[i];
    }
    cout<<"Enter initially : ";
    cin>>initially;
    arr[x]=initially;
    arr=sort_list(arr,x);
   cout<<"Total head movement : "<<scan(arr,initially,x);
    return 0;
}
