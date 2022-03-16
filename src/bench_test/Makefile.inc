#
# Makefile.am for the Enterprise Management module.
#
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

bin_PROGRAMS += bench_test/bench_test

bench_test_bench_test_CPPFLAGS = \
	$(AM_CPPFLAGS) \
	$(iocore_include_dirs) \
	-I$(abs_top_srcdir)/include \
	-I$(abs_top_srcdir)/lib \
	-I$(abs_top_srcdir)/proxy \
	-I$(abs_top_srcdir)/proxy/http \
	-I$(abs_top_srcdir)/proxy/http2 \
	-I$(abs_top_srcdir)/proxy/http3 \
	-I$(abs_top_srcdir)/proxy/logging \
	-I$(abs_top_srcdir)/proxy/http/remap \
	-I$(abs_top_srcdir)/proxy/hdrs \
	-I$(abs_top_srcdir)/proxy/shared \
	-I$(abs_top_srcdir)/mgmt \
	-I$(abs_top_srcdir)/mgmt/utils \
	$(TS_INCLUDES) \
	@OPENSSL_INCLUDES@ \
	@BORINGOCSP_INCLUDES@

bench_test_bench_test_DFLAGS = \
	$(AM_LDFLAGS) \
	@YAMLCPP_LDFLAGS@ \
	@BORINGOCSP_LDFLAGS@

bench_test_bench_test_SOURCES = \
	bench_test/Crash.cc \
	bench_test/EventName.cc \
	bench_test/EventName.h \
	bench_test/FetchSM.cc \
	bench_test/FetchSM.h \
	bench_test/HostStatus.cc \
	bench_test/InkAPI.cc \
	bench_test/InkIOCoreAPI.cc \
	bench_test/SocksProxy.cc \
	shared/overridable_txn_vars.cc \
	bench_test/bench_test.cc

if BUILD_TESTS
bench_test_bench_test_SOURCES += \
	bench_test/InkAPITest.cc
endif

bench_test_bench_test_LDADD = \
	$(top_builddir)/proxy/http/libhttp.a \
	$(top_builddir)/proxy/http/remap/libhttp_remap.a \
	$(top_builddir)/proxy/http2/libhttp2.a \
	$(top_builddir)/proxy/logging/liblogging.a \
	$(top_builddir)/proxy/hdrs/libhdrs.a \
	$(top_builddir)/proxy/shared/libdiagsconfig.a \
	$(top_builddir)/mgmt/libmgmt_p.la \
	$(top_builddir)/iocore/utils/libinkutils.a \
	$(top_builddir)/iocore/dns/libinkdns.a \
	$(top_builddir)/iocore/hostdb/libinkhostdb.a \
	$(top_builddir)/iocore/dns/libinkdns.a \
	$(top_builddir)/iocore/cache/libinkcache.a \
	$(top_builddir)/lib/fastlz/libfastlz.a \
	$(top_builddir)/iocore/aio/libinkaio.a \
	$(top_builddir)/src/tscore/libtscore.la \
	$(top_builddir)/src/tscpp/util/libtscpputil.la \
	$(top_builddir)/proxy/libproxy.a \
	$(top_builddir)/iocore/net/libinknet.a \
	$(top_builddir)/lib/records/librecords_p.a \
	$(top_builddir)/iocore/eventsystem/libinkevent.a \
	@HWLOC_LIBS@ \
	@LIBPCRE@ \
	@LIBRESOLV@ \
	@LIBZ@ \
	@LIBLZMA@ \
	@LIBPROFILER@ \
	@OPENSSL_LIBS@ \
	@YAMLCPP_LIBS@ \
	@BORINGOCSP_LIBS@ \
	-lm \
	-lbenchmark

if IS_DARWIN
bench_test_bench_test_LDADD += $(LUAJIT_DARWIN_LDFLAGS)
endif

if ENABLE_QUIC
bench_test_bench_test_LDADD += \
  $(top_builddir)/proxy/http3/libhttp3.a \
  $(top_builddir)/iocore/net/quic/libquic.a
endif
