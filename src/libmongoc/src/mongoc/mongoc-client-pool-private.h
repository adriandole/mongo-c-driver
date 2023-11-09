/*
 * Copyright 2015 MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mongoc-prelude.h"

#ifndef MONGOC_CLIENT_POOL_PRIVATE_H
#define MONGOC_CLIENT_POOL_PRIVATE_H

#include <bson/bson.h>

#include "mongoc-client-pool.h"
#include "mongoc-queue-private.h"
#include "mongoc-topology-description.h"
#include "mongoc-topology-private.h"

BSON_BEGIN_DECLS
typedef struct _mongoc_client_pool_t {
   bson_mutex_t mutex;
   mongoc_cond_t cond;
   mongoc_queue_t queue;
   mongoc_topology_t *topology;
   mongoc_uri_t *uri;
   uint32_t min_pool_size;
   uint32_t max_pool_size;
   uint32_t size;
#ifdef MONGOC_ENABLE_SSL
   bool ssl_opts_set;
   mongoc_ssl_opt_t ssl_opts;
#endif
   bool apm_callbacks_set;
   mongoc_apm_callbacks_t apm_callbacks;
   void *apm_context;
   int32_t error_api_version;
   bool error_api_set;
   mongoc_server_api_t *api;
   bool client_initialized;
   mongoc_set_t *clients;
   uint32_t client_counter;
} _mongoc_client_pool_t;


/* for tests */
void
_mongoc_client_pool_set_stream_initiator (mongoc_client_pool_t *pool,
                                          mongoc_stream_initiator_t si,
                                          void *user_data);
size_t
mongoc_client_pool_get_size (mongoc_client_pool_t *pool);
size_t
mongoc_client_pool_num_pushed (mongoc_client_pool_t *pool);
mongoc_topology_t *
_mongoc_client_pool_get_topology (mongoc_client_pool_t *pool);

BSON_END_DECLS


#endif /* MONGOC_CLIENT_POOL_PRIVATE_H */
