/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:53 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:53 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_PRIVATE_H
# define OPTION_PRIVATE_H

typedef enum			e_ordering
{
	REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
}						t_ordering;

typedef struct			s_option_data
{
	const char			*optstring;
	t_option_info		*longopts;
	int					long_only;
	int					*longind;

	int					optind;
	int					opterr;
	int					optopt;
	char				*optarg;

	int					private_initialized;
	char				*private_nextchar;

	t_ordering			private_ordering;

	int					private_first_nonopt;
	int					private_last_nonopt;
}						t_option_data;

/*
** Test whether ARGV[optind] points to a non-option argument.
** Either it does not have option syntax, or there is an environment flag
** from the shell indicating it is not an option.  The later information
** is only used when the used in the GNU libc.
*/

# define NONOPTION_P (argv[d->optind][0] != '-' || argv[d->optind][1] == '\0')

void					option_preparation(t_option_data *d);
void					option_exchange(char **argv, t_option_data *d);
int						option_advance_to_next_argv_element(
							int argc, char **argv, t_option_data *d);
void					option_check_nonopt_values(t_option_data *d);

int						option_treat_longoption(
							int argc, char **argv, t_option_data *d);
int						option_treat_shortoption(
							int argc, char **argv, t_option_data *d);

int						private_option_getopt(t_arguments *args,
							t_option_arguments *options, int longonly);

#endif
