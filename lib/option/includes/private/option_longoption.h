/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_longoption.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:55 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:55 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_LONGOPTION_H
# define OPTION_LONGOPTION_H

typedef struct				s_option_list
{
	t_option_info			*p;
	struct s_option_list	*next;
}							t_option_list;

typedef struct				s_treat_longoption
{
	char					*nameend;
	unsigned int			namelen;
	t_option_info			*p;
	t_option_info			*pfound;
	t_option_list			*ambig_list;
	int						exact;
	int						indfound;
	int						option_index;
}							t_treat_longoption;

int							option_treat_longoption_arguments(\
	t_arguments *args, t_treat_longoption *info, t_option_data *d);

int							option_treat_longoption_ambiguous(\
	char **argv, t_treat_longoption *info, t_option_data *d);

int							option_treat_longoption_unrecognized(\
	char **argv, t_option_data *d);

void						option_treat_longoption_test_match(\
	t_treat_longoption *info, t_option_data *d);

int							option_treat_longoption_get_namelen(\
	t_treat_longoption *info, t_option_data *d);

#endif
