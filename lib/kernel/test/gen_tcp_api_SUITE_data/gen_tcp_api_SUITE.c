/*
 * %CopyrightBegin%
 *
 * Copyright Ericsson AB 2009-2013. All Rights Reserved.
 *
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * %CopyrightEnd%
 */
#include "erl_nif.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <sys/socket.h>
#include <sys/types.h>

#ifdef __WIN32__
#include <winsock2.h>
#else

#endif

#define sock_open(af, type, proto)  socket((af), (type), (proto))

static ERL_NIF_TERM getsockfd(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    int fd;

    fd = sock_open(AF_INET, SOCK_STREAM, 0);
    return enif_make_int(env, fd);
}

static ERL_NIF_TERM closesockfd(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    int fd;

    enif_get_int(env, argv[0], &fd);

    close(fd);

    return enif_make_int(env, fd);
}

static ErlNifFunc nif_funcs[] =
{
    {"getsockfd", 0, getsockfd},
    {"closesockfd", 1, closesockfd}
};

ERL_NIF_INIT(gen_tcp_api_SUITE,nif_funcs,NULL,NULL,NULL,NULL)
