/* program file splitter belum jadi 100% */
#include<stdio.h>
#include<string.h>
#include<errno.h>
int lenstr(const char*str)
{
    int y=0;
	while(str[y]!=0)
	{
		y++;
	}
	return y;
}
int clrstr(char *str)
{
	int x;
	for(x=0;x<=lenstr(str);x++)str[x]='\0';
	return x;
}
char repstr(char *str)
{
	int x;
	for(x=0;x<=lenstr(str);x++)
    {
        if(str[x]=='\n')str[x]=0;
    }
	return x;
}
char cpystr(char*s1,const char*s2)
{
	int x;
	clrstr(s1);
	for(x=0;x<=lenstr(s2);x++)
	{
		s1[x]=s2[x];
	}
	return x;

}
char catstr(char *s1,const char *s2)
{
	int x=lenstr(s1),y=lenstr(s2),z=x+y,a;
	for(x,a=0;x<=z,a<=y;x++,a++)
	{
		s1[x]=s2[a];
	}
	return x,a;

}
int cmpstr(char *s1,char*s2)
{
	int x,y,z=0;
	if(lenstr(s1)>lenstr(s2))y=lenstr(s1);
	else y=lenstr(s2);
		for(x=0;x<=y;x++)
		{
			if(s1[x]>s2[x])
			{
				z=1;
				break;
			}
			else if(s1[x]<s2[x])
			{
				z=-1;
				break;
			}
		}
	return z;
}
int main(int x,char*y[])
{
    int z,bc=0,bincount=0,fcount=0
    /*filecountter*/,input;
    register int gc/*get char*/;
    long long int sz_detect;
    long double sz_detect2;
    char rdfl[2048]/*read file*/,fn[FILENAME_MAX],fn2[FILENAME_MAX],fnlog[FILENAME_MAX];
    FILE*readf,*writef,*R,*log;
    for(z=1;z<x;z++)
    {

        if(y[z][0]=='b'&&y[z][1]=='p'&&y[z][2]=='='&&y[z][3]!='\0')
        {
            sscanf(&y[z][3],"%d",(int)&sz_detect);
            if(sz_detect==0)
            {
                printf("minimum size is 1 byte\n");
                break;
            }
            readf=fopen(y[z+1],"rb");
            if(readf!=NULL)
            {
                op:
                fcount++;
                if(y[z+2]=='\0')cpystr(fn,y[z+1]);
                else cpystr(fn,y[z+2]);
                sprintf(fn2,".part%d",fcount);
                catstr(fn,fn2);
                R=fopen(fn,"r+");
                if(R!=NULL)
                {
                    if(bc>=18500000)printf("\n");
                    printf("file (%s) is exist, this program can't continue\n",fn);
                    printf("total %d file(s)\n",fcount-1);
                    break;
                }
                if(y[z+2]=='\0')
                {
                    cpystr(fnlog,y[z+1]);
                    catstr(fnlog,".cs");
                    log=fopen(fnlog,"a+");
                    fprintf(log,"%s",fn);
                }
                else
                {
                    cpystr(fnlog,y[z+2]);
                    catstr(fnlog,".cs");
                    log=fopen(fnlog,"a+");
                    fprintf(log,"%s",fn);
                }
                writef=fopen(fn,"wb");
                while(1)
                {
                    gc=getc(readf);
                    if(feof(readf))
                    {
                        fclose(writef);
                        fclose(R);
                        fclose(log);
                        break;
                    }
					putc(gc,writef);
                    bincount++;
                    if(bincount==(int)sz_detect)
                    {
                        fprintf(log,"\n");
                        fclose(writef);
                        fclose(R);
                        fclose(log);
                        bincount=0;
                        goto op;
                    }
                    bc++;
                    if(bc%18500000==0)printf(".");
                }
                if(bc>=18500000)printf("\n");
                printf("total %d file(s)\n",fcount);
                break;
            }
            else
            {
                printf("Error : %s\n",strerror(errno));
                break;
            }
            fclose(log);
        }
        else if(y[z][0]=='c'&&y[z][1]=='s')
        {
            if(!y[z+2])
            {
                printf("type read -h to help\n");
                break;

            }
            if(!y[z+1])
            {
                printf("type read -h to help\n");
                break;
            }
            R=fopen(y[z+2],"r+");
            if(R!=NULL)
            {
                printf("file (%s) is exist, you must use another filename\n",y[z+2]);
                break;
            }
            else
            {
                log=fopen(y[z+1],"r+");
                if(log!=NULL)
                {
                    while(!feof(log))
                    {
                        fgets(rdfl,2048,log);
                        repstr(rdfl);
                        cpystr(fnlog,rdfl);
                        readf=fopen(fnlog,"rb");
                        if(readf!=NULL)
                        {
                            printf("file (%s) ",fnlog);
                            writef=fopen(y[z+2],"ab+");
                            fseek(writef,SEEK_SET,SEEK_END);
                            while(1)
                            {
                                gc=fgetc(readf);
                                if(feof(readf))break;
                                bc++;
                                if(bc%18500000==0)
                                {
                                    printf(".");
                                    bc=0;
                                }
                                fputc(gc,writef);
                            }
                            printf("done\n");
                            fclose(readf);
                        }
                        else
                        {
                            printf("file (%s) %s\n",fnlog,strerror(errno));
                            fclose(readf);
                        }
                    }
                }
                else printf("Error : %s\n",strerror(errno));
            }
        }
    }
    return 0;
}

