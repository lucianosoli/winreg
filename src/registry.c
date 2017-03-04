#include "registry.h"

File_base_bloc *read_file_base_bloc(char *buf)
{
	/*
		Read the file base bloc, alloc
		a new file base bloc srtucture
		and fill it with the value in
		buf string
	*/

	File_base_bloc *fbc;

	fbc = NULL;

	fbc = (File_base_bloc*) malloc(sizeof(File_base_bloc));
	if(fbc == NULL)
	{
		printf("Error d'allocation de fbc\n");
		return NULL;
	}

	bzero(fbc, sizeof(File_base_bloc));

	strncpy(fbc->signature, buf, 4);
	fill_int(&(fbc->primary_seq_number), &buf[4]);
	fill_int(&(fbc->secondary_seq_number), &buf[8]);
	fill_long(&(fbc->last_written_timestamp), &buf[12]);
	fill_int(&(fbc->major_version), &buf[20]);
	fill_int(&(fbc->minor_version), &buf[24]);
	fill_int(&(fbc->file_type), &buf[28]);
	fill_int(&(fbc->file_format), &buf[32]);
	fill_int(&(fbc->root_cell_offset), &buf[36]);
	fill_int(&(fbc->hive_bin_data_size), &buf[40]);
	fill_int(&(fbc->clustering_factor), &buf[44]);
	strncpy(fbc->filename, &buf[48], 64);
	strncpy(fbc->reserved, &buf[112], 396);
	fill_int(&(fbc->checksum), &buf[508]);
	strncpy(fbc->reserved2, &buf[512], 3576);
	fill_int(&(fbc->boot_type), &buf[4088]);
	fill_int(&(fbc->boot_recover), &buf[4092]);

	return fbc;
}

Hive_bin_header *read_hive_bin_header(char *buf)
{
	/*
		Read the hive bin header, alloc
		a new hive bin header srtucture
		and fill it with the value in
		buf string
	*/

	Hive_bin_header *hbh;

	hbh = NULL;

	hbh = (Hive_bin_header*) malloc(sizeof(Hive_bin_header));
	if(hbh == NULL)
	{
		printf("Error d'allocation de hbh\n");
		return NULL;
	}

	bzero(hbh, sizeof(Hive_bin_header));

	strncpy(hbh->signature, buf, 4);
	fill_int(&(hbh->offset), &buf[4]);
	fill_int(&(hbh->size), &buf[8]);
	strncpy(hbh->reserved, &buf[12], 8);
	fill_long(&(hbh->timestamp), &buf[20]);
	fill_int(&(hbh->spare), &buf[28]);

	return hbh;
}

Key_node *read_key_node(char *buf, long offset, int size)
{
	/*
		Read key node, alloc a new
		key node structure and fill it
		with the value in buff string
	*/

	int i, f;
	Key_node *nk;

	nk = NULL;

	nk = (Key_node*) malloc(sizeof(Key_node));
	if(nk == NULL)
	{
		printf("Error d'allocation de nk\n");
		return NULL;
	}

	bzero(nk, sizeof(Key_node));

	nk->key_name = (char*) malloc(sizeof(char)*(size-76+1));

	strncpy(nk->signature, &buf[offset+0], 2);
	fill_short(&(nk->flags), &buf[offset+2]);
	fill_long(&(nk->last_written_timestamp), &buf[offset+4]);
	fill_int(&(nk->access_bits), &buf[offset+12]);
	fill_int(&(nk->parent), &buf[offset+16]);
	fill_int(&(nk->number_subkeys), &buf[offset+20]);
	fill_int(&(nk->number_volatile_subkeys), &buf[offset+24]);
	fill_int(&(nk->subkeys_list_offset), &buf[offset+28]);
	fill_int(&(nk->volatile_subkeys_list_offset), &buf[offset+32]);
	fill_int(&(nk->number_key_values), &buf[offset+36]);
	fill_int(&(nk->key_values_list_offset), &buf[offset+40]);
	fill_int(&(nk->key_security_offset), &buf[offset+44]);
	fill_int(&(nk->class_name_offset), &buf[offset+48]);
	fill_short(&(nk->largest_subkey_name_length), &buf[offset+52]);
	fill_char(&(nk->flags_2), &buf[offset+54]);
	fill_char(&(nk->debug), &buf[offset+55]);
	fill_int(&(nk->largest_subkey_class_name_length), &buf[offset+56]);
	fill_int(&(nk->largest_value_name_length), &buf[offset+60]);
	fill_int(&(nk->largest_value_data_size), &buf[offset+64]);
	fill_int(&(nk->workvar), &buf[offset+68]);
	fill_short(&(nk->key_name_length), &buf[offset+72]);
	fill_short(&(nk->class_name_length), &buf[offset+74]);
	strncpy(nk->key_name, &buf[offset+76], size-76);

/*
	WARNING: need to review this function to take
	care UTF-16-LE strings and not sure the stop
	byte is 03 for ascii strings
*/

	for(i=0, f=0; i<(size-76); i++)
	{
		if((nk->key_name)[i] == 0x03)
		{
			(nk->key_name)[i] = '\0';
			f = 1;
			break;
		}
	}

	if(f != 1)
		printf("Error: no end of string found (nk function)\n");

	return nk;
}

int nb_to_read(char *buf)
{
	/*
		Return the number of Bytes to read
		in function of the signatures
	*/
	if(strncmp(buf, "regf", 4) == 0)
		return 4096;
	else if(strncmp(buf, "hbin", 4) == 0)
		return 32;

	return 0;
}

int read_cell(char *buf, long offset)
{
	/*
		Return the size of a cell
		Requiere stdlib

		Warning possible buffer overflow here
	*/

	int tmp;

	fill_int(&tmp, &buf[offset]);

	return abs(tmp);
}

void fill_char(char *c, char *buf)
{
	/*
		Fill char from buf
	*/

	*c = buf[0] & 0xFF;
}

void fill_short(short *s, char *buf)
{
	/*
		Fill short from buf
	*/

	*s = buf[1] & 0xFF;
	*s = ((*s) << 8) + (buf[0] & 0xFF);
}

void fill_int(int *i, char *buf)
{
	/*
		Fill int from buf
	*/

	*i = buf[3] & 0xFF;
	*i = ((*i) << 8) + (buf[2] & 0xFF);
	*i = ((*i) << 8) + (buf[1] & 0xFF);
	*i = ((*i) << 8) + (buf[0] & 0xFF);
}

void fill_long(long *l, char *buf)
{
	/*
		Fill long from buf
	*/

	*l = buf[7] & 0xFF;
	*l = ((*l) << 8) + (buf[6] & 0xFF);
	*l = ((*l) << 8) + (buf[5] & 0xFF);
	*l = ((*l) << 8) + (buf[4] & 0xFF);
	*l = ((*l) << 8) + (buf[3] & 0xFF);
	*l = ((*l) << 8) + (buf[2] & 0xFF);
	*l = ((*l) << 8) + (buf[1] & 0xFF);
	*l = ((*l) << 8) + (buf[0] & 0xFF);

}
