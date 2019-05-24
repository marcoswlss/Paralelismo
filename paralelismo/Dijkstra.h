#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>

int sem_create(key_t key, int initval)
{
	int semid;
	
	union semun
	{
		int val;
		struct seminfo *buf;
		unsigned short int array[4];
	}arg_ctl;
	
	semid = semget(ftok("djikstra.h", key), 1, IPC_CREAT|IPC_EXCL|0666);
	if (semid == -1)
	{
		semget(ftok("djikstra.h", key), 1, 0666);
		if (semid == -1)
		{
			printf("[ERRO] semget()\n");
			return 1;
		}
	}
	
	arg_ctl.val = initval;
	if(semctl(semid, 0, SETVAL, arg_ctl) == -1)
	{
		printf("[ERRO] semctl()\n");
		return 1;
	}	
	
	return semid;
}

void P(int semid)
{
	struct sembuf sempar[1];
	sempar[0].sem_num = 0;
	sempar[0].sem_op  = -1;
	sempar[0].sem_flg = SEM_UNDO;

	if(semop(semid, sempar, 1) == -1)
		printf("[ERRO] P()\n");
}

void V(int semid)
{
	struct sembuf sempar[1];
	sempar[0].sem_num = 0;
	sempar[0].sem_op  = 1;
	sempar[0].sem_flg = SEM_UNDO;

	if(semop(semid, sempar, 1) == -1)
		printf("[ERRO] V()\n");
}

void sem_delete(int semid)
{
	if(semctl(semid, 0, IPC_RMID) == -1)
		printf("[ERRO] IPC_RMID\n");
}

