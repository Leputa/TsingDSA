#include <stdio.h>
#include "temperature.h"

typedef struct _station_type
{
    int x, y;
    int temp;
} station_type;

static FILE * fr = NULL;   //FILE是一个类型？ 
static FILE * fw = NULL;

static int n, m;
static int last_response, query_index;
static station_type stations[50000];

extern int GetNumOfStation(void)
{
    int i;
    fr = fopen("temperature.in", "r");   //fopen("文件名","打开方式")
    fw = fopen("temperature.out", "w");  // r打开只读文件，该文件必须存在。w打开只写文件
    fscanf(fr, "%d %d", &n, &m);         //fscanf就是从文件中读取数据，保存到第三个参数开始的变量里(fp是一个FILE类型的指针)
    for (i = 0; i < n; i++)
      fscanf(fr, "%d %d %d", &stations[i].x, &stations[i].y, 
                  &stations[i].temp);
    query_index = 0;
    last_response = 0;
    return n;
}

extern void GetStationInfo(int no, int *x, int *y, int *temp)
{
    *x = stations[no].x;
    *y = stations[no].y;
    *temp = stations[no].temp;
}

extern int GetQuery(int *x1, int *y1, int *x2, int *y2)
{
    if (query_index < m) {
        fscanf(fr, "%d %d %d %d", x1, y1, x2, y2);
        query_index++;
        return 1;
    } else
      return 0;
}

extern void Response(int temp)
{
    if (last_response > query_index)
      fprintf(fw, "No Query\n");
    for (last_response++; last_response < query_index; last_response++)
      fprintf(fw, "Missing\n");
    fprintf(fw, "%d\n", temp);
    if (query_index == m) {
        fclose(fr);
        fclose(fw);
    }
}
