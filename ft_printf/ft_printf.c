/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:04:27 by dlanotte          #+#    #+#             */
/*   Updated: 2021/02/09 19:24:56 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_s_switcher(char *str, int i, va_list variables, int *ast)
{
	int				pr_c;

	pr_c = 0;
	if ((str[ft_c_par(str, i)] == 'd') || str[ft_c_par(str,i)] == 'i')
		pr_c = pr_c + ft_ip(va_arg(variables, int), (char *)str, i, ast);
	else if (str[ft_c_par(str,i)] == 's')
		pr_c = pr_c + ft_sp(va_arg(variables, char *), (char *)str, i, ast);
	else if (str[ft_c_par(str,i)] == 'c')
		pr_c = pr_c + ft_cp(va_arg(variables, int), (char *)str, i, ast);
	else if (str[ft_c_par(str,i)] == 'u')
		pr_c = pr_c + ft_up(va_arg(variables, unsigned int)
		, (char *)str, i, ast);
	return (pr_c);
}

static int	ft_switcher(char *str, int i, va_list variables, int *asterisk)
{
	int				pr_c;

	pr_c = 0;
	if (str[i] == '%' && str[i + 1] != '%')
		pr_c += ft_s_switcher(str, i, variables, asterisk);
	else
	{
		if (ft_cc_pr((char *)str, i) && str[i] == '%' && str[i + 1] == '%')
		{
			pr_c = pr_c + ft_putchar(str[i]);
			i++;
		}
		else if (ft_cc_pr((char *)str, i))
			pr_c = pr_c + ft_putchar(str[i]);
	}
	return (pr_c);
}

int			ft_printf(const char *str, ...)
{
	va_list		variables;
	va_list		*variables_p;
	int			i;
	int			pr_c;
	int			*asterisk;

	i = 0;
	pr_c = 0;
	variables_p = &variables;
	va_start(variables, str);
	asterisk = ft_check_asterisk(variables_p, (char *)str);
	while (str[i])
	{
		pr_c += ft_switcher((char *)str, i, variables, asterisk);
		i += ft_skip_content((char *)str, i);
	}
	va_end(variables);
	return (pr_c);
}

bool		ft_cc_pr(char *str, int i)
{
	if (str[i] == '%' && str[i + 1] == '%')
		return (true);
	else if (str[i] == ' ')
		return (true);
	else if (!ft_is_parameter(str[i]) && !ft_is_flag(str[i]))
		return (true);
	else
	{
		while (str[i--])
		{
			if (str[i] == '%')
				return (false);
			else if (ft_is_parameter(str[i]))
				return (true);
		}
	}
	return (true);
}

int			ft_skip_content(char *str, int i)
{
	int			skip;

	skip = 1;
	if (str[i] != '%' || (str[i] == '%' && str[i - 1] == '%'))
		return (1);
	while (str[i + skip] && !ft_is_parameter(str[i + skip]))
		skip++;
	return (skip);
}

int	main(void)
{
	bool			DEBUG = false;
	bool			DEBUG_F = false;
	char			Author[] = "zxcvbinz";
	char			Lettera = 'Z';
	int				Numero = -50006;
	char			NumeroChar[] = "100012";
	unsigned int	int_u = 4294967295;

	ft_printf("--%d--\n", ft_printf("%*.*s\n", 100, 3, "Ciao"));
	printf("--%d--\n", printf("%*.*s\n %*s", 100, 3,"Ciao", 2, "2"));

	//ft_printf(" ---- %10.4d\n", ft_printf("Ciao Mondo %010.0c", Lettera));
	//printf(" ---- %10.4d\n", printf("Ciao Mondo %010.0c", Lettera));

	if (DEBUG)
	{
		ft_printf("NUM: %d\n", ft_printf("iiii\n||||||MY VERSION||||||\nCiao Mondo, io mi chiamo %.3s\n(%%)", Author));
		ft_printf("MY PRINTF: %d\n", ft_printf("ID: %c(c) Test by %s(s) %i(i) + %d(d) = %s(s) unsigned int: %u(u) Controllo Flag=0*.\n", Lettera, Author, Numero, Numero, NumeroChar, int_u));
	 
		printf("ORI: %d\n", printf("iiii\n||||||OR VERSION||||||\nCiao Mondo, io mi chiamo %.3s\n(%%)", Author));
		printf("OR PRINTF: %d\n\n", printf("ID: %c(c) Test by %s(s) %i(i) + %d(d) = %s(s) unsigned int: %u(u) Controllo Flag=0*.\n", Lettera, Author, Numero, Numero, NumeroChar, int_u));
	}
	else if (DEBUG_F)
	{
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %01.s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %1.2s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %10.3s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %010.8s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %01.s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %.1s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %.10s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %.20s", Author));
		ft_printf(" - NUM: %5.4d\n", ft_printf("TEST FLAG : %100s", Author));
		printf("\n");
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %01.s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %1.2s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %10.3s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %010.8s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %01.s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %.1s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %.10s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %.20s", Author));
		printf(" - ORI: %5.4d\n", printf("TEST FLAG : %100s", Author));
	}

	return (0);
}