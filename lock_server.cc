// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

lock_server::lock_server():
  nacquire (0)
{
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);
}

lock_protocol::status
lock_server::stat(int clt, lock_protocol::lockid_t lid, int &r)
{
  lock_protocol::status ret = lock_protocol::OK;
  printf("stat request from clt %d\n", clt);
  r = nacquire;
  return ret;
}

lock_protocol::status
lock_server::acquire(int clt, lock_protocol::lockid_t lid, int &r)
{
  lock_protocol::status ret = lock_protocol::OK;
	// Your lab2 part2 code goes here
  // printf("acquire request from clt %d\n", clt);
  pthread_mutex_lock(&mutex);
  if (locks.find(lid) != locks.end()) {
    while (locks[lid]) {
      pthread_cond_wait(&cond, &mutex);
    }
  }
  locks[lid] = true;
  pthread_mutex_unlock(&mutex);
  return ret;
}

lock_protocol::status
lock_server::release(int clt, lock_protocol::lockid_t lid, int &r)
{
  lock_protocol::status ret = lock_protocol::OK;
	// Your lab2 part2 code goes here
  // printf("release request from clt %d\n", clt);
  pthread_mutex_lock(&mutex);
  if (locks.find(lid) == locks.end()) {
    ret = lock_protocol::NOENT;
  }
  else {
    locks[lid] = false;
    pthread_cond_signal(&cond);
  }
  pthread_mutex_unlock(&mutex);
  return ret;
}
