#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->e_lines = NULL;
	chunk->runCount = 0;
	chunk->runCapacity = 0;
	initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(Line, chunk->e_lines, chunk->runCapacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
	// Append bytecode
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code,
		oldCapacity, chunk->capacity);
		chunk->lines = GROW_ARRAY(int, chunk->lines,
		oldCapacity, chunk->capacity);
	}
	// Increment run if same op
	if (chunk->runCount > 0 && chunk->e_lines[chunk->runCount - 1].line == line) {
		chunk->e_lines[chunk->runCount - 1].count += 1;
	} else { // Create new Line object in Line* array
		if (chunk->runCapacity < chunk->runCount + 1) {
			int old = chunk->runCapacity;
			chunk->runCapacity = GROW_CAPACITY(old);
			chunk->e_lines = GROW_ARRAY(Line, chunk->e_lines, old, chunk->runCapacity);
		}
		chunk->runCount += 1;
		chunk->e_lines[chunk->runCount].count = 1;
		chunk->e_lines[chunk->runCount].line = line;
	}

	chunk->code[chunk->count++] = byte;
}

int getLine(const Chunk* chunk, int index) {
	int running = 0;
	for (int i = 0; i < chunk->runCount; i++) {
		running += chunk->e_lines[i].count;
		if (index < running) {
			return chunk->e_lines[i].line;
		}
	}
	return -1; // error
}

int addConstant(Chunk* chunk, Value value) {
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}



