#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int programCounter=1;
int branchNum=0;
int branchFlag=0;

struct immediate{
    int location;
    char* content;
};  

struct immediate branches[10];


void parseFromFile(FILE* fp,char* inst,char* inst2,int* reg1){
    char temp[4];
    char temp2[6]="     \0";
    int i=0;
    fscanf(fp,"%s",inst);
    
    while(inst[i]!='\0'){
        if(inst[i]==':'){
            branches[branchNum].content=malloc(sizeof(char)*10);
            for(int j=0;j<i;j++){
                branches[branchNum].content[j]=inst[j];
            }
            branches[branchNum].location=programCounter;
            branchNum++;
            programCounter++;
            branchFlag++;
            return;
        }
        if(inst[0]=='j'){
            fscanf(fp,"%s",temp);
            inst[1]=programCounter+'0';
            strcpy(inst2,temp);
            programCounter++;
            return;
        }
        i++;
    }
    fscanf(fp,"%s",temp);
    if (temp[3]=='\0'){
        *reg1=(int)temp[1]-48;
    }
    else{
        *reg1=(int)temp[1]-48;
        *reg1*=10;
        *reg1+=(int)temp[2]-48;
    }
    programCounter++;

}

void parseRemainder(FILE* fp,char* inst,char* inst2,int* reg2,int* reg3,int* imm){
    if(!branchFlag){
        char temp[7];
        int count,count2=1;
        int j=11;
        int neg=0;
        int i=0;
        *reg2=0,*reg3=0,*imm=0;
        fscanf(fp,"%s",temp);
        if(strcmp(inst,"add")==0){
            if (temp[3]=='\0'){
                *reg2=(int)temp[1]-48;
            }
            else{
                *reg2=(int)temp[1]-48;
                *reg2*=10;
                *reg2+=(int)temp[2]-48;
            }
            
            fscanf(fp,"%s",temp);
            printf("%s\n",temp);
            while(temp[i+1]!='\0'){
                if(count>1){
                    printf("test\n");
                    *reg3*=10;
                }
                *reg3+=(int)temp[i+1]-48;
                count++;
                i++;
            }
            /*
            if (temp[3]=='\0'){
                *reg3=(int)temp[1]-48;
            }
            else{
                *reg3=(int)temp[1]-48;
                *reg3*=10;
                *reg3+=(int)temp[2]-48;
            }
            */
        }
        if(strcmp(inst,"addi")==0){
            if (temp[3]=='\0'){
                *reg2=(int)temp[1]-48;
            }
            else{
                *reg2=(int)temp[1]-48;
                *reg2*=10;
                *reg2+=(int)temp[2]-48;
            }
            
            fscanf(fp,"%s",temp);
            int i=0;
            while(temp[i]!='\0'){
                if((int)temp[i]==45){
                    neg=-1;
                }
                else{
                    j=(int)temp[i]-48;
                    if((i+neg)>0){
                        *reg3*=10;
                    }
                    *reg3+=j;
                }
                i++;
            }
            if(neg==-1){
                *imm*=neg;
            }
        }
        if(strcmp(inst,"bge")==0){
            if (temp[3]=='\0'){
                *reg2=(int)temp[1]-48;
            }
            else{
                *reg2=(int)temp[1]-48;
                *reg2*=10;
                *reg2+=(int)temp[2]-48;
            }
            for(int i=0;i<branchNum;i++){
                if(strcmp(inst2,branches[i].content)==0){
                    *imm=branches[i].location-(int)inst[1]-48;
                }
            }
        }
        if(strcmp(inst,"sll")==0){
            if (temp[3]=='\0'){
                *reg2=(int)temp[1]-48;
            }
            else{
                *reg2=(int)temp[1]-48;
                *reg2*=10;
                *reg2+=(int)temp[2]-48;
            }
            
            fscanf(fp,"%s",temp);
            
            while(temp[i]!='\0'){
                if((int)temp[i]==45){
                    neg=-1;
                }   
                else{
                    j=(int)temp[i]-48;
                    if((i+neg)>0){
                        *reg3*=10;
                    }
                    *reg3+=j;
                }
                i++;
            }
            if(neg==-1){
                *reg3*=neg;
            }
        }
        if(strcmp(inst,"lw")==0){
            while(temp[i]!='('){
                
                if((int)temp[i]==45){
                    neg=-1;
                }
                else{
                    j=(int)temp[i]-48;
                
                    if((i+neg)>0){
                        *imm*=10;
                    }
                    *imm+=j;
                }
                i++;
            }
        
            if(neg==-1){
                *imm*=neg;
            }
        
            while(temp[i]!=')'){
                
                if((int)temp[i]>47&& (int)temp[i]<58){
                
                    
                    if(count2>1){
                        *reg2*=10;
                    }
                    count2++;
                    *reg2+=(int)temp[i]-48;
                }
                i++;
            }

        }
        if(inst[0]=='j'){
            for(int i=0;i<branchNum;i++){
                if(strcmp(inst2,branches[i].content)==0){
                    *imm=branches[i].location-(int)inst[1]+48;
                }
            }
        }
    }
    else{
        branchFlag=0;
    }
}


int main(){
    FILE* fp;
    fp=fopen("test.txt","r");
    char output[6],output2[6];
    int reg1=0,reg2=0,reg3=0,imm=0;
    int *reg1x=&reg1,*reg2x=&reg2,*reg3x=&reg3,*immx=&imm;
    for(int i=1;i<5;i++){
        parseFromFile(fp,output,output2,reg1x);
        //printf("%s\n",output2);
        parseRemainder(fp,output,output2,reg2x,reg3x,immx);
        printf("%s %d %d %d %d\n",output,reg1,reg2,reg3,imm);
        
    }
    for(int i=0;i<branchNum;i++){
        printf("%s %d\n",branches[i].content,branches[i].location);
        free(branches[branchNum].content);
    }
    return 0;
}

