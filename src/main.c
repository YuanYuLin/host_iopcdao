#include <sys/socket.h>
#include <sys/epoll.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <syslog.h>

#define DAO_KV_MAX	128

/*
 * bit 0 ~ 3 : DAOTYPE 
 * bit 4 :
 * bit 5 :
 * bit 6 :
 * bit 7 : last record
 *
 */
#define DAOTYPE_UNKNOWN		0x00
#define DAOTYPE_JSON_512	0x01 

#define DAOTYPE_LAST_RECORD	0x80 
#define DAOTYPE_DATALEN_500	500

struct dao_hdr_t {
	uint32_t chksum;
	uint8_t type;
	uint8_t key_len;
	uint16_t val_len;
	uint32_t resv;
};

struct dao_kv_512_t {
	struct dao_hdr_t hdr;
	uint8_t data[DAOTYPE_DATALEN_500];
};

//struct dao_kv_t dao_kv[DAO_KV_MAX];
struct dao_kv_t *dao_kv;

static int usage_main_init_dao()
{
	printf("main_init_dao <record_file>\n");
}

static int main_daoinit(int argc, char** argv)
{
	uint16_t max_record_count = 0;
	uint8_t record_type = DAOTYPE_UNKNOWN;
	uint8_t* record_file = NULL;
	uint8_t* ptr = dao_kv;
	int i = 0;

	if(argc < 2) {
		usage_main_init_dao();
	}

	max_record_count = strtoul(argv[1], NULL, 10);
	record_type = strtoul(argv[2], NULL, 10);
	record_file = argv[3];
	ptr = malloc(max_record_count * sizeof(struct dao_kv_512_t));
	memset(ptr, 0, max_record_count * sizeof(struct dao_kv_512_t));

	for(i=0;i<max_record_count;i++) {
		dao_kv[i] = 
	}
}

struct sub_fun_t {
	uint8_t name[20];
	int (*fun)(int argc, char** argv);
};

static struct sub_fun_t list[] = {
	{ "main_daoinit", main_daoinit },
	{ "", NULL }
};

static void main_usage()
{
    int i = 0;
    int list_size = sizeof(list)/sizeof(struct sub_fun_t);
    printf("\n");
    for(i=0;i<list_size;i++){
	    printf("  %s help\n", list[i].name);
    }
}

int main(int argc, char** argv)
{
    int i = 0;
    int list_size = sizeof(list)/sizeof(struct sub_fun_t);
    uint8_t* main_func = NULL;
    if(argc < 2){
	    main_usage();
	    return 1;
    }
    main_func = argv[1];
    for(i=0;i<list_size;i++){
	    if(!strcmp(main_func, list[i].name)){
		    list[i].fun(argc - 1, &argv[1]);
	    }
    }
    return 0;
}

