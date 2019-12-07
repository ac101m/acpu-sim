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


/* Load 32 bit word */
uint32_t read32(Memory_t *const memory, uint32_t const address) {
  checkAddress(memory, address, 0x03);
  void *const page = getPage(memory, getPageIndex(memory, address));
  return *((uint32_t *)(page + getPageOffset(memory, address)));
}


/* Load 16 bit word */
uint16_t read16(Memory_t *const memory, uint32_t const address) {
  checkAddress(memory, address, 0x01);
  void *const page = getPage(memory, getPageIndex(memory, address));
  return *((uint16_t*)(page + getPageOffset(memory, address)));
}


/* Load 8 bit word */
uint8_t read8(Memory_t *const memory, uint32_t const address) {
  checkAddress(memory, address, 0x00);
  void *const page = getPage(memory, getPageIndex(memory, address));
  return *((uint8_t*)(page + getPageOffset(memory, address)));
}


/* Store 32 bit word */
void write32(Memory_t *const memory, uint32_t const address, uint32_t const data) {
  checkAddress(memory, address, 0x03);
  void *const page = (uint32_t*)getPage(memory, getPageIndex(memory, address));
  *((uint32_t*)(page + getPageOffset(memory, address))) = data;
}


/* Store 16 bit word */
void write16(Memory_t *const memory, uint32_t const address, uint16_t const data) {
  checkAddress(memory, address, 0x01);
  void *const page = getPage(memory, getPageIndex(memory, address));
  *((uint16_t*)(page + getPageOffset(memory, address))) = data;
}


/* Store 8 bit word */
void write8(Memory_t *const memory, uint32_t const address, uint8_t const data) {
  checkAddress(memory, address, 0x00);
  void *const page = getPage(memory, getPageIndex(memory, address));
  *((uint8_t*)(page + getPageOffset(memory, address))) = data;
}
