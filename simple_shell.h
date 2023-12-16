#ifndef _SIMPLE_SHELL_
#define _SIMPLE_SHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* To point to an arr of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - a struct that contains all relevant data on runtime
 * @argvec: The argument vector
 * @inp: The command line written by the user
 * @args: tokens of the command line
 * @stats: last status of the shell
 * @count: lines counter
 * @envir: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **argvec;
	char *inp;
	char **args;
	int stats;
	int count;
	char **envir;
	char *pid;
} dataShell;

/**
 * struct sepList - a single linked list
 * @septor: ; | &
 * @nextNode: The next node
 * Description: The single linked list to store separators
 */
typedef struct sepList
{
	char septor;
	struct sepList *nextNode;
} seppList;

/**
 * struct lineList - a single linked list
 * @cmline: The command line
 * @nextNode: The next node
 * Description: The single linked list to store command lines
 */
typedef struct lineList
{
	char *cmline;
	struct lineList *nextNode;
} lineeList;

/**
 * struct varList - a single linked list
 * @lenVar: The length of the variable
 * @vvalue: The value of the variable
 * @lenVal: The length of the value
 * @nextNode: The next node
 * Description: The single linked list to store variables
 */
typedef struct varList
{
	int lenVar;
	char *vvalue;
	int lenVal;
	struct varList *nextNode;
} r_var;

/**
 * struct builtin - The builtin struct for command args.
 * @cmname: The name of the command builtin i.e cd, exit, env
 * @df: data type pointer function.
 */
typedef struct builtin
{
	char *cmname;
	int (*df)(dataShell *data_sh);
} builtin_t;

/* auxLists.c */
seppList *addSepNodeEnd(seppList **head, char sep);
void freeSepList(seppList **head);
lineeList *addLineNodeEnd(lineeList **head, char *line);
void freeLineList(lineeList **head);

/* auxLists2.c */
r_var *addRvarNode(r_var **head, int lvar, char *var, int lval);
void freeRvarList(r_var **head);

/* auxStr functions */
char *_stringcat(char *dest, const char *src);
char *_stringcpy(char *dest, char *src);
int _stringcmp(char *s1, char *s2);
char *_stringchr(char *s, char c);
int _stringspn(char *s, char *accept);

/* auxMem.c */
void _memcopy(void *newptr, const void *ptr, unsigned int size);
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocatedp(char **ptr, unsigned int old_size, unsigned int new_size);

/* auxStr2.c */
char *_stringdup(const char *s);
int _stringlen(const char *s);
int cmpChars(char str[], const char *delim);
char *_stringtok(char str[], const char *delim);
int _is_digit(const char *s);

/* auxStr3.c */
void revString(char *s);

/* checkSyntaxError.c */
int repeatedChar(char *input, int i);
int errorSepOp(char *input, int i, char last);
int firstChar(char *input, int *i);
void printSyntaxError(dataShell *datash, char *input, int i, int bool);
int checkSyntaxError(dataShell *datash, char *input);

/* shellLoop.c */
char *withoutComment(char *in);
void shellLoop(dataShell *datash);

/* readLine.c */
char *readLine(int *i_eof);

/* splitt.c */
char *swapChar(char *inp, int bool);
void addNodes(seppList **head_s, lineeList **head_l, char *inp);
void goNext(seppList **list_s, lineeList **list_l, dataShell *datash);
int splitCommands(dataShell *datash, char *inp);
char **splitLine(char *inp);

/* repVar.c */
void checkEnv(r_var **h, char *in, dataShell *data);
int checkVars(r_var **h, char *in, char *st, dataShell *data);
char *replacedInput(r_var **head, char *input, char *newInput, int nlen);
char *repVar(char *input, dataShell *datash);

/* getLine.c */
void bringLine(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);

/* execLine */
int execLine(dataShell *datash);

/* cmdExec.c */
int isCdir(char *path, int *i);
char *_which(char *cmd, char **envir);
int isExecutable(dataShell *datash);
int checkErrorCmd(char *dir, dataShell *datash);
int cmdExec(dataShell *datash);

/* envir1.c */
char *_getenvir(const char *name, char **_environ);
int _envir(dataShell *datash);

/* envir2.c */
char *copyInfo(char *name, char *value);
void setEnvir(char *name, char *value, dataShell *datash);
int _setEnvir(dataShell *datash);
int _unsetEnvir(dataShell *datash);

/* cdir.c */
void cdirDot(dataShell *datash);
void cdirTo(dataShell *datash);
void cdirPrev(dataShell *datash);
void cdirToHome(dataShell *datash);

/* cdShell.c */
int cdShell(dataShell *datash);

/* getBuiltin */
int (*getBuiltin(char *cmd))(dataShell *datash);

/* _exitShell.c */
int exitShell(dataShell *datash);

/* auxStdlib.c */
int getLen(int n);
char *auxItoa(int n);
int _atoi(char *s);

/* auxError1.c */
char *stringcatCdir(dataShell *, char *, char *, char *);
char *errorGetCdir(dataShell *datash);
char *errorNotFound(dataShell *datash);
char *errorExitShell(dataShell *datash);

/* auxError2.c */
char *errorGetAlias(char **args);
char *errorEnvir(dataShell *datash);
char *errorSyntax(char **args);
char *errorPermission(char **args);
char *errorPath126(dataShell *datash);


/* getError.c */
int getError(dataShell *datash, int eval);

/* getSigint.c */
void getSigint(int sig);

/* auxHelp.c */
void auxHelpEnvir(void);
void auxHelpSetenvir(void);
void auxHelpUnsetenvir(void);
void auxHelpGeneral(void);
void auxHelpExit(void);

/* auxHelp2.c */
void auxHelp(void);
void auxHelpAlias(void);
void auxHelpCdir(void);

/* getHelp.c */
int getHelp(dataShell *datash);

#endif
