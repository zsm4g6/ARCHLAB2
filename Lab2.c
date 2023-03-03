#include <stdio.h>
#include <string.h>

void parseFromFile(FILE* fp,char* inst,int* reg1){
    char temp[4];
    fscanf(fp,"%s",inst);
    fscanf(fp,"%s",temp);
    if (temp[3]=='\0'){
        *reg1=(int)temp[1]-48;
    }
    else{
        *reg1=(int)temp[1]-48;
        *reg1*=10;
        *reg1+=(int)temp[2]-48;
    }

}

void parseRemainder(FILE* fp,char* inst,int* reg2,int* reg3,int* imm){
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
        if (temp[3]=='\0'){
            *reg3=(int)temp[1]-48;
        }
        else{
            *reg3=(int)temp[1]-48;
            *reg3*=10;
            *reg3+=(int)temp[2]-48;
        }
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

}


int main(){
    FILE* fp;
    fp=fopen("test.txt","r");
    //parseInstructionFromFile(fp);
    char output[6];
    int reg1,reg2,reg3,imm;
    int *reg1x=&reg1,*reg2x=&reg2,*reg3x=&reg3,*immx=&imm;
    
    parseFromFile(fp,output,reg1x);
    parseRemainder(fp,output,reg2x,reg3x,immx);
    printf("%s %d %d %d %d\n",output,reg1,reg2,reg3,imm);
    return 0;
}

