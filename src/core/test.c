#include "core_internal.h"

void	test_env(void);
void	test_builtins(void);
void	test_cd(void);
void	test_echo(int c, char **v);
void	test_export(int c, char **v);
void	test_unset(int c, char **v);

int	main(int c, char **v, char **e)
{
	(void)c;
	(void)v;
	printf("bootstraping... [%d]\n", setup(e));
	test_export(c, v);
	return (0);
}

void	test_env(void)
{
	set_env_var("USER", "youssef");
	env(2, NULL);
}

void	test_builtins(void)
{
	t_list *cur = g_shell.builtins;
	printf("builtins:\n");
	while (cur)
	{
		printf("\t");
		t_keyvalue *kv = cur->content;
		t_builtin *builtin = kv->value;
		(*builtin)(0, NULL);
		cur = cur->next;
	}
}
void	test_cd(void)
{
	printf("wd: %s\n", g_shell.wd);
	cd(1, NULL);
	char *p[2];
	p[0] = "ls";
	p[1] = NULL;
	if (fork() == 0)
		execve("/bin/ls", p, NULL);
	else
	printf("wd: %s\n", g_shell.wd);
}
void	test_echo(int c, char **v)
{
	echo(c, v);
}
void	test_export(int c, char **v)
{
	shell_export(c, v);
	if (c > 1)
		shell_export(1, NULL);
}
void	test_unset(int c, char **v)
{
	unset(c, v);
	shell_export(1, NULL);
}
