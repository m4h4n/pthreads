/*
  +----------------------------------------------------------------------+
  | pthreads                                                             |
  +----------------------------------------------------------------------+
  | Copyright (c) Joe Watkins 2012                                		 |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Joe Watkins <joe.watkins@live.co.uk>                         |
  +----------------------------------------------------------------------+
 */
#ifndef HAVE_PTHREADS_OBJECT_H
#define HAVE_PTHREADS_OBJECT_H

/*
* @TODO
*	implement verbose debugging mode in threads
*	try and find a way a thread can throw an exception in cid so that ThreadingException can be implemented and not just cause deadlocks
*/

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

#ifndef HAVE_PTHREADS_H
#	include <src/pthreads.h>
#endif

#ifndef HAVE_PTHREADS_THREAD_H
#	include <src/thread.h>
#endif

/* {{{ object creation and destruction */
zend_object_value pthreads_connection_stackable_ctor(zend_class_entry *entry TSRMLS_DC);
zend_object_value pthreads_object_stackable_ctor(zend_class_entry *entry TSRMLS_DC);
zend_object_value pthreads_connection_worker_ctor(zend_class_entry *entry TSRMLS_DC);
zend_object_value pthreads_object_worker_ctor(zend_class_entry *entry TSRMLS_DC);
zend_object_value pthreads_connection_thread_ctor(zend_class_entry *entry TSRMLS_DC);
zend_object_value pthreads_object_thread_ctor(zend_class_entry *entry TSRMLS_DC);
void pthreads_base_ctor(PTHREAD base, zend_class_entry *entry TSRMLS_DC);
void pthreads_base_dtor(void *arg TSRMLS_DC);
void * PHP_PTHREAD_ROUTINE(void *);
/* }}} */

/*
* @NOTE
*	pthreads_state_* functions work with pthreads_state directly
*	pthreads_*_state functions work with specific PTHREAD state
*/

/* {{{ state and stack management */
int pthreads_set_state_ex(PTHREAD thread, int state, long timeout TSRMLS_DC);
int pthreads_set_state(PTHREAD thread, int state TSRMLS_DC);
int pthreads_unset_state(PTHREAD thread, int state TSRMLS_DC);
int pthreads_import(PTHREAD thread, zval** return_value TSRMLS_DC);
int pthreads_stack_pop(PTHREAD thread, PTHREAD work TSRMLS_DC);
int pthreads_stack_push(PTHREAD thread, PTHREAD work TSRMLS_DC);
int pthreads_stack_next(PTHREAD thread, zval *this_ptr TSRMLS_DC);
int pthreads_stack_length(PTHREAD thread TSRMLS_DC);
/* }}} */

/* {{{ TSRM manipulation */
#define PTHREADS_FETCH_ALL(ls, id, type) ((type) (*((void ***) ls))[TSRM_UNSHUFFLE_RSRC_ID(id)])
#define PTHREADS_FETCH_CTX(ls, id, type, element) (((type) (*((void ***) ls))[TSRM_UNSHUFFLE_RSRC_ID(id)])->element)
#define PTHREADS_CG(ls, v) PTHREADS_FETCH_CTX(ls, compiler_globals_id, zend_compiler_globals*, v)
#define PTHREADS_CG_ALL(ls) PTHREADS_FETCH_ALL(ls, compiler_globals_id, zend_compiler_globals*)
#define PTHREADS_EG(ls, v) PTHREADS_FETCH_CTX(ls, executor_globals_id, zend_executor_globals*, v)
#define PTHREADS_SG(ls, v) PTHREADS_FETCH_CTX(ls, sapi_globals_id, sapi_globals_struct*, v)
#define PTHREADS_EG_ALL(ls) PTHREADS_FETCH_ALL(ls, executor_globals_id, zend_executor_globals*) 
/* }}} */

/* {{{ fetches a PTHREAD from a specific object in a specific context */
#define PTHREADS_FETCH_FROM_EX(object, ls) (PTHREAD) zend_object_store_get_object(object, ls) /* }}} */

/* {{{ fetches a PTHREAD from a specific object in the current context */
#define PTHREADS_FETCH_FROM(object) (PTHREAD) zend_object_store_get_object(object TSRMLS_CC) /* }}} */

/* {{{ fetches the current PTHREAD from $this */
#define PTHREADS_FETCH (PTHREAD) zend_object_store_get_object(this_ptr TSRMLS_CC) /* }}} */

/* {{{ handlers included here for access to macros above */
#ifndef HAVE_PTHREADS_HANDLERS_H
#	include <src/handlers.h>
#endif /* }}} */

#endif /* HAVE_PTHREADS_OBJECT_H */
