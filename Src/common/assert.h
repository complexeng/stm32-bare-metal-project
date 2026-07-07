#ifndef ASSERT_H
#define ASSERT_H

#define ASSERT(condition) if (!(condition)) { assert_handler(); }

void assert_handler(void);

#endif
