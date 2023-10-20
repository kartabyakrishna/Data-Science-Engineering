#include <iostream>
using namespace std;
struct Sparse{
    int row;
    int col;
    int value;
};
int main(){
    int count=0;
    int m,n,i,j;
    
    cout<<"Enter the order of the matrix\n";
    cin>>m>>n;
    
    cout<<"Enter matrix elements: \n";
    int a[m][n];
    
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
            if(a[i][j]!=0)
            count++;
        }
    }
    int k=1;  
    struct Sparse S[count+1];
    S[0].row=m;
    S[0].col=n;
    S[0].value=count;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(a[i][j]>0){
                S[k].row=i;
                S[k].col=j;
                S[k].value=a[i][j];
                k++;
            }
            
        }
    }
    
    cout<<"\n Dimention of Sparse Matrix: "
           <<m<<"X"<<n;
           
    cout<<"\n Sparse Matrix : \n";
    
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            cout<<a[i][j]<<"\t";
        }
        cout<<"\n";
    } 
    cout<<"\nRow\tColumn\tValue\n";
        
      for(i=0;i<count+1;i++){
          cout<<S[i].row<<"\t"<<S[i].col<<"\t"<<S[i].value;
          cout<<"\n";
      }
      int b[S[0].row][S[0].col]={};
      
       for(i=1;i<S[0].value+1;i++){
         b[S[i].row][S[i].col]=(S[i].value);
         }

          cout<<"\n Dimention of Sparse Matrix: "
           <<m<<"X"<<n;
    
    cout<<"\n Reconstructed  Sparse Matrix : \n";
    
    for(i=0;i<S[0].row;i++){
        for(j=0;j<S[0].col;j++){
            cout<<b[i][j]<<"\t";
        }
        cout<<"\n";
    }
    
      
      return 0;}   
