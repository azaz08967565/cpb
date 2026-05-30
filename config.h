void createCustomProject(const char *name) {
	printf("Place your custom script in config.h and remove this message\n");
}
const char *main_c_content_custom = "";

const char *makefile_content_custom = "";

const char *help =
	"Usage: cpb <project_name> <flag>\n"
	"List of flags:\n"
	"-s - simple project\n"
	"-l - large project\n"
	"-c - custom project\n"
	"-h - prints this message\n";
const char *main_c_content = 
	"#include <stdio.h>\n\n"
	"int main(int argc, char *argv[]) {\n"
	"\tprintf(\"Hello World!\\n\");\n"
	"\treturn 0;\n"
	"}\n";
char *makefile_content_large = 
	"CC = %s\n"
	"CFLAGS = %s\n"
	"INCLUDES = -I%s\n"
	"LIBS = -L%s\n"
	"SRC_DIR = %s\n"
	"OBJ_DIR = %s\n"
	"EXE = %s\n"
	"MKDIR = mkdir -p\n"
	"RM = rm -f\n"
	"RMDIR = rm -rf\n"
	"SRCS = \\\n"
	"\t$(SRC_DIR)/%s.c\n"
	"OBJS = $(patsubst $(SRC_DIR)/%%.c, $(OBJ_DIR)/%%.o, $(SRCS))\n"
	"all: $(EXE)\n"
	"$(EXE): $(OBJS)\n"
	"\t$(CC) -o $@ $^ $(LIBS)\n"
	"$(OBJ_DIR)/%%.o: $(SRC_DIR)/%%.c | $(OBJ_DIR)\n"
	"\t$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@\n"
	"$(OBJ_DIR):\n"
	"\t$(MKDIR) $(OBJ_DIR)\n"
	"clean:\n"
	"\t$(RM) $(EXE)\n"
	"\t$(RMDIR) $(OBJ_DIR)\n"
	".PHONY: all clean\n";
char *makefile_content_simple =
	"all:\n"
	"\t%s %s %s.c -o %s\n";
