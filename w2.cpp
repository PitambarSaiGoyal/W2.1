#include<stdio.h>
#include<string.h>
#include<string>
#include<fstream>

using namespace std;

#define directory argv[1]
#define proj_name argv[2]
#define title_font argv[3]
#define doc_font argv[4]
#define edit_font argv[5]


int main(int argc,char *argv[])
{

	char path[1000];//String to hold the path 
	fstream src,src2;
	fstream doc;
	char line[1000],Line[1000]; string l,L;//use strcpy to convert between them
	
	strcpy(path,directory);
    strcat(path,"\\");
	strcat(path,proj_name);
	strcat(path,".weave");
	
	src.open(path);
	src2.open(path);
	
	//Documentation path:
	strcpy(path,"");
	strcpy(path,directory);
	strcat(path,"\\");
	strcat(path,proj_name);
	strcat(path,".html");
	
	doc.open(path,ios_base::out);
	
	doc<<"<html>\n<head>\n<title>"<<proj_name<<"\n</title>\n</head>\n";
	doc<<"<body>\n<h1 style=\"font-family:"<<title_font<<";text-align:center;\">\n";
	doc<<proj_name<<"\n</h1>\n";
	
	
	fstream prog[1000];
	int pno=-1;
	//Macro count:
	int macno=0;
	
	char macname[1000];
	
	while(!src.eof())
	{
	 	if(!strcmp(line,"@"))
	 	{
	 	  doc<<"<p style=\"font-family:"<<doc_font<<";font-size:100%;text-align:justify;\"><br>\n";
	 	  getline(src,l);strcpy(line,l.c_str());
		  while(strcmp(line,"/@"))
		  {
		  	doc<<line<<"<br>";
		  	getline(src,l);strcpy(line,l.c_str());
		  } 	
		}
		
		if(!strcmp(line,"/@"))
		{
			doc<<"\n</p>\n";
		}
		
		if(!strcmp(line,"$"))
	 	{
	 	  	
	 	  pno++;
		  strcpy(path,"");
	 	  strcpy(path,directory);
	 	  strcat(path,"\\");
	 	  getline(src,l);strcpy(line,l.c_str());
	 	  strcat(path,line);
	 	  prog[pno].open(path,ios_base::app);
		  doc<<"<p style=\"font-family:"<<edit_font<<";font-size:100%;text-align:left;padding-left:45px;padding-right:45px\">\n<b>";
	 	  getline(src,l);strcpy(line,l.c_str());
		  while(strcmp(line,"/$"))
		  {
			if(line[0]=='[' && line[1]=='[')
			{
				doc<<line<<"<br>\n"; 
		        strcat( line,":-");
		        src2.seekg( 0, src2.beg );
		        strcpy(Line,"");
		        getline(src2,L);strcpy(Line,L.c_str());
		        while( strcmp(Line,"endw") )
		        {
		        	
		        	if(!strcmp(line,Line))
		        	{
		        		getline(src2,L);strcpy(Line,L.c_str());
		        		while(strcmp(Line,"/$"))
		        		{
		        			prog[pno]<<Line<<endl;
		        			getline(src2,L);strcpy(Line,L.c_str());
						}
					}
		        	getline(src2,L);strcpy(Line,L.c_str());
				}
			}
			
			else
			{
			 doc<<line<<"<br>\n"; 
			 prog[pno]<<line<<endl;
			}
            getline(src,l);strcpy(line,l.c_str());
		  } 	
		}
		
		if(!strcmp(line,"/$"))
		{
			doc<<"\n</b></p>\n";
		}
		
		if(!strcmp(line,"endw"))
		{
			doc<<"\n</body>\n</html>\n";
		}
		
	    strcpy(line,"");	
		getline(src,l);strcpy(line,l.c_str());
	 	
	}	
	
	src.close();
	doc.close();
	
	return 0;
	
}


