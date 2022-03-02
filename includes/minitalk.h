#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_talk
{
	int		c;
	int		index;
	int		len;
	int		error;
	int		sig_num;
	char	*str;
}				t_talk;

t_talk	g_talk;

#endif