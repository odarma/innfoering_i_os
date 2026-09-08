#include <stdio.h>
#include <stdlib.h>

typedef struct prosess {
   int nummer;
   char status;
   float start_tid;
   float CPU_tid;
} Prosess;

Prosess *kopier(Prosess p) {
    Prosess *ny_p = malloc(sizeof(Prosess));

    if (ny_p == NULL) {
        return NULL;
    }

    ny_p->nummer = p.nummer;
    ny_p->status = p.status;
    ny_p->start_tid = p.start_tid;
    ny_p->CPU_tid = p.CPU_tid;

    return ny_p;
}
int main(void) {
    Prosess p1 = {101, 'R', 0.5f, 12.3f};

    Prosess *kopi_ptr = kopier(p1);

    if (kopi_ptr == NULL) {
        printf("Kunne ikke allokere minne for prosesskopien.\n");
        return 1;
    }

    printf("--- Original prosess ---\n");
    printf("Nummer: %d, Status: %c, Starttid: %.2f, CPU-tid: %.2f\n\n", 
            p1.nummer, p1.status, p1.start_tid, p1.CPU_tid);

    printf("--- Kopiert prosess ---\n");
    printf("Nummer: %d, Status: %c, Starttid: %.2f, CPU-tid: %.2f\n", 
            kopi_ptr->nummer, kopi_ptr->status, kopi_ptr->start_tid, kopi_ptr->CPU_tid);

    free(kopi_ptr);

    // sette pekeren til NULL etter free for Ã¥ unngÃ¥ "dangling pointers"
    kopi_ptr = NULL;

    return 0;
}