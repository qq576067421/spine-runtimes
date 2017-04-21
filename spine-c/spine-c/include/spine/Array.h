/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_ARRAY_H
#define SPINE_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#define _SP_ARRAY_DECLARE_TYPE(name, itemType) \
	typedef struct name { int size; int capacity; itemType* items; } name; \
	name* name##_create(int initialCapacity); \
	void name##_dispose(name* self); \
	void name##_clear(name* self); \
	void name##_setSize(name* self, int newSize); \
	void name##_ensureCapacity(name* self, int newCapacity); \
	void name##_add(name* self, itemType value); \
	void name##_removeAt(name* self, int index); \
	int name##_contains(name* self, itemType value); \
	itemType name##_pop(name* self); \
	itemType name##_peek(name* self);

#define _SP_ARRAY_IMPLEMENT_TYPE(name, itemType) \
	name* name##_create(int initialCapacity) { \
		name* array = MALLOC(name, 1); \
		array->size = 0; \
		array->capacity = initialCapacity; \
		array->items = CALLOC(itemType, initialCapacity); \
		return array; \
	} \
	void name##_dispose(name* self) { \
		FREE(self->items); \
		FREE(self); \
	} \
	void name##_clear(name* self) { \
		self->size = 0; \
	} \
	void name##_setSize(name* self, int newSize) { \
		self->size = newSize; \
		if (self->capacity < newSize) { \
			self->capacity = MAX(8, (int)(self->size * 1.75f)); \
			self->items = REALLOC(self->items, itemType, self->capacity); \
		} \
    } \
	void name##_ensureCapacity(name* self, int newCapacity) { \
		if (self->capacity >= newCapacity) return; \
		self->capacity = newCapacity; \
		self->items = REALLOC(self->items, itemType, self->capacity); \
	} \
	void name##_add(name* self, itemType value) { \
		if (self->size == self->capacity) { \
            self->capacity = MAX(8, (int)(self->size * 1.75f)); \
            self->items = REALLOC(self->items, itemType, self->capacity); \
		} \
		self->items[self->size++] = value; \
    } \
	void name##_removeAt(name* self, int index) { \
		self->size--; \
		memmove(self->items + index, self->items + index + 1, sizeof(itemType) * (self->size - index)); \
		self->items[self->size] = 0; \
    } \
	int name##_contains(name* self, itemType value) { \
		itemType* items = self->items; \
		int i, n; \
		for (i = 0, n = self->size; i < n; i++) { \
			if (items[i] == value) return -1; \
		} \
		return 0; \
	} \
	itemType name##_pop(name* self) { \
		itemType item = self->items[--self->size]; \
		self->items[self->size] = 0; \
		return item; \
	} \
	itemType name##_peek(name* self) { \
		return self->items[self->size - 1]; \
	}

_SP_ARRAY_DECLARE_TYPE(spFloatArray, float)
_SP_ARRAY_DECLARE_TYPE(spIntArray, int)
_SP_ARRAY_DECLARE_TYPE(spShortArray, short)

#ifdef __cplusplus
}
#endif

#endif /* SPINE_ARRAY_H */
