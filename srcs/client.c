#include "minitalk.h"

void	send_byte(int pid, int c)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		if ((c >> j) & 1)
			kill(pid, SIGUSR2);
		else if (!((c >> j) & 1))
			kill(pid, SIGUSR1);
		j--;
		usleep(100000);
	}
}

void	send_msg(int pid, char *msg, int len)
{
	int		i;
	int		k;

	k = 31;
	i = 0;
	while (k >= 0)
	{
		if ((len >> k) & 1)
			kill(pid, SIGUSR2);
		else if (!((len >> k) & 1))
			kill(pid, SIGUSR1);
		k--;
		usleep(10000);
	}
	while (msg[i])
		send_byte(pid, msg[i++]);
	send_byte(pid, 0);
}

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_putstr("done!");
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	int	len;

	signal(SIGUSR1, &sig_handler);
	signal(SIGUSR2, &sig_handler);
	if (argc == 3)
	{
		len = ft_strlen(argv[2]);
		send_msg(ft_atoi(argv[1]), argv[2], len);
		pause();
	}
	else
	{
		ft_putstr("usage: ./client _pid_  _msg to send_\n");
	}
}
