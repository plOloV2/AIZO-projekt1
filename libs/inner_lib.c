#include<omp.h>
#include<stdlib.h>
#include<float.h>
#include<math.h>
#include<limits.h>

void* gen_data(int size, size_t type_size){                 //function to generate random array of given size and type

    void *res = malloc(type_size * size);

    if(res == NULL)
        return NULL;

    for(int i = 0; i < size; i++){
        unsigned char *byte_ptr = (unsigned char *)res + (i * type_size);

        for(int k = 0; k < type_size; k++) 
            byte_ptr[k] = rand() % 256;

    }

    return res;
}

int compareINT(const void* a, const void* b){               //used by build in qsort algorithm in growing order, compares two int

    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a > int_b) - (int_a < int_b);
}

int rev_compareINT(const void* a, const void* b){           //used by build in qsort algorithm in desendng order, compares two int

    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a < int_b) - (int_a > int_b);
}

int compare_arraysINT(int *a, int *b, int size){            //used to compare two arrays of ints

    for(int i = 0; i < size; i++)
        if(a[i] != b[i])
            return 0;
        
    return 1;
}

int compareDOUBLE(const void* a, const void* b){                //used by build in qsort algorithm in growing order, compares two double

    double double_a = *(const double *)a;
    double double_b = *(const double *)b;

    return (double_a > double_b) - (double_a < double_b);
}

int rev_compareDOUBLE(const void* a, const void* b){            //used by build in qsort algorithm in desendng order, compares two double

    double double_a = *(const double *)a;
    double double_b = *(const double *)b;

    return (double_a < double_b) - (double_a > double_b);
}

int compare_arraysDOUBLE(double *a, double *b, int size){       //used to compare two arrays of doubles

    for(int i = 0; i < size; i++)
        if(a[i] != b[i])
            return 0;
        
    return 1;
}

double sort(void *data, int size, int config, void *ref, void (*f)(void *, int, int)){      //function used to comapre time of sorting, takes pointer to sorting algorithm as parameter,
                                                                                            //if sorted array don't match ref[], return -1, else returns time of sorting in s as double

    double t = omp_get_wtime();             //starts time measurment
    (*f)(data, size, config);               //cals sort function
    t = omp_get_wtime() - t;                //ends measurment

    if(config != 4){
        if(!compare_arraysINT(data, ref, size))    //checks if arrays was sorted corectly
            return -1.0;
    } else if(!compare_arraysDOUBLE(data, ref, size))
            return -1.0;

    return t;
}
