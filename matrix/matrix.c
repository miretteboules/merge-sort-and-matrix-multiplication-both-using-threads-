#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
int step_i = 0;
size_t mat1[50][50],mat2[50][50],matrix[50][50],matrix2[50][50];
float time1,time2;
int  row1,row2,column1,column2,i=0,j=0;
//function that do multiplication (a thread for every row)
void *multbyrow(void *th)
{
      int core = step_i++;

    // Each thread computes 1 row of matrix multiplication
    for (int i = core * row1 /row1; i < (core + 1) * row1 / row1; i++)
        for (int j = 0; j < column2; j++)
            for (int k = 0; k <column1; k++)
                matrix[i][j] += mat1[i][k] * mat2[k][j];
    pthread_exit(NULL);
}
//funtction that do multiplication (element by element)for  each element a thread)
void *multbyelement(void *th)
{
    int  k,sum=0;
    for(k=0;k<column1; k++)
        sum+=mat1[i][k]*mat2[k][j];
    matrix2[i][j]=sum;

    if(i<row1)
    {
        if(j<column2)
        {

            j++;
        }
        else
        {
            i++;
            j=0;
        }
    }
    pthread_exit(NULL);
}
int main()
{ //reading matrices from input file
    FILE *f,*fout;
    f=fopen("input.txt","r");
    int  i,j;
    clock_t start,end;
    fscanf(f,"%d %d \n",&row1,&column1);

    for(i=0; i<row1; i++)
        for(j=0; j<column1; j++)
            fscanf(f,"%d ",&mat1[i][j]);
    fscanf(f,"%d %d \n",&row2,&column2);
    for(i=0; i<row2; i++)
        for(j=0; j<column2; j++)
            fscanf(f,"%d ",&mat2[i][j]);
//creating threads for each row and waiting for them
    int  k,v;
    start=clock();
    pthread_t multhrea[row1];
    for(v=0; v<row1; v++)
    {
        pthread_create(&multhrea[v],NULL,multbyrow,NULL);
    }
    for(k=0; k<row1; k++)
        pthread_join(multhrea[k],NULL);
    end=clock();
    time1=((float)(end-start))/CLOCKS_PER_SEC;

    //creating threads for each element and waiting for them
    int  y,x,z=row1*column2+2,c;
    start=clock();
    pthread_t multhread2[z];
    for(c=0;c<z; c++)
        pthread_create(&multhread2[c],NULL,multbyelement,NULL);

    int  n;
    for(n=0; n<z; n++)
        pthread_join(multhread2[n],NULL);
    end=clock();
    time2=((float)(end-start))/CLOCKS_PER_SEC;



    //printing the resultant matix and elapsed time in an output file
    fout=fopen("output.txt","w+");
    fprintf(fout,"result matrix row by row: \n");
    for(i=0; i<row1; i++)
    {
        for(j=0; j<column2; j++)
            fprintf(fout,"%d ",matrix[i][j]);
        fprintf(fout,"\n");
    }
    fprintf(fout,"elappsed time= %f",time1);
    fprintf(fout,"\n");
      fprintf(fout,"result matrix element by element: \n");
    for(i=0; i<row1; i++)
    {
        for(j=0; j<column2; j++)
            fprintf(fout,"%d ",matrix2[i][j]);
        fprintf(fout,"\n");
    }
     fprintf(fout,"elappsed time= %f\n",time2);
    fprintf(fout,"the difference in time is = %f ",(time2-time1));

    fclose(f);
    fclose(fout);
    return(0);
}

