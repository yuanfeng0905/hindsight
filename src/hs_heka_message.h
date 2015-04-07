/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/** Hindsight Heka message representation @file */

#ifndef hs_heka_message_h_
#define hs_heka_message_h_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
  HS_FIELD_STRING,
  HS_FIELD_BYTES,
  HS_FIELD_INTEGER,
  HS_FIELD_DOUBLE,
  HS_FIELD_BOOL
} hs_field_value_type;


typedef enum {
  HS_HEKA_UUID = 1,
  HS_HEKA_TIMESTAMP = 2,
  HS_HEKA_TYPE = 3,
  HS_HEKA_LOGGER = 4,
  HS_HEKA_SEVERITY = 5,
  HS_HEKA_PAYLOAD = 6,
  HS_HEKA_ENV_VERSION = 7,
  HS_HEKA_PID = 8,
  HS_HEKA_HOSTNAME = 9,
  HS_HEKA_FIELD = 10
} hs_heka_pb_id;


typedef struct hs_heka_field
{
  const char* name;
  const char* representation;
  const unsigned char* value;

  int name_len;
  int representation_len;
  int value_len;
  int value_items;
  hs_field_value_type value_type;
} hs_heka_field;


typedef struct hs_heka_message
{
  const char* uuid;
  const char* type;
  const char* logger;
  const char* payload;
  const char* env_version;
  const char* hostname;
  hs_heka_field* fields;

  int64_t timestamp;
  int32_t severity;
  int32_t pid;

  int type_len;
  int logger_len;
  int payload_len;
  int env_version_len;
  int hostname_len;
  int fields_len;
  int fields_size;

} hs_heka_message;


void hs_init_heka_message(hs_heka_message* m, size_t size);
void hs_clear_heka_message(hs_heka_message* m);
bool hs_decode_heka_message(hs_heka_message* m,
                            const unsigned char* buf,
                            size_t len);
bool hs_read_numeric_field(hs_heka_message* m,
                           const char* name,
                           size_t nlen,
                           int fi,
                           int ai,
                           double* val);
bool hs_read_string_field(hs_heka_message* m,
                          const char* name,
                          size_t nlen,
                          int fi,
                          int ai,
                          const char** val,
                          size_t* vlen);
void hs_free_heka_message(hs_heka_message* m);

#endif