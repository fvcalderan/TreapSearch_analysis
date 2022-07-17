#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* list of modes:
 * 0 - ordered unique
 * 1 - inversely ordered unique
 * 2 - almost ordered unique
 * 3 - random unique
 * 4 - ordered
 * 5 - inversely ordered
 * 6 - almost ordered
 * 7 - random
 */

/* swap two elements from an array */
void swap(int * A, int i, int j)
{
    int aux = A[i];
    A[i] = A[j];
    A[j] = aux;
}

int main(int argc, char **argv)
{
    /* declare variables */
    int A_size, A_mode, A_seed, *A, i, j, aux1, aux2;
    char *file_name;
    FILE *f;

    /* check amount of arguments */
    if (argc != 5) {
        printf("Usage: %s file_name size mode seed\n", argv[0]);
        return EXIT_SUCCESS;
    }

    /* name arguments */
    file_name = argv[1];
    A_size = atoi(argv[2]);
    A_mode = atoi(argv[3]);
    A_seed = atoi(argv[4]);

    srand(A_seed); /* lock random seed for reproducibility */

    /* allocate memory for the array */
    A = (int *) malloc(A_size * sizeof(int));

    switch (A_mode) {
        case 0: /* ordered unique elements */
            for (i = 0; i < A_size; i++)
                A[i] = i;
            break;

        case 1: /* inversely ordered unique elements */
            for (i = 0; i < A_size; i++)
                A[i] = A_size - i - 1;
            break;

        case 2: /* almost ordered unique elements (1% of elements swapped) */
            for (i = 0; i < A_size; i++)
                A[i] = i;
            for (i = 0; i < (int)ceil(A_size * 0.005); i++) {
                aux1 = rand() % A_size; /* get random index aux1 */
                do
                    aux2 = rand() % A_size; /* get random unique index aux2 */
                while (aux1 == aux2);
                swap(A, aux1, aux2);
            }
            break;

        case 3: /* randomly ordered unique elements */
            for (i = 0; i < A_size; i++)
                A[i] = i;
            for (i = 0; i < A_size; i++) {
                aux1 = rand() % A_size; /* ger random index aux1 */
                swap(A, i, aux1);
            }
            break;

        case 4: /* ordered elements */
            for (i = j = 0; i < A_size; i++) {
                j += (int)(rand() % 2);
                A[i] = j;
            }
            break;

        case 5: /* inversely ordered elements */
            for (i = j = 0; i < A_size; i++) {
                j += (int)(rand() % 2);
                A[i] = A_size - j - 1;
            }
            break;

        case 6: /* almost ordered elements (1% of elements swapped) */
            for (i = j = 0; i < A_size; i++) {
                j += (int)(rand() % 2);
                A[i] = j;
            }
            for (i = 0; i < (int)ceil(A_size * 0.005); i++) {
                aux1 = rand() % A_size; /* get random index aux1 */
                do
                    aux2 = rand() % A_size; /* get random unique index aux2 */
                while (aux1 == aux2);
                swap(A, aux1, aux2);
            }
            break;

        case 7: /* randomly ordered elements */
            for (i = j = 0; i < A_size; i++) {
                j += (int)(rand() % 2);
                A[i] = j;
            }
            for (i = 0; i < A_size; i++) {
                aux1 = rand() % A_size; /* ger random index aux1 */
                swap(A, i, aux1);
            }
            break;
    }

    /* save to file */
    f = fopen(file_name, "wb");
    fwrite(A, sizeof(int), A_size, f);

    /* free memory, close file descriptors and return success */
    free(A);
    fclose(f);
    return EXIT_SUCCESS;
}
