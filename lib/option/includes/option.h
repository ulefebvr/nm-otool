/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:48 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:48 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

/*
** Structure to pass the main arguments to the getopt function.
*/
typedef struct				s_arguments
{
	int						argc;
	char					**argv;
	char					**env;
}							t_arguments;

/*
** Structure for the long option.
**
** name : --name_of_the_option.
** has_arg : [no_argument | required_argument | optional_argument].
** flag : flag to set if option found.
** val : equivalent for the short option value.
*/
typedef struct				s_option_info
{
	const char				*name;
	int						has_arg;
	int						*flag;
	int						val;
}							t_option_info;

/*
** Structure for the options settings.
**
** opstring: for the list of short option handled,
** longopts: list of long option.
** longind: index of the long option if found.
** long_only: set to 0 by default.
*/
typedef struct				s_option_arguments
{
	const char				*optstring;
	t_option_info			*longopts;
	int						*longind;
}							t_option_arguments;

# define NO_ARGUMENT		0
# define REQUIRED_ARGUMENT	1
# define OPTIONAL_ARGUMENT	2

/*
** For communication from `getopt' to the caller.
** When `getopt' finds an option that takes an argument,
** the argument value is returned here.
** Also, when `ordering' is RETURN_IN_ORDER,
** each non-option ARGV-element is returned here.
*/
extern char					*g_option_optarg;

/*
** Index in ARGV of the next element to be scanned.
** This is used for communication to and from the caller
** and for communication between successive calls to `getopt'.
**
** On entry to `getopt', zero means this is the first call; initialize.
**
** When `getopt' returns -1, this is the index of the first of the
** non-option elements that the caller should itself scan.
**
** Otherwise, `optind' communicates from one call to the next
** how much of ARGV has been scanned so far.
*/
extern int					g_option_optind;

/*
** Callers store zero here to inhibit the error message
** for unrecognized options.
*/
extern int					g_option_opterr;

/*
** Set to an option character which was unrecognized.
** This must be initialized on some systems to avoid linking in the
** system's own getopt implementation.
*/
extern int					g_option_optopt;

/*
** This version of getopt handle only the short option.
*/
int							option_getopt(
								t_arguments *args, const char *optstring);

/*
** This version of getopt handle both the long and short option.
*/
int							option_getopt_long(
								t_arguments *args, t_option_arguments *options);

/*
** This version of getopt handle only the long option.
*/
int							option_getopt_long_only(
								t_arguments *args, t_option_arguments *options);

#endif
