#ifndef ACPU_SIM_MEMORY_INCLUDED
#define ACPU_SIM_MEMORY_INCLUDED


typedef struct {
  unsigned size;
  unsigned page_count;
  unsigned page_size;
  void **pages;
  uint32_t page_offset_width;
  uint32_t page_index_width;
  uint32_t page_offset_mask;
  uint32_t page_index_mask;
} Memory_t;


/* Create & destroy memory pool */
void initMemory(Memory_t *const memory, unsigned const address_width);
void freeMemory(Memory_t *const memory);


#endif // ACPU_SIM_MEMORY_INCLUDED
