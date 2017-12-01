/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smalltalk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 17:01:12 by iwagner           #+#    #+#             */
/*   Updated: 2017/10/27 15:45:51 by scollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	greetings(char *hyp, FILE *fp)
{
	if (strstr(hyp, "WHO") && strstr(hyp, "YOU"))
	{
		system("say \"I am SABRE\"");
		fwrite("\tWHO ARE YOU\n", 1, strlen("\tWHO ARE YOU\n"), fp);
	}
	else if (strstr(hyp, "I") && strstr(hyp, "AM") && strstr(hyp, "HELLO"))
	{
		system("say \"Nice to meet you\"");
		fwrite("\tGREETINGS\n", 1, strlen("\tGREETINGS\n"), fp);
	}
	else if (strstr(hyp, "HOW") && strstr(hyp, "FEELING"))
	{
		system("say \"I am feeling electric\"");
		fwrite("\tHOW ARE YOU FEELING\n", 1,
			strlen("\tHOW ARE YOU FEELING\n"), fp);
	}
	else if (strstr(hyp, "HELLO"))
	{
		system("say \"Hello\"");
		fwrite("\tHELLO\n", 1, strlen("\tHELLO\n"), fp);
	}
}

void	smalltalk(char *hyp, FILE *fp)
{
	if (strstr(hyp, "LICKS") && strstr(hyp, "TOOTSIE"))
	{
		system("say \"42\"");
		fwrite("\tHOW MANY LICKS DOES IT TAKE TO GET TO	THE CENTER OF A \
			TOOTSIE POP\n", 1, strlen("\tHOW MANY LICKS DOES IT TAKE TO GET TO\
				THE CENTER OF A TOOTSIE POP\n"), fp);
	}
	else if (strstr(hyp, "YOU") && strstr(hyp, "LOVE"))
	{
		system("say \"I know.\"");
		fwrite("\tI LOVE YOU\n", 1, strlen("\tI LOVE YOU\n"), fp);
	}
	else if (strstr(hyp, "WHO") && strstr(hyp, "GAETAN"))
	{
		system("say -v \"Nicolas\" I can be Gaetan.");
		fwrite("\tWHO IS GAETAN\n", 1, strlen("\tWHO IS GAETAN\n"), fp);
	}
	else if (strstr(hyp, "GEE") && strstr(hyp, "PLAYED"))
	{
		system("say \"Gee gee, ease zee\"");
		fwrite("\tGG\n", 1, strlen("\tGG\n"), fp);
	}
}

void	smalltalk2(char *hyp, FILE *fp)
{
	if (strstr(hyp, "WHAT") && (strstr(hyp, "ANSWER") || strstr(hyp, "LIFE") \
		|| strstr(hyp, "UNIVERSE") || strstr(hyp, "EVERYTHING")))
	{
		system("say \"42!\"");
		fwrite("\tWHAT IS THE ANSWER TO LIFE, THE UNIVERSE, AND \
			EVERYTHING?\n", 1, strlen("\tWHAT IS THE ANSWER TO LIFE,\
				THE UNIVERSE,AND EVERYTHING?\n"), fp);
	}
	else if (strstr(hyp, "WHAT") && (strstr(hyp, "SILICON") ||
		strstr(hyp, "VALLEY") || strstr(hyp, "FOURTY") || strstr(hyp, "TWO")))
	{
		system("say \"42 silicon valley is a tuition-free coding school where\
			future nobel prize-winning genius definitely-not-idiot\
				billionaire playboy philanthropist master ninjas,Elliot \
				Tregoning, Sam North, Sam Collet, and Ian Wagner preside.\"");
		fwrite("\t42 SILICON VALLEY\n", 1, strlen("\t42 SILICON VALLEY\n"), fp);
	}
	else if (strstr(hyp, "WHAT") && strstr(hyp, "YOU") && strstr(hyp, "ARE"))
	{
		system("say \"I am machine\"");
		fwrite("\tWHAT ARE YOU?\n", 1, strlen("\tWHAT ARE YOU?\n"), fp);
	}
}

void	smalltalk3(char *hyp, FILE *fp)
{
	int random;

	if (strstr(hyp, "WHO") && (strstr(hyp, "KING")))
	{
		system("say -v \"Zarvox\" \"Ian is the 42 King.\
			He is smart, handsome, and everyonelikes him\" ");
		fwrite("\tWHO IS THE KING?\n", 1, strlen("\tWHO IS THE KING?\n"), fp);
	}
	else if (strstr(hyp, "WHO") && (strstr(hyp, "GOOD") || strstr(hyp, "BOY")))
	{
		random = random_num(0, 1);
		if (random == 0)
			system("say -v \"Zarvox\" \"I am...\" ");
		else if (random == 1)
			system("say \"Me\"");
		fwrite("\tWHO IS A GOOD BOY!?\n", 1,\
			strlen("\nWHO IS A GOOD BOY!?\n"), fp);
	}
}

void	smalltalk4(char *hyp, FILE *fp)
{
	if (strstr(hyp, "GOOD"))
	{
		system("say \"Thanks\"");
		fwrite("\tGOOD\n", 1, strlen("\tGOOD\n"), fp);
	}
	else if (strstr(hyp, "WHAT") && strstr(hyp, "THINK") &&
		strstr(hyp, "TEA") && strstr(hyp, "WHY"))
	{
		system("say \"It is a good thing I don't have legs...\"");
		fwrite("\tWHAT DO YOU THINK OF TTY?\n", 1,\
			strlen("\tWHAT DO YOU THINK OF TTY?\n"), fp);
	}
	else if (strstr(hyp, "THANKS") || (strstr(hyp, "THANK")
		&& strstr(hyp, "YOU")))
	{
		system("say \"No problem.\"");
		fwrite("\tTHANKS\n", 1, strlen("\tTHANKS\n"), fp);
	}
}
