#include "simple_shell.h"
/**
 * cdirDot - changes to the parent directory
 * @data_sh: data relevant (envir)
 * Return: no return
 */
void cdirDot(dataShell *data_sh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _stringdup(pwd);
	setEnvir("OLDPWD", cp_pwd, data_sh);
	dir = data_sh->args[1];
	if (_stringcmp(".", dir) == 0)
	{
		setEnvir("PWD", cp_pwd, data_sh);

		free(cp_pwd);
		return;
	}
	if (_stringcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	revString(cp_strtok_pwd);
	cp_strtok_pwd = _stringtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _stringtok(NULL, "\0");
		if (cp_strtok_pwd != NULL)
			revString(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		setEnvir("PWD", cp_strtok_pwd, data_sh);
	}
	else
	{
		chdir("/");
		setEnvir("PWD", "/", data_sh);
	}
	data_sh->stats = 0;
	free(cp_pwd);
}
/**
 * cdirTo - changes to a directory given
 * by user
 *
 * @data_sh: data relevant
 * Return: none
 */
void cdirTo(dataShell *data_sh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data_sh->args[1];
	if (chdir(dir) == -1)
	{
		getError(data_sh, 2);
		return;
	}

	cp_pwd = _stringdup(pwd);
	setEnvir("OLDPWD", cp_pwd, data_sh);

	cp_dir = _stringdup(dir);
	setEnvir("PWD", cp_dir, data_sh);

	free(cp_pwd);
	free(cp_dir);

	data_sh->stats = 0;

	chdir(dir);
}
/**
 * cdirPrev - changes 2 d rev directory
 * @data_sh: data relevant (envir)
 * Return: none
 */
void cdirPrev(dataShell *data_sh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _stringdup(pwd);

	p_oldpwd = _getenvir("OLDPWD", data_sh->envir);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _stringdup(p_oldpwd);

	setEnvir("OLDPWD", cp_pwd, data_sh);

	if (chdir(cp_oldpwd) == -1)
		setEnvir("PWD", cp_pwd, data_sh);

	else
		setEnvir("PWD", cp_oldpwd, data_sh);

	p_pwd = _getenvir("PWD", data_sh->envir);

	write(STDOUT_FILENO, p_pwd, _stringlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data_sh->stats = 0;

	chdir(p_pwd);
}
/**
 * cdirToHome - changes to home dir
 * @data_sh: data relevant (envir)
 * Return: none
 */
void cdirToHome(dataShell *data_sh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _stringdup(pwd);

	home = _getenvir("HOME", data_sh->envir);

	if (home == NULL)
	{
		setEnvir("OLDPWD", p_pwd, data_sh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		getError(data_sh, 2);
		free(p_pwd);
		return;
	}

	setEnvir("OLDPWD", p_pwd, data_sh);
	setEnvir("PWD", home, data_sh);
	free(p_pwd);
	data_sh->stats = 0;
}
