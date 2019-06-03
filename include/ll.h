/*-------------------------------------------------------------------*/
#ifndef _LL_H_
#define _LL_H_
/*-------------------------------------------------------------------*/
/* DEF_LIST for struct definitions. see if primitives can be used */
#define LIST_NAME(type)  ll_##type
#define DEF_LIST(type)  struct LIST_NAME(type) {         \
                          struct type data;              \
                          struct LIST_NAME(type) *next;  \
                        }
#define NEXT(var)   (var->next)
#define DATA(var)   (var->data)
/*-------------------------------------------------------------------*/
#define LIST(list_name, type) struct LIST_NAME(type)* list_name
#define COPY_DATA(tail, val, type)                      \
          memcpy(&DATA(tail), &val, sizeof(struct type))
/*-------------------------------------------------------------------*/
#define MALLOC_ENTRY(type)  (struct LIST_NAME(type) *)  \
          malloc(sizeof(struct LIST_NAME(type)))       
#define FREE_ENTRY(entry)    free(entry)
/*-------------------------------------------------------------------*/
#define LIST_TAIL(tail, list_name)              \
            do {                                \
              tail = list_name;                 \
              while(tail != NULL) {             \
                tail = NEXT(tail);              \
              }                                 \
            } while(0)
/*-------------------------------------------------------------------*/
#define LIST_ADD(list_name, tail, val, type)                  \
            do {                                              \
              LIST(tail, type);                               \
              LIST_TAIL(tail, list_name);                     \
              if(tail == list_name) {                         \
                list_name = MALLOC_ENTRY(type);               \
                COPY_DATA(list_name, val, type);              \
                NEXT(list_name) = NULL;                       \
              } else {                                        \
                tail = MALLOC_ENTRY(type);                    \
                COPY_DATA(tail, val, type);                   \
                NEXT(tail) = NULL;                            \
              }                                               \
            } while(0)
/*-------------------------------------------------------------------*/
#endif /* _LL_H_ */
/*-------------------------------------------------------------------*/
