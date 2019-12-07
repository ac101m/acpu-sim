#ifndef ACPU_SIM_MEMORY_INCLUDED
#define ACPU_SIM_MEMORY_INCLUDED


/* Standard */
#include <stdint.h>


typedef struct {
  unsigned size;
  unsigned page_size;
  unsigned page_count;
  unsigned page_offset_width;
  unsigned page_index_width;
  uint32_t page_offset_mask;
  uint32_t page_index_mask;
  uint8_t **pages;
} Memory_t;


/* Create & destroy memory pool */
void initMemory(Memory_t *const memory, unsigned const address_width);
void freeMemory(Memory_t *const memory);


#endif // ACPU_SIM_MEMORY_INCLUDED
