#ifndef MAIN_H
#include "main.h"
#endif

#ifndef REGISTRY_H
#define REGISTRY_H

#include <stdio.h>

#define REG_NONE 0x00000000
#define REG_SZ 0x0000001
#define REG_EXPAND_SZ 0x0000002
#define REG_BINARY 0x0000003
#define REG_DWORD 0x0000004
#define REG_DWORD_BIG_ENDIAN 0x0000005
#define REG_LINK 0x0000006
#define REG_MULTI_SZ 0x0000007
#define REG_RESOURCE_LIST 0x0000008
#define REG_FULL_RESOURCE_DESCRIPTOR 0x0000009
#define REG_RESOURCE_REQUIREMENTS_LIST 0x000000A
#define REG_QWORD 0x000000B

// Windows 7

typedef struct {
	char signature[4];
	int primary_seq_number;
	int secondary_seq_number;
	long last_written_timestamp;
	int major_version;
	int minor_version;
	int file_type;
	int file_format;
	int root_cell_offset;
	int hive_bin_data_size;
	int clustering_factor;
	char filename[64];
	char reserved[396];
	int checksum;
	char reserved2[3576];
	int boot_type;
	int boot_recover;
}File_base_bloc;

typedef struct {
	char signature[5];
	int offset;
	int size;
	long reserved;
	long timestamp;
	short sapre;
}Hive_bin_header;

typedef struct {
}Cell;

typedef struct {
	short signature;	// signature: li
	short number_elements;	// number of elements
				// list of elements
}Indef_leaf;

typedef struct {
	short signature;	// signature : lf
	short number_elements;	// number of elements
				// list of elements
}Fast_leaf;

typedef struct {
	short signature;	// signature : lh
	short number_elements;	// number of elements
				// list of elements
}Hash_leaf;

typedef struct {
	short signature;	// signature : ri
	short number_elements;	// number of elements
				// list of elements
}Index_root;

typedef struct {
	char signature[2];			// signature : nk
	short flags;				// Bit mask
	long last_written_timestamp;		// last written timestamp
	int access_bits;
	int parent;				// offset of parent key node
	int number_subkeys;			// number of subkeys
	int number_volatile_subkeys;
	int subkeys_list_offset;
	int volatile_subkeys_list_offset;
	int number_key_values;
	int key_values_list_offset;
	short largest_subkey_name_length;
	char flags_2;				// Virtualization control flags + User flags
	char debug;				// for debuggin
	int largest_subkey_class_name_length;
	int largest_value_data_size;
	int workvar;				// cached index
	short key_name_length;
	short class_name_length;
						// key name strings
}Key_node;

typedef struct {
	char signature[2];	// signature : vk
	short name_length;
	long data_size;
	long data_offset;
	long data_type;
	short flags;
	short spare;
				// Value name string
}Key_value;

typedef struct {
	short signature;		// signature : sk
	short reserved;
	int flink;
	int blink;
	int reference_count;
	int security_descriptor_size;
					// Security descriptor
}Key_security;

typedef struct {			// Requiered Minor version field > 3
	short signature;		// signature : db
	short number_segments;
	int offset_list_segments;
}Big_data;

File_base_bloc *read_file_base_bloc(char *buf);
int nb_to_read(char *buf);
void fill_int(int *i, char *buf);
void fill_long(long *l, char *buf);

#endif
