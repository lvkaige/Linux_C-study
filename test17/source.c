#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

// 数据库中一条数据的结构体
struct Address {
    int id;// 数据的id
    int set;// 数据的有效位

    // 一条数据保存的 “姓名” “邮箱” 信息。
    char name[MAX_DATA];
    char email[MAX_DATA];
};

// 数据库的结构体
struct Database {
    // 定义了一个记录数据的数组rows，类型为“数据”，容量为MAX_ROWS。
    struct Address rows[MAX_ROWS];
};

// 链接的结构体，连接了一个文件和一个数据库
struct Connection {
    FILE *file;// 一个文件指针
    struct Database *db;// 一个数据库指针
};

// 报错处理
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// 打印传入的“数据”类型参数，打印出这个数据的信息。
void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",addr->id, addr->name, addr->email);
}

// Database_load 函数用于从文件中加载数据库内容到内存中。
// 它使用 fread 函数来读取一个 struct Database 的大小的数据块，并将其放入连接的数据库中。
void Database_load(struct Connection *conn)
{
    // 读取成功后rc的值是1，失败了是0
    // 作用是打开文件从里面读取数据，将内容存到数据库中
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
{
    // 为链接分配内存空间
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error");

    // 为这个链接的数据库分配内存空间
    conn->db = malloc(sizeof(struct Database));

    if(!conn->db) die("Memory error");

    // 处理输入的指令
    if(mode == 'c') {
        // 写指令
        conn->file = fopen(filename, "w");
    } else {
        // 读指令
        conn->file = fopen(filename, "r+");
        // 如果已经连接到了一个文件
        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file");

    return conn;
}

// 链接与数据库都是在内存当中的，关闭的时候要释放内存
void Database_close(struct Connection *conn)
{
    if(conn) {
        // 关闭链接里连接着的文件
        if(conn->file) fclose(conn->file);
        // 释放链接里连接着的数据库
        if(conn->db) free(conn->db);
        // 释放链接
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    // 文件指针重新定位到文件的开头
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.");

    // 将程序内存中的数据缓冲区与文件同步，以确保文件中的数据与内存中的数据一致。
    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.");
}

// 创建数据库（初始化数据库），如果利用已经创建好数据库的文件再次创建数据库，原文件里的数据就会清空
void Database_create(struct Connection *conn)
{
    int i = 0;
    // 遍历数据库结构体中用于保存数据的数组，大小为MAX_ROWS
    for(i = 0; i < MAX_ROWS; i++) {
        // 生成一个数据，将其值的id设置为序号，set设置为0（set如果是1的话说明这个id已经有数据了），姓名和邮箱为空
        struct Address addr = {.id = i, .set = 0};
        // 将刚才生成的数据传入链接中的数据库的数组中，这是一个初始化的过程
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first");

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
    // 设置一个数据，其值是文件数据库数组中的第id个数据
    struct Address *addr = &conn->db->rows[id];

    // 如果这个数据的set位是1，说明这个数据有效，否则报错
    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

// 传入一个链接，一条“数据”的id
void Database_delete(struct Connection *conn, int id)
{
    // 类似初始化，id不变，将有效位设置为0
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    // 设置一个数据库指针，指向链接中的数据库
    struct Database *db = conn->db;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            // 将数据库中的每个元素都遍历一遍打印出来
            Address_print(cur);
        }
    }
}

// 创建一个数据库，先自己创建一个数据库文件，例如： test.bat，之后执行“ ./Database test.bar=t c ”,将数据库内数据放入内存。
int main(int argc, char *argv[])
{
    // 检测输入的参数是否合法，第一个参数是“./Database”,第二个是自己创建的数据库文件名，第三个是操作指令。
    if(argc < 3) die("USAGE: Database <dbfile> <action> [action params]");

    // 将第二个参数设置为 filename ，文件名。
    char *filename = argv[1];
    // 将第三个参数的首字母设置为 action ，用作操作指令。
    char action = argv[2][0];

    // 设置 conn 为一个链接，连接到输入参数对应的数据库。
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':// create
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':// get
            if(argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':// set
            if(argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':// delete
            if(argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':// list
            Database_list(conn);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
