#include "../incs/minishell.h"

int categorize_cmd(t_info *info)
{
	int		ret;
	int		idx;

	ret = 0;
	if (del_quote(&(info->set->set[0])))
	{
		printf("ERROR: trim_cmd malloc error\n");
		return (1);
	}
	info->set->cmd = info->set->set[0];
	if (select_sh_bti(info))
	{
		printf("ERROR: select_shell_bti error\n");
		return (-1);
	}
#if 0
	else if (run_bti(info))
	{
		printf("ERROR: run_bti error\n");
		return (-1);
	}
#endif

	//if(bti_path) -> fork
	//else bti_path is NULL -> show error message.
	//after using bti function with execve, free path.
	//arg_beg = arg_list->next;
	//make list to arr function.(arg_beg, env_list)
	//after using arg_beg array, env array, free.(pk_split_free)
	//strncmp(find one)
	return (ret);
}