#ifdef _WIN32
	#include <windows.h>
	#define MKDIR(path) mkdir(path)
#else
	#include <sys/stat.h>
	#include <sys/types.h>
	#define MKDIR(path) mkdir(path, 0755)
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "config.h"

char *flag = "-s";

void createDir(const char *dirname) {
	if(MKDIR(dirname) != 0) {
		printf("ERROR %s - directory creation failed\n", dirname);
		exit(EXIT_FAILURE);
	} else {
		printf("%s - directory created\n", dirname);
	}
}

void createFile(const char *filename, const char *content) {
	FILE *file = fopen(filename, "w");
	if(!file) {
		printf("ERROR %s - file creation failed\n", filename);
		exit(EXIT_FAILURE);
	}
	if(fputs(content, file) == EOF) {
		printf("ERROR %s - writing failed\n", filename);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	printf("%s - file created\n", filename);
}

void createCmain(const char *name, const char *src_dir) {
	int size = snprintf(NULL, 0, "%s/%s.c", src_dir, name);
	if(size < 0) {
		printf("ERROR formating C main failed\n");
		exit(EXIT_FAILURE);
	}
	char *path = (char*)malloc(size+1);
	if(!path) {
		printf("ERROR memory allocation failed\n");
		exit(EXIT_FAILURE);
	} 
	snprintf(path, size+1, "%s/%s.c", src_dir, name);
	createFile(path, main_c_content);
	free(path);
}
void createMakefile(char *flag,char *cc, char *flags, const char *name, char *include, char *obj, char *lib, char *src) {
	if(!strcmp(flag,"-l")) {
		int size = snprintf(NULL,0, makefile_content_large,
			cc, flags, include, lib,
			src, obj,name,name);
		if(size < 0) {
		printf("ERROR formating Makefile failed\n");
		exit(EXIT_FAILURE);
		}
		char *content = (char*)malloc(size+1);
		if(!content) {
			printf("ERROR memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		snprintf(content, size+1,makefile_content_large,
			cc, flags, include, lib,
			src, obj,name, name);
		createFile("makefile", content);
		free(content);
	}
	else if(!strcmp(flag,"-s")) {
		int size = snprintf(NULL,0,makefile_content_simple,cc,flags,name,name);
		if(size < 0) {
			printf("ERROR formating C main failed\n");
			exit(EXIT_FAILURE);
		}
		char *content = (char*)malloc(size+1);
		if(!content) {
			printf("ERROR memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		snprintf(content, size+1,makefile_content_simple,
		cc,flags,name,name);
		createFile("makefile", content);
		free(content);
	}
	else {
	printf("ERROR unknown flag for makefile");
	exit(EXIT_FAILURE);
	}
}

void cd(const char *dir) {
	if(chdir(dir) != 0) {
	printf("ERROR can't cd into %s", dir);
	exit(EXIT_FAILURE);
	}
}

void createLargeProject(const char *name) {
	createDir(name);
	cd(name);
	createDir("build");
	createDir("build/include");
	createDir("build/lib");
	createDir("build/obj");
	createDir("build/src");
	createCmain(name,"build/src");
	createMakefile(flag,"gcc","-O3",name,"build/include","build/obj","build/lib","build/src");
	printf("Project '%s' structure created successfully!\n", name);
}

void createSimpleProject(const char *name) {
	createDir(name);
	createCmain(name,name);
	cd(name);
	createMakefile(flag,"gcc","-O3",name,"build/include","build/obj","build/lib","build/src");
}
int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf(help);
		return -1;
	}
	const char *name = argv[1];
	if(argc == 3) {
		flag = argv[2];
		if(!strcmp(flag,"-s")) createSimpleProject(name);
		else if(!strcmp(flag,"-l")) createLargeProject(name);
		else if(!strcmp(flag,"-h")) printf(help);
		else if (!strcmp(flag,"-c")) createCustomProject(name);
		else printf("Incorrect flag, use \"cpb -h\" for help\n");
	}
	else if(argc < 3) {
		if(!strcmp(name,"-h")) printf(help);
		else createSimpleProject(name);
	}
	else printf(help);
	return 0;
}
