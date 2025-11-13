#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_RETURN,
	OP_CONSTANT_LONG,
} OpCode;

typedef struct {
	int line;
	int count;
} Line;

typedef struct {
	int count;
	int capacity;
	uint8_t* code;
	int* lines; // Error reporting, bad line number encoding strat
	ValueArray constants;
	Line* e_lines;
	int runCount;
	int runCapacity;
} Chunk;



void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void writeConstant(Chunk* chunk, Value value, int line);
int getLine(const Chunk* chunk, int index);

#endif

