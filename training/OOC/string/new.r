#ifndef NEW_R
#define NEW_R

/* Private class definition */
struct Class {
	size_t size;
	void * (*ctor)(void *self, va_list *app);
	void * (*dtor)(void *self);
	void * (*clone)(const void *self);
	int (*differ)(const void *self, const void *b);
};

#endif
