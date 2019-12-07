/* Internal */
#include "machine/memory.h"

/* Standard */
#include <stdio.h>
#include <stdlib.h>


/* Memory */
#define ACPU_SIM_MEMORY_MAX_ADDRESS_WIDTH 32


/* Initialises a memory space */
void initMemory(Memory_t * const memory, unsigned const address_width) {

  /* Check address width for correctness */
  if(address_width > ACPU_SIM_MEMORY_MAX_ADDRESS_WIDTH) {
    printf("Error, the maximum allowed address bit count is %d\n", ACPU_SIM_MEMORY_MAX_ADDRESS_WIDTH);
    exit(1);
  }

  /* Break address field into page and offset */
  unsigned page_address_width = address_width / 2;
  unsigned page_index_width = address_width - page_address_width;

  memory->size = 0x01 << address_width;
  memory->page_count = 0x01 << page_index_width;
  memory->page_size = 0x01 << page_address_width;

  /* Allocate memory for page table */
  memory->pages = (void*)malloc(memory->page_count * sizeof(void*));

  /* Initialise page pointers to NULL */
  for(unsigned i = 0; i < memory->page_count; i++) {
    memory->pages[i] = NULL;
  }
}


/* Free all allocated pages */
void freeMemory(Memory_t * const memory) {

  /* Free page memory for all used pages */
  for(unsigned i = 0; i < memory->page_count; i++) {
    if(memory->pages[i] != NULL) {
      free(memory->pages[i]);
    }
  }

  /* Free page table */
  free(memory->pages);
}
