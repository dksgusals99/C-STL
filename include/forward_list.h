#ifndef C_STL_FORWARD_LIST_H
#define C_STL_FORWARD_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//매크로로 확장되는, 단방향 연결리스트 유사템플릿입니다.
//단방향 연결리스트의 유사클래스를 생성합니다.
#define decl_forward_list(declname, type) \
\
/*단방향 리스트 유사클래스 전방선언이오*/ \
struct declname; \
typedef struct declname declname; \
\
/*단방향 리스트의 노드 타입이오*/ \
struct declname##_node; \
typedef struct declname##_node declname##_node; \
\
/*전용 반복자 유사클래스 전방선언이오*/ \
struct declname##_iterator; \
typedef struct declname##_iterator declname##_iterator; \
\
\
/*반복자 유사클래스*/ \
struct declname##_iterator \
{ \
  declname##_node* ptr; \
  \
  /*반복을 수행하오*/ \
  void (*next)(declname##_iterator*); \
  /*값이나 그 포인터를 가져오는 것이오*/ \
  type (*get)(const declname##_iterator*); \
  type* (*get_ptr)(declname##_iterator*); \
  const type* (*get_cptr)(const declname##_iterator*); \
  \
    /*두 반복자를 비교할진저!*/ \
  bool (*equals)(const declname##_iterator*, const declname##_iterator*); \
}; \
/*나는 이것을 메서드의 [선언]이라 칭하겠노라.*/ \
void declname##_iterator_next(declname##_iterator*); \
type declname##_iterator_get(const declname##_iterator*); \
type* declname##_iterator_get_ptr(declname##_iterator*); \
const type* declname##_iterator_get_cptr(const declname##_iterator*); \
bool declname##_iterator_equals(const declname##_iterator*, const declname##_iterator*); \
/*비멤버 make 함수요*/ declname##_iterator new_##declname##_iterator(declname##_node*); \
\
\
struct declname##_node \
{ \
  type value; /*값입니다..*/\
  declname##_node* next; /*다음 포인터입니다.*/\
}; \
\
declname##_node* declname##_new_node(const type* v, declname##_node* next) \
{ \
  declname##_node* temp = \
    malloc(sizeof(declname##_node)); \
  temp->value = *v; \
  temp->next = next; \
  return temp; \
} \
\
\
/*실체화되는 연결리스트 유사클래스요*/ \
struct declname \
{ \
  declname##_node* const head; \
  const size_t length; \
  \
  /*객체를 깨끗이 비운다오*/ \
  void (*clear)(declname*); \
  size_t (*size)(const declname*); \
  \
  /*비어있는지 여부를 확인하오*/ \
  bool (*is_empty)(const declname*); \
  bool (*is_not_empty)(const declname*); \
  \
  /*앞에서 접근을 하오*/ \
  type (*front)(const declname*); \
  type* (*front_ptr)(declname*); \
  const type* (*front_cptr)(const declname*); \
  void (*push_front)(declname*, type); \
  void (*pop_front)(declname*); \
  \
  /*특정 반복자 위치 뒤에 값과 함께 노드를 추가하오*/ \
  declname##_iterator (*insert_after)(declname*, declname##_iterator*, const type*); \
  \
  /*반복자를 받아서 그 뒤를 삭제*/ \
  declname##_iterator (*erase_after)(declname*, declname##_iterator*); \
  declname##_iterator (*erase_range)(declname*, declname##_iterator*, declname##_iterator*); \
  \
  /*값에 대응하는 노드 삭제*/ \
  void (*remove)(declname*, type); \
  void (*remove_by)(declname*, bool(*)(const type*)); \
  \
  /*반복자를 반환하오*/ \
  declname##_iterator (*begin)(declname*); \
  declname##_iterator (*end)(declname*); \
  \
  /*선형탐색 후 찾은 위치의 반복자를 반환하오*/ \
  declname##_iterator (*find)(const declname*, const type); \
  declname##_iterator (*find_by)(const declname*, bool(*)(const type*)); \
  \
  /*선형탐색으로 포함 여부를 확인하오*/ \
  bool (*contains)(const declname*, const type); \
  bool (*contains_by)(const declname*, bool(*)(const type*)); \
  \
  /*콜백함수를 받아서 범위기반 루프를 도는 것이오*/ \
  void (*for_each)(const declname*, void(*)(type)); \
  void (*for_each_ptr)(declname*, void(*)(type*)); \
  void (*for_each_cptr)(const declname*, void(*)(const type*)); \
}; \
/*메서드 선언이오*/ \
void declname##_clear(declname*); \
bool declname##_is_empty(const declname*); \
bool declname##_is_not_empty(const declname*); \
type declname##_front(const declname*); \
type* declname##_front_ptr(declname*); \
const type* declname##_front_cptr(const declname*); \
void declname##_push_front(declname*, type); \
void declname##_pop_front(declname*); \
declname##_iterator declname##_insert_after(declname*, declname##_iterator*, const type*); \
declname##_iterator declname##_erase_after(declname*, declname##_iterator*); \
declname##_iterator declname##_erase_range(declname*, declname##_iterator*, declname##_iterator*); \
void declname##_remove(declname*, type); \
void declname##_remove_by(declname*, bool(*)(const type*)); \
size_t declname##_size(const declname*); \
declname##_iterator declname##_begin(declname*); \
declname##_iterator declname##_end(declname*); \
declname##_iterator declname##_find(const declname*, const type); \
declname##_iterator declname##_find_by(const declname*, bool(*)(const type*)); \
bool declname##_contains(const declname*, const type); \
bool declname##_contains_by(const declname*, bool(*)(const type*)); \
void declname##_for_each(const declname*, void(*)(type)); \
void declname##_for_each_ptr(declname*, void(*)(type*)); \
void declname##_for_each_cptr(const declname*, void(*)(const type*)); \
/*비멤버 함수요*/\
declname new_##declname (void); \
\
\
/*이것이 바로... [정의]란 것이다...*/\
void declname##_clear(declname* self)\
{ \
    assert(self!=NULL); \
    while(self->head != NULL) \
      declname##_pop_front(self); \
} \
\
bool declname##_is_empty(const declname* self) \
{ \
    assert(self!=NULL); \
    return self->head == NULL; \
} \
\
bool declname##_is_not_empty(const declname* self) \
{ \
    assert(self!=NULL); \
    return self->head != NULL; \
} \
\
type declname##_front(const declname* self) \
{ \
    assert(self!=NULL); \
    assert(self->head!=NULL); \
    return self->head->value; \
} \
\
type* declname##_front_ptr(declname* self) \
{ \
    assert(self!=NULL); \
    assert(self->head!=NULL); \
    return &(self->head->value); \
} \
\
const type* declname##_front_cptr(const declname* self) \
{ \
    assert(self!=NULL); \
    assert(self->head!=NULL); \
  return &(self->head->value); \
} \
\
void declname##_push_front(declname* self, type v) \
{ \
    *(declname##_node**)&self->head = declname##_new_node(&v,self->head); \
    ++ *(size_t*)&self->length; \
} \
\
void declname##_pop_front(declname* self) \
{ \
    assert(self!=NULL); \
    assert(self->head!=NULL); \
    \
    declname##_node* temp = self->head; \
    if(self->head->next != NULL) \
        *(declname##_node**)&self->head = self->head->next; \
    free(temp); \
    -- *(size_t*)&self->length; \
} \
\
declname##_iterator declname##_insert_after(declname* self, declname##_iterator* pos, const type*v) \
{ \
    assert(pos->ptr!=NULL); \
    if(pos->ptr!=NULL) \
    { \
      declname##_node* after = pos->ptr->next; \
      after = declname##_new_node(v, after->next); \
      return new_##declname##_iterator(after); \
    } \
    else \
      return declname##_end(self); \
} \
\
declname##_iterator declname##_erase_after(declname* self, declname##_iterator* pos) \
{ \
    assert(pos->ptr!=NULL); \
    declname##_node* after = pos->ptr->next; \
    assert(after!=NULL); \
    pos->ptr->next = after->next; \
    free(after); \
    return new_##declname##_iterator(after->next); \
} \
\
declname##_iterator declname##_erase_range(declname* self, declname##_iterator* begin, declname##_iterator* end) \
{ \
  assert(begin->ptr!=NULL); \
  declname##_node* before = begin->ptr; \
  declname##_node* after = end->ptr; \
  before->next = after; \
  declname##_iterator_next(begin); \
  while(!declname##_iterator_equals(begin, end)) \
	{ \
		free(begin->ptr); \
		declname##_iterator_next(begin); \
	} \
	\
	return new_##declname##_iterator(after); \
} \
\
void declname##_remove(declname* self, type v) \
{ \
  declname##_node* current_pos = self->head; \
  declname##_node* before = NULL; \
  while(current_pos!=NULL) \
  { \
    if(current_pos->value == v) \
    { \
      if(before!=NULL) \
        before->next = current_pos->next; \
      free(current_pos); \
    } \
    \
    before = current_pos; \
    current_pos = current_pos->next; \
  } \
} \
\
void declname##_remove_by(declname* self, bool(*eq)(const type*)) \
{ \
  declname##_node* current_pos = self->head; \
  declname##_node* before = NULL; \
  while(current_pos!=NULL) \
  { \
    if(eq(&current_pos->value)) \
    { \
      if(before!=NULL) \
        before->next = current_pos->next; \
      free(current_pos); \
    } \
    \
    before = current_pos; \
    current_pos = current_pos->next; \
  } \
} \
\
size_t declname##_size(const declname* self) \
{ \
  return self->length; \
} \
\
declname##_iterator declname##_begin(declname* self) \
{ \
  declname##_iterator it = \
    new_##declname##_iterator(self->head); \
  return it; \
} \
\
declname##_iterator declname##_end(declname* self) \
{ \
  declname##_iterator it = \
    new_##declname##_iterator(NULL); \
  return it; \
} \
\
declname##_iterator declname##_find(const declname* self, const type key) \
{ \
  const declname##_node* current_pos = self->head; \
  while(current_pos!=NULL) \
    if(current_pos->value == key) \
      return new_##declname##_iterator((declname##_node*)current_pos); \
    else \
      current_pos = current_pos->next; \
  \
  return self->end((declname*)&self); \
} \
\
declname##_iterator declname##_find_by(const declname* self, bool(*eq)(const type*)) \
{ \
  const declname##_node* current_pos = self->head; \
  while(current_pos!=NULL) \
    if(eq(&current_pos->value)) \
      return new_##declname##_iterator((declname##_node*)current_pos); \
    else \
      current_pos = current_pos->next; \
  \
  return self->end((declname*)&self); \
} \
\
int declname##_comparer(const void* lhs, const void* rhs) \
{ \
  return *(type*)lhs - *(type*)rhs; \
} \
\
bool declname##_contains(const declname* self, const type key) \
{ \
  const declname##_node* current_pos = self->head; \
  while(current_pos!=NULL) \
    if(current_pos->value == key) \
      return true; \
    else \
      current_pos = current_pos->next; \
  \
  return false; \
} \
\
bool declname##_contains_by(const declname* self, bool(*eq)(const type*)) \
{ \
  const declname##_node* current_pos = self->head; \
  while(current_pos!=NULL) \
    if(eq(&current_pos->value)) \
      return true; \
    else \
      current_pos = current_pos->next; \
  \
  return false; \
} \
\
void declname##_for_each(const declname* self, void(*f)(type)) \
{ \
  const declname##_node* current_pos = self->head; \
  while(current_pos!=NULL) \
  { \
    f(current_pos->value); \
    current_pos = current_pos->next; \
  } \
} \
\
void declname##_for_each_ptr(declname* self, void(*f)(type*)) \
{ \
  declname##_node* current_pos = self->head; \
  while(current_pos!=NULL) \
  { \
    f(& current_pos->value); \
    current_pos = current_pos->next; \
  } \
} \
\
void declname##_for_each_cptr(const declname* self, void(*f)(const type*)) \
{ \
  const declname##_node* current_pos = self->head; \
  while(current_pos!=NULL) \
  { \
    f(& current_pos->value); \
    current_pos = current_pos->next; \
  } \
} \
\
\
declname new_##declname (void) \
{ \
  static declname temp = \
  { \
    .head = NULL, \
    .length = 0, \
    .clear = declname##_clear, \
    .is_empty = declname##_is_empty, \
    .is_not_empty = declname##_is_not_empty, \
    .front = declname##_front, \
    .front_ptr = declname##_front_ptr, \
    .front_cptr = declname##_front_cptr, \
    .push_front = declname##_push_front, \
    .pop_front = declname##_pop_front, \
    .insert_after = declname##_insert_after, \
    .erase_after = declname##_erase_after, \
    .erase_range = declname##_erase_range, \
    .remove = declname##_remove, \
    .remove_by = declname##_remove_by, \
    .size = declname##_size, \
    .begin = declname##_begin, \
    .end = declname##_end, \
    .find = declname##_find, \
    .find_by = declname##_find_by, \
    .contains = declname##_contains, \
    .contains_by = declname##_contains_by, \
    .for_each = declname##_for_each, \
    .for_each_ptr = declname##_for_each_ptr, \
    .for_each_cptr = declname##_for_each_cptr \
  }; \
  return temp; \
} \
\
\
/*이제부터 반복자 메서드 정의요*/\
void declname##_iterator_next(declname##_iterator* self) \
{ \
    assert(self->ptr!=NULL); \
    if(self->ptr->next!=NULL) \
    self->ptr = self->ptr->next; \
} \
\
type declname##_iterator_get(const declname##_iterator* self) \
{ \
    assert(self->ptr!=NULL); \
    return self->ptr->value; \
} \
type* declname##_iterator_get_ptr(declname##_iterator* self) \
{ \
    assert(self->ptr!=NULL); \
    return &(self->ptr->value); \
} \
const type* declname##_iterator_get_cptr(const declname##_iterator* self) \
{ \
    assert(self->ptr!=NULL); \
  return &(self->ptr->value); \
} \
\
bool declname##_iterator_equals(const declname##_iterator* self, const declname##_iterator* other) \
{ \
  return self->ptr == other->ptr; \
} \
\
declname##_iterator new_##declname##_iterator(declname##_node* p) \
{ \
  static declname##_iterator it = \
  { \
    .ptr = NULL, \
    .next = declname##_iterator_next, \
    .get = declname##_iterator_get, \
    .get_ptr = declname##_iterator_get_ptr, \
    .get_cptr = declname##_iterator_get_cptr, \
    .equals = declname##_iterator_equals, \
  }; \
  it.ptr = p; \
  return it; \
}

#endif