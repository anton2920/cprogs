#ifndef LAB_DEV_LIBS_H
#define LAB_DEV_LIBS_H

/* Header inclusion */

/* New data types */
struct DataItem {
    unsigned long key;
    char data[20];
};

/* Functions' declarations */
int hashCode(unsigned long key);
struct DataItem *search(unsigned long key);
void insert(unsigned long key, char *data);
struct DataItem *delete(struct DataItem *item);

#endif
