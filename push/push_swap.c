/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:23:02 by jeetienn          #+#    #+#             */
/*   Updated: 2025/02/21 20:14:49 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_stack(t_stack_node **a, t_stack_node **b)
{
	if (stack_len(*a) == 2)
		sa(a, false);
	else if (stack_len(*a) == 3)
		sort_three(a);
	else
		sort_stacks(a, b);
}

int main(int argc, char *argv[])
{
    t_stack_node *a;
    t_stack_node *b;
    char **split_argv;

    a = NULL;
    b = NULL;
    split_argv = NULL;
    if (argc == 1 || (argc == 2 && !argv[1][0]))
        return (1);
    else if (argc == 2)
    {
        split_argv = ft_split(argv[1], ' ');
        if (!split_argv || !split_argv[0])  // Vérifier si split a échoué ou est vide
        {
            write(2, "Error\n", 6);
            free_split(split_argv);  // Libérer si alloué mais vide
            return (1);
        }
        init_stack_a(&a, split_argv, split_argv);
    }
    else
        init_stack_a(&a, argv + 1, NULL);

    if (!stack_sorted(a))
        sort_stack(&a, &b);
    
    free_stack(&a);
    if (split_argv)
        free_split(split_argv);
    
    return (0);
}
