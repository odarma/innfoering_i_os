#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *byte_size(long double n_bytes)
{
   long double kB = 1024L;
   long double MB = 1024L * kB;
   long double GB = 1024L * MB;
   long double TB = 1024L * GB;
   long double PB = 1024L * TB;
   long double EB = 1024L * PB;
   long double ZB = 1024L * EB;

   char *result = (char *) malloc(sizeof(char) * 20);

   if (n_bytes < 0)
     return NULL;

   if (n_bytes >= ZB)
      sprintf(result, "%5.1Lf ZB", n_bytes/ZB);
   else if (n_bytes >= EB)
      sprintf(result, "%5.1Lf EB", n_bytes/EB);
   else if (n_bytes >= PB)
      sprintf(result, "%5.1Lf PB", n_bytes/PB);
   else if (n_bytes >= TB)
      sprintf(result, "%5.1Lf TB", n_bytes/TB);
   else if (n_bytes >= GB)
      sprintf(result, "%5.1Lf GB", n_bytes/GB);
   else if (n_bytes >= MB)
      sprintf(result, "%5.1Lf MB", n_bytes/MB);
   else if (n_bytes >= kB)
      sprintf(result, "%5.1Lf kB", n_bytes/kB);
   else
      sprintf(result, "%5.0Lf B", n_bytes);

   return result;
}

void main()
{
    int pointer_size;
    int block_size;
    long double max_disk_size;
    long double max_file_size;

    printf("Ptr.size in bits (32|64)? ");
    scanf("%d", &pointer_size);
    printf("Block size in kB (1|2|4|8)? ");
    scanf("%d", &block_size);

    max_disk_size = (long double)block_size * 1024L * pow(2, (double)pointer_size);
    max_file_size = (12 + 1024 + 1024*1024 + 1024*1024*1024) * (long double)block_size * 1024L;

    printf("Max. disk size : %s\n", byte_size(max_disk_size));
    printf("Max. file size : %s\n", byte_size(max_file_size));
}