#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int p[2];

	pipe(p);
	write(p[1], "this is a message\n", 18);
	close(p[1]);
	int pid = fork();
	if (pid == 0)
	{
		char s[250];
		int r = read(p[0], s, 249);
		s[r] = 0;
		printf("msg: %s", s);
		return (0);
	}
	return (0);
}
