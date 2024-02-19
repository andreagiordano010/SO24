

int wait_sem(int id_sem, int numsem) {

	int err;
	struct	sembuf sem_buf;

	sem_buf.sem_num = num_sem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = -1;

	err = semop(id_sem, &sem_buf, 1); //semaforo rosso


	if (err < 0)
		perror("sem fallita");

	return err;
}

int signal_sem(int id_sem, int numsem) {

	int err;
	struct sembuf sem_buf;

	sem_buf.sem_num = num_sem;
	sem_buf.sem_flg = 0;
	sem_buf.sem_op = 1;

	err = semop(id_sem, &sem_buf, 1); //semaforo verde
	if (err < 0)

		perror("errore signal");
	return err;

	}


key_t shmkey = IPC_PRIVATE;
key_t semkey = IPC_PRIVATE;

int ds_shm = shmget(shmkey, sizeof(int), IPC_CREATE | 0664);

struct prodcons* p = shmat(ds_shm, NULL, 0);


int ds_sem = semget(semkey, 4, IPC_CREATE | 0664);

semctl(ds_sem, SPAZIO_DISPONIBILE, SETVAL, DIM_BUFFER);
semctl(ds_sem, MESSAGGIOP_DISPONIBILE, SETVAL, 0);
semctl(ds_sem, MUTEX_P, SETVAL, 1);
semctl(ds_sem, MUTEC_C, SETVAL, 1);









#define DIM_BUF 3
struct prodcons {
	int buffer[DIM_BUF];
	int testa;
	int coda;


};


void produttore(struct prodcons* p, ds_sem) {

	wait_sem(ds_sem, SPAZIO_DISPONIBILE);

	wait_sem(ds_sem, MUTEX_P);

	sleep(2);

	p.buffer[p.testa] = rand() % 100;

	p->testa = (p.testa + 1 ) % DIM_BUFFER;

	signal_sem(ds_sem, MUTEX_P);

	signal_sem(ds_sem, MESSAGGIO_DISPONIBILE);


	void consumatore(struct prodcons* p, ds_sem) {

		wait_sem(ds_sem, MESSAGGIO_DISPONIBILE);

		wait_sem(ds_sem, MUTEX_C);

		sleep(2);

		

		p->coda = (p.coda + 1) % DIM_BUFFER;

		signal_sem(ds_sem, MUTEX_C);

		signal_sem(ds_sem, SPAZIO_DISPONIBILE);



	}























































		 





}



	