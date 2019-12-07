#ifndef ACPU_SIM_MEMORY_INCLUDED
#define ACPU_SIM_MEMORY_INCLUDED


/* Standard */
#include <stdint.h>


typedef struct {
  unsigned size;
  unsigned page_size;
  unsigned page_count;

  unsigned address_width;
  unsigned page_offset_width;
  unsigned page_index_width;

  uint32_t address_mask;
  uint32_t page_offset_mask;
  uint32_t page_index_mask;

  void **pages;
} Memory_t;


/* Create & destroy memory pool */
void initMemory(Memory_t *const memory, unsigned const address_width);
void freeMemory(Memory_t *const memory);

/* Loads */
uint32_t read32(Memory_t *const memory, uint32_t const address);
uint16_t read16(Memory_t *const memory, uint32_t const address);
uint8_t read8(Memory_t *const memory, uint32_t const address);

/* Stores */
void write32(Memory_t *const memory, uint32_t const address, uint32_t const data);
void write16(Memory_t *const memory, uint32_t const address, uint16_t const data);
void write8(Memory_t *const memory, uint32_t const address, uint8_t const data);


#endif // ACPU_SIM_MEMORY_INCLUDED
