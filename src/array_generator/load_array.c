#include <stdio.h>
#include <stdlib.h>

/* print array elements in an organized manner */
void print_array(int *A, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main(int argc, char **argv) {
    /* declare variables */
    int *A, A_size;
    char *file_name;
    FILE *f;

    /* check amount of arguments */
    if (argc != 3) {
        printf("Usage: %s file_name size\n", argv[0]);
        return EXIT_SUCCESS;
    }

    /* name arguments */
    file_name = argv[1];
    A_size = atoi(argv[2]);

    /* load array */
    A = (int *) malloc(A_size * sizeof(int));
    f = fopen(file_name, "rb");
    fread(A, sizeof(int), A_size, f);

    /* print loaded array */
    print_array(A, A_size);

    /* free memory, close file descriptors and return success */
    free(A);
    fclose(f);
    return EXIT_SUCCESS;
}
