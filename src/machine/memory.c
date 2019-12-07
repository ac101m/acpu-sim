/* Internal */
#include "machine/memory.h"

/* Standard */
#include <stdio.h>
#include <stdlib.h>


/* Memory */
#define ACPU_SIM_MEMORY_MAX_ADDRESS_WIDTH 31


/* Initialises a memory space */
void initMemory(Memory_t *const memory, unsigned const address_width) {

  /* Check address width for correctness */
  if(address_width > ACPU_SIM_MEMORY_MAX_ADDRESS_WIDTH) {
    printf("Error, the maximum allowed address bit count is %d\n", ACPU_SIM_MEMORY_MAX_ADDRESS_WIDTH);
    exit(1);
  }

  /* Break address field into page and offset */
  memory->address_width = address_width;
  memory->page_offset_width = address_width / 2;
  memory->page_index_width = address_width - memory->page_offset_width;

  /* Initialise address widths */
  memory->size = 0x01 << address_width;
  memory->page_size = 0x01 << memory->page_offset_width;
  memory->page_count = 0x01 << memory->page_index_width;

  /* Initialise address masks */
  memory->address_mask = memory->size - 1;
  memory->page_offset_mask = memory->page_size - 1;
  memory->page_index_mask = (memory->page_count - 1) << memory->page_offset_width;

  /* Allocate memory for page table */
  memory->pages = (void **)malloc(memory->page_count * sizeof(void *));

  /* Initialise page pointers to NULL */
  for(unsigned i = 0; i < memory->page_count; i++) {
    memory->pages[i] = NULL;
  }
}


/* Free all allocated pages */
void freeMemory(Memory_t *const memory) {

  /* Free page memory for all used pages */
  for(unsigned i = 0; i < memory->page_count; i++) {
    if(memory->pages[i] != NULL) {
      free(memory->pages[i]);
    }
  }

  /* Free page table */
  free(memory->pages);
}


/* Get pointer to page for given address */
inline uint32_t getPageIndex(Memory_t *const memory, uint32_t const address) {
  return (address & memory->page_index_mask) >> memory->page_offset_width;
}


/* Get page offset for given address */
inline uint32_t getPageOffset(Memory_t *const memory, uint32_t const address) {
  return address & memory->page_offset_mask;
}


/* Get a page, if the requested page isn't allocated, allocate it */
inline void *getPage(Memory_t *const memory, uint32_t const page_index) {
  if(memory->pages[page_index] == NULL) {
    memory->pages[page_index] = (void *)malloc(memory->page_size);
  }
  return memory->pages[page_index];
}


/* Check alignment and  of address */
inline void checkAddress(Memory_t *const memory, uint32_t const address, uint32_t const lsb_mask) {
  uint32_t const address_mask = memory->address_mask & (~lsb_mask);

  /* Check address validity using combined mask */
  if(address & address_mask) {
    if(address & lsb_mask) {
      printf("Memory Error! misaligned memory access.\n");
    }
    if(address & (~memory->address_mask)) {
      printf("Memory Error! access beyond memory limits.\n");
    }
    exit(1);
  }
}

