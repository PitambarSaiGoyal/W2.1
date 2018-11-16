#include<stdio.h>
#include<string.h>
#include<string>
#include<fstream>

using namespace std;


int main()
{

	printf("Enter project name:");
	
	char proj_name[1000];
	scanf("%s",proj_name);
	
	printf("Enter Directory:");
	
	char directory[1000];
	scanf("%s",directory);
	
	printf("Start doc:");
	
	char stdoc[1000];
	scanf("%s",stdoc);
	
	printf("End doc:");
	
	char endoc[1000];
	scanf("%s",endoc);
	
	printf("Start edit:");
	
	char sted[1000];
	scanf("%s",sted);
	
	printf("End edit:");
	
	char ended[1000];
	scanf("%s",ended);
	
	char path[1000];//String to hold the path 
	
	strcpy(path,directory);
    strcat(path,"\\");
	strcat(path,proj_name);
	strcat(path,".weave");
	
	fstream src,src2;
	src.open(path);
	src2.open(path);
	
	//Documentation path:
	strcpy(path,"");
	strcpy(path,directory);
	strcat(path,"\\");
	strcat(path,proj_name);
	strcat(path,".html");
	
	fstream doc;
	doc.open(path,ios_base::app);
	
	doc<<"<html>\n<head>\n<title>"<<proj_name<<"\n</title>\n</head>\n";
	doc<<"<body>\n<h1 style=\"font-family:CMU Serif;text-align:center;\">\n";
	doc<<proj_name<<"\n</h1>\n";
	
	char line[1000],Line[1000]; string l,L;//use strcpy to convert between them
	
	fstream prog[1000];
	int pno=-1;
	//Macro count:
	int macno=0;
	while(!src.eof())
	{
	 	if(!strcmp(line,stdoc))
	 	{
	 	  doc<<"<h3 style=\"font-family:CMU Serif;text-align:justify;\"><br>\n";
	 	  getline(src,l);strcpy(line,l.c_str());
		  while(strcmp(line,endoc))
		  {
		  	doc<<line<<"<br>";
		  	getline(src,l);strcpy(line,l.c_str());
		  } 	
		}
		
		if(!strcmp(line,endoc))
		{
			doc<<"\n</h3>\n";
		}
		
		if(!strcmp(line,sted))
	 	{
	 	  	
	 	  pno++;
		  strcpy(path,"");
	 	  strcpy(path,directory);
	 	  strcat(path,"\\");
	 	  getline(src,l);strcpy(line,l.c_str());
	 	  strcat(path,line);
	 	  prog[pno].open(path,ios_base::app);
		  doc<<"<h2 style=\"font-family:Courier New;text-align:left;padding-left:45px;padding-right:45px\">\n<b>";
	 	  getline(src,l);strcpy(line,l.c_str());
		  while(strcmp(line,ended))
		  {
			if(line[0]=='%')
			{
				doc<<line<<"<br>\n</b>\n"; 
		        strcpy( line, l.substr( 1, string::npos ).c_str() );
		        src2.seekg( 0, src2.beg );
		        strcpy(Line,"");
		        getline(src2,L);strcpy(Line,L.c_str());
		        while( strcmp(Line,"endw") )
		        {
		        	
		        	if(!strcmp(line,Line))
		        	{
		        		getline(src2,L);strcpy(Line,L.c_str());
		        		while(strcmp(Line,ended))
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
			 doc<<line<<"<br>\n</b>\n"; 
			 prog[pno]<<line<<endl;
			}
            getline(src,l);strcpy(line,l.c_str());
		  } 	
		}
		
		if(!strcmp(line,ended))
		{
			doc<<"\n</h2>\n";
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

	scanf("%c",&line[0]);
	
	return 0;
	
}


