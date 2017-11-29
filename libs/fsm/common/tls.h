#pragma once

#ifdef WIN32
#include <log4cplus/config/windowsh-inc.h>
typedef DWORD tls_key_type;

#else
#include <pthread.h>
typedef pthread_key_t * tls_key_type;
typedef void * tls_value_type;

#endif

namespace fsm {
	typedef void(*tls_init_cleanup_func_type)(void *);

	inline tls_key_type tls_init(tls_init_cleanup_func_type);
	inline void * tls_get_value(tls_key_type);
	inline void tls_set_value(tls_key_type, void *);
	inline void tls_cleanup(tls_key_type);


#if defined (WIN32)

	tls_key_type
		tls_init(tls_init_cleanup_func_type)
	{
		return TlsAlloc();
	}


	void * tls_get_value(tls_key_type k)
	{
		return TlsGetValue(k);
	}


	void
		tls_set_value(tls_key_type k, void * value)
	{
		TlsSetValue(k, value);
	}


	void
		tls_cleanup(tls_key_type k)
	{
		TlsFree(k);
	}

#else 
	tls_key_type
		tls_init(tls_init_cleanup_func_type cleanupfunc)
	{
		pthread_key_t * key = new pthread_key_t;
		pthread_key_create(key, cleanupfunc);
		return key;
	}


	tls_value_type
		tls_get_value(tls_key_type key)
	{
		return pthread_getspecific(*key);
	}


	void
		tls_set_value(tls_key_type key, tls_value_type value)
	{
		pthread_setspecific(*key, value);
	}


	void
		tls_cleanup(tls_key_type key)
	{
		pthread_key_delete(*key);
		delete key;
	}

#endif
}