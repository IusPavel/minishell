#include "minishell.h"

void sighandler(int sig)
{
	printf("Получен сигнал %d. Необходима обработка.\n", sig);
}