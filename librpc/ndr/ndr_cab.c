/*
   Unix SMB/CIFS implementation.

   routines for marshalling/unmarshalling cab structures

   Copyright (C) Guenther Deschner 2016

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "includes.h"
#include "librpc/gen_ndr/ndr_cab.h"

_PUBLIC_ void ndr_print_cf_time(struct ndr_print *ndr, const char *name, const struct cf_time *r)
{
	uint8_t hour = 0, minute = 0, seconds = 0;
	char *s;
	if (r == NULL) { ndr_print_null(ndr); return; }
	hour = r->time >> 11;
	minute = (r->time >> 5) & 0x3f;
	seconds = (r->time << 1) & 0x3e;
	s = talloc_asprintf(ndr, "%02d:%02d:%02d", hour, minute, seconds);
	if (s == NULL) { return; }
	ndr_print_string(ndr, "time", s);
	talloc_free(s);
}

_PUBLIC_ void ndr_print_cf_date(struct ndr_print *ndr, const char *name, const struct cf_date *r)
{
	uint16_t year = 0;
	uint8_t month = 0, day = 0;
	char *s;
	if (r == NULL) { ndr_print_null(ndr); return; }
	year = (r->date >> 9);
	year += 1980;
	month = (r->date >> 5 & 0xf);
	day = (r->date & 0x1f);
	s = talloc_asprintf(ndr, "%02d/%02d/%04d", day, month, year);
	if (s == NULL) { return; }
	ndr_print_string(ndr, "date", s);
	talloc_free(s);
}

uint32_t ndr_count_cfdata(const struct cab_file *r)
{
	uint32_t count = 0, i;

	for (i = 0; i < r->cfheader.cFolders; i++) {
		count += r->cffolders[i].cCFData;
	}

	return count;
}

_PUBLIC_ enum ndr_err_code ndr_push_cab_file(struct ndr_push *ndr, int ndr_flags, const struct cab_file *r)
{
	uint32_t cntr_cffolders_0;
	uint32_t cntr_cffiles_0;
	uint32_t cntr_cfdata_0;
	{
		uint32_t _flags_save_STRUCT = ndr->flags;
		ndr_set_flags(&ndr->flags, LIBNDR_PRINT_ARRAY_HEX|LIBNDR_FLAG_LITTLE_ENDIAN|LIBNDR_FLAG_NOALIGN);
		NDR_PUSH_CHECK_FLAGS(ndr, ndr_flags);
		if (ndr_flags & NDR_SCALARS) {
			NDR_CHECK(ndr_push_align(ndr, 4));
			NDR_CHECK(ndr_push_CFHEADER(ndr, NDR_SCALARS, &r->cfheader));
			for (cntr_cffolders_0 = 0; cntr_cffolders_0 < (r->cfheader.cFolders); cntr_cffolders_0++) {
				NDR_CHECK(ndr_push_CFFOLDER(ndr, NDR_SCALARS, &r->cffolders[cntr_cffolders_0]));
			}
			for (cntr_cffiles_0 = 0; cntr_cffiles_0 < (r->cfheader.cFiles); cntr_cffiles_0++) {
				NDR_CHECK(ndr_push_CFFILE(ndr, NDR_SCALARS, &r->cffiles[cntr_cffiles_0]));
			}
#if 0
			NDR_CHECK(ndr_push_uint32(ndr, NDR_SCALARS, ndr_count_cfdata(r)));
#endif
			for (cntr_cfdata_0 = 0; cntr_cfdata_0 < (ndr_count_cfdata(r)); cntr_cfdata_0++) {
				NDR_CHECK(ndr_push_CFDATA(ndr, NDR_SCALARS, &r->cfdata[cntr_cfdata_0]));
			}
			NDR_CHECK(ndr_push_trailer_align(ndr, 4));
		}
		if (ndr_flags & NDR_BUFFERS) {
		}
		ndr->flags = _flags_save_STRUCT;
	}
	return NDR_ERR_SUCCESS;
}

_PUBLIC_ enum ndr_err_code ndr_pull_cab_file(struct ndr_pull *ndr, int ndr_flags, struct cab_file *r)
{
	uint32_t size_cffolders_0 = 0;
	uint32_t cntr_cffolders_0;
	TALLOC_CTX *_mem_save_cffolders_0 = NULL;
	uint32_t size_cffiles_0 = 0;
	uint32_t cntr_cffiles_0;
	TALLOC_CTX *_mem_save_cffiles_0 = NULL;
	uint32_t size_cfdata_0 = 0;
	uint32_t cntr_cfdata_0;
	TALLOC_CTX *_mem_save_cfdata_0 = NULL;
	{
		uint32_t _flags_save_STRUCT = ndr->flags;
		ndr_set_flags(&ndr->flags, LIBNDR_PRINT_ARRAY_HEX|LIBNDR_FLAG_LITTLE_ENDIAN|LIBNDR_FLAG_NOALIGN);
		NDR_PULL_CHECK_FLAGS(ndr, ndr_flags);
		if (ndr_flags & NDR_SCALARS) {
			NDR_CHECK(ndr_pull_align(ndr, 4));
			NDR_CHECK(ndr_pull_CFHEADER(ndr, NDR_SCALARS, &r->cfheader));
			size_cffolders_0 = r->cfheader.cFolders;
			NDR_PULL_ALLOC_N(ndr, r->cffolders, size_cffolders_0);
			_mem_save_cffolders_0 = NDR_PULL_GET_MEM_CTX(ndr);
			NDR_PULL_SET_MEM_CTX(ndr, r->cffolders, 0);
			for (cntr_cffolders_0 = 0; cntr_cffolders_0 < (size_cffolders_0); cntr_cffolders_0++) {
				NDR_CHECK(ndr_pull_CFFOLDER(ndr, NDR_SCALARS, &r->cffolders[cntr_cffolders_0]));
			}
			NDR_PULL_SET_MEM_CTX(ndr, _mem_save_cffolders_0, 0);
			size_cffiles_0 = r->cfheader.cFiles;
			NDR_PULL_ALLOC_N(ndr, r->cffiles, size_cffiles_0);
			_mem_save_cffiles_0 = NDR_PULL_GET_MEM_CTX(ndr);
			NDR_PULL_SET_MEM_CTX(ndr, r->cffiles, 0);
			for (cntr_cffiles_0 = 0; cntr_cffiles_0 < (size_cffiles_0); cntr_cffiles_0++) {
				NDR_CHECK(ndr_pull_CFFILE(ndr, NDR_SCALARS, &r->cffiles[cntr_cffiles_0]));
			}
			NDR_PULL_SET_MEM_CTX(ndr, _mem_save_cffiles_0, 0);
#if 0
			NDR_CHECK(ndr_pull_uint32(ndr, NDR_SCALARS, &r->cfdata_count));
#else
			r->cfdata_count = ndr_count_cfdata(r);
#endif
			size_cfdata_0 = r->cfdata_count;
			NDR_PULL_ALLOC_N(ndr, r->cfdata, size_cfdata_0);
			_mem_save_cfdata_0 = NDR_PULL_GET_MEM_CTX(ndr);
			NDR_PULL_SET_MEM_CTX(ndr, r->cfdata, 0);
			for (cntr_cfdata_0 = 0; cntr_cfdata_0 < (size_cfdata_0); cntr_cfdata_0++) {
				NDR_CHECK(ndr_pull_CFDATA(ndr, NDR_SCALARS, &r->cfdata[cntr_cfdata_0]));
			}
			NDR_PULL_SET_MEM_CTX(ndr, _mem_save_cfdata_0, 0);
			NDR_CHECK(ndr_pull_trailer_align(ndr, 4));
		}
		if (ndr_flags & NDR_BUFFERS) {
		}
		ndr->flags = _flags_save_STRUCT;
	}
	return NDR_ERR_SUCCESS;
}