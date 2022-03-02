#include "minitalk.h"

void	finish_client(int client)
{
	int	i;

	ft_putstr(g_talk.str);
	free(g_talk.str);
	g_talk.str = NULL;
	ft_putchar('\n');
	g_talk.c = 0;
	g_talk.len = 0;
	g_talk.index = 0;
	g_talk.sig_num = 0;
	i = kill(client, SIGUSR1);
	if (i == -1)
		error_exit("The client is gone!");
}

void	get_len(void)
{
	g_talk.len = (g_talk.len << 8) ^ g_talk.c;
	if (g_talk.sig_num == 32)
	{
		g_talk.str = ft_calloc(g_talk.len + 1, sizeof(char));
		g_talk.len = 0;
	}
}

void	sig_handler(int sig, siginfo_t *info, void *contex)
{
	(void)contex;
	g_talk.sig_num++;
	g_talk.c = g_talk.c << 1;
	if (sig == SIGUSR2)
		g_talk.c = g_talk.c ^ 1;
	if (g_talk.sig_num % 8 == 0)
	{
		if (g_talk.sig_num <= 32)
			get_len();
		else
		{
			if (g_talk.str)
				g_talk.str[g_talk.index++] = g_talk.c;
			else
				error_exit("Memori error");
			if (!g_talk.c)
				finish_client(info->si_pid);
		}
		g_talk.c = 0;
	}
	g_talk.error = kill(info->si_pid, SIGUSR2);
	if (g_talk.error == -1)
		finish_client(info->si_pid);
	(void)contex;
}

int	main(void)
{
	struct sigaction	sig;

	g_talk.c = 0;
	g_talk.len = 0;
	g_talk.index = 0;
	g_talk.sig_num = 0;
	sig.sa_sigaction = sig_handler;
	sig.sa_flags = SA_SIGINFO;
	ft_putstr("PID:");
	ft_putnbr(getpid());
	ft_putchar('\n');
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
}
