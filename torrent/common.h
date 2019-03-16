typedef struct _test_struct{
    char name[100];
} test_struct_t;

typedef struct address{
    char ip[15];
    int port;
} address_t;

typedef struct result_struct_{
    char status[4];
    address_t addresses[10];
    int count;
} result_struct_t;

typedef struct node{

    address_t addresses[10];
    int count;
    char* avaible_files[10];
    int count_files;
} node_t;
