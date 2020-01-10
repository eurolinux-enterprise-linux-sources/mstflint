/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/***
         *** This file was generated at "2016-11-06 15:18:05"
         *** by:
         ***    > /mswg/release/eat_me/last_release/adabe_plugins/adb2c/adb2pack.py --input adb/cx4fw/cx4fw.adb --file-prefix cx4fw --prefix cx4fw_
         ***/
#include "cx4fw_layouts.h"

void cx4fw_uid_entry_pack(const struct cx4fw_uid_entry *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->num_allocated);

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->step);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->uid);

}

void cx4fw_uid_entry_unpack(struct cx4fw_uid_entry *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 24;
	ptr_struct->num_allocated = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 16;
	ptr_struct->step = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 64;
	ptr_struct->uid = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

}

void cx4fw_uid_entry_print(const struct cx4fw_uid_entry *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx4fw_uid_entry ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "num_allocated        : " UH_FMT "\n", ptr_struct->num_allocated);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "step                 : " UH_FMT "\n", ptr_struct->step);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "uid                  : " U64H_FMT "\n", ptr_struct->uid);

}

int cx4fw_uid_entry_size(void)
{
	 return 16;
}

void cx4fw_uid_entry_dump(const struct cx4fw_uid_entry *ptr_struct, FILE* file)
{
	cx4fw_uid_entry_print(ptr_struct, file, 0);
}

void cx4fw_guids_pack(const struct cx4fw_guids *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx4fw_uid_entry_pack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 128;
	cx4fw_uid_entry_pack(&(ptr_struct->macs), ptr_buff + offset/8);

}

void cx4fw_guids_unpack(struct cx4fw_guids *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	cx4fw_uid_entry_unpack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 128;
	cx4fw_uid_entry_unpack(&(ptr_struct->macs), ptr_buff + offset/8);

}

void cx4fw_guids_print(const struct cx4fw_guids *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx4fw_guids ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cx4fw_uid_entry_print(&(ptr_struct->guids), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "macs:\n");
	cx4fw_uid_entry_print(&(ptr_struct->macs), file, indent_level + 1);

}

int cx4fw_guids_size(void)
{
	 return 64;
}

void cx4fw_guids_dump(const struct cx4fw_guids *ptr_struct, FILE* file)
{
	cx4fw_guids_print(ptr_struct, file, 0);
}

void cx4fw_operation_key_pack(const struct cx4fw_operation_key *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->key_modifier);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 8, ptr_struct->key);

}

void cx4fw_operation_key_unpack(struct cx4fw_operation_key *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 16;
	ptr_struct->key_modifier = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	offset = 64;
	ptr_struct->key = adb2c_pop_integer_from_buff(ptr_buff, offset, 8);

}

void cx4fw_operation_key_print(const struct cx4fw_operation_key *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx4fw_operation_key ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "key_modifier         : " UH_FMT "\n", ptr_struct->key_modifier);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "key                  : " U64H_FMT "\n", ptr_struct->key);

}

int cx4fw_operation_key_size(void)
{
	 return 16;
}

void cx4fw_operation_key_dump(const struct cx4fw_operation_key *ptr_struct, FILE* file)
{
	cx4fw_operation_key_print(ptr_struct, file, 0);
}

void cx4fw_mfg_info_pack(const struct cx4fw_mfg_info *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i = 0; i < 16; i++) {
	offset = adb2c_calc_array_field_address(24, 8, i, 2560, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->psid[i]);
	}

	offset = 255;
	adb2c_push_bits_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->guids_override_en);

	offset = 232;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);

	offset = 224;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->major_version);

	offset = 256;
	cx4fw_guids_pack(&(ptr_struct->guids), ptr_buff + offset/8);

}

void cx4fw_mfg_info_unpack(struct cx4fw_mfg_info *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i = 0; i < 16; i++) {
	offset = adb2c_calc_array_field_address(24, 8, i, 2560, 1);
	ptr_struct->psid[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->psid[16] = '\0';
	offset = 255;
	ptr_struct->guids_override_en = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 1);

	offset = 232;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 224;
	ptr_struct->major_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 256;
	cx4fw_guids_unpack(&(ptr_struct->guids), ptr_buff + offset/8);

}

void cx4fw_mfg_info_print(const struct cx4fw_mfg_info *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx4fw_mfg_info ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	fprintf(file, "psid                 : \"%s\"\n", ptr_struct->psid);
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids_override_en    : " UH_FMT "\n", ptr_struct->guids_override_en);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major_version        : " UH_FMT "\n", ptr_struct->major_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cx4fw_guids_print(&(ptr_struct->guids), file, indent_level + 1);

}

int cx4fw_mfg_info_size(void)
{
	 return 320;
}

void cx4fw_mfg_info_dump(const struct cx4fw_mfg_info *ptr_struct, FILE* file)
{
	cx4fw_mfg_info_print(ptr_struct, file, 0);
}

void cx4fw_device_info_pack(const struct cx4fw_device_info *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature0);

	offset = 32;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature1);

	offset = 64;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature2);

	offset = 96;
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature3);

	offset = 152;
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->minor_version);

	offset = 143;
	adb2c_push_bits_to_buff(ptr_buff, offset, 9, (u_int32_t)ptr_struct->major_version);

	offset = 256;
	cx4fw_guids_pack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 880;
	adb2c_push_bits_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->vsd_vendor_id);

	for (i = 0; i < 208; i++) {
	offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
	adb2c_push_bits_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->vsd[i]);
	}

	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
	cx4fw_operation_key_pack(&(ptr_struct->keys[i]), ptr_buff + offset/8);
	}

}

void cx4fw_device_info_unpack(struct cx4fw_device_info *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	offset = 0;
	ptr_struct->signature0 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 32;
	ptr_struct->signature1 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 64;
	ptr_struct->signature2 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 96;
	ptr_struct->signature3 = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);

	offset = 152;
	ptr_struct->minor_version = (u_int8_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);

	offset = 143;
	ptr_struct->major_version = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 9);

	offset = 256;
	cx4fw_guids_unpack(&(ptr_struct->guids), ptr_buff + offset/8);

	offset = 880;
	ptr_struct->vsd_vendor_id = (u_int16_t)adb2c_pop_bits_from_buff(ptr_buff, offset, 16);

	for (i = 0; i < 208; i++) {
	offset = adb2c_calc_array_field_address(920, 8, i, 4096, 1);
	ptr_struct->vsd[i] = (char)adb2c_pop_bits_from_buff(ptr_buff, offset, 8);
	}

	ptr_struct->vsd[208] = '\0';
	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(2816, 128, i, 4096, 1);
	cx4fw_operation_key_unpack(&(ptr_struct->keys[i]), ptr_buff + offset/8);
	}

}

void cx4fw_device_info_print(const struct cx4fw_device_info *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx4fw_device_info ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature0           : " U32H_FMT "\n", ptr_struct->signature0);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature1           : " U32H_FMT "\n", ptr_struct->signature1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature2           : " U32H_FMT "\n", ptr_struct->signature2);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature3           : " U32H_FMT "\n", ptr_struct->signature3);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "minor_version        : " UH_FMT "\n", ptr_struct->minor_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "major_version        : " UH_FMT "\n", ptr_struct->major_version);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cx4fw_guids_print(&(ptr_struct->guids), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "vsd_vendor_id        : " UH_FMT "\n", ptr_struct->vsd_vendor_id);

	fprintf(file, "vsd                  : \"%s\"\n", ptr_struct->vsd);
	for (i = 0; i < 4; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "keys_%03d:\n", i);
	cx4fw_operation_key_print(&(ptr_struct->keys[i]), file, indent_level + 1);
	}

}

int cx4fw_device_info_size(void)
{
	 return 512;
}

void cx4fw_device_info_dump(const struct cx4fw_device_info *ptr_struct, FILE* file)
{
	cx4fw_device_info_print(ptr_struct, file, 0);
}

void cx4fw_image_signature_pack(const struct cx4fw_image_signature *ptr_struct, u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(0, 32, i, 2560, 1);
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature_uuid[i]);
	}

	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(128, 32, i, 2560, 1);
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->keypair_uuid[i]);
	}

	for (i = 0; i < 64; i++) {
	offset = adb2c_calc_array_field_address(256, 32, i, 2560, 1);
	adb2c_push_integer_to_buff(ptr_buff, offset, 4, (u_int32_t)ptr_struct->signature[i]);
	}

}

void cx4fw_image_signature_unpack(struct cx4fw_image_signature *ptr_struct, const u_int8_t* ptr_buff)
{
	u_int32_t offset;
	int i = 0;
	(void)offset;
	(void)i;
	(void)ptr_struct;
	(void)ptr_buff;

	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(0, 32, i, 2560, 1);
	ptr_struct->signature_uuid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}

	for (i = 0; i < 4; i++) {
	offset = adb2c_calc_array_field_address(128, 32, i, 2560, 1);
	ptr_struct->keypair_uuid[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}

	for (i = 0; i < 64; i++) {
	offset = adb2c_calc_array_field_address(256, 32, i, 2560, 1);
	ptr_struct->signature[i] = (u_int32_t)adb2c_pop_integer_from_buff(ptr_buff, offset, 4);
	}

}

void cx4fw_image_signature_print(const struct cx4fw_image_signature *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx4fw_image_signature ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	for (i = 0; i < 4; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature_uuid_%03d  : " U32H_FMT "\n", i, ptr_struct->signature_uuid[i]);
	}

	for (i = 0; i < 4; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "keypair_uuid_%03d    : " U32H_FMT "\n", i, ptr_struct->keypair_uuid[i]);
	}

	for (i = 0; i < 64; i++) {
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "signature_%03d       : " U32H_FMT "\n", i, ptr_struct->signature[i]);
	}

}

int cx4fw_image_signature_size(void)
{
	 return 320;
}

void cx4fw_image_signature_dump(const struct cx4fw_image_signature *ptr_struct, FILE* file)
{
	cx4fw_image_signature_print(ptr_struct, file, 0);
}

void cx4fw_cx4fw_Nodes_pack(const union cx4fw_cx4fw_Nodes *ptr_struct, u_int8_t* ptr_buff)
{
	cx4fw_guids_pack(&(ptr_struct->guids), ptr_buff);
}

void cx4fw_cx4fw_Nodes_unpack(union cx4fw_cx4fw_Nodes *ptr_struct, const u_int8_t* ptr_buff)
{
	cx4fw_guids_unpack(&(ptr_struct->guids), ptr_buff);
}

void cx4fw_cx4fw_Nodes_print(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE* file, int indent_level)
{
	adb2c_add_indentation(file, indent_level);
	fprintf(file, "======== cx4fw_cx4fw_Nodes ========\n");
	int i = 0;
	(void)i;
	(void)ptr_struct;
	(void)file;
	(void)indent_level;

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "image_signature:\n");
	cx4fw_image_signature_print(&(ptr_struct->image_signature), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "device_info:\n");
	cx4fw_device_info_print(&(ptr_struct->device_info), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "mfg_info:\n");
	cx4fw_mfg_info_print(&(ptr_struct->mfg_info), file, indent_level + 1);

	adb2c_add_indentation(file, indent_level);
	fprintf(file, "guids:\n");
	cx4fw_guids_print(&(ptr_struct->guids), file, indent_level + 1);

}

int cx4fw_cx4fw_Nodes_size(void)
{
	 return 512;
}

void cx4fw_cx4fw_Nodes_dump(const union cx4fw_cx4fw_Nodes *ptr_struct, FILE* file)
{
	cx4fw_cx4fw_Nodes_print(ptr_struct, file, 0);
}

