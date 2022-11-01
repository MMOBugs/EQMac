// mkplugin.cpp : Creates a plugin
//

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <direct.h>
#include <io.h>
#include <string.h>


#define FileExists(name) (!_access(name,0))

bool CreateDirectory(const char *name)
{
	printf("Creating directory %s...",name);
	if (!_mkdir(name))
	{
		printf("Success\n");
		return true;
	}
	printf("Failed\n");
	return false;	
}

void FixName(char *buffer)
{
	char temp[256];
	char prefix[4]={0};
	strncpy(prefix,buffer,3);
	if (!stricmp(prefix,"MQ2"))
	{
		strcpy(temp,buffer);
		temp[0]='M';
		temp[1]='Q';
	}
	else
	{
		temp[0]='M';
		temp[1]='Q';
		temp[2]='2';
		strcpy(&temp[3],buffer);
	}
	prefix[0]=temp[3];
	prefix[1]=0;
	_strupr(prefix);
	temp[3]=prefix[0];
	strcpy(buffer,temp);
}

void Filter(const char *from, char *to, const char *plugin)
{
	// filter out MQ2Template
	// replace with (plugin)
	/*
	char *pos=stristr(from,"MQ2Template");
	if (!pos)
	{
		strcpy(to,from);
		return;
	}
	*/
	int i=0,o=0,plen=(int)strlen(plugin);
	for (i ; from[i] ; i++)
	{ //               12345678901
		if (!strnicmp("MQ2Template",&from[i],11)) // fuck it we dont need to be incredibly efficient for this program!
		{
			i+=(int)strlen("MQ2Template")-1;
			for (int x = 0 ; x < plen ; x++)
			{
				to[o++]=plugin[x];
			}
		}
		else
			to[o++]=from[i];
	}
	to[o++]=0;
}

bool CreateFileFromTemplate(const char *infilename, const char *outfilename, const char *plugin)
{
	printf("Creating file %s from %s...",outfilename,infilename);
	FILE *infile=fopen(infilename,"rt");
	if (!infile) goto cfftfail;
	FILE *outfile=fopen(outfilename,"wt");
	if (!outfile) goto cfftfail;
	char in[2048];
	char out[2048];
	while(fgets(in,2048,infile))
	{
		Filter(in,out,plugin);
		fputs(out,outfile);
	}


	printf("Success\n");
	return true;	
cfftfail:
	printf("Failed\n");
	return false;
}

#define FailMake(whatever) {if (!whatever) {printf("-- Failed --");return;}}

void MakePlugin(const char *xname)
{
	char name[256];
	char infile[256];
	char outfile[256];
	strcpy(name,xname);
	FixName(name);
	printf("-- Creating plugin %s -- \n",name);
	FailMake(CreateDirectory(name));

	strcpy(infile,"MQ2Template\\MQ2Template.vcproj");
	sprintf(outfile,"%s\\%s.vcproj",name,name);
	FailMake(CreateFileFromTemplate(infile,outfile,name));

	strcpy(infile,"MQ2Template\\MQ2Template.dsp");
	sprintf(outfile,"%s\\%s.dsp",name,name);
	FailMake(CreateFileFromTemplate(infile,outfile,name));

	strcpy(infile,"MQ2Template\\MQ2Template.mak");
	sprintf(outfile,"%s\\%s.mak",name,name);
	FailMake(CreateFileFromTemplate(infile,outfile,name));

	strcpy(infile,"MQ2Template\\MQ2Template.dep");
	sprintf(outfile,"%s\\%s.dep",name,name);
	FailMake(CreateFileFromTemplate(infile,outfile,name));

	strcpy(infile,"MQ2Template\\makefile");
	sprintf(outfile,"%s\\makefile",name);
	FailMake(CreateFileFromTemplate(infile,outfile,name));

	strcpy(infile,"MQ2Template\\MQ2Template.cpp");
	sprintf(outfile,"%s\\%s.cpp",name,name);
	FailMake(CreateFileFromTemplate(infile,outfile,name));

	printf("-- Plugin %s successfully created --\n",name);
}

int main(int argc, char* argv[])
{
	if (_chdir("MQ2Template"))
	{
		printf("mkplugin must be run from the parent directory of MQ2Template");
		return 0;
	}
	_chdir("..");
	if (argc==1)
	{
		printf("Usage: mkplugin [plugin name] [plugin name] [plugin name] [...]\n");
		printf("Creates each directory and sets up the required files based on MQ2Template.  Fails if the directory already exists.\n");
		return 0;
	}
	for (int i = 1 ; i < argc ; i++)
	{
		MakePlugin(argv[i]);
	}

	return 0;
}
