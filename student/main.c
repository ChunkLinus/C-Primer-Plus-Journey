#include<stdio.h>
#include<stdlib.h>
struct student{
        char name[40];
        int number;
        char level;
    };
void NUM(struct student *lee,int i);
int main()
{
    FILE *source=fopen("student.txt","r");
    FILE *final=fopen("final.txt","w");

    if(source==NULL)
    {
        fprintf(stderr,"wrong");
        exit(EXIT_FAILURE);
    }
    
    struct student{
        char name[40];
        int number;
        char level;
    };
    
    int count=0;
    int capacity=2;
    struct student*lee=(struct student*)malloc(capacity*sizeof(struct student));
    if(lee==NULL)
    {
        fprintf(stderr,"WRONG");
        exit(EXIT_FAILURE);
    }


    while(fscanf(source,"%s %d %c",lee[count].name,&lee[count].number,&lee[count].level)==3)
        {
            count++;
            if(count>=capacity)
            {
                capacity*=2;
                struct student *ronster = (struct student *)realloc(lee, capacity * sizeof(struct student));
                if(ronster==NULL)
                {
                    fprintf(stderr,"WRONG");
                    free(lee);
                    exit(EXIT_FAILURE);
                }
                lee=ronster;
                printf("data in\n");
            } 
        }
    NUM(lee,count);

    // ====== 加上这段补刀代码 ======
    for(int k = 0; k < count; k++) {
        // fprintf 用法和 printf 一模一样，只是前面加个文件指针 final
        // 建议用空格隔开，方便以后再读取
        fprintf(final, "%s %d %c\n", lee[k].name, lee[k].number, lee[k].level);
    }
    // ============================

    fclose(source);
    fclose(final);
    free(lee);

    fclose(source);
    fclose(final);
    free(lee);
    lee=NULL;

    return 0;
    
}
void NUM(struct student *lee,int i)
{
    for(int j=0;j<i;j++){
        for(int l=0;l<i-j-1;l++){
            if(lee[l].number<lee[l+1].number){
            struct student code=lee[l];
            lee[l]=lee[l+1];
            lee[l+1]=code;
            }
        }
    }
    for(int s=0;s<i-1;s++){
        printf("%s,%d,%c\n",lee[s].name,lee[s].number,lee[s].level);
    }

    printf("win");
}